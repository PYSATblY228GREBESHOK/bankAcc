#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <locale> 

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNumber, double initialBalance, double interest) {
        if (initialBalance < 0 || interest < 0) {
            throw invalid_argument("Initial balance и процентная ставка должны быть положительными");
        }
        accountNumber = accNumber;
        balance = initialBalance;
        interestRate = interest;
    }

    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма вклада должна быть неотрицательной.");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Сумма снятия должна быть неотрицательной.");
        }
        if (amount > balance) {
            throw invalid_argument("Недостаточно средств на счете.");
        }
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }

    double getInterest() const {
        return balance * interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double newRate) {
        if (newRate < 0) {
            throw invalid_argument("Процентная ставка должна быть неотрицательной.");
        }
        interestRate = newRate;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount < 0) {
        throw invalid_argument("Сумма перевода должна быть неотрицательной.");
    }
    if (amount > from.balance) {
        return false;
    }
    from.balance -= amount;
    to.balance += amount;
    return true;
}

int main() {
    // Установка кодовой страницы консоли для корректного отображения символов
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Установка локали для корректной работы с символами
    setlocale(LC_ALL, "Russian");

    // Ваш код
    cout.imbue(locale(""));

    try {
        BankAccount account1(123456, 1000.0, 0.05);
        BankAccount account2(789012, 500.0, 0.03);

        cout << "Начальный баланс счета 1: " << account1.getBalance() << endl;
        cout << "Начальный баланс счета 2: " << account2.getBalance() << endl;

        double transferAmount = 200.0;
        if (transfer(account1, account2, transferAmount)) {
            cout << "Перевод выполнен успешно!" << endl;
        }
        else {
            cout << "Перевод не выполнен из-за недостаточных средств." << endl;
        }

        cout << "Конечный баланс счета 1: " << account1.getBalance() << endl;
        cout << "Конечный баланс счета 2: " << account2.getBalance() << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    system("pause");

    return 0;
}
