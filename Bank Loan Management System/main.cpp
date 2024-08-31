#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Loan {
public:
    Loan(int id, double amount, double interestRate, int termMonths)
        : id(id), amount(amount), interestRate(interestRate), termMonths(termMonths), balance(amount) {}

    int getId() const { return id; }
    double getAmount() const { return amount; }
    double getInterestRate() const { return interestRate; }
    int getTermMonths() const { return termMonths; }
    double getBalance() const { return balance; }
    
    void makePayment(double payment) {
        balance -= payment;
        if (balance < 0) balance = 0;
    }

    double calculateMonthlyPayment() const {
        double monthlyRate = interestRate / 12 / 100;
        double numerator = monthlyRate * pow(1 + monthlyRate, termMonths);
        double denominator = pow(1 + monthlyRate, termMonths) - 1;
        return amount * (numerator / denominator);
    }

    void displayLoanDetails() const {
        cout << "Loan ID: " << id << endl;
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Term: " << termMonths << " months" << endl;
        cout << "Remaining Balance: $" << fixed << setprecision(2) << balance << endl;
    }

private:
    int id;
    double amount;
    double interestRate;
    int termMonths;
    double balance;
};

class LoanManagementSystem {
public:
    void addLoan(const Loan& loan) {
        loans.push_back(loan);
    }

    void makePayment(int loanId, double payment) {
        for (auto& loan : loans) {
            if (loan.getId() == loanId) {
                loan.makePayment(payment);
                cout << "Payment of $" << fixed << setprecision(2) << payment << " made to Loan ID " << loanId << endl;
                return;
            }
        }
        cout << "Loan ID " << loanId << " not found!" << endl;
    }

    void displayLoans() const {
        for (const auto& loan : loans) {
            loan.displayLoanDetails();
            cout << "------------------------" << endl;
        }
    }

    void calculateAndDisplayPayments() const {
        for (const auto& loan : loans) {
            cout << "Loan ID " << loan.getId() << " Monthly Payment: $" << fixed << setprecision(2) << loan.calculateMonthlyPayment() << endl;
        }
    }

private:
    vector<Loan> loans;
};

int main() {
    LoanManagementSystem lms;

    lms.addLoan(Loan(1, 10000, 5.0, 24));
    lms.addLoan(Loan(2, 5000, 3.5, 12));

    int choice;
    do {
        cout << "Bank Loan Management System" << endl;
        cout << "1. Display All Loans" << endl;
        cout << "2. Make Payment" << endl;
        cout << "3. Calculate and Display Monthly Payments" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lms.displayLoans();
                break;
            case 2: {
                int loanId;
                double payment;
                cout << "Enter Loan ID: ";
                cin >> loanId;
                cout << "Enter Payment Amount: ";
                cin >> payment;
                lms.makePayment(loanId, payment);
                break;
            }
            case 3:
                lms.calculateAndDisplayPayments();
                break;
            case 4:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
