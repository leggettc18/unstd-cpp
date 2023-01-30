#include <stddef.h>
#include <iterator>
namespace unstd {
template <class T, size_t S>
class Array {
private:
    T mData[S];
public:
    constexpr size_t Size() const {
        return S;
    }

    T& operator[](size_t index) { return mData[index]; }
    const T& operator[](size_t index) const { return mData[index]; }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        Iterator(pointer ptr) : mPtr(ptr) {}
        reference operator*() const { return *mPtr; }
        pointer operator->() { return mPtr; }
        Iterator& operator++() { mPtr++; return *this; }
        Iterator operator++(T) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.mPtr == b.mPtr; };
        friend bool operator != (const Iterator& a, const Iterator& b) { return a.mPtr != b.mPtr; };

    private:
        pointer mPtr;
    };

    Iterator begin() { return Iterator(&mData[0]); }
    Iterator end() { return Iterator(&mData[this->Size()]); }
};
}
