#include <iostream>
#include <limits>
#include <type_traits>


template <typename T>
void overflowNumericType() {
    T large_value = std::numeric_limits<T>::max() / 3;
    T overflown = large_value * 4;
    if constexpr (std::is_integral_v<T> && sizeof(T) <= 2) {
        std::cout << static_cast<int>(overflown) << std::endl;
    } else {
        std::cout << overflown << std::endl;
    }
}


int main() {

    overflowNumericType<uint32_t>();  // Not a UB

    overflowNumericType<uint64_t>();  // Not a UB

    overflowNumericType<int16_t>();  // Oops: https://github.com/google/sanitizers/issues/940

    overflowNumericType<int32_t>();

    overflowNumericType<int64_t>();

    overflowNumericType<float>();  // No report

    overflowNumericType<double>();  // No report


}
