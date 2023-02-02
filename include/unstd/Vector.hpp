#pragma once

#include <stddef.h>
#include <utility>
#include <iterator>

namespace Unstd {
template <typename T> class Vector {
  public:
    Vector() {
    }
    Vector(size_t initialSize) : mCapacity(initialSize) {
        Realloc(initialSize);
    }

    ~Vector() {
        Clear();
        ::operator delete(mData, mCapacity * sizeof(T));
    }

    constexpr void PushBack(const T& value) {
        if (mSize >= mCapacity) {
            if (mCapacity == 0) {
                Realloc(2);
            } else {
                Realloc(mCapacity + (mCapacity / 2));
            }
        }
        mData[mSize] = value;
        mSize++;
    }

    constexpr void PushBack(T&& value) {
        EmplaceBack(std::move(value));
    }

    template <typename... Args> T& EmplaceBack(Args&&... args) {
        if (mSize >= mCapacity) {
            Realloc(2);
        } else {
            Realloc(mCapacity + (mCapacity / 2));
        }
        new (&mData[mSize]) T(std::forward<Args>(args)...);
        return mData[mSize++];
    }

    void PopBack() {
        if (mSize > 0) {
            mSize--;
            mData[mSize].~T();
        }
    }

    void Clear() {
        for (size_t i = 0; i < mSize; i++) {
            mData[i].~T();
        }
        mSize = 0;
    }

    size_t Size() {
        return mSize;
    }

    size_t Capacity() {
        return mCapacity;
    }

    const T& operator[](size_t index) const {
        return mData[index];
    }

    T& operator[](size_t index) {
        return mData[index];
    }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        Iterator(pointer ptr) : mPtr(ptr) {
        }
        reference operator*() const {
            return *mPtr;
        }
        pointer operator->() {
            return mPtr;
        }
        Iterator& operator++() {
            mPtr++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.mPtr == b.mPtr;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.mPtr != b.mPtr;
        }

      private:
        pointer mPtr;
    };

    // Excluding linting for these functions since they are required as is
    // for this class to function as an iterator.

    // NOLINTNEXTLINE
    Iterator begin() {
        return Iterator(&mData[0]);
    }
    // NOLINTNEXTLINE
    Iterator end() {
        return Iterator(&mData[mSize]);
    }

  private:
    T* mData = nullptr;

    size_t mSize = 0;
    size_t mCapacity = 0;

    void Realloc(size_t capacity) {
        T* newBlock = (T*)::operator new(capacity * sizeof(T));

        size_t oldSize = mSize;
        if (capacity < mSize) {
            mSize = capacity;
        }

        if (mData != nullptr) {
            for (size_t i = 0; i < oldSize; i++) {
                new (&newBlock[i]) T(std::move(mData[i]));
            }

            for (size_t i = 0; i < oldSize; i++) {
                mData[i].~T();
            }
        }
        ::operator delete(mData, mCapacity * sizeof(T));
        mData = newBlock;
        mCapacity = capacity;
    }
};
} // namespace Unstd
