#include <iostream>
#include <vector>
#include <random>

class StressHelper {
public:
    StressHelper(int push_pct, int pop_pct)
        : PRNG(72874),
          push_pct(push_pct),
          event_dist(1, push_pct + pop_pct),
          upd_dist(-1000, 1000) {
    }

    enum Event {Push, Pop};
    Event randEvent() {
        return event_dist(PRNG) <= push_pct ? Push : Pop;
    }

    uint64_t randUpdate() {
        return upd_dist(PRNG);
    }

private:
    std::mt19937 PRNG;
    int push_pct;
    std::uniform_int_distribution<int> event_dist;
    std::uniform_int_distribution<uint64_t> upd_dist;
};

void stressTest() {
    std::cout << std::endl << "STRESS TEST" << std::endl;
    std::vector<uint64_t> stack{0};
    uint64_t pushed = 0;
    uint64_t popped = 0;
    constexpr size_t kNumIters = 10000;

    StressHelper stress(2, 2);
    for (size_t iter = 0; iter < kNumIters; ++iter) {
        if (stress.randEvent() == StressHelper::Push) {
            uint64_t upd = stress.randUpdate();
            pushed += upd;
            stack.push_back(upd);
        } else {
            popped += stack.back();
            stack.pop_back();
        }
    }
    while (!stack.empty()) {
        popped += stack.back();
        stack.pop_back();
    }

    std::cout << "pushed: " << pushed << std::endl;
    std::cout << "popped: " << popped << std::endl;

}

void simpleTest() {
    std::cout << std::endl << "SIMPLE TEST" << std::endl;
    std::vector<int> vector = {1, 2, 3};
    constexpr size_t kNumIters = 10;
    for (size_t iter = 0; iter < kNumIters; ++iter) {
        std::cout << iter << " -> " << vector.back() << std::endl;
        vector.pop_back();
    }
}


int main() {
    simpleTest();
    stressTest();
    return EXIT_SUCCESS;
}
