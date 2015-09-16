#include <iostream>
#include <thread>

int main() {
    std::thread my_thread([]() {
        std::cout << "Hello, Concurrent World!\n";
    });
    my_thread.join();
}
