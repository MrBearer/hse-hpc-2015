#include <iostream>
#include <thread>

class BackgroundTask {
public:
    void operator()() const {
        std::cout << "Hello, Concurrent World!\n";
    }
};

int main() {
    BackgroundTask task;
    std::thread my_thread(task);
    my_thread.join();
}