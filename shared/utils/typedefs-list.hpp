#pragma once
// This file should only ever be included in typedefs.h

template<class T, class Ptr = List<T>*>
struct ListWrapper {
    static_assert(sizeof(Ptr) == sizeof(void*), "Size of Ptr type must be the same as a void*!");
    
    constexpr ListWrapper(Ptr p) : ptr(p) {}

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;

    using iterator = pointer;
    using const_iterator = const_pointer;

    constexpr int size() const {
        return ptr->size;
    }
    T& operator[](size_t i) {
        return ptr->items->values[i];
    }
    const T& operator[](size_t i) const {
        return ptr->items->values[i];
    }

    /// @brief Get a given index, performs bound checking and throws std::runtime_error on failure.
    /// @param i The index to get.
    /// @return The reference to the item.
    T& get(size_t i) {
        THROW_UNLESS(i < size() && i >= 0);
        return ptr->items->values[i];
    }
    /// @brief Get a given index, performs bound checking and throws std::runtime_error on failure.
    /// @param i The index to get.
    /// @return The const reference to the item.
    const T& get(size_t i) const {
        THROW_UNLESS(i < size() && i >= 0);
        return ptr->items->values[i];
    }
    /// @brief Tries to get a given index, performs bound checking and returns a std::nullopt on failure.
    /// @param i The index to get.
    /// @return The WrapperRef<T> to the item, mostly considered to be a T&.
    std::optional<WrapperRef<T>> try_get(size_t i) {
        if (i >= size() || i < 0) {
            return std::nullopt;
        }
        return WrapperRef(ptr->items->values[i]);
    }
    /// @brief Tries to get a given index, performs bound checking and returns a std::nullopt on failure.
    /// @param i The index to get.
    /// @return The WrapperRef<const T> to the item, mostly considered to be a const T&.
    std::optional<WrapperRef<const T>> try_get(size_t i) const {
        if (i >= size() || i < 0) {
            return std::nullopt;
        }
        return WrapperRef(ptr->items->values[i]);
    }

    iterator begin() {
        return ptr->items->values;
    }
    iterator end() {
        return &ptr->items->values[size()];
    }
    const_iterator begin() const {
        return ptr->items->values;
    }
    const_iterator end() const {
        return &ptr->items->values[size()];
    }

    private:
    Ptr ptr;
};