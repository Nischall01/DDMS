#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <tlhelp32.h>

#ifdef _WIN32
#define nap(x) Sleep((x) * 1000) // Sleep function for Windows, takes milliseconds
#else
#define nap(x) sleep(x) // Sleep function for Unix-like systems, takes seconds
#endif

#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

#define FILENAME_SIZE 1024 // Defining value for FILENAME_SIZE
#define MAX_LINE 2048      // Defining value for MAX_LINE
#define CH_LIMIT 40        // Defining value for CH_LIMIT
#define USERNAME_LINE 1
#define PASSWORD_LINE 2
#define EMAIL_LINE 3

// Structures
struct datetime {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} dt;

// Function Declarations
void press();
void menu();
void submenu_userdata();
int getMenuChoice();
void clearInputBuffer();
void hold();
void notriesleft();
void clrs();
void UI();
void dtime(int *, int *, int *, int *, int *, int *);
void login();
void sign_up();
int checkforspaces(char *);
int addrecord();
int openrecord();
int editrecord();
int deleterecord();
int addreminder();
int deletereminder();
int clearreminders();
void editusername();
void editpassword();
void editemailaddress();
int records();
int reminders();
void submenu_reminders();
void checkuserfile();
bool exit_module(const char *);
BOOL isProcessRunning(const char *);

// Universal Variables
int isnotint;
char buffer[MAX_LINE];
char name[CH_LIMIT];  // This variable holds the name
char pass[CH_LIMIT];  // This variable holds the password
char email[CH_LIMIT]; // This variable holds the email address
char line[MAX_LINE];




int main() {
    clrs();
      if (!isProcessRunning("Reminder_notifier.exe"))
    {
        system("start Reminder\\Reminder_notifier.exe");
        getchar();
    }
    checkuserfile();
    login();
    UI();
    return 0;
}

BOOL isProcessRunning(const char* processName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        printf("Error creating snapshot: %lu\n", GetLastError());
        return FALSE;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe32))
    {
        CloseHandle(hSnapshot);
        printf("Error getting first process: %lu\n", GetLastError());
        return FALSE;
    }

    do
    {
        if (strcmp(pe32.szExeFile, processName) == 0)
        {
            CloseHandle(hSnapshot);
            return TRUE;
        }
    } while (Process32Next(hSnapshot, &pe32));

    CloseHandle(hSnapshot);
    return FALSE;
}

void login() {
    int passwordtries = 5;
    int emailtries = 5;
    char enteredpass[CH_LIMIT];
    char enteredeaddy[CH_LIMIT];
    // Extract the username, password and email address from user info file.
    FILE *file;
    file = fopen("Program_files/user_info.dat", "r");
    fscanf(file, "%s %s %s", name, pass, email);
    fclose(file); // File handling STOPs.

    //  Login Page
    int i;
    int namelength = strlen(name);
    printf("\t\t-------------");
    for (i = 0; i < namelength; i++) {
        printf("-");
    }
    printf("\n");
    printf("\t\t| Welcome, %s |", name);
    printf("\n");
    printf("\t\t-------------");
    for (i = 0; i < namelength; i++) {
        printf("-");
    }
    do {
        printf("\n");
        printf("\n\tEnter password => ");
        scanf("%s", enteredpass);
        if (strcmp(enteredpass, pass) == 0) {
            break;
        } else if (strcmp(enteredpass, "EXIT") == 0) {
            clrs();
            printf("\tHave a great Day.");
            nap(1.5);
            exit(0);
        } else if (strcmp(enteredpass, "RESET") == 0) {
            clrs();
            do {
                printf("\nEnter your email address entered during the login or enter 'EXIT' to exit:\n=> ");
                scanf("%s", enteredeaddy);
                if (strcmp(enteredeaddy, email) == 0) {
                    clrs();
                    editpassword();
                    main();
                } else if (strcmp(enteredeaddy, "EXIT") == 0) {
                    main();
                } else {
                    clrs();
                    emailtries--;
                    printf("\nIncorrect Email address. Please try again. Tries left: %d\n", emailtries);
                    if (emailtries == 0) { // if wrong email is entered more than '5' times the program will terminate.
                        notriesleft();
                    }
                }
            } while (emailtries > 0);
            if (emailtries == 0) {
                notriesleft();
            }
        } else {
            passwordtries--;
            clrs();
            printf("\nIncorrect Password, please try again or if you forgot your password enter 'RESET'. Enter 'EXIT' to exit. Tries left: %d", passwordtries);
        }
    } while (passwordtries > 0);

    if (passwordtries == 0) { // if wrong password is entered more than '5' times the program will terminate.
        notriesleft();
    }
}

void UI() {
    clrs();
    while (1) {
        clrs();
        reminders();
        menu();
        int choice1;
        choice1 = getMenuChoice();
        clrs();
        switch (choice1) {
        case 1:
            if (addrecord() == 0) {
                break;
            }
            clrs();
            break;

        case 2:
            while (1) {
                clrs();
                printf("\t|Open a record|\n");
                if (records() == 0) {
                    press();
                    break;
                } else {
                    if (openrecord() == 1) {
                        break;
                    }
                }
            }
            break;

        case 3:
            while (1) {
                clrs();
                printf("\t|Edit a record|\n");
                if (records() == 0) {
                    press();
                    break;
                } else {
                    if (editrecord() == 1) {
                        break;
                    }
                }
            }
            break;

        case 4:
            while (1) {
                clrs();
                printf("\t|Delete a record|\n");
                if (records() == 0) {
                    press();
                    break;
                } else {
                    if (deleterecord() == 1) {
                        break;
                    }
                }
            }

            break;

        case 5:
            while (1) {
                clrs();
                char choice2;
                submenu_userdata();
                printf(" => ");
                scanf(" %c", &choice2); // Added a space before %c to consume any leading whitespace
                switch (choice2) {
                case '1':
                    editusername();
                    continue;
                case '2':
                    editpassword();
                    continue;
                case '3':
                    editemailaddress();
                    continue;
                case '4':
                    break;
                case '.':
                    break;
                default:
                    clrs();
                    printf("Invalid input. Please enter a valid option.");
                    press();
                    continue;
                }
                break;
            }
            break;

        case 6:
            while (1) {
                clrs();
                char choice3;
                submenu_reminders();
                printf(" => ");
                scanf(" %c", &choice3); // Added a space before %c to consume any leading whitespace
                switch (choice3) {
                case '1':
                    addreminder();
                    continue;
                case '2':
                    clrs();
                    if (reminders() == 0) {
                        press();
                        continue;
                    }
                    if (deletereminder() == 0) {
                        printf("Reminder deletion completed successfully.\n");
                    } else {
                        printf("Reminder deletion failed.\n");
                    }
                    continue;
                case '3':
                    clrs();
                    if (reminders() == 0) {
                        press();
                        continue;
                    }
                    clearreminders();
                    continue;
                case '4':
                    break;
                case '.':
                    break;
                default:
                    clrs();
                    printf("Invalid input. Please enter a valid option.");
                    press();
                    continue;
                }
                break;
            }
            break;
        case 7:
            clrs();
            FILE *file;
            file = fopen("README.pdf", "r");
            if (file == NULL) {
                perror("Error! ");
                getchar();
            } else {
                system("README.pdf");
            }
            fclose(file);
            break;
        case 8:
            clrs();
            printf("\tReminder_notifier.exe will run in the background. Check Task Manager to find and close it.");
            nap(3);
            clrs();
            printf("\tHave a great Day.");
            nap(1.5);
            clrs();
            exit(0);
        default:
            clrs();
            printf("Invalid input. Please enter a valid option.");
            press();
            break;
        }
    }
}

// Function Definitions

void clrs()
{
    system("cls");
}

void checkuserfile()
{
    FILE *file;
    file = fopen("Program_files/user_info.dat", "r"); // Opens the file the holds user info to read
    bool isEmptyLine = true;
    int lineCount = 1;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lineCount++;
            if (isEmptyLine)
            {
                printf("Line %d is empty.\n", lineCount);
            }
            isEmptyLine = true;
        }
        else if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
        {
            isEmptyLine = false;
        }
    }
    if (file)
    {
        fseek(file, 0, SEEK_END);        // Move the file pointer to the end of the file
        long file_size = ftell(file);    // Get the position of the file pointer (i.e., the file size)
        if (file_size == 0 || file == 0) // Checks if the file exists or not & if it does, checks if it's empty or not.
        {
            fclose(file);
            sign_up();
        }
        else if (lineCount < 3)
        {
            fclose(file);
            printf("Error in the user file. Please Signup\n");
            printf("\nPress any key to continue !\n");
            getchar();
            sign_up();
        }
    }
    else
    {
        rewind(file);
        file = fopen("Program_files/user_info.dat", "w");
        sign_up();
    }
    fclose(file);
}

void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}

void press()
{
    printf("\n\tPress any key to continue!");
    clearInputBuffer();
    getchar();
    clrs();
}

void menu()
{
    FILE *fp;
    fp = fopen("Program_files/Menu.txt", "r");
    if (fp == NULL)
    {
        perror("Error! ");
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);
    printf("\n");
}

void submenu_userdata()
{
    FILE *fp;
    fp = fopen("Program_files/Submenu_userdata.txt", "r");
    if (fp == NULL)
    {
        perror("Error! ");
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);
    printf("\n");
}

void submenu_reminders()
{
    FILE *fp;
    fp = fopen("Program_files/Submenu_reminders.txt", "r");
    if (fp == NULL)
    {
        perror("Error! ");
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);
    printf("\n");
}

int getMenuChoice()
{
    int choice;
    printf(" => ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        getchar();
        clrs();
        // Clear the input buffer
        clearInputBuffer();
    }
    else
    {
        clearInputBuffer();
        return choice;
    }
}

void notriesleft()
{
    clrs();
    printf("\n\t********** No tries left. **********");
    nap(1.5);
    exit(0);
}

int records()
{
    FILE *file;
    file = fopen("Program_files/Records.dat", "r");
    if (file == NULL)
    {
        fclose(file);
        clrs();
        file = fopen("Program_files/Records.dat", "w");
        fclose(file);
        records();
    }
    printf("\nRecords:\n");
    fseek(file, 0, SEEK_END);     // Move the file pointer to the end of the file
    long file_size = ftell(file); // Get the position of the file pointer (i.e., the file size)
    fclose(file);
    if (file_size == 0)
    {
        printf("There are no records.\n");
        printf("\n");
        return 0;
    }
    else
    {
        file = fopen("Program_files/Records.dat", "r");
        // Read and print the contents character by character until the EOF is reached
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }
        printf("\n");
        fclose(file); // Close the file after reading
        return 1;
    }
}

int reminders()
{
    FILE *file;
    file = fopen("Program_files/Reminders.dat", "r");
    if (file == NULL)
    {
        fclose(file);
        clrs();
        file = fopen("Program_files/Reminders.dat", "w");
        fclose(file);
        reminders();
    }
    printf("\tReminders\n       ```````````\n");
    fseek(file, 0, SEEK_END);     // Move the file pointer to the end of the file
    long file_size = ftell(file); // Get the position of the file pointer (i.e., the file size)
    fclose(file);
    if (file_size == 0)
    {
        printf("There are no reminders.\n");
        printf("\n");
        return 0;
    }
    else
    {
        file = fopen("Program_files/Reminders.dat", "r");
        // Read and print the contents character by character until the EOF is reached
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }
        printf("\n");
        fclose(file); // Close the file after reading
        return 1;
    }
}

void sign_up()
{
    clrs();
    char buffer[MAX_LINE];
    FILE *file;
    file = fopen("Program_files/user_info.dat", "w"); // Open the file in "write" mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    printf("\nPlease enter your username, password, and email address to SIGN UP. [NOTE] - No fields can be empty nor can it contain spaces.\n");

    // Input username

    printf("\nUsername: ");
    if (fgets(buffer, MAX_LINE, stdin) == NULL)
    {
        printf("Error reading input.\n");
        fclose(file);
        return;
    }
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == ' ')
        {
            printf("!!Invalid Input!! Username cannot contain spaces.\n");
            getchar();
            fclose(file);
            sign_up();
        }
    }
    if (strlen(buffer) == 0)
    {
        printf("!! This field cannot be empty.\n");
        getchar();
        fclose(file);
        sign_up();
    }
    strcat(buffer, "\n");
    fputs(buffer, file);

    // Input password
    printf("Password: ");
    if (fgets(buffer, MAX_LINE, stdin) == NULL)
    {
        printf("Error reading input.\n");
        fclose(file);
        return;
    }
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == ' ')
        {
            printf("!!Invalid Input!! Password cannot contain spaces.\n");
            getchar();
            fclose(file);
            sign_up();
        }
    }
    if (strlen(buffer) == 0)
    {
        printf("!! This field cannot be empty.\n");
        getchar();
        fclose(file);
        sign_up();
    }
    strcat(buffer, "\n");
    fputs(buffer, file);

    // Input email address
    printf("Email Address: ");
    if (fgets(buffer, MAX_LINE, stdin) == NULL)
    {
        printf("Error reading input.\n");
        fclose(file);
        return;
    }
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == ' ')
        {
            printf("!!Invalid Input!! Email address cannot contain spaces.\n");
            getchar();
            fclose(file);
            sign_up();
        }
    }
    if (strlen(buffer) == 0)
    {
        printf("!! This field cannot be empty.\n");
        getchar();
        fclose(file);
        sign_up();
    }
    fputs(buffer, file);
    fclose(file);
    clrs();
    printf("Sign up successful!\n");
    press();
    main();
}

int addrecord()
{
    clrs();
    FILE *file, *fp;
    dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);
    char record_name[50];
    char lc_record_name[50];     // To store record_name in lowercase.
    char lc_record_name_txt[50]; // To add .txt on the lowercase record_name
    int record_name_len;
    printf("Record name: ");
    scanf(" %[^\n]", record_name);
    if (exit_module(record_name))
    {
        return 0;
    }
    if (checkforspaces(record_name) == 1)
    {
        clrs();
        printf("Invalid input! A record name shouldn't contain any spaces.");
        getchar();
        clrs();
        return 0;
    }

    // Remove newline character from the input
    size_t len = strlen(record_name);
    if (len > 0 && record_name[len - 1] == '\n')
    {
        record_name[len - 1] = '\0';
    }
    // Initialize lc_record_name to all null characters
    memset(lc_record_name, '\0', sizeof(lc_record_name));
    memset(lc_record_name_txt, '\0', sizeof(lc_record_name_txt));
    // Convert each character to lowercase and store in lc_record_name
    for (int i = 0; record_name[i]; i++)
    {
        lc_record_name[i] = tolower((unsigned char)record_name[i]);
        lc_record_name_txt[i] = tolower((unsigned char)record_name[i]);
    }

    if (fopen(strcat(lc_record_name_txt, ".txt"), "r") != NULL)
    {
        clrs();
        printf("%s already exists.", lc_record_name_txt);
        hold();
        return 0;
    }

    // Add the record in the record entry
    file = fopen("Program_files/Records.dat", "a");
    fprintf(file, "(%d-%02d-%02d) %s\n", dt.year, dt.month, dt.day, lc_record_name);
    fclose(file);

    strcat(record_name, ".txt");
    printf("\n%s\n", record_name);
    file = fopen(record_name, "w");
    if (file != NULL)
    {
        // Print Record name, Date & Time onto the file
        fprintf(file, "Record Name: %s\n", record_name);
        fprintf(file, "Date: %d-%02d-%02d\n", dt.year, dt.month, dt.day);
        fprintf(file, "Time: %02d:%02d:%02d\n", dt.hour, dt.min, dt.sec);

        // Enter the record data
        char record_data[100];
        printf("=> ");
        scanf(" %[^\n]", record_data);
        if (exit_module(record_data))
        {
            return 0;
        }
        // Add the record text to the new record file
        fprintf(file, "\n%s", record_data);
        fclose(file);
        printf("\nNew record added successfully.");
        hold();
        clrs();
    }
    else
    {
        printf("Error: Unable to create the record file.\n");
        hold();
        clrs();
    }
    fclose(file);
}

int openrecord()
{
    char record[50];
    printf("=> ");
    scanf("%s", record);
    if (exit_module(record))
    {
        return 1;
    }
    strcat(record, ".txt");
    FILE *file;
    file = fopen(record, "r");
    if (file == NULL)
    {
        perror("\nError! ");
        hold();
    }
    else
    {
        // Read and print the contents character by character until the end of file (EOF) is reached
        clrs();
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }
        printf("\n\n");
        hold();
        fclose(file);
        return 0;
    }
}

int editrecord()
{
    char record[50];
    printf("=> ");
    scanf("%s", record);
    if (exit_module(record))
    {
        return 1;
    }
    strcat(record, ".txt");
    FILE *file;
    file = fopen(record, "r");
    if (file == NULL)
    {
        perror("\nError! ");
        hold();
    }
    else
    {
        printf("%s\n", record);
        system(record);
        printf("\nThe record is sucessfully edited.");
        hold();
        clrs();
        return 0;
    }
    fclose(file);
}

int deleterecord()
{
    char recordToDelete[100];
    char record[100];
    printf("=> ");
    scanf("%s", recordToDelete); // Reading user input, limiting the word to 99 characters
    if (exit_module(recordToDelete))
    {
        return 1;
    }
    strcpy(record, recordToDelete);
    strcat(record, ".txt");
    FILE *file;
    file = fopen(record, "r");
    if (file == NULL)
    {
        perror("\nError! ");
        hold();
        fclose(file);
    }
    else
    {
        fclose(file);
        remove(record);
        FILE *originalFile, *tempFile;
        char line[256];

        // Open the original record file in read mode
        originalFile = fopen("Program_files/Records.dat", "r");
        if (originalFile == NULL)
        {
            perror("Error! \n");
            hold();
        }

        // Open a temporary record file in write mode
        tempFile = fopen("temp.dat", "w");
        if (tempFile == NULL)
        {
            perror("Error! \n");
            hold();
            fclose(originalFile);
        }

        // Read lines from the original file, and write to the temporary file
        while (fgets(line, sizeof(line), originalFile) != NULL)
        {
            if (strstr(line, recordToDelete) == NULL)
            {
                fputs(line, tempFile);
            }
        }

        // Close both files
        fclose(originalFile);
        fclose(tempFile);

        // Delete the original file
        remove("Program_files/Records.dat");

        // Rename the temporary file to the original file name
        if (rename("temp.dat", "Program_files/Records.dat") != 0)
        {
            printf("Error renaming the temporary file.\n");
        }
        printf("\nThe record has been deleted successfully.");
        hold();
        clrs();
        return 0;
    }
}

int addreminder()
{
    clrs();
    char when[2];

    dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);
    char reminder_title[50], date[15];
    int month, day, hour, minute;
    int hour1, minute1;
    int intid;
    int oldintid;
    char stringid[5];
    printf("Reminder Id: ");
    scanf("%d", &intid);
    sprintf(stringid, "%d", intid);
    if (exit_module(stringid))
    {
        return 0;
    }
    // Check if the id is longer than 3 letters.
    if (strlen(stringid) > 3)
    {
        clrs();
        printf("Invalid input! Ids shouldn't be longer than 3 letters.");
        hold();
        return 0;
    }
    // Check if the ID already exists
    FILE *fp;
    fp = fopen("Program_files/Reminders.dat", "r");
    // Read and check the first 5 characters of each line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(stringid, line, strlen(stringid)) == 0)
        {
            clrs();
            printf("A reminder with Id '%d' already exits. Enter a unique Id.", intid);
            hold();
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);

    printf("Reminder Title: ");
    scanf(" %[^\n]", reminder_title);
    if (exit_module(reminder_title))
    {
        return 0;
    }
    printf("\n1. Today\n");
    printf("2. Tommorrow\n");
    printf("3. Day\n");
    printf("4. Month and day\n");
    printf("=> ");
    scanf("%s", when);
    if (exit_module(when))
    {
        return 0;
    }
    switch (when[0])
    {
    case '1':
        strcpy(date, "Today");
        FILE *ft;
        ft = fopen("Program_files/Today.txt", "w");

        printf("\t{Due time}\n");
        printf("Hour: ");
        scanf("%d", &hour1);
        if (hour1 > 24)
        {
            printf("Please enter a valid value.");
            clrs();
            addreminder();
        }
        printf("Minute: ");
        scanf("%d", &minute1);
        if (minute1 > 60)
        {
            printf("Please enter a valid value.");
            clrs();
            addreminder();
        }
        fprintf(ft, "%d %d %s\n", hour1, minute1, reminder_title);
        fclose(ft);
        FILE *file;
        file = fopen("Program_files/Reminders.dat", "a");
        fprintf(file, "%d (%s) (%d:%d) %s \n", intid, date, hour1, minute1, reminder_title);
        fclose(file);
        printf("\nNew reminder added successfully.");
        hold();
        return 0;
        break;

    case '2':
        strcpy(date, "Tommorrow");
        break;
    case '3':
        printf("Enter Day: ");
        scanf("%d", &day);
        if (day > 30)
        {
            clrs();
            printf("Please, enter a valid month.\n");
            hold();
            clrs();
            clearInputBuffer();
            addreminder();
        }
        sprintf(date, "%d/%d", day, dt.month);
        break;
    case '4':
        printf("Enter Month: ");
        scanf("%d", &month);
        if (month > 12)
        {
            clrs();
            printf("Please, enter a valid month.\n");
            hold();
            clrs();
            clearInputBuffer();
            addreminder();
        }
        break;
    default:
        break;
    }

    printf("\t{Due time}\n");
    printf("Hour: ");
    scanf("%d", &hour);
    if (hour > 24)
    {
        printf("Please enter a valid value.");
        clrs();
        addreminder();
    }
    printf("Minute: ");
    scanf("%d", &minute);
    if (minute > 60)
    {
        printf("Please enter a valid value.");
        clrs();
        addreminder();
    }

    FILE *file;
    file = fopen("Program_files/Reminders.dat", "a");
    fprintf(file, "%d (%s) (%d:%d) %s \n", intid, date, hour, minute, reminder_title);
    fclose(file);
    printf("\nNew reminder added successfully.");
    hold();
}

int deletereminder()
{
    char idToDelete[5];
    printf("Enter the ID of the reminder to be deleted: ");
    scanf("%4s", idToDelete);
    char tempFileName[] = "temp.dat";
    FILE *originalFile, *tempFile;
    // Open the original record file in read mode
    originalFile = fopen("Program_files/Reminders.dat", "r");
    if (originalFile == NULL)
    {
        perror("Error opening the original file");
        hold();
        return 1;
    }
    // Open a temporary record file in write mode
    tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL)
    {
        perror("Error opening the temporary file");
        hold();
        fclose(originalFile);
        return 1;
    }
    char line[256];  // Adjust the buffer size as needed
    int deleted = 0; // Flag to track if a reminder was deleted

    while (fgets(line, sizeof(line), originalFile) != NULL)
    {
        // Remove trailing newline characters if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Check if the line contains the ID to be deleted
        if (strncmp(idToDelete, line, strlen(idToDelete)) != 0)
        {
            fprintf(tempFile, "%s\n", line);
        }
        else
        {
            deleted = 1; // Set the flag if a reminder is deleted
        }
    }
    // Close both files
    fclose(originalFile);
    fclose(tempFile);
    // Check if a reminder was deleted
    if (!deleted)
    {
        clrs();
        printf("No reminder with ID '%s' found.\n", idToDelete);
        hold();
        remove(tempFileName); // Delete the temporary file
        return 1;
    }
    // Delete the original file
    if (remove("Program_files/Reminders.dat") != 0)
    {
        perror("Error deleting the original file");
        hold();
        return 1;
    }
    // Rename the temporary file to the original file name
    if (rename(tempFileName, "Program_files/Reminders.dat") != 0)
    {
        perror("Error renaming the temporary file");
        hold();
        return 1;
    }
    clrs();
    printf("The reminder with ID '%s' has been deleted successfully.\n", idToDelete);
    hold();
    return 0;
}

int clearreminders()
{
    char yorn[2];
    printf("Are you sure? y/n\n=>");
    scanf("%s", yorn);
    if (strcmp(yorn, "y") == 0)
    {
        FILE *fp = fopen("Program_files/Reminders.dat", "w");
        fclose(fp);
        clrs();
        printf("The Reminders are cleared.");
    }
    else if (strcmp(yorn, "n") == 0)
    {
        return 0;
    }
    else
    {
        printf("Error! Invalid input.");
    }
    hold();
    clrs();
}

void editusername()
{
    clrs();
    char replacement[50];
    printf("Enter new username: ");
    scanf("%s", replacement);

    FILE *original;
    FILE *temp;
    original = fopen("Program_files/user_info.dat", "r");
    temp = fopen("temp.dat", "w");

    if (original == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        return;
    }
    char buffer[MAX_LINE];
    int current_line = 1;

    while (fgets(buffer, MAX_LINE, original) != NULL)
    {
        if (current_line == 1)
        {
            // Replace the content of the 1st line with the replacement
            fputs(replacement, temp);
            fputs("\n", temp); // Add a new line after the replacement
        }
        else
        {
            // Write other lines as they are to the output file
            fputs(buffer, temp);
        }
        current_line++;
    }
    fclose(original); // Close the original file after reading
    fclose(temp);
    if (remove("Program_files/user_info.dat") != 0)
    {
        perror("Error removing the file!");
        printf("\nError no.%d\n", errno);
    }
    if (rename("temp.dat", "Program_files/user_info.dat") != 0)
    {
        perror("Error renaming the file!");
        printf("\nError no.%d\n", errno);
    }
    clrs();
    printf("\tUsername replaced successfully.\n");
    hold();
}

void editpassword()
{
    clrs();
    char replacement[50];
    printf("Enter new password: ");
    scanf("%s", replacement);

    FILE *original;
    FILE *temp;
    original = fopen("Program_files/user_info.dat", "r");
    temp = fopen("temp.dat", "w");

    if (original == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        return;
    }

    char buffer[MAX_LINE];
    int current_line = 1;

    while (fgets(buffer, MAX_LINE, original) != NULL)
    {
        if (current_line == 2)
        {
            // Replace the content of the 1st line with the replacement
            fputs(replacement, temp);
            fputs("\n", temp); // Add a new line after the replacement
        }
        else
        {
            // Write other lines as they are to the output file
            fputs(buffer, temp);
        }
        current_line++;
    }
    fclose(original); // Close the original file after reading
    fclose(temp);
    if (remove("Program_files/user_info.dat") != 0)
    {
        perror("Error removing the file!");
        printf("\nError no.%d\n", errno);
    }
    if (rename("temp.dat", "Program_files/user_info.dat") != 0)
    {
        perror("Error renaming the file!");
        printf("\nError no.%d\n", errno);
    }
    clrs();
    printf("\tPassword replaced successfully.\n");
    hold();
}

void editemailaddress()
{
    clrs();
    char replacement[50];
    printf("Enter new email address: ");
    scanf("%s", replacement);

    FILE *original;
    FILE *temp;
    original = fopen("Program_files/user_info.dat", "r");
    temp = fopen("temp.dat", "w");

    if (original == NULL || temp == NULL)
    {
        printf("Error opening files.\n");
        return;
    }

    char buffer[MAX_LINE];
    int current_line = 1;

    while (fgets(buffer, MAX_LINE, original) != NULL)
    {
        if (current_line == 3)
        {
            // Replace the content of the 1st line with the replacement
            fputs(replacement, temp);
            fputs("\n", temp); // Add a new line after the replacement
        }
        else
        {
            // Write other lines as they are to the output file
            fputs(buffer, temp);
        }
        current_line++;
    }
    fclose(original); // Close the original file after reading
    fclose(temp);
    if (remove("Program_files/user_info.dat") != 0)
    {
        perror("Error removing the file!");
        printf("\nError no.%d\n", errno);
    }
    if (rename("temp.dat", "Program_files/user_info.dat") != 0)
    {
        perror("Error renaming the file!");
        printf("\nError no.%d\n", errno);
    }
    clrs();
    printf("Email address replaced successfully.\n");
    hold();
}

bool exit_module(const char *filename)
{
    if (strcmp(filename, ".") == 0)
    {
        return true; // File exists
    }
    return false; // File doesn't exist
}

void hold()
{
    clearInputBuffer();
    getchar();
}

void dtime(int *y, int *m, int *d, int *h, int *mi, int *s)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    *y = t.wYear;
    *m = t.wMonth;
    *d = t.wDay;
    *h = t.wHour;
    *mi = t.wMinute;
    *s = t.wSecond;
}

int checkforspaces(char *record_name)
{
    int i;
    size_t len = strlen(record_name);
    for (i = 0; i < len; i++)
    {
        if (record_name[i] == ' ')
        {
            return 1;
        }
    }
}