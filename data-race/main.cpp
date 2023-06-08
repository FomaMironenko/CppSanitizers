#include <iostream>
#include <thread>
#include <atomic>

constexpr size_t kNumIter = 1'000'000;
using State = int;

void UpdateState(State& state, int update) {
    for (size_t iter = 0; iter < kNumIter; ++iter) {
        state += update;
    }
}

int main() {
    State shared_state{0};

    std::thread t1{UpdateState, std::ref(shared_state), 0};
    std::thread t2{UpdateState, std::ref(shared_state), 1};
    t1.join();
    t2.join();

    std::cout << shared_state << std::endl;

    return EXIT_SUCCESS;
}