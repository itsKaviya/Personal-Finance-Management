#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

// Account and Transaction Classes
struct Transaction {
    int choice;
    string date;
    string description;
    double amount;
};

class Account {
    private:
        vector<Transaction> transactions;

    public:
    void personal_details(int age, const char* name, const char* qualification, double income) {
        cout << "\n-------------------- Your Personal Profile ------------------\n";
        cout << "Name                 : " << name << "\n";
        cout << "Qualification        : " << qualification << "\n";
        cout << "Age                  : " << age << " years\n";
        cout << "Monthly Income       : Rs." << fixed << setprecision(2) << income << "\n";
        cout << "----------------------------------------------------------------\n";
    }

    // Add Transaction Module
    void addTransaction(int choice, string date, string description, double amount) {
        Transaction t;
        t.choice = choice;
        t.date = date;
        t.description = description;
        t.amount = amount;
        transactions.push_back(t);
    }

    // Module for expense tracker
    void totalexpense() {
        double total = 0.0;
        cout << "------------------- Expense tracker ----------------------\n";
        cout << "Date\t\t\tDescription\t\t\tAmount\n";
        // This step is done to only extract and display the expense done so far.
        for (int i = 0; i < transactions.size(); i++) {
            if (transactions[i].choice == 2) {
                cout << transactions[i].date << "\t\t\t" << transactions[i].description
                     << "\t\t\t" << transactions[i].amount << endl;
                total += transactions[i].amount;
            }
        }
        cout << "Total Expenses: " << total << endl;
    }

    // Module used to print the transactions entered by the user so far
    void print_transactions() {
        cout << left << setw(15) << "Date"
             << setw(25) << "Description"
             << setw(15) << "Amount"
             << setw(15) << "Type" << endl;
    
        cout << string(64, '-') << endl;
    
        for (const auto& t : transactions) {
            cout << left << setw(15) << t.date
                 << setw(25) << t.description
                 << setw(15) << fixed << setprecision(2) << t.amount
                 << setw(15) << (t.choice == 1 ? "Deposit" : "Withdrawal") 
                 << endl;
        }
    }

    // This module returns the user the balance left after all the transaction
    double get_balance() {
        double balance = 0.0;
        for (int i = 0; i < transactions.size(); i++) {
            if (transactions[i].choice == 1)
                balance += transactions[i].amount;  // Calculation for deposit
            else
                balance -= transactions[i].amount;  // Calculation for withdrawal
        }
        return balance;
    }

    // This module shows the user their savings
    void saving_calculator(double income) {
        double rate_of_interest = 0;
        double monthly_contribution = 0;
        int total_years = 0;

        cout << "-------------------- Savings Calculator ------------------\n";
        
        if (income < 0) {
        cout << "Error: Income must be non-negative. Cannot proceed with savings calculation.\n";
        return;
    }
        
        do {
            cout << "Monthly Contribution: ";
            cin >> monthly_contribution;
            if (monthly_contribution < 0)
                cout << "Monthly Contribution Must Be >= 0" << endl;
        } while (monthly_contribution < 0);
        
        do {
            cout << "Rate Of Interest (%): ";
            cin >> rate_of_interest;
            if (rate_of_interest < 0)
                cout << "Rate Of Interest Must Be >= 0" << endl;
        } while (rate_of_interest < 0);
        
        do {
            cout << "Years To Grow: ";
            cin >> total_years;
            if (total_years <= 0)
                cout << "Years Must Be > 0" << endl;
        } while (total_years <= 0);
        
        cout << endl;
        cout << setw(10) << "Monthly Saving\n\n";
        cout << setw(10) << "Year";
        cout << setw(25) << "Start Balance";
        cout << setw(15) << "Interest";
        cout << setw(20) << "End Balance";
        cout << endl;
        for (int i = 0; i < 70; i++) cout << "*";
        cout << endl;
        
        double current_balance = income;
        for (int year = 1; year <= total_years; year++) {
            cout << setw(10) << year;
            cout << setw(25) << fixed << setprecision(2) << current_balance;
            double interest = current_balance * (rate_of_interest / 100);
            current_balance += interest + monthly_contribution;
            cout << setw(15) << fixed << setprecision(2) << interest;
            cout << setw(20) << fixed << setprecision(2) << current_balance;
            cout << endl;
        }
    }

    // This module helps the user to understand how much he should pay as tax
    double tax_planner(double income) {
        cout << "-------------------- Tax Planner ------------------\n";
        double annualIncome = income*12;
        cout << "Your estimated annual income: Rs." << fixed << setprecision(2) << annualIncome << "\n\n";
        double tax = 0.0;
        double surcharge = 0.0;
        
        // Tax slabs and rates
        const double slab1Rate = 0.0;
        const double slab2Rate = 0.05;
        const double slab3Rate = 0.2;
        const double slab4Rate = 0.3;
        
        // Tax slab amounts
        const double slab1Limit = 250000.0;
        const double slab2Limit = 500000.0;
        const double slab3Limit = 1000000.0;
        
        // Education and health cess rate
        const double cessRate = 0.04;
        
        // Surcharge rates
        const double surcharge1Rate = 0.1;
        const double surcharge2Rate = 0.15;
        const double surcharge3Rate = 0.25;
        
        if (annualIncome <= slab1Limit) {
            tax = 0.0;
        } else if (annualIncome <= slab2Limit) {
            tax = (annualIncome - slab1Limit) * slab2Rate;
        } else if (annualIncome <= slab3Limit) {
            tax = (slab2Limit - slab1Limit) * slab2Rate + (annualIncome - slab2Limit) * slab3Rate;
        } else {
            tax = (slab2Limit - slab1Limit) * slab2Rate + (slab3Limit - slab2Limit) * slab3Rate + (annualIncome - slab3Limit) * slab4Rate;
        }
        
        // Surcharge calculation - Fixed logic
        if (annualIncome > 5000000.0 && annualIncome <= 10000000.0) {
            surcharge = tax * surcharge1Rate;
        } else if (annualIncome > 10000000.0 && annualIncome <= 20000000.0) {
            surcharge = tax * surcharge2Rate;
        } else if (annualIncome > 20000000.0) {
            surcharge = tax * surcharge3Rate;
        }
        
        double cessAmount = (tax + surcharge) * cessRate;
        double totalTax = tax + surcharge + cessAmount;

        cout << "-----------------------------------------------------\n";
        cout << left << setw(30) << "Base Income Tax:" << "Rs" << fixed << setprecision(2) << tax << endl;
        cout << left << setw(30) << "Applicable Surcharge:" << "Rs" << surcharge << endl;
        cout << left << setw(30) << "Health & Education Cess (4%):" << "Rs" << cessAmount << endl;
        cout << "-----------------------------------------------------\n";
        cout << left << setw(30) << "Total Tax Liability:" << "Rs" << totalTax << endl;

        if (totalTax == 0) {
            cout << "You do not owe any income tax this year based on the current income.\n";
        } else {
            cout << "Please ensure to plan for this amount when filing your returns.\n";
        }

        return totalTax;
    }

    // Budget planner variables
    double set_budget = 0, current_budget = 0, remaining_budget = 0;
    int set_type;

    void print_budget_summary() {
        print_transactions();
        cout << "\nCurrent Expense = " << current_budget;
        remaining_budget = set_budget - current_budget;
        cout << "\nRemaining money left from the Planned budget = " << remaining_budget;
    }

    // Budget planner
    void budget_planner() {
        cout << "-------------------- Budget Planner ------------------\n";
        do {
            cout << "Do you want to set a Monthly (0) or Yearly (1) budget? Enter 0 or 1: ";
            cin >> set_type;
            if (set_type != 0 && set_type != 1)
                cout << "Invalid input. Please enter 0 for Monthly or 1 for Yearly.\n";
        } while (set_type != 0 && set_type != 1);

        do {
            cout << "Enter the total amount you want to allocate as your budget (Rs.): ";
            cin >> set_budget;
            if (set_budget <= 0)
                cout << "Budget set must be a positive number.\n";
        } while (set_budget <= 0);
        
        current_budget = 0;
        for (const auto& t : transactions) {
            if (t.choice == 2) current_budget += t.amount;
        }
    
        remaining_budget = set_budget - current_budget;
    
        cout << "\nBudget Summary:\n";
        cout << "-------------------------------------------------\n";
        cout << "Budget Type     : " << (set_type == 0 ? "Monthly" : "Yearly") << "\n";
        cout << "Planned Budget  : Rs." << set_budget << "\n";
        cout << "Current Expense : Rs." << current_budget << "\n";
        cout << "Remaining Budget: Rs." << remaining_budget << "\n";
        cout << "-------------------------------------------------\n";

        if (remaining_budget < 0) {
            cout << "You have exceeded your budget by Rs." << -remaining_budget << "!\n";
            cout << "Consider reducing unnecessary expenses.\n";
        } else if (remaining_budget <= 1000) {
            cout << "You are close to hitting your limit. Only Rs." << remaining_budget << " left.\n";
        } else {
            cout << "Great! You're within your budget. Keep it up!\n";
        }
    }

    // Investment tracker
    void investment_tracker() {
        double initialAmount, monthlyDeposit, annualInterestRate, targetAmount;
        int numYears;

        cout << "---------------------- Investment Tracker ---------------------\n";

        cout << "Let's help you estimate your savings and check if you can reach your investment goals.\n\n";
        cout << "Enter your initial investment amount Rs.: ";
        cin >> initialAmount;
        cout << "Enter how much you plan to deposit each month Rs.: ";
        cin >> monthlyDeposit;
        cout << "Enter the expected annual interest rate (%): ";
        cin >> annualInterestRate;
        cout << "Enter your target amount (Rs.) to reach your financial goal: ";
        cin >> targetAmount;
        cout << "Over how many years do you plan to invest?: ";
        cin >> numYears;

        double interest = annualInterestRate / 100;
        double totalAmount = initialAmount;
        
        for (int i = 1; i <= numYears * 12; i++) {
            totalAmount += monthlyDeposit;
            double monthlyInterest = totalAmount * (interest / 12);
            totalAmount += monthlyInterest;
        }

        cout << "\nAfter " << numYears << " years, you will have saved Rs." << fixed << setprecision(2) << totalAmount << "\n\n";

        // Investment goals
        double propertyCost = 500000;
        double propertyAmountNeeded = propertyCost - totalAmount;
        if (propertyAmountNeeded <= 0) {
            cout << "Congratulations, you can afford to invest in a property!" << endl;
        } else {
            cout << "You need to save an additional Rs." << fixed << setprecision(2) << propertyAmountNeeded << " to invest in a property." << endl;
        }
        
        double carCost = 150000;
        double carAmountNeeded = carCost - totalAmount;
        if (carAmountNeeded <= 0) {
            cout << "Congratulations, you can afford to buy a new car!" << endl;
        } else {
            cout << "You need to save an additional Rs." << fixed << setprecision(2) << carAmountNeeded << " to buy a new car." << endl;
        }
        
        double educationCost = 50000;
        double educationAmountNeeded = educationCost - totalAmount;
        if (educationAmountNeeded <= 0) {
            cout << "Congratulations, you can afford to make an educational investment!" << endl;
        } else {
            cout << "You need to save an additional Rs." << fixed << setprecision(2) << educationAmountNeeded << " to make an educational investment." << endl;
        }
        
        double jewelCost = 10000;
        double jewelAmountNeeded = jewelCost - totalAmount;
        if (jewelAmountNeeded <= 0) {
            cout << "Congratulations, you can afford to invest in jewels!" << endl;
        } else {
            cout << "You need to save an additional Rs." << fixed << setprecision(2) << jewelAmountNeeded << " to invest in jewels." << endl;
        }
    }
};

// Debt tracking classes
class Debt {
protected:
    string name;
public:
    double balance;
    Debt(const string& name, double balance) : name(name), balance(balance) {}

    friend void displayDebtInfo(const Debt& debt);

    virtual double calculateInterest() const = 0;
    virtual ~Debt() {}
};

void displayDebtInfo(const Debt& debt) {
    cout << "Description of Debt: " << debt.name << endl;
    cout << "Amount Borrowed through Debt Rs.:" << debt.balance << endl;
}

class Loan : public Debt {
private:
    double interestRate;

public:
    Loan(const string& name, double balance, double interestRate) 
        : Debt(name, balance), interestRate(interestRate) {}

    double calculateInterest() const override {
        return balance * (interestRate / 100);
    }
};

class Mortgage : public Debt {
private:
    double interestRate;
    int years;

public:
    Mortgage(const string& name, double balance, double interestRate, int years) 
        : Debt(name, balance), interestRate(interestRate), years(years) {}

    double calculateInterest() const override {
        return balance * (interestRate / 100) * years;
    }
};

class CreditCard : public Debt {
private:
    double interestRate;

public:
    CreditCard(const string& name, double balance, double interestRate) 
        : Debt(name, balance), interestRate(interestRate) {}

    double calculateInterest() const override {
        return balance * (interestRate / 100);
    }
};

void debt_tracker() {
    vector<Debt*> debts;
    string name;
    double balance;
    double interestRate;
    int years;
    int numDebts;
    cout << "---------------------- Debt Tracker ----------------------\n";
    cout << "\nYou are now entering your debt details..." << endl;
    cout << "Debt Types:\n";
    cout << "1 - Loan (Fixed interest)\n";
    cout << "2 - Mortgage (Interest over time)\n";
    cout << "3 - Credit Card (Rolling interest)\n";

    cout << "\nEnter the number of debts you want to track: ";
    cin >> numDebts;

    for (int i = 0; i < numDebts; ++i) {
        int debtType;
        cout << "\n--- Debt #" << i + 1 << " ---\n";
        cout << "Enter debt type (1 - Loan, 2 - Mortgage, 3 - Credit Card): ";
        cin >> debtType;

        cout << "Provide a short description or purpose for this debt (e.g., Home Loan, Education Loan, Credit Card Bill): ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter the amount needed Rs.: ";
        cin >> balance;

        cout << "Enter interest rate (%): ";
        cin >> interestRate;

        if (debtType == 1) {
            debts.push_back(new Loan(name, balance, interestRate));
        } else if (debtType == 2) {
            cout << "Enter number of years for mortgage: ";
            cin >> years;
            debts.push_back(new Mortgage(name, balance, interestRate, years));
        } else if (debtType == 3) {
            debts.push_back(new CreditCard(name, balance, interestRate));
        } else {
            cout << "Invalid debt type. Skipping this entry.\n";
        }
    }

    cout << "\n------------------ Debt Summary -----------------------:\n\n";
    for (const Debt* debt : debts) {
        displayDebtInfo(*debt);
        cout << "Interest Amount: Rs." << fixed << setprecision(2) << debt->calculateInterest() << endl;
        cout << "------------------------------------------------------\n";
    }

    // Clean up memory
    for (Debt* debt : debts) {
        delete debt;
    }
}


// Main function
int main() {
    Account account;
    
    int age;
    double income;
    char name[50];
    char qualification[25];
    
    cout << "\nEnter your age: ";
    cin >> age;
    cin.ignore();
    cout << "\nEnter your name: ";
    cin.getline(name, 50);
    cout << "\nEnter your Education Qualification: ";
    cin.getline(qualification, 25);
    cout << "\nEnter your monthly income: ";
    cin >> income;
    
    int choice;
    do {
        cout << "\nChoose an option:\n";
        cout << "1. Personal details\n2. Add a transaction\n3. Print all transactions\n4. Print current balance\n";
        cout << "5. Expense tracker\n6. Debt tracker\n7. Savings calculator\n8. Investment tracker\n";
        cout << "9. Tax Planner\n10. Budget Planner\n11. Exit\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                account.personal_details(age, name, qualification, income);
                break;
                
            case 2: {
                int transactionChoice;
                string date, description;
                double amount;

                cout << "\n--------------------- New Transaction Entry --------------------\n";
                cout << "Select Transaction Type:\n";
                cout << "1. Deposit\n";
                cout << "2. Withdraw\n";
                cout << "Enter your choice (1 or 2): ";
                cin >> transactionChoice;
                cout << "Enter date (dd/mm/yyyy): ";
                cin >> date;
                cout << "Enter a short description (e.g., Salary, Groceries, Rent): ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter amount : Rs. ";
                cin >> amount;
                account.addTransaction(transactionChoice, date, description, amount);
                cout << "\nTransaction successfully recorded!\n";
                cout << "------------------------------------------------------------------\n";
                break;
            }
            case 3:
                account.print_transactions();
                break;
            case 4:
                cout << "------------------- Account Summary ------------------\n";
                cout << "Available balance: Rs." << account.get_balance() << endl;
                break;
            case 5:
                account.totalexpense();
                break;
            case 6:
                debt_tracker();
                break;
            case 7:
                account.saving_calculator(income);
                break;
            case 8:
                account.investment_tracker();
                break;
            case 9: {
                double taxAmount = account.tax_planner(income);
                break;
            }
            case 10:
                account.budget_planner();
                break;
            case 11:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
        
    } while (choice != 11 );
    
    return 0;
}