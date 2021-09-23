#include "../../shared/utils/capstone-utils.hpp"
#include <android/log.h>

csh handle;
bool valid = false;

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#ifndef ID
#define ID "beatsaber-hook"
#endif

void __attribute__((constructor)) init_capstone() {
    cs_err e1 = cs_open(CS_ARCH_ARM64, CS_MODE_ARM, &handle);
    cs_option(handle, CS_OPT_DETAIL, 1);
    if (e1) {
        __android_log_print(Logging::CRITICAL, "QuestHook[" ID "|" VERSION "] capstone", "capstone initialization failed! %u", e1);
        SAFE_ABORT();
    }
    valid = true;
}

csh getHandle() {
    return handle;
}

uint32_t* readb(const uint32_t* addr) {
    cs_insn* insns;
    // Read from addr, 1 instruction, with pc at addr, into insns.
    // TODO: consider using cs_disasm_iter
    auto count = cs_disasm(handle, reinterpret_cast<const uint8_t*>(addr), sizeof(uint32_t), reinterpret_cast<uint64_t>(addr), 1, &insns);
    CRASH_UNLESS(count == 1);
    auto inst = insns[0];
    // Thunks have a single b
    CRASH_UNLESS(inst.id == ARM64_INS_B);
    auto platinsn = inst.detail->arm64;
    CRASH_UNLESS(platinsn.op_count != 1);
    auto op = platinsn.operands[0];
    CRASH_UNLESS(op.type != ARM64_OP_IMM);
    // Our b dest is addr + (imm << 2)
    auto dst = reinterpret_cast<uint32_t*>(inst.address + (op.imm << 2));
    cs_free(insns, 1);
    return dst;
}
