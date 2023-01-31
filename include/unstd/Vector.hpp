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

    void PushBack(const T& value) {
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

    void PushBack(T&& value) {
        if (mSize >= mCapacity) {
            if (mCapacity == 0) {
                realloc(2);
            } else {
                realloc(mCapacity + (mCapacity / 2));
            }
        }
        mData[mSize] = std::move(value);
        mSize++;
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
        T* newBlock = new T[capacity];

        if (capacity < mSize) {
            mSize = capacity;
        }

        for (size_t i = 0; i < mSize; i++) {
            newBlock[i] = std::move(mData[i]);
        }
        delete[] mData;
        mData = newBlock;
        mCapacity = capacity;
    }
};
}
