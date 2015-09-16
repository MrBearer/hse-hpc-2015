#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <assert.h>

void uppercase1(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), (int (*)(int))std::toupper);
}

void uppercase2(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), (int (*)(int))std::toupper);
}

void uppercase3(std::unique_ptr<std::string> s) {
    std::transform(s->begin(), s->end(), s->begin(), (int (*)(int))std::toupper);
    std::cout << *s;
}

int main() {
    std::string s("Hello, Concurrent World!\n");

    std::thread my_thread1(uppercase1, s); // pass by value
    my_thread1.join();
    std::cout << s;

    std::thread my_thread2(uppercase2, std::ref(s)); // pass by reference
    my_thread2.join();
    std::cout << s;

    std::unique_ptr<std::string> s_ptr(new std::string("Hello, Concurrent World!\n"));
    std::thread my_thread3(uppercase3, std::move(s_ptr)); // move (transfer ownership)
    my_thread3.join();
    assert(s_ptr == NULL);
}