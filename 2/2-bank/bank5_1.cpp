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
    if (from.withdraw(amount)) {
        std::printf("%d: withdraw %d OK\n", client_id, amount);
        to.deposit(amount);
        std::printf("%d: deposit %d OK\n", client_id, amount);
    } else {
        std::printf("%d: withdraw %d ERROR\n", client_id, amount);
    }
}

void client(int client_id, Account& from, Account& to, int amount) {
    if (&from > &to) {
        std::unique_lock<std::mutex> lock_from(from.getLock());
        std::unique_lock<std::mutex> lock_to(to.getLock());
        transfer(client_id, from, to, amount);
    } else {
        std::unique_lock<std::mutex> lock_to(to.getLock());
        std::unique_lock<std::mutex> lock_from(from.getLock());
        transfer(client_id, from, to, amount);
    }
}

int main(int argc, char* argv[]) {
    Account a(100);
    Account b(100);

    std::thread t1(client, 1, std::ref(a), std::ref(b), 10);
    std::thread t2(client, 2, std::ref(b), std::ref(a), 20);

    t1.join();
    t2.join();

    std::cout << "balance a = " << a.getBalance() << "\n";
    std::cout << "balance b = " << b.getBalance() << "\n";
}