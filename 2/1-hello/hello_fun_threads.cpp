#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

void hello(unsigned id) {
    std::cout << id << ": Hello, Concurrent World!\n";
}

int main() {
    unsigned num_proc = std::thread::hardware_concurrency();
    std::cout << "Processors: " << num_proc << "\n";
    std::vector<std::thread> threads;
    for(unsigned i=0; i<num_proc; ++i) {
        threads.push_back(std::thread(hello, i));
    }
    std::for_each(threads.begin(), threads.end(), 
            std::mem_fn(&std::thread::join));
}