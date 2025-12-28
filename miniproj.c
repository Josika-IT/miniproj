#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    do {
        printf("\n========== ATM MENU ==========\n");
        printf("1. Create Account\n");
        printf("2. Deposit Amount\n");
        printf("3. Withdraw Amount\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                balanceEnquiry();
                break;
            case 5:
                printf("Thank you for using ATM\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 5);

    return 0;
}

/* Create Account */
void createAccount() {
    FILE *fp;
    struct Account acc;

    fp = fopen("accounts.dat", "ab");
    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Account Holder Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

/* Deposit Amount */
void deposit() {
    FILE *fp;
    struct Account acc;
    int accNo;
    float amount;
    int found = 0;

    fp = fopen("accounts.dat", "rb+");
    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&acc, sizeof(acc), 1, fp)) {
        if(acc.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("Deposit successful!\n");
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Account not found!\n");

    fclose(fp);
}

/* Withdraw Amount */
void withdraw() {
    FILE *fp;
    struct Account acc;
    int accNo;
    float amount;
    int found = 0;

    fp = fopen("accounts.dat", "rb+");
    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&acc, sizeof(acc), 1, fp)) {
        if(acc.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if(amount <= acc.balance) {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("Withdrawal successful!\n");
            } else {
                printf("Insufficient balance!\n");
            }
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Account not found!\n");

    fclose(fp);
}

/* Balance Enquiry */
void balanceEnquiry() {
    FILE *fp;
    struct Account acc;
    int accNo;
    int found = 0;

    fp = fopen("accounts.dat", "rb");
    if(fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&acc, sizeof(acc), 1, fp)) {
        if(acc.accNo == accNo) {
            printf("\nAccount Holder Name: %s", acc.name);
            printf("\nAvailable Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Account not found!\n");

    fclose(fp);
}
