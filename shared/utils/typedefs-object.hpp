#pragma once

#ifdef HAS_CODEGEN
#include "System/Object.hpp"
typedef Il2CppClass Il2CppVTable;
struct MonitorData;
struct Il2CppObject : public System::Object {
    union {
        Il2CppClass *klass;
        Il2CppVTable *vtable;
    };
    MonitorData *monitor;
};
#else
typedef Il2CppClass Il2CppVTable;
struct MonitorData;
typedef struct Il2CppObject
{
    union
    {
        Il2CppClass *klass;
        Il2CppVTable *vtable;
    };
    MonitorData *monitor;
} Il2CppObject;
#endif