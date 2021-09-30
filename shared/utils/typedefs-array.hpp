#pragma once
#include <optional>
#include <vector>
#include <span>
#include "il2cpp-type-check.hpp"

#if __has_include(<concepts>)
#include <concepts>
#elif __has_include(<experimental/concepts>)
#include <experimental/concepts>
#else
#warning "Please have some form of concepts support!"
#endif

template<class T, class U>
/// @brief If type T can be assigned to by type U&&
/// @tparam T The left hand side of the assignment
/// @tparam U The right hand side of the assignment
concept has_assignment = requires (T arg, U&& other) {
    arg = other;
};

template<class T>
requires (!std::is_reference_v<T>)
/// @brief A std::wrapper_reference implementation that perfect forwards to contained assignment operators.
struct WrapperRef {
    /// @brief Explicitly create a wrapper reference from a reference who MUST LIVE LONGER THAN THIS INSTANCE!
    explicit constexpr WrapperRef(T& instance) : ptr(std::addressof(instance)) {}
    // Assignment for any U type that is valid to be assigned.
    template<class U>
    requires (has_assignment<T, U>)
    WrapperRef& operator=(U&& other) {
        *ptr = other;
        return *this;
    }
    // Standard Assignment
    WrapperRef& operator=(const WrapperRef& x) noexcept = default;
    // Getter operation, implicit conversion
    constexpr operator T& () const noexcept {
        return *ptr;
    }
    // Getter operation, explicit conversion
    constexpr T& get() const noexcept {
        return *ptr;
    }
    // Invoke operation
    template<class... ArgTypes>
    constexpr std::invoke_result_t<T&, ArgTypes...> operator() (ArgTypes&&... args) const {
        return std::invoke(get(), std::forward<ArgTypes>(args)...);
    }
    private:
    T* ptr;
};

#pragma pack(push)

#ifdef HAS_CODEGEN
typedef int32_t il2cpp_array_lower_bound_t;
#define IL2CPP_ARRAY_MAX_INDEX ((int32_t) 0x7fffffff)
#define IL2CPP_ARRAY_MAX_SIZE  ((uint32_t) 0xffffffff)

typedef struct Il2CppArrayBounds
{
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
} Il2CppArrayBounds;

#if IL2CPP_COMPILER_MSVC
#pragma warning( push )
#pragma warning( disable : 4200 )
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#endif

#include "System/Array.hpp"
struct Il2CppArray : public System::Array {
    /* bounds is NULL for szarrays */
    Il2CppArrayBounds *bounds;
    /* total number of elements of the array */
    il2cpp_array_size_t max_length;
};

struct Il2CppArraySize : public Il2CppArray {
    ALIGN_TYPE(8) void* vector[IL2CPP_ZERO_LEN_ARRAY];
};

static const size_t kIl2CppSizeOfArray = offsetof(Il2CppArraySize, vector);
static const size_t kIl2CppOffsetOfArrayBounds = offsetof(Il2CppArray, bounds);
static const size_t kIl2CppOffsetOfArrayLength = offsetof(Il2CppArray, max_length);
#else
#include "typedefs-object.hpp"
typedef int32_t il2cpp_array_lower_bound_t;
#define IL2CPP_ARRAY_MAX_INDEX ((int32_t) 0x7fffffff)
#define IL2CPP_ARRAY_MAX_SIZE  ((uint32_t) 0xffffffff)

typedef struct Il2CppArrayBounds
{
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
} Il2CppArrayBounds;

#if IL2CPP_COMPILER_MSVC
#pragma warning( push )
#pragma warning( disable : 4200 )
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#endif

//Warning: Updates to this struct must also be made to IL2CPPArraySize C code
#ifdef __cplusplus
typedef struct Il2CppArray : public Il2CppObject
{
#else
typedef struct Il2CppArray
{
    Il2CppObject obj;
#endif //__cplusplus
    /* bounds is NULL for szarrays */
    Il2CppArrayBounds *bounds;
    /* total number of elements of the array */
    il2cpp_array_size_t max_length;
} Il2CppArray;

#ifdef __cplusplus
typedef struct Il2CppArraySize : public Il2CppArray
{
#else
//mono code has no inheritance, so its members must be available from this type
typedef struct Il2CppArraySize
{
    Il2CppObject obj;
    Il2CppArrayBounds *bounds;
    il2cpp_array_size_t max_length;
#endif //__cplusplus
    ALIGN_TYPE(8) void* vector[IL2CPP_ZERO_LEN_ARRAY];
} Il2CppArraySize;

static const size_t kIl2CppSizeOfArray = (offsetof(Il2CppArraySize, vector));
static const size_t kIl2CppOffsetOfArrayBounds = (offsetof(Il2CppArray, bounds));
static const size_t kIl2CppOffsetOfArrayLength = (offsetof(Il2CppArray, max_length));
#endif

#include "utils.h"
#include "il2cpp-utils-methods.hpp"
#include <initializer_list>

template<class T>
struct Array : public Il2CppArray
{
    static_assert(is_value_type_v<T>, "T must be a C# value type! (primitive, pointer or Struct)");
    ALIGN_TYPE(8) T values[IL2CPP_ZERO_LEN_ARRAY];

    inline il2cpp_array_size_t Length() const {
        if (bounds) {
            return bounds->length;
        }
        return max_length;
    }
    T& operator[](size_t i) {
        return values[i];
    }
    const T& operator[](size_t i) const {
        return values[i];
    }

    /// @brief Get a given index, performs bound checking and throws std::runtime_error on failure.
    /// @param i The index to get.
    /// @return The reference to the item.
    T& get(size_t i) {
        THROW_UNLESS(i < Length() && i >= 0);
        return values[i];
    }
    /// @brief Get a given index, performs bound checking and throws std::runtime_error on failure.
    /// @param i The index to get.
    /// @return The const reference to the item.
    const T& get(size_t i) const {
        THROW_UNLESS(i < Length() && i >= 0);
        return values[i];
    }
    /// @brief Tries to get a given index, performs bound checking and returns a std::nullopt on failure.
    /// @param i The index to get.
    /// @return The WrapperRef<T> to the item, mostly considered to be a T&.
    std::optional<WrapperRef<T>> try_get(size_t i) {
        if (i >= Length() || i < 0) {
            return std::nullopt;
        }
        return WrapperRef(values[i]);
    }
    /// @brief Tries to get a given index, performs bound checking and returns a std::nullopt on failure.
    /// @param i The index to get.
    /// @return The WrapperRef<const T> to the item, mostly considered to be a const T&.
    std::optional<WrapperRef<const T>> try_get(size_t i) const {
        if (i >= Length() || i < 0) {
            return std::nullopt;
        }
        return WrapperRef(values[i]);
    }

    static Array<T>* New(std::initializer_list<T> vals) {
        il2cpp_functions::Init();
        auto* arr = reinterpret_cast<Array<T>*>(il2cpp_functions::array_new(
            il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<T>::get(), vals.size()));
        memcpy(arr->values, vals.begin(), sizeof(T)*vals.size());
        return arr;
    }

    static Array<T>* NewLength(il2cpp_array_size_t size) {
        il2cpp_functions::Init();
        return reinterpret_cast<Array<T>*>(il2cpp_functions::array_new(
            il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<T>::get(), size));
    }

    template<typename... TArgs>
    static Array<T>* New(TArgs&&... args) {
        return New({args...});
    }

    template<class U = Il2CppObject*>
    U GetEnumerator() {
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
            this, "System.Collections.Generic.IEnumerable`1.GetEnumerator", 0));
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<U>(this, method));
    }

    bool Contains(T item) {
        // TODO: find a better way around the existence of 2 methods with this name (the 2nd not being generic at all)
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
            this, "System.Collections.Generic.ICollection`1.Contains", 1));
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<bool>(this, method, item));
    }
    void CopyTo(::Array<T>* array, int arrayIndex) {
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
            this, "System.Collections.Generic.ICollection`1.CopyTo", 2));
        CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(this, method, array, arrayIndex));
    }
    int IndexOf(T item) {
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(this, "System.Collections.Generic.IList`1.IndexOf", 1));
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<int>(this, method, item));
    }
    /// @brief Copies the array to the provided vector reference of same type.
    /// @param vec The vector to copy to.
    void copy_to(std::vector<T>& vec) const {
        vec.assign(values, values + Length());
    }
    /// @brief Provides a reference span of the held data within this array. The span should NOT outlive this instance.
    /// @return The created span.
    std::span<T> ref_to() {
        return std::span(values, Length());
    }
    /// @brief Provides a reference span of the held data within this array. The span should NOT outlive this instance.
    /// @return The created span.
    const std::span<T> ref_to() const {
        return std::span(const_cast<T*>(values), Length());
    }
};

template<typename TArg>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Array<TArg>*> {
    static inline Il2CppClass* get() {
        il2cpp_functions::Init();
        if constexpr (std::is_same_v<std::decay_t<TArg>, Il2CppObject*>) {
            il2cpp_functions::CheckS_GlobalMetadata();
            return il2cpp_functions::array_class_get(il2cpp_functions::defaults->object_class, 1);
        } else {
            static auto& logger = getLogger();
            Il2CppClass* eClass = RET_0_UNLESS(logger, il2cpp_no_arg_class<TArg>::get());
            return il2cpp_functions::array_class_get(eClass, 1);
        }
    }
};

template<typename T, class Ptr = Array<T>*>
struct ArrayW {
    static_assert(sizeof(Ptr) == sizeof(void*), "Size of Ptr type must be the same as a void*!");

    /// @brief Create an ArrayW from a pointer
    constexpr ArrayW(Ptr initVal) : val(initVal) {}
    /// @brief Default constructor creates an empty array that is wrapped
    ArrayW() : val(Array<T>::NewLength(0)) {}
    template<class U>
    requires (!std::is_same_v<std::nullptr_t, U>)
    ArrayW(std::initializer_list<U> vals) : val(Array<T>::New(vals)) {}
    ArrayW(il2cpp_array_size_t size) : val(Array<T>::NewLength(size)) {}

    inline il2cpp_array_size_t Length() const {
        return val->Length();
    }
    T& operator[](size_t i) {
        return val->values[i];
    }
    const T& operator[](size_t i) const {
        return val->values[i];
    }

    /// @brief Get a given index, performs bound checking and throws std::runtime_error on failure.
    /// @param i The index to get.
    /// @return The reference to the item.
    T& get(size_t i) {
        THROW_UNLESS(i < Length() && i >= 0);
        return val->values[i];
    }
    /// @brief Get a given index, performs bound checking and throws std::runtime_error on failure.
    /// @param i The index to get.
    /// @return The const reference to the item.
    const T& get(size_t i) const {
        THROW_UNLESS(i < Length() && i >= 0);
        return val->values[i];
    }
    /// @brief Tries to get a given index, performs bound checking and returns a std::nullopt on failure.
    /// @param i The index to get.
    /// @return The WrapperRef<T> to the item, mostly considered to be a T&.
    std::optional<WrapperRef<T>> try_get(size_t i) {
        if (i >= Length() || i < 0) {
            return std::nullopt;
        }
        return WrapperRef(val->values[i]);
    }
    /// @brief Tries to get a given index, performs bound checking and returns a std::nullopt on failure.
    /// @param i The index to get.
    /// @return The WrapperRef<const T> to the item, mostly considered to be a const T&.
    std::optional<WrapperRef<const T>> try_get(size_t i) const {
        if (i >= Length() || i < 0) {
            return std::nullopt;
        }
        return WrapperRef(val->values[i]);
    }

    template<class U = Il2CppObject*>
    U GetEnumerator() {
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
            this, "System.Collections.Generic.IEnumerable`1.GetEnumerator", 0));
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<U>(val, method));
    }
    bool Contains(T item) {
        // TODO: find a better way around the existence of 2 methods with this name (the 2nd not being generic at all)
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
            val, "System.Collections.Generic.ICollection`1.Contains", 1));
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<bool>(val, method, item));
    }
    void CopyTo(::Array<T>* array, int arrayIndex) {
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
            val, "System.Collections.Generic.ICollection`1.CopyTo", 2));
        CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe(val, method, array, arrayIndex));
    }
    int IndexOf(T item) {
        static auto* method = CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(val, "System.Collections.Generic.IList`1.IndexOf", 1));
        return CRASH_UNLESS(il2cpp_utils::RunMethodUnsafe<int>(val, method, item));
    }
    /// @brief Copies the array to the provided vector reference of same type.
    /// @param vec The vector to copy to.
    void copy_to(std::vector<T>& vec) const {
        vec.assign(val->values, val->values + Length());
    }
    /// @brief Provides a reference span of the held data within this array. The span should NOT outlive this instance.
    /// @return The created span.
    std::span<T> ref_to() {
        return std::span(val->values, Length());
    }
    /// @brief Provides a reference span of the held data within this array. The span should NOT outlive this instance.
    /// @return The created span.
    const std::span<T> ref_to() const {
        return std::span(const_cast<T*>(val->values), Length());
    }

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = T const&;
    using iterator = pointer;
    using const_iterator = const_pointer;

    iterator begin() {
        return val->values;
    }
    iterator end() {
        return &val->values[Length()];
    }
    const_iterator begin() const {
        return val->values;
    }
    const_iterator end() const {
        return &val->values[Length()];
    }
    explicit operator const Ptr() const {
        return val;
    }
    explicit operator Ptr() {
        return val;
    }
    explicit operator Il2CppArray*() {
        return reinterpret_cast<Il2CppArray*>(val);
    }
    explicit operator Il2CppArray* const() const {
        return reinterpret_cast<Il2CppArray* const>(val);
    }

    private:
    Ptr val;
};

template<class T, class Ptr>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ArrayW<T, Ptr>> {
    static inline Il2CppClass* get() {
        static auto klass = ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Array<T>*>::get();
        return klass;
    }
};

#pragma pack(pop)
