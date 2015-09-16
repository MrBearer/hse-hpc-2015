#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

class Account {
public:
    Account(int balance): balance(balance) {
    }

    int getBalance() const {
        return balance;
    }

    void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (balance >= amount) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(1)); // uncomment to rob the bank
            balance -= amount;
            return true;
        } else {
            return false;
        }
    }

private:
    int balance;
};

void client(int client_id, Account& a, int amount) {
    std::printf("%d: balance %d\n", client_id, a.getBalance());
    bool result = a.withdraw(amount);
    if (result) {
        std::printf("%d: withdraw %d OK\n", client_id, amount);
    } else {
        std::printf("%d: withdraw %d ERROR\n", client_id, amount);
    }
    std::printf("%d: balance %d\n", client_id, a.getBalance());
}

int main(int argc, char* argv[]) {
    Account a(100);

    std::thread t1(client, 1, std::ref(a), 90);
    std::thread t2(client, 2, std::ref(a), 90);

    t1.join();
    t2.join();

    std::cout << "balance " << a.getBalance() << "\n";
}
