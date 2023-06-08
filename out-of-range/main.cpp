#include <initializer_list>
#include <iostream>
#include <vector>
#include <string>


int* allocate(std::initializer_list<int> ilist) {
    int* dynamic_array = new int[ilist.size()];
    for (size_t idx = 0; idx < ilist.size(); ++idx) {
        dynamic_array[idx] = static_cast<int>(idx);
    }
    return dynamic_array;
}

template <class Container>
void testArrayAccess(const char* TEST_NAME, Container& array_like, size_t n) {
    std::cout << std::endl << TEST_NAME << std::endl;
    for (size_t idx = 0; idx < n; ++idx) {
        auto value = array_like[idx];
        printf("[%02lu] -> %d\n", idx, value);
    }
}


int main() {
    // Containers size
    constexpr size_t kSize = 5;

    int static_array[kSize] = {0, 1, 2, 3, 4};
    testArrayAccess("STATIC ARRAY", static_array, 2 * kSize);

    int* dynamic_array = allocate({0, 1, 2, 3, 4});
    testArrayAccess("DYNAMIC ARRAY", dynamic_array, 2 * kSize);

    std::vector<int> vector = {0, 1, 2, 3, 4};
    testArrayAccess("STL VECTOR", vector, 2 * kSize);

    // Stack buffer overflow due to small string optimization
    std::string small_string = std::string(15, '1');
    testArrayAccess("SHORT STRING", small_string, 2 * small_string.size());

    // Heap buffer overflow (exact long string size might differ in defferent stl implementations)
    std::string long_string = std::string(16, '1');
    testArrayAccess("LONG STRING", long_string, 2 * long_string.size());

    delete [] dynamic_array;
}
