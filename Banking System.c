#include <stdio.h>
#include <windows.h>
#include <conio.h>

struct account
{
    char name[20];
    int age;
    char father[20], mother[20], address[40];
    unsigned long long number;
};
int string_check(char *words)
{
    int i, j;
    j = strlen(words);
    if (j < 3)
    {
        return 1;
    }
    for (i = 0; i < j; i++)
    {
        if (isalpha(*(words + i)) == 0)
        {
            if (*(words + i) != ' ')
            {
                return 1;
            }
        }
    }
    return 0;
}
void file_check()
{
    FILE *fp;
    fp = fopen("main", "r");
    if (fp == NULL)
    {
        fp = fopen("main", "w");
        putw(34576532, fp);
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
}
void create_account()
{
    struct account ac;
    FILE *fp;
    int user_account;
    char filename[10], check;
    system("cls");
    printf("%47s\n\n\n\n", "Create Account");
    printf("%55s", "Press enter to continue . . . ");
    check = getch();
    if (check != 13)
        return;
    file_check();
    system("cls");
    printf("%47s\n\n", "Create Account");
    printf("Enter your name : ");
    gets(ac.name);
    while (string_check(ac.name))
    {
        printf("\nYou have not entered a correct name, press any key to enter it again . . .");
        getch();
        printf("\nEnter your name : ");
        gets(ac.name);
    }
    printf("Enter your age : ");
    scanf("%d", &ac.age);
    fflush(stdin);
    while (ac.age < 1 || ac.age > 120)
    {
        printf("\nYou have not entered a correct age, press any key to enter it again . . .");
        getch();
        printf("\nEnter your age : ");
        scanf("%d", &ac.age);
        fflush(stdin);
    }
    printf("Enter your father's name : ");
    gets(ac.father);
    while (string_check(ac.father))
    {
        printf("\nYou have not entered a correct name, press any key to enter it again . . .");
        getch();
        printf("\nEnter your father's name : ");
        gets(ac.father);
    }
    printf("Enter your mother's name : ");
    gets(ac.mother);
    while (string_check(ac.mother))
    {
        printf("\nYou have not entered a correct name, press any key to enter it again . . .");
        getch();
        printf("\nEnter your mother's name : ");
        gets(ac.mother);
    }
    printf("Enter your address : ");
    gets(ac.address);
    while (strlen(ac.address) < 10)
    {
        printf("\nPlease enter your full address, press any key to enter it again . . .");
        getch();
        printf("\nEnter your address : ");
        gets(ac.address);
    }
    printf("Enter your phone number : ");
    scanf("%llu", &ac.number);
    fflush(stdin);
    while (ac.number <= 5999999999 || ac.number >= 10000000000)
    {
        printf("\nYou have not entered a correct number, press any key to re-enter the number . . .");
        getch();
        printf("\nEnter your phone number : ");
        scanf("%llu", &ac.number);
        fflush(stdin);
    }
    fp = fopen("main", "r+");
    user_account = getw(fp);
    itoa(user_account, filename, 10);
    ++user_account;
    rewind(fp);
    putw(user_account, fp);
    fclose(fp);
    printf("\nYour Account Number : \"%s\".\nCarefully save it for future activities.", filename);
    printf("\n\nPress any key to return to main menu . . .");
    fp = fopen(filename, "w");
    fwrite(&ac, sizeof(ac), 1, fp);
    putw(0, fp);
    fclose(fp);
    getch();
}
void check_transaction()
{
    FILE *fp;
    int user_account, balance, money;
    char filename[10], status[10];
    SYSTEMTIME stime;
    system("cls");
    printf("%49s", "Check Transaction");
    printf("\n\nEnter your Account Number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again . . .");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nAccount not found, press any key to return to main menu");
        getch();
        return;
    }
    fseek(fp, 118, 1);
    printf("\n   Date        Time      Status    Money    Balance");
    while (getc(fp) != EOF)
    {
        fseek(fp, -1L, 1);
        fread(&stime, sizeof(stime), 1, fp);
        fprintf(stdout, "\n%02d-%02d-%d", stime.wDay, stime.wMonth, stime.wYear);
        fprintf(stdout, "   %02d:%02d:%02d   ", stime.wHour, stime.wMinute, stime.wSecond);
        fgets(status, 9, fp);
        money = getw(fp);
        balance = getw(fp);
        fseek(fp, 2L, 1);
        fprintf(stdout, "%-10s %d      %d", status, money, balance);
    }
    printf("\n\nPress any key to continue . . . ");
    getch();
}
void cash_withdrawal()
{
    SYSTEMTIME stime;
    FILE *fp;
    char filename[10], check, name[20], father_name[20], mother_name[20];
    int withdraw = 0, user_account, balance;
    system("cls");
    printf("%47s\n\n", "Cash Withdrawal");
    printf("Enter the account number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nAccount not found, press any key to return to main menu");
        getch();
        return;
    }
    fread(&name, 20, 1, fp);
    fseek(fp, 4, 1);
    fread(&father_name, 20, 1, fp);
    fread(&mother_name, 20, 1, fp);
    printf("*******Detail of Account Holder*******\n\n");
    printf("Name : %s\n", name);
    printf("Father Name : %s\n", father_name);
    printf("Mother Name : %s\n\n", mother_name);
    printf("Do you want to withdraw from this account(y/n) : ");
    check = getchar();
    fflush(stdin);
    if (check == 'n')
    {
        fclose(fp);
        return;
    }
    printf("Enter the amount to withdraw : ");
    scanf("%d", &withdraw);
    fflush(stdin);
    while (withdraw == 0)
    {
        printf("Please enter a correct amount, press any to enter it again . . .");
        getch();
        printf("Enter the amount to withdraw : ");
        scanf("%d", &withdraw);
        fflush(stdin);
    }
    fseek(fp, -4, 2);
    balance = getw(fp);
    if (balance < withdraw)
    {
        printf("Balance is insufficient, press any to return to main menu");
        fclose(fp);
        getch();
        return;
    }
    fclose(fp);
    fp = fopen(filename, "a");
    balance -= withdraw;
    GetLocalTime(&stime);
    putc('\n', fp);
    fwrite(&stime, sizeof(stime), 1, fp);
    fputs("withdraw", fp);
    putw(withdraw, fp);
    putw(balance, fp);
    printf("\nCash withdraw successfully, press any to return to main menu");
    fclose(fp);
    getch();
}
void cash_deposit()
{
    SYSTEMTIME stime;
    int deposit, user_account, balance;
    char check, filename[10], name[20], father_name[20], mother_name[20];
    FILE *fp;
    system("cls");
    printf("%46s\n\n", "Cash Deposit");
    printf("Enter your account number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nAccount not found, press any key to return to main menu");
        getch();
        return;
    }
    fread(&name, 20, 1, fp);
    fseek(fp, 4, 1);
    fread(&father_name, 20, 1, fp);
    fread(&mother_name, 20, 1, fp);
    printf("*******Detail of Account Holder*******\n\n");
    printf("Name : %s\n", name);
    printf("Father Name : %s\n", father_name);
    printf("Mother Name : %s\n\n", mother_name);
    printf("Do you want to deposit to this account(y/n) : ");
    check = getchar();
    fflush(stdin);
    if (check == 'n')
    {
        fclose(fp);
        return;
    }
    printf("\nEnter the amount to deposit : ");
    scanf("%d", &deposit);
    fseek(fp, -4, 2);
    balance = getw(fp);
    balance += deposit;
    fclose(fp);
    fp = fopen(filename, "a");
    GetLocalTime(&stime);
    putc('\n', fp);
    fwrite(&stime, sizeof(stime), 1, fp);
    fputs("deposit ", fp);
    putw(deposit, fp);
    putw(balance, fp);
    printf("\nYour money have been deposited, press any to return to main menu");
    fclose(fp);
    getch();
}
void view_account()
{
    struct account ac;
    FILE *fp;
    int user_account;
    char filename[10];
    system("cls");
    printf("%46s", "View Account");
    printf("\n\nEnter your Account Number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Account not found, press any key to return to main menu");
        getch();
        return;
    }
    fread(&ac, sizeof(ac), 1, fp);
    printf("*******Detail of Account Holder*******\n\n");
    printf("Name : %s\n", ac.name);
    printf("Age : %d\n", ac.age);
    printf("Father Name : %s\n", ac.father);
    printf("Mother Name : %s\n", ac.mother);
    printf("Address : %s\n", ac.address);
    printf("Phone Number : %llu\n\n", ac.number);
    printf("Press any key to return . . .");
    fclose(fp);
    getch();
}
void name_update(FILE *fp)
{
    char name[20];
    system("cls");
    printf("%50s\n\n", "Account Name Update");
    printf("Enter your name : ");
    gets(name);
    while (string_check(name))
    {
        printf("\nYou have not entered a correct name, press any key to enter it again");
        getch();
        printf("\nEnter your name : ");
        gets(name);
    }
    rewind(fp);
    fwrite(&name, 20, 1, fp);
    printf("\nAccount Name updated successfully,\nCheck complete details in the \"view account\" option\n\n");
    printf("Press any to return to update main menu");
    getch();
}
void age_update(FILE *fp)
{
    int age;
    system("cls");
    printf("%48s\n\n", "Account Age Update");
    printf("Enter your age : ");
    scanf("%d", &age);
    fflush(stdin);
    while (age < 1 || age > 120)
    {
        printf("\nYou have not entered a correct age, press any key to enter it again");
        getch();
        printf("\nEnter your age : ");
        scanf("%d", &age);
        fflush(stdin);
    }
    fseek(fp, 20, 0);
    fwrite(&age, 4, 1, fp);
    printf("\nAge updated successfully,\nCheck complete details in the \"view account\" option\n\n");
    printf("Press any to return to update main menu");
    getch();
}
void fathername_update(FILE *fp)
{
    char father[20];
    system("cls");
    printf("%53s\n\n", "Account Father Name Update");
    printf("Enter your father's name : ");
    gets(father);
    while (string_check(father))
    {
        printf("\nYou have not entered a correct name, press any key to enter it again");
        getch();
        printf("\nEnter your father's name : ");
        gets(father);
    }
    fseek(fp, 24, 0);
    fwrite(&father, 20, 1, fp);
    printf("\nFather Name updated successfully,\nCheck complete details in the \"view account\" option\n\n");
    printf("Press any to return to update main menu");
    getch();
}
void mothername_update(FILE *fp)
{
    char mother[20];
    system("cls");
    printf("%53s\n\n", "Account Mother Name Update");
    printf("Enter your mother's name : ");
    gets(mother);
    while (string_check(mother))
    {
        printf("\nYou have not entered a correct name, press any key to enter it again");
        getch();
        printf("\nEnter your mother's name : ");
        gets(mother);
    }
    fseek(fp, 44, 0);
    fwrite(&mother, 20, 1, fp);
    printf("\nMother Name updated successfully,\ncheck complete details in the \"view account\" option\n\n");
    printf("Press any to return to update main menu");
    getch();
}
void address_update(FILE *fp)
{
    char address[40];
    system("cls");
    printf("%51s\n\n", "Account Address Update");
    printf("Enter your address : ");
    gets(address);
    while (strlen(address) < 10)
    {
        printf("\nPlease entered your full address, press any key to enter it again . . .");
        getch();
        printf("\nEnter your address : ");
        gets(address);
    }
    fseek(fp, 64, 0);
    fwrite(&address, 40, 1, fp);
    printf("\nAddress updated successfully,\nCheck complete details in the \"view account\" option\n\n");
    printf("Press any to return to update main menu");
    getch();
}
void phonenumber_update(FILE *fp)
{
    unsigned long long number;
    system("cls");
    printf("%53s\n\n", "Account Phone Number Update");
    printf("Enter your phone number : ");
    scanf("%llu", &number);
    fflush(stdin);
    while (number <= 5999999999 || number >= 10000000000)
    {
        printf("\nYou have not entered a correct number, press any key to re-enter the number . . .");
        getch();
        printf("\nEnter your phone number : ");
        scanf("%llu", &number);
        fflush(stdin);
    }
    fseek(fp, 104, 0);
    fwrite(&number, 8, 1, fp);
    printf("\nPhone Number updated successfully,\nCheck complete details in the \"view account\" option\n\n");
    printf("Press any to return to update main menu");
    getch();
}
void update_account()
{
    FILE *fp;
    int user_account;
    char filename[10], check;
    system("cls");
    printf("%51s\n\n", "Update Account Details");
    printf("Enter your Account Number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("Account not found, press any key to return to main menu");
        getch();
        return;
    }
    while (1)
    {
        system("cls");
        printf("%53s\n\n", "Update account details menu");
        printf("%-40s%s\n", "[1] - Name update", "[2] - Age update");
        printf("%-40s%s\n", "[3] - Father Name update", "[4] - Mother Name update");
        printf("%-40s%s\n%s", "[5] - Address update", "[6] - Phone Number update", "[7] - Main Menu");
        printf("\n\nEnter your choice : ");
        check = getchar();
        fflush(stdin);
        if (check == '1')
        {
            name_update(fp);
        }
        else if (check == '2')
        {
            age_update(fp);
        }
        else if (check == '3')
        {
            fathername_update(fp);
        }
        else if (check == '4')
        {
            mothername_update(fp);
        }
        else if (check == '5')
        {
            address_update(fp);
        }
        else if (check == '6')
        {
            phonenumber_update(fp);
        }
        else if (check == '7')
        {
            fclose(fp);
            return;
        }
        else
        {
            printf("Wrong Choice, press any key to re-enter choice");
            getch();
        }
    }
}
void delete_account()
{
    FILE *fp;
    int user_account;
    char filename[10], name[20], father_name[20], mother_name[20], check;
    system("cls");
    printf("%47s\n\n", "Delete Account");
    printf("Enter Account Number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Account not found, press any key to return to main menu");
        getch();
        return;
    }
    fread(&name, 20, 1, fp);
    fseek(fp, 4, 1);
    fread(&father_name, 20, 1, fp);
    fread(&mother_name, 20, 1, fp);
    printf("*******Detail of Account Holder*******\n\n");
    printf("Name : %s\n", name);
    printf("Father Name : %s\n", father_name);
    printf("Mother Name : %s\n", mother_name);
    printf("\nDo you want to delete this account(y/n) : ");
    check = getchar();
    fflush(stdin);
    if (check == 'y')
    {
        char verify;
        fclose(fp);
        printf("\nDo you really want to delete this account");
        printf("\nDeleting this account will delete all data about this account\n");
        printf("\nNow, you want to delete this account(y/n) : ");
        verify = getchar();
        if (verify == 'y')
        {
            remove(filename);
            printf("Account deleted successfully, press any key to continue . . ");
            getch();
        }
    }
}
void check_balance()
{
    FILE *fp;
    char name[20], father_name[20], mother_name[20], filename[10], check;
    int user_account, balance;
    system("cls");
    printf("%46s\n\n", "Check Balance");
    printf("Enter your account number : ");
    scanf("%d", &user_account);
    fflush(stdin);
    while (user_account < 34576532 || user_account > 99999999)
    {
        printf("\nYou have not entered a correct account number, press any key to enter it again");
        getch();
        printf("\nEnter your Account Number : ");
        scanf("%d", &user_account);
        fflush(stdin);
    }
    itoa(user_account, filename, 10);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Account not found, press any key to return to main menu");
        getch();
        return;
    }
    fread(&name, 20, 1, fp);
    fseek(fp, 4, 1);
    fread(&father_name, 20, 1, fp);
    fread(&mother_name, 20, 1, fp);
    printf("*******Detail of Account Holder*******\n\n");
    printf("Name : %s\n", name);
    printf("Father Name : %s\n", father_name);
    printf("Mother Name : %s\n\n", mother_name);
    printf("Do you want to check balance of this account(y/n) : ");
    check = getchar();
    fflush(stdin);
    if (check == 'y')
    {
        fseek(fp, -4, 2);
        balance = getw(fp);
        printf("\nYour account : %s balance is Rs %d", filename, balance);
        printf("\n\nPress any key to continue . . .");
        getch();
    }
    fclose(fp);
}
void main()
{
    while (1)
    {
        char che;
        system("cls");
        fflush(stdin);
        printf("%39s\n\n", "Welcome to the Bank");
        printf("%-40s%s\n", "[1] - Create Account", "[2] - Check Transactions");
        printf("%-40s%s\n", "[3] - Cash Withdrawal", "[4] - Cash Deposit");
        printf("%-40s%s\n", "[5] - View Account", "[6] - Update Account");
        printf("%-40s%s\n%s", "[7] - Delete Account", "[8] - Check Balance", "[9] - Exit");
        printf("\nEnter your choice : ");
        che = getchar();
        fflush(stdin);
        if (che == '1')
        {
            create_account();
        }
        else if (che == '2')
        {
            check_transaction();
        }
        else if (che == '3')
        {
            cash_withdrawal();
        }
        else if (che == '4')
        {
            cash_deposit();
        }
        else if (che == '5')
        {
            view_account();
        }
        else if (che == '6')
        {
            update_account();
        }
        else if (che == '7')
        {
            delete_account();
        }
        else if (che == '8')
        {
            check_balance();
        }
        else if (che == '9')
        {
            exit(0);
        }
        else
        {
            printf("Wrong Choice, press any key to re-enter choice");
            getch();
        }
    }
}