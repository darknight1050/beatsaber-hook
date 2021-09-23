#pragma once
#include "../../shared/utils/utils.h"
#include "../../extern/capstone/shared/capstone/capstone.h"
#include "../../extern/capstone/shared/platform.h"
#include <array>
#include <tuple>

namespace cs {
csh getHandle();

uint32_t* readb(const uint32_t* addr);

template<arm64_insn... args>
constexpr bool insnMatch(cs_insn* insn) {
    if constexpr (sizeof...(args) > 0) {
        return (((insn->id == args) || ...));
    }
    return false;
};

template<uint32_t nToRetOn, auto match, auto skip, auto conversionFunc, int retCount = -1, size_t szBytes = 4096>
requires ((nToRetOn >= 1 && (szBytes & 4) == 0))
auto findNth(const uint32_t* addr) {
    cs_insn* insn = cs_malloc(getHandle());
    auto ptr = reinterpret_cast<uint64_t>(addr);
    auto instructions = reinterpret_cast<const uint8_t*>(addr);

    int rCount = retCount;
    uint32_t nCalls = nToRetOn;
    size_t sz = szBytes;
    while (sz > 0) {
        bool res = cs_disasm_iter(getHandle(), &instructions, &sz, &ptr, insn);
        if (res) {
            // Valid decode, so lets check to see if it is a match or we need to break.
            if (insn->id == ARM64_INS_RET) {
                if (rCount == 0) {
                    // Early termination!
                    cs_free(insn, 1);
                    CRASH_UNLESS(false, "Could not find: %u call at: %p within: %i rets! Found all of the rets first!", nToRetOn, addr, retCount);
                }
                rCount--;
            } else {
                if (match(insn)) {
                    if (nCalls == 1) {
                        auto val = conversionFunc(insn);
                        cs_free(insn, 1);
                        return val;
                    } else {
                        nCalls--;
                    }
                } else if (skip(insn)) {
                    if (nCalls == 1) {
                        std::string name(insn->mnemonic);
                        cs_free(insn, 1);
                        CRASH_UNLESS(false, "Found: %u match, at: %p within: %i rets, but the result was a %s! Cannot compute destination address!", nToRetOn, addr, retCount, name.c_str());
                    } else {
                        nCalls--;
                    }
                }
            }
            // Other instructions are ignored silently
        }
        else {
            // Invalid instructions are ignored silently.
            // In order to skip these properly, we must increment our instructions, ptr, and size accordingly.
            sz -= 4;
            ptr += 4;
            instructions += 4;
        }
    }
    // If we run out of bytes to parse, we fail
    cs_free(insn, 1);
    CRASH_UNLESS(false, "Could not find: %u call at: %p within: %i rets, within size: %zu!", nToRetOn, addr, retCount, szBytes);
}

uint32_t* blConv(cs_insn* insn) {
    // BL is pc + (imm << 2)
    return reinterpret_cast<uint32_t*>((insn->detail->arm64.operands[0].imm << 2) + insn->address);
}

template<uint32_t nToRetOn, bool includeR = false, int retCount = -1, size_t szBytes = 4096>
requires ((nToRetOn >= 1 && (szBytes & 4) == 0))
auto findNthBl(const uint32_t* addr) {
    if constexpr (includeR) {
        return findNth<nToRetOn, &insnMatch<ARM64_INS_BL>, &insnMatch<ARM64_INS_BLR>, &blConv, retCount, szBytes>(addr);
    } else {
        return findNth<nToRetOn, &insnMatch<ARM64_INS_BL>, &insnMatch<>, &blConv, retCount, szBytes>(addr);
    }
}

uint32_t* bConv(cs_insn* insn) {
    // B is pc + (imm << 2)
    return reinterpret_cast<uint32_t*>((insn->detail->arm64.operands[0].imm << 2) + insn->address);
}

template<uint32_t nToRetOn, bool includeR = false, int retCount = -1, size_t szBytes = 4096>
requires ((nToRetOn >= 1 && (szBytes & 4) == 0))
auto findNthB(const uint32_t* addr) {
    if constexpr (includeR) {
        return findNth<nToRetOn, &insnMatch<ARM64_INS_B>, &insnMatch<ARM64_INS_BR>, &bConv, retCount, szBytes>(addr);
    } else {
        return findNth<nToRetOn, &insnMatch<ARM64_INS_B>, &insnMatch<>, &bConv, retCount, szBytes>(addr);
    }
}

std::tuple<uint32_t*, arm64_reg, uint32_t*> pcRelConv(cs_insn* insn) {
    if (insn->id == ARM64_INS_ADR) {
        // ADR is just pc + imm
        return {reinterpret_cast<uint32_t*>(insn->address), insn->detail->arm64.operands[0].reg, reinterpret_cast<uint32_t*>(insn->detail->arm64.operands[1].imm + insn->address)};
    } else {
        // ADRP is (pc & 1:12(0)) + (imm << 12)
        return {reinterpret_cast<uint32_t*>(insn->address), insn->detail->arm64.operands[0].reg, reinterpret_cast<uint32_t*>(((insn->address >> 12) << 12) + (insn->detail->arm64.operands[1].imm << 12))};
    }
}

template<uint32_t nToRetOn, int retCount = -1, size_t szBytes = 4096>
requires ((nToRetOn >= 1 && (szBytes & 4) == 0))
auto findNthPcRel(const uint32_t* addr) {
    return findNth<nToRetOn, &insnMatch<ARM64_INS_ADR, ARM64_INS_ADRP>, &insnMatch<>, &pcRelConv, retCount, szBytes>(addr);
}

bool check_match(cs_insn* in, arm64_reg reg) {
    for (uint8_t i = 0; i < in->detail->arm64.op_count; i++) {
        // Instruction should have at least an IMM and a REG
        // somehow need to convert imm properly to resulting imm offset off of reg
        // dst reg needs to match passed in reg
        // src reg on loads needs to match passed in reg
        // wtf does capstone do here?
        // TODO:
        return true;
    }
    return false;
}

auto regConv(cs_insn* match) {
    for (uint8_t i = 0; i < match->detail->arm64.op_count; i++) {
        if (match->detail->arm64.operands[i].type == ARM64_OP_IMM) {
            return match->detail->arm64.operands[i].imm;
        }
    }
    return int64_t(0);
}

template<uint32_t nToRetOn, int retCount = -1, size_t szBytes = 4096>
requires ((nToRetOn >= 1 && (szBytes & 4) == 0))
auto findNthReg(const uint32_t* addr, arm64_reg reg) {
    return findNth<nToRetOn, [reg](cs_insn* in) { return check_match(in, reg); }, &insnMatch<>, &regConv, retCount, szBytes>(addr);
}

template<uint32_t nToRetOn, uint32_t nImmOff, size_t szBytes = 4096>
requires ((nToRetOn >= 1 && nImmOff >= 1 && (szBytes & 4) == 0))
auto getpcaddr(const uint32_t* addr) {
    auto pcrel = findNthPcRel<nToRetOn, -1, szBytes>(addr);
    // addr is in first slot of tuple, reg in second, dst imm in third
    auto reginst = findNthReg<nImmOff, -1, szBytes>(std::get<0>(pcrel), std::get<1>(pcrel));
}
}