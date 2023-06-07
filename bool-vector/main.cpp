#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

template <class T>
auto GetOrderStatistics(const std::vector<T>& elements, int k) {
    assert(k >= 0 && static_cast<size_t>(k) < elements.size());
    std::vector<T> sorted = elements;
    std::sort(sorted.begin(), sorted.end());
    return sorted[k];
}

int main() {

    std::cout << "vector<int>" << std::endl;
    std::vector<int> numbers = {4, 3, 2, 1, 0};

    auto int_val = GetOrderStatistics(numbers, 0);
    std::cout << "[0]: " << int_val << std::endl;

    int_val = GetOrderStatistics(numbers, 2);
    std::cout << "[2]: " << int_val << std::endl;


    std::cout << "vector<bool>" << std::endl;
    std::vector<bool> bools = {true, false, false, true};

    auto bool_val = GetOrderStatistics(bools, 1);
    std::cout << "[1]: " << bool_val << std::endl;

    bool_val = GetOrderStatistics(bools, 2);
    std::cout << "[2]: " << bool_val << std::endl;

    bool_val = GetOrderStatistics(bools, 3);
    std::cout << "[3]: " << bool_val << std::endl;

}
