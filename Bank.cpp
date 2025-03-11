#include <iostream>
#include <unordered_map>

class BankAccount {
private:
    int accountNumber;
    double balance;

public:
    BankAccount(int accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance) {}

    void Deposit(double amount) {
        if (amount <= 0) {
            std::cerr << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        std::cout << "Deposited: $" << amount << " | New Balance: $" << balance << "\n";
    }

    void Withdraw(double amount) {
        if (amount > balance) {
            std::cerr << "Insufficient funds!\n";
            return;
        }
        balance -= amount;
        std::cout << "Withdrawn: $" << amount << " | Remaining Balance: $" << balance << "\n";
    }

    double GetBalance() const {
        return balance;
    }
};

class Bank {
private:
    std::unordered_map<int, BankAccount> accounts;

public:
    void CreateAccount(int accNum, double initialBalance) {
        accounts.emplace(accNum, BankAccount(accNum, initialBalance));
        std::cout << "Account " << accNum << " created successfully!\n";
    }

    BankAccount* GetAccount(int accNum) {
        auto it = accounts.find(accNum);
        if (it != accounts.end())
            return &(it->second);
        return nullptr;
    }
};

int main() {
    Bank bank;
    int choice, accNum;
    double amount;

    do {
        std::cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit\nChoose an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            bank.CreateAccount(accNum, 0);
            break;

        case 2:
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            std::cout << "Enter Amount: ";
            std::cin >> amount;
            if (BankAccount* acc = bank.GetAccount(accNum))
                acc->Deposit(amount);
            else
                std::cerr << "Account not found!\n";
            break;

        case 3:
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            std::cout << "Enter Amount: ";
            std::cin >> amount;
            if (BankAccount* acc = bank.GetAccount(accNum))
                acc->Withdraw(amount);
            else
                std::cerr << "Account not found!\n";
            break;

        case 4:
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            if (BankAccount* acc = bank.GetAccount(accNum))
                std::cout << "Balance: $" << acc->GetBalance() << "\n";
            else
                std::cerr << "Account not found!\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
