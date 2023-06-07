#include <iostream>
#include <mutex>
#include <thread>

/**
 * Compile with ThreadSanitizer and run via:
 * TSAN_OPTIONS=detect_deadlocks=1 ./tsan
 * 
 * For more descriptive ThreadSanitizer output:
 * TSAN_OPTIONS=detect_deadlocks=1:second_deadlock_stack=1 ./tsan
 */

struct SharedState {

    std::mutex mtx_1;
    std::mutex mtx_2;

    void directLockOrder() noexcept {
        std::lock_guard guard_1(mtx_1);
        std::lock_guard guard_2(mtx_2);
    }

    void inverseLockOrder() noexcept {
        std::lock_guard guard_2(mtx_2);
        std::lock_guard guard_1(mtx_1);
    }

    void dummyLock() {
        mtx_1.lock();
        mtx_1.lock();
    }

};


void testSingleThread() {
    SharedState state;
    state.directLockOrder();
    state.inverseLockOrder();
}

void testTwoThreads() {
    constexpr size_t kNumItreations = 10;
    SharedState state;

    std::thread t1([&state]() {
        for (size_t iter = 0; iter < kNumItreations; ++iter) {
            state.directLockOrder();
        }
    });

    std::thread t2([&state]() {
        for (size_t iter = 0; iter < kNumItreations; ++iter) {
            state.inverseLockOrder();
        }
    });

    t1.join();
    t2.join();
}


int main() {

    testSingleThread();

    testTwoThreads();

    // Locks
    SharedState state;
    state.dummyLock();

    return EXIT_SUCCESS;

}
