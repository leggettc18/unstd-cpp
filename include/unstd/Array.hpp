#include <stddef.h>
#include <iterator>
#include "Iterator.hpp"

namespace Unstd {
template <class Array> class ArrayIterator : public BaseIterator<Array> {
    using iterator_category = std::forward_iterator_tag;
    using BaseIterator<Array>::BaseIterator;

  public:
    ArrayIterator& operator++() {
        this->mPtr++;
        return *this;
    }

    ArrayIterator operator++(int) {
        ArrayIterator tmp = *this;
        ++(*this);
        return tmp;
    }
};

template <class T, size_t S> class Array {
  private:
    T mData[S];

  public:
    constexpr size_t Size() const {
        return S;
    }

    T& operator[](size_t index) {
        return mData[index];
    }
    const T& operator[](size_t index) const {
        return mData[index];
    }

    // Omitting these from Linting since they are required
    // as is for this class to function with iterators.

    // NOLINTNEXTLINE
    ArrayIterator<T> begin() {
        return ArrayIterator<T>(&mData[0]);
    }
    // NOLINTNEXTLINE
    ArrayIterator<T> end() {
        return ArrayIterator<T>(&mData[this->Size()]);
    }
};
} // namespace Unstd
