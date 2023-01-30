
#include <stddef.h>
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
};
}
