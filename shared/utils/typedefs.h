#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#pragma pack(push)

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>
#include <initializer_list>

#include <cassert>
// For including il2cpp properly
#ifdef _MSC_VER
#undef _MSC_VER
#endif
#ifndef __GNUC__
#define __GNUC__
#endif

#define NET_4_0 true
#include "il2cpp-config.h"
#include "il2cpp-api-types.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-tabledefs.h"

#ifdef __cplusplus

template<class T>
struct Array;

extern "C" {
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif /* __cplusplus */

#if __has_include("System/Array.hpp") && !defined(NO_CODEGEN_USE)
#define HAS_CODEGEN
#include <stdint.h>
#include <stddef.h>
#include "il2cpp-windowsruntime-types.h"
#else
// TODO: find a way to include this without putting the types in the global namespace?
#include "manual-il2cpp-typedefs.h"
#endif

#include "il2cpp-functions.hpp"
#include "il2cpp-utils-methods.hpp"
#include "il2cpp-type-check.hpp"

#include "typedefs-array.hpp"
#include "typedefs-delegate.hpp"
#include "typedefs-wrappers.hpp"

#include <stdint.h>

namespace il2cpp_utils {
    namespace array_utils {
        static char* il2cpp_array_addr_with_size(Il2CppArray *array, int32_t size, uintptr_t idx)
        {
            return ((char*)array) + kIl2CppSizeOfArray + size * idx;
        }
        #define load_array_elema(arr, idx, size) ((((uint8_t*)(arr)) + kIl2CppSizeOfArray) + ((size) * (idx)))

        #define il2cpp_array_setwithsize(array, elementSize, index, value)  \
            do {    \
                void*__p = (void*) il2cpp_utils::array_utils::il2cpp_array_addr_with_size ((array), elementSize, (index)); \
                memcpy(__p, &(value), elementSize); \
            } while (0)
        #define il2cpp_array_setrefwithsize(array, elementSize, index, value)  \
            do {    \
                void*__p = (void*) il2cpp_utils::array_utils::il2cpp_array_addr_with_size ((array), elementSize, (index)); \
                memcpy(__p, value, elementSize); \
                } while (0)
        #define il2cpp_array_addr(array, type, index) ((type*)(void*) il2cpp_utils::array_utils::il2cpp_array_addr_with_size (array, sizeof (type), index))
        #define il2cpp_array_get(array, type, index) ( *(type*)il2cpp_array_addr ((array), type, (index)) )
        #define il2cpp_array_set(array, type, index, value)    \
            do {    \
                type *__p = (type *) il2cpp_array_addr ((array), type, (index));    \
                *__p = (value); \
            } while (0)
        #define il2cpp_array_setref(array, index, value)  \
            do {    \
                void* *__p = (void* *) il2cpp_array_addr ((array), void*, (index)); \
                /* il2cpp_gc_wbarrier_set_arrayref ((array), __p, (MonoObject*)(value));    */\
                *__p = (value);    \
            } while (0)
    }
}

#ifdef HAS_CODEGEN

#ifdef USE_CODEGEN_FIELDS
#define _HAD_CODEGEN_FIELDS
#else
#define USE_CODEGEN_FIELDS
#endif

#include "System/String.hpp"
struct Il2CppString : public System::String {};
#endif

#ifdef HAS_CODEGEN
#include "System/Collections/Generic/List_1.hpp"
template<class T>
using List = System::Collections::Generic::List_1<T>;
#else
// System.Collections.Generic.List
template<class T>
struct List : Il2CppObject
{
    Array<T>* items;
    int size;
    int version;
    Il2CppObject* syncRoot;
};
DEFINE_IL2CPP_ARG_TYPE_GENERIC_CLASS(List, "System.Collections.Generic", "List`1");
#endif
#include "typedefs-list.hpp"

#ifdef HAS_CODEGEN
// TODO: QiCache and Il2CppComObject ("System.__Il2CppComObject (dummy type that replaces System.__ComObject)")

#if __has_include("System/zzzz__AppDomain_def.hpp")
#include "System/zzzz__AppDomain_def.hpp"
// self-typedef'd in il2cpp-class-internals.h
struct Il2CppAppDomain : public System::AppDomain {};
NEED_NO_BOX(Il2CppAppDomain);
#endif

#if __has_include("System/zzzz__AppDomainSetup_def.hpp")
#include "System/zzzz__AppDomainSetup_def.hpp"
// self-typedef'd in il2cpp-class-internals.h
struct Il2CppAppDomainSetup : public System::AppDomainSetup {};
NEED_NO_BOX(Il2CppAppDomainSetup);
#endif

#if __has_include("System/zzzz__ArgumentException_def.hpp")
#include "System/zzzz__ArgumentException_def.hpp"
typedef System::ArgumentException Il2CppArgumentException;
#endif
// TODO: Il2CppDecimal is System::Decimal?

typedef enum Il2CppDecimalCompareResult
{
    IL2CPP_DECIMAL_CMP_LT = -1,
    IL2CPP_DECIMAL_CMP_EQ,
    IL2CPP_DECIMAL_CMP_GT
} Il2CppDecimalCompareResult;

// TODO: Il2CppDouble, Il2CppDouble_double are System::Double?

#if __has_include("System/zzzz__Exception_def.hpp")
#include "System/zzzz__Exception_def.hpp"
// self-typedef'd in il2cpp-api-types.h
struct Il2CppException : public System::Exception {};
#endif

#if __has_include("System/zzzz__IOAsyncResult_def.hpp")
#include "System/zzzz__IOAsyncResult_def.hpp"
typedef System::IOAsyncResult Il2CppIOAsyncResult;
#endif

#if __has_include("System/zzzz__IOSelectorJob_def.hpp")
#include "System/IOSelectorJob.hpp"
typedef System::IOSelectorJob Il2CppIOSelectorJob;
#endif

#if __has_include("System/zzzz__MarshalByRefObject_def.hpp")
#include "System/zzzz__MarshalByRefObject_def.hpp"
typedef System::MarshalByRefObject Il2CppMarshalByRefObject;
#endif

#if __has_include("System/zzzz__MonoAsyncCall_def.hpp")
#include "System/zzzz__MonoAsyncCall_def.hpp"
typedef System::MonoAsyncCall Il2CppAsyncCall;
#endif

#if __has_include("System/zzzz__MonoType_def.hpp")
#include "System/zzzz__MonoType_def.hpp"
struct Il2CppReflectionMonoType : public System::MonoType {
    const Il2CppType* GetIl2CppType() const;
};
#endif

#if __has_include("System/zzzz__RuntimeType_def.hpp")
#include "System/zzzz__RuntimeType_def.hpp"
struct Il2CppReflectionRuntimeType : public System::RuntimeType {};
#endif

// TODO: Il2CppSingle, Il2CppSingle_float are System::Single?

#if __has_include("System/zzzz__SystemException_def.hpp")
#include "System/zzzz__SystemException_def.hpp"
typedef System::SystemException Il2CppSystemException;
#endif

#if __has_include("System/zzzz__Type_def.hpp")
#include "System/zzzz__Type_def.hpp"
// self-typedef'd in il2cpp-api-types.h
struct Il2CppReflectionType : public System::Type {};
#endif

#if __has_include("System/zzzz__TypedReference_def.hpp")
#include "System/zzzz__TypedReference_def.hpp"
typedef System::TypedReference Il2CppTypedRef;
#endif

#if __has_include("System/Diagnostics/zzzz__StackFrame_def.hpp")
#include "System/Diagnostics/zzzz__StackFrame_def.hpp"
typedef System::Diagnostics::StackFrame Il2CppStackFrame;
#endif

// TODO: Il2CppCalendarData is System::Globalization::CalendarData minus 4 fields at the end?

// TODO: Il2CppCultureData is System::Globalization::CultureData minus 13 fields at the end?

#if __has_include("System/Globalization/zzzz__CultureInfo_def.hpp")
#include "System/Globalization/zzzz__CultureInfo_def.hpp"
typedef System::Globalization::CultureInfo Il2CppCultureInfo;
#endif

#if __has_include("System/Globalization/zzzz__DateTimeFormatInfo_def.hpp")
#include "System/Globalization/zzzz__DateTimeFormatInfo_def.hpp"
typedef System::Globalization::DateTimeFormatInfo Il2CppDateTimeFormatInfo;
#endif

#if __has_include("System/Globalization/zzzz__NumberFormatInfo_def.hpp")
#include "System/Globalization/zzzz__NumberFormatInfo_def.hpp"
typedef System::Globalization::NumberFormatInfo Il2CppNumberFormatInfo;
#endif

#if __has_include("System/Globalization/zzzz__RegionInfo_def.hpp")
#include "System/Globalization/zzzz__RegionInfo_def.hpp"
typedef System::Globalization::RegionInfo Il2CppRegionInfo;
#endif

#if __has_include("System/Globalization/zzzz__SortKey_def.hpp")
#include "System/Globalization/zzzz__SortKey_def.hpp"
typedef System::Globalization::SortKey Il2CppSortKey;
#endif

#if __has_include("System/Net/zzzz__SocketAddress_def.hpp")
#include "System/Net/zzzz__SocketAddress_def.hpp"
typedef System::Net::SocketAddress Il2CppSocketAddress;
#endif

// "Corresponds to Mono's internal System.Net.Sockets.Socket.SocketAsyncResult class. Has no relation to Il2CppAsyncResult."
#if __has_include("System/Net/Sockets/zzzz__SocketAsyncResult_def.hpp")
#include "System/Net/Sockets/zzzz__SocketAsyncResult_def.hpp"
typedef System::Net::Sockets::SocketAsyncResult Il2CppSocketAsyncResult;
#endif

#if __has_include("System/Reflection/zzzz__EventInfo_def.hpp")
#include "System/Reflection/zzzz__EventInfo_def.hpp"
typedef System::Reflection::EventInfo Il2CppReflectionEvent;
#endif

#if __has_include("System/Reflection/zzzz__MonoEvent_def.hpp")
#include "System/Reflection/zzzz__MonoEvent_def.hpp"
typedef System::Reflection::MonoEvent Il2CppReflectionMonoEvent;
#endif

#if __has_include("System/Reflection/zzzz__MonoEventInfo_def.hpp")
#include "System/Reflection/zzzz__MonoEventInfo_def.hpp"
typedef System::Reflection::MonoEventInfo Il2CppReflectionMonoEventInfo;
#endif

#if __has_include("System/Reflection/zzzz__MonoField_def.hpp")
#include "System/Reflection/zzzz__MonoField_def.hpp"
typedef System::Reflection::MonoField Il2CppReflectionField;
#endif

#if __has_include("System/Reflection/zzzz__MonoProperty_def.hpp")
#include "System/Reflection/zzzz__MonoProperty_def.hpp"
typedef System::Reflection::MonoProperty Il2CppReflectionProperty;
#endif

#if __has_include("System/Reflection/zzzz__MonoMethod_def.hpp")
#include "System/Reflection/zzzz__MonoMethod_def.hpp"
// self-typedef'd in il2cpp-api-types.h
struct Il2CppReflectionMethod : public System::Reflection::MonoMethod {};
#endif

#if __has_include("System/Reflection/zzzz__MonoGenericMethod_def.hpp")
#include "System/Reflection/zzzz__MonoGenericMethod_def.hpp"
typedef System::Reflection::MonoGenericMethod Il2CppReflectionGenericMethod;
#endif

#if __has_include("System/Reflection/zzzz__MonoMethodInfo_def.hpp")
#include "System/Reflection/zzzz__MonoMethodInfo_def.hpp"
typedef System::Reflection::MonoMethodInfo Il2CppMethodInfo;
#endif

#if __has_include("System/Reflection/zzzz__MonoPropertyInfo_def.hpp")
#include "System/Reflection/zzzz__MonoPropertyInfo_def.hpp"
typedef System::Reflection::MonoPropertyInfo Il2CppPropertyInfo;
#endif

#if __has_include("System/Reflection/zzzz__ParameterInfo_def.hpp")
#include "System/Reflection/zzzz__ParameterInfo_def.hpp"
typedef System::Reflection::ParameterInfo Il2CppReflectionParameter;
#endif

#if __has_include("System/Reflection/zzzz__Module_def.hpp")
#include "System/Reflection/zzzz__Module_def.hpp"
typedef System::Reflection::Module Il2CppReflectionModule;
#endif

#if __has_include("System/Reflection/zzzz__AssemblyName_def.hpp")
#include "System/Reflection/zzzz__AssemblyName_def.hpp"
typedef System::Reflection::AssemblyName Il2CppReflectionAssemblyName;
#endif

#if __has_include("System/Reflection/zzzz__Assembly_def.hpp")
#include "System/Reflection/zzzz__Assembly_def.hpp"
typedef System::Reflection::Assembly Il2CppReflectionAssembly;
#endif

#if __has_include("System/Reflection/Emit/zzzz__UnmanagedMarshal_def.hpp")
#include "System/Reflection/Emit/zzzz__UnmanagedMarshal_def.hpp"
typedef System::Reflection::Emit::UnmanagedMarshal Il2CppReflectionMarshal;
#endif

/* Stripped in 1.13.5 Update
#include "System/Reflection/zzzz__ManifestResourceInfo_def.hpp"
typedef System::Reflection::zzzz__ManifestResourceInfo_def Il2CppManifestResourceInfo;
*/

#if __has_include("System/Reflection/zzzz__Pointer_def.hpp")
#include "System/Reflection/zzzz__Pointer_def.hpp"
typedef System::Reflection::Pointer Il2CppReflectionPointer;
#endif

// TODO: Il2CppResourceLocation seems to be the System.Reflection.ResourceLocation enum

#if __has_include("System/Runtime/InteropServices/zzzz__ErrorWrapper_def.hpp")
#include "System/Runtime/InteropServices/zzzz__ErrorWrapper_def.hpp"
typedef System::Runtime::InteropServices::ErrorWrapper Il2CppErrorWrapper;
#endif

// "Inherited by Microsoft.Win32.SafeHandles.SafeWaitHandle"
#if __has_include("System/Runtime/InteropServices/zzzz__SafeHandle_def.hpp")
#include "System/Runtime/InteropServices/zzzz__SafeHandle_def.hpp"
typedef System::Runtime::InteropServices::SafeHandle Il2CppSafeHandle;
#endif

#if __has_include("System/Runtime/Remoting/Contexts/zzzz__Context_def.hpp")
#include "System/Runtime/Remoting/Contexts/zzzz__Context_def.hpp"
// self-typedef'd in il2cpp-class-internals.h
struct Il2CppAppContext : public System::Runtime::Remoting::Contexts::Context {};
NEED_NO_BOX(Il2CppAppContext);
#endif

#if __has_include("System/Runtime/Remoting/Messaging/zzzz__AsyncResult_def.hpp")
#include "System/Runtime/Remoting/Messaging/zzzz__AsyncResult_def.hpp"
// self-typedef'd in il2cpp-api-types.h
struct Il2CppAsyncResult : public System::Runtime::Remoting::Messaging::AsyncResult {};
NEED_NO_BOX(Il2CppAsyncResult);
#endif

// TODO: Il2CppCallType which "is a copy of System.Runtime.Remoting.Messaging.CallType" enum

// TODO: Il2CppMethodMessage is System::Runtime::Remoting::Messaging::MonoMethodMessage minus 4 fields at the end?

#if __has_include("System/Text/zzzz__StringBuilder_def.hpp")
#include "System/Text/zzzz__StringBuilder_def.hpp"
typedef System::Text::StringBuilder Il2CppStringBuilder;
#endif

#if __has_include("System/Threading/zzzz__InternalThread_def.hpp")
#include "System/Threading/zzzz__InternalThread_def.hpp"
typedef System::Threading::InternalThread Il2CppInternalThread;
#endif

#if __has_include("System/Threading/zzzz__Thread_def.hpp")
#include "System/Threading/zzzz__Thread_def.hpp"
// self-typedef'd in il2cpp-api-types.h
struct Il2CppThread : public System::Threading::Thread {};
#endif

#ifndef _HAD_CODEGEN_FIELDS
#undef USE_CODEGEN_FIELDS
#endif

#undef _HAD_CODEGEN_FIELDS

// include impls
#if __has_include("System/zzzz__AppDomain_impl.hpp")
#include "System/zzzz__AppDomain_impl.hpp"
#endif
#if __has_include("System/zzzz__AppDomainSetup_impl.hpp")
#include "System/zzzz__AppDomainSetup_impl.hpp"
#endif
#if __has_include("System/zzzz__ArgumentException_impl.hpp")
#include "System/zzzz__ArgumentException_impl.hpp"
#endif
#if __has_include("System/zzzz__Exception_impl.hpp")
#include "System/zzzz__Exception_impl.hpp"
#endif
#if __has_include("System/zzzz__IOAsyncResult_impl.hpp")
#include "System/zzzz__IOAsyncResult_impl.hpp"
#endif
#if __has_include("System/IOSelectorJob.hpp")
#include "System/IOSelectorJob.hpp"
#endif
#if __has_include("System/zzzz__MarshalByRefObject_impl.hpp")
#include "System/zzzz__MarshalByRefObject_impl.hpp"
#endif
#if __has_include("System/zzzz__MonoAsyncCall_impl.hpp")
#include "System/zzzz__MonoAsyncCall_impl.hpp"
#endif
#if __has_include("System/zzzz__MonoType_impl.hpp")
#include "System/zzzz__MonoType_impl.hpp"
// include required for this implementation
#include "System/zzzz__RuntimeTypeHandle_impl.hpp"
inline const Il2CppType* Il2CppReflectionMonoType::GetIl2CppType() const {
    return reinterpret_cast<Il2CppType*>(_impl.value);
}
#endif
#if __has_include("System/zzzz__RuntimeType_impl.hpp")
#include "System/zzzz__RuntimeType_impl.hpp"
#endif
#if __has_include("System/zzzz__SystemException_impl.hpp")
#include "System/zzzz__SystemException_impl.hpp"
#endif
#if __has_include("System/zzzz__Type_impl.hpp")
#include "System/zzzz__Type_impl.hpp"
#endif
#if __has_include("System/zzzz__TypedReference_impl.hpp")
#include "System/zzzz__TypedReference_impl.hpp"
#endif
#if __has_include("System/Diagnostics/zzzz__StackFrame_impl.hpp")
#include "System/Diagnostics/zzzz__StackFrame_impl.hpp"
#endif
#if __has_include("System/Globalization/zzzz__CultureInfo_impl.hpp")
#include "System/Globalization/zzzz__CultureInfo_impl.hpp"
#endif
#if __has_include("System/Globalization/zzzz__DateTimeFormatInfo_impl.hpp")
#include "System/Globalization/zzzz__DateTimeFormatInfo_impl.hpp"
#endif
#if __has_include("System/Globalization/zzzz__NumberFormatInfo_impl.hpp")
#include "System/Globalization/zzzz__NumberFormatInfo_impl.hpp"
#endif
#if __has_include("System/Globalization/zzzz__RegionInfo_impl.hpp")
#include "System/Globalization/zzzz__RegionInfo_impl.hpp"
#endif
#if __has_include("System/Globalization/zzzz__SortKey_impl.hpp")
#include "System/Globalization/zzzz__SortKey_impl.hpp"
#endif
#if __has_include("System/Net/zzzz__SocketAddress_impl.hpp")
#include "System/Net/zzzz__SocketAddress_impl.hpp"
#endif
#if __has_include("System/Net/Sockets/zzzz__SocketAsyncResult_impl.hpp")
#include "System/Net/Sockets/zzzz__SocketAsyncResult_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__EventInfo_impl.hpp")
#include "System/Reflection/zzzz__EventInfo_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoEvent_impl.hpp")
#include "System/Reflection/zzzz__MonoEvent_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoEventInfo_impl.hpp")
#include "System/Reflection/zzzz__MonoEventInfo_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoField_impl.hpp")
#include "System/Reflection/zzzz__MonoField_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoProperty_impl.hpp")
#include "System/Reflection/zzzz__MonoProperty_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoMethod_impl.hpp")
#include "System/Reflection/zzzz__MonoMethod_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoGenericMethod_impl.hpp")
#include "System/Reflection/zzzz__MonoGenericMethod_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoMethodInfo_impl.hpp")
#include "System/Reflection/zzzz__MonoMethodInfo_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__MonoPropertyInfo_impl.hpp")
#include "System/Reflection/zzzz__MonoPropertyInfo_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__ParameterInfo_impl.hpp")
#include "System/Reflection/zzzz__ParameterInfo_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__Module_impl.hpp")
#include "System/Reflection/zzzz__Module_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__AssemblyName_impl.hpp")
#include "System/Reflection/zzzz__AssemblyName_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__Assembly_impl.hpp")
#include "System/Reflection/zzzz__Assembly_impl.hpp"
#endif
#if __has_include("System/Reflection/Emit/zzzz__UnmanagedMarshal_impl.hpp")
#include "System/Reflection/Emit/zzzz__UnmanagedMarshal_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__ManifestResourceInfo_impl.hpp")
#include "System/Reflection/zzzz__ManifestResourceInfo_impl.hpp"
#endif
#if __has_include("System/Reflection/zzzz__Pointer_impl.hpp")
#include "System/Reflection/zzzz__Pointer_impl.hpp"
#endif
#if __has_include("System/Runtime/InteropServices/zzzz__ErrorWrapper_impl.hpp")
#include "System/Runtime/InteropServices/zzzz__ErrorWrapper_impl.hpp"
#endif
#if __has_include("System/Runtime/InteropServices/zzzz__SafeHandle_impl.hpp")
#include "System/Runtime/InteropServices/zzzz__SafeHandle_impl.hpp"
#endif
#if __has_include("System/Runtime/Remoting/Contexts/zzzz__Context_impl.hpp")
#include "System/Runtime/Remoting/Contexts/zzzz__Context_impl.hpp"
#endif
#if __has_include("System/Runtime/Remoting/Messaging/zzzz__AsyncResult_impl.hpp")
#include "System/Runtime/Remoting/Messaging/zzzz__AsyncResult_impl.hpp"
#endif
#if __has_include("System/Text/zzzz__StringBuilder_impl.hpp")
#include "System/Text/zzzz__StringBuilder_impl.hpp"
#endif
#if __has_include("System/Threading/zzzz__InternalThread_impl.hpp")
#include "System/Threading/zzzz__InternalThread_impl.hpp"
#endif
#if __has_include("System/Threading/zzzz__Thread_impl.hpp")
#include "System/Threading/zzzz__Thread_impl.hpp"
#endif

#else
// From Runtime.cpp (some may need the * removed):
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppMulticastDelegate*, multicastdelegate);
NEED_NO_BOX(Il2CppMulticastDelegate);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppAsyncCall*, async_call);
NEED_NO_BOX(Il2CppAsyncCall);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppInternalThread*, internal_thread);
NEED_NO_BOX(Il2CppInternalThread);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionEvent*, event_info);
NEED_NO_BOX(Il2CppReflectionEvent);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppStringBuilder*, stringbuilder);
NEED_NO_BOX(Il2CppStringBuilder);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppStackFrame*, stack_frame);
NEED_NO_BOX(Il2CppStackFrame);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionAssemblyName*, assembly_name);
NEED_NO_BOX(Il2CppReflectionAssemblyName);
// DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionAssembly*, assembly);
#ifndef UNITY_2021
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionAssembly*, mono_assembly);
NEED_NO_BOX(Il2CppReflectionAssembly);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionField*, mono_field);
NEED_NO_BOX(Il2CppReflectionField);
// DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionParameter*, parameter_info);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionParameter*, mono_parameter_info);
NEED_NO_BOX(Il2CppReflectionParameter);
#endif
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionModule*, module);
NEED_NO_BOX(Il2CppReflectionModule);
#ifndef UNITY_2021
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionPointer*, pointer);
NEED_NO_BOX(Il2CppReflectionPointer);
#endif
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppSystemException*, system_exception);
NEED_NO_BOX(Il2CppSystemException);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppArgumentException*, argument_exception);
NEED_NO_BOX(Il2CppArgumentException);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppMarshalByRefObject*, marshalbyrefobject);
NEED_NO_BOX(Il2CppMarshalByRefObject);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppSafeHandle*, safe_handle);
NEED_NO_BOX(Il2CppSafeHandle);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppSortKey*, sort_key);
NEED_NO_BOX(Il2CppSortKey);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppErrorWrapper*, error_wrapper);
NEED_NO_BOX(Il2CppErrorWrapper);
// TODO: attempt to move out of this conditional if codegen ever gets an Il2CppComObject?
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppComObject*, il2cpp_com_object);
NEED_NO_BOX(Il2CppComObject);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppTypedRef, typed_reference);
#endif
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppDelegate*, delegate);
NEED_NO_BOX(Il2CppDelegate);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionMonoType*, monotype);
NEED_NO_BOX(Il2CppReflectionMonoType);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppThread*, thread);
NEED_NO_BOX(Il2CppThread);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionRuntimeType*, runtimetype);
NEED_NO_BOX(Il2CppReflectionRuntimeType);
#ifndef UNITY_2021
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionMonoEventInfo*, mono_event_info);
NEED_NO_BOX(Il2CppReflectionMonoEventInfo);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppReflectionMethod*, mono_method);
NEED_NO_BOX(Il2CppReflectionMethod);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppMethodInfo*, mono_method_info);
NEED_NO_BOX(Il2CppMethodInfo);
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppPropertyInfo*, mono_property_info);
NEED_NO_BOX(Il2CppPropertyInfo);
#endif
DEFINE_IL2CPP_DEFAULT_TYPE(Il2CppException*, exception);
NEED_NO_BOX(Il2CppException);

DEFINE_IL2CPP_ARG_TYPE(long double, "System", "Decimal");

template<class T, class Ptr>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ListW<T, Ptr>> {
    static inline Il2CppClass* get() {
        static auto klass = ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<List<T>*>::get();
        return klass;
    }
};

#include "utils/Il2CppHashMap.h"
#include "utils/HashUtils.h"
#include "utils/StringUtils.h"

struct NamespaceAndNamePairHash
{
    size_t operator()(const std::pair<const char*, const char*>& pair) const
    {
        return il2cpp::utils::HashUtils::Combine(il2cpp::utils::StringUtils::Hash(pair.first), il2cpp::utils::StringUtils::Hash(pair.second));
    }
};

struct NamespaceAndNamePairEquals
{
    bool operator()(const std::pair<const char*, const char*>& p1, const std::pair<const char*, const char*>& p2) const
    {
        return !strcmp(p1.first, p2.first) && !strcmp(p1.second, p2.second);
    }
};

struct Il2CppNameToTypeHandleHashTable : public Il2CppHashMap<std::pair<const char*, const char*>, Il2CppMetadataTypeHandle, NamespaceAndNamePairHash, NamespaceAndNamePairEquals>
{
    typedef Il2CppHashMap<std::pair<const char*, const char*>, Il2CppMetadataTypeHandle, NamespaceAndNamePairHash, NamespaceAndNamePairEquals> Base;
    Il2CppNameToTypeHandleHashTable() : Base()
    {
    }
};

typedef struct Il2CppImageGlobalMetadata
{
    TypeDefinitionIndex typeStart;
    TypeDefinitionIndex exportedTypeStart;
    CustomAttributeIndex customAttributeStart;
    MethodIndex entryPointIndex;
    const Il2CppImage* image;
} Il2CppImageGlobalMetadata;

#pragma pack(pop)

#endif /* TYPEDEFS_H */
