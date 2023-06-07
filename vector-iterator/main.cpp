#include <iostream>
#include <vector>
#include <cassert>


void AppendToVector(const std::vector<int>& from, std::vector<int>& to) {
    for (int value : from) {
        to.push_back(value);
    }
}

int main() {
    std::vector<int> to{1, 2, 3};
    std::vector<int> from{4, 5, 6};

    auto to_begin = to.begin();
    AppendToVector(from, to);
    for (size_t idx = 0; idx < 6; ++idx) {
        std::cout << *(to_begin++) << std::endl;
    }

    return EXIT_SUCCESS;
}
