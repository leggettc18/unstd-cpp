#pragma once

#include <stddef.h>
#include <utility>
namespace unstd {
template<typename T>
class Vector {
public:
    Vector() {}
    Vector(size_t initialSize): mCapacity(initialSize) {
        realloc(initialSize);
    }

    ~Vector() {
        Clear();
        ::operator delete(mData, mCapacity * sizeof(T));
    }

    constexpr void PushBack(const T& value) {
        if (mSize >= mCapacity) {
            if (mCapacity == 0) {
                realloc(2);
            } else {
                realloc(mCapacity + (mCapacity / 2));
            }
        }
        mData[mSize] = value;
        mSize++;
    }

    constexpr void PushBack(T&& value) {
        EmplaceBack(std::move(value));
    }

    template<typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (mSize >= mCapacity) {
            realloc(2);
        } else {
            realloc(mCapacity + (mCapacity / 2));
        }
        new(&mData[mSize]) T(std::forward<Args>(args)...);
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
private:
    T* mData = nullptr;

    size_t mSize = 0;
    size_t mCapacity = 0;

    void realloc(size_t capacity) {
        T* newBlock = (T*)::operator new(capacity * sizeof(T));

        size_t oldSize = mSize;
        if (capacity < mSize) {
            mSize = capacity;
        }

        if (mData != nullptr) {
            for (size_t i = 0; i < oldSize; i++) {
                new(&newBlock[i]) T(std::move(mData[i]));
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
}
