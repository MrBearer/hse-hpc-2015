#include <chrono>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <thread>

class Account {
public:
    Account(int balance): balance(balance), m() {
    }

    int getBalance() const {
        return balance;
    }

    void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        } else {
            return false;
        }
    }

    std::unique_lock<std::mutex> getLock() {
        std::unique_lock<std::mutex> lock(m);
        return lock;
    }

private:
    int balance;
    std::mutex m;
};

void transfer(int client_id, Account& from, Account& to, int amount) {
    std::unique_lock<std::mutex> lock_from(from.getLock());
    if (from.withdraw(amount)) {
        std::printf("%d: withdraw %d OK\n", client_id, amount);
        fflush(stdout); // to see withdraw messages
        std::unique_lock<std::mutex> lock_to(to.getLock());
        to.deposit(amount);
        lock_to.unlock();
        lock_from.unlock();
        std::printf("%d: deposit %d OK\n", client_id, amount);
    } else {
        lock_from.unlock();
        std::printf("%d: withdraw %d ERROR\n", client_id, amount);
    }
}

int main(int argc, char* argv[]) {
    Account a(100);
    Account b(100);

    std::thread t1(transfer, 1, std::ref(a), std::ref(b), 10);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1)); // uncomment to avoid deadlock
    std::thread t2(transfer, 2, std::ref(b), std::ref(a), 20);

    t1.join();
    t2.join();

    std::cout << "balance a = " << a.getBalance() << "\n";
    std::cout << "balance b = " << b.getBalance() << "\n";
}