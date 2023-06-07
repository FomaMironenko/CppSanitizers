#include <iostream>
#include <mutex>

std::mutex shared_state_mutex;
int shared_state = 0;

int ProcessSharedState() {
    ++shared_state;
    return shared_state * 2;
}

int main() {
    int* acquired_data_prt = nullptr;
    {
        std::lock_guard<std::mutex> guard(shared_state_mutex);
        int acquired_data = ProcessSharedState();
        acquired_data_prt = &acquired_data;
    }
    std::cout << "Processed state is: " << *acquired_data_prt << std::endl;

    return EXIT_SUCCESS;
}
