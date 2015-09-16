#include <assert.h>
#include <iostream>
#include <thread>

void hello() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Hello, Concurrent World!\n";
}

void spawnThread() {
    std::cout << "Starting spawn\n";
    std::thread my_thread(hello);
    my_thread.detach();
    assert(!my_thread.joinable());
    std::cout << "Exiting spawn\n";
}

int main() {
    spawnThread();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}