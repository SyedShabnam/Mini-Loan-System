#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define NAME_LENGTH 50

// ----------------------------
// Array for Eligible Customers
// ----------------------------
char eligibleCustomers[MAX_CUSTOMERS][NAME_LENGTH];
int totalEligible = 0;

void addEligibleCustomer(const char* name) {
    if (totalEligible < MAX_CUSTOMERS) {
        strcpy(eligibleCustomers[totalEligible], name);
        totalEligible++;
    } else {
        printf("Eligible customer list is full!\n");
    }
}

void displayEligibleCustomers() {
    printf("\nList of Customers Eligible for Loans:\n");
    for (int i = 0; i < totalEligible; i++) {
        printf("%d. %s\n", i + 1, eligibleCustomers[i]);
    }
}

// ----------------------------
// Linked List for Active Loans
// ----------------------------
typedef struct LoanNode {
    char customerName[NAME_LENGTH];
    float loanAmount;
    float emiAmount;
    int tenureMonths;
    struct LoanNode* next;
} LoanNode;

LoanNode* loanHead = NULL;

LoanNode* createLoanNode(const char* name, float loan, float emi, int tenure) {
    LoanNode* newNode = (LoanNode*)malloc(sizeof(LoanNode));
    strcpy(newNode->customerName, name);
    newNode->loanAmount = loan;
    newNode->emiAmount = emi;
    newNode->tenureMonths = tenure;
    newNode->next = NULL;
    return newNode;
}

void addActiveLoan(const char* name, float loan, float emi, int tenure) {
    LoanNode* newLoan = createLoanNode(name, loan, emi, tenure);
    newLoan->next = loanHead;
    loanHead = newLoan;
}

void displayActiveLoans() {
    printf("\nActive Loans with EMI Details:\n");
    LoanNode* current = loanHead;
    while (current != NULL) {
        printf("Customer: %s | Loan: %.2f | EMI: %.2f | Tenure: %d months\n",
               current->customerName, current->loanAmount,
               current->emiAmount, current->tenureMonths);
        current = current->next;
    }
}

// ----------------------------
// Main Function with User Input
// ----------------------------
int main() {
    int choice;
    char name[NAME_LENGTH];
    float loan, emi;
    int tenure;

    while (1) {
        printf("\n--- Mini Bank Loan System ---\n");
        printf("1. Add Eligible Customer\n");
        printf("2. View Eligible Customers\n");
        printf("3. Add Active Loan\n");
        printf("4. View Active Loans\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                fgets(name, NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // remove newline
                addEligibleCustomer(name);
                break;

            case 2:
                displayEligibleCustomers();
                break;

            case 3:
                printf("Enter customer name: ");
                fgets(name, NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter loan amount: ");
                scanf("%f", &loan);
                printf("Enter EMI amount: ");
                scanf("%f", &emi);
                printf("Enter tenure in months: ");
                scanf("%d", &tenure);
                getchar(); // consume newline

                addActiveLoan(name, loan, emi, tenure);
                break;

            case 4:
                displayActiveLoans();
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
