#pragma once

#include <cstddef>

namespace Unstd {
template <class T> class BaseIterator {
  protected:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    T* mPtr;

  public:
    BaseIterator(pointer ptr) : mPtr(ptr) {
    }

    reference operator*() const {
        return *mPtr;
    }

    pointer operator->() {
        return mPtr;
    }

    friend bool operator==(const BaseIterator& a, const BaseIterator& b) {
        return a.mPtr == b.mPtr;
    }

    friend bool operator!=(const BaseIterator& a, const BaseIterator& b) {
        return a.mPtr != b.mPtr;
    }
};
} // namespace Unstd
