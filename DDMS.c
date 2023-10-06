#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#define nap(x) Sleep(x * 1000) // Define nap for Windows
#else
#include <unistd.h>
#define nap(x) sleep(x) // Define nap for UNIX
#endif
#include <unistd.h>
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
struct datetime
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} dt;

// Function Declarations
void press();
int main();
void menu();
void submenu_userdata();
int getMenuChoice();
int wanttocontinue();
void clearInputBuffer();
void hold();
void notriesleft();
void clrs();
void UI();
void dtime(int *, int *, int *, int *, int *, int *);
void sign_up();
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

// Universal Variables
int tries = 5;
int isnotint;
char buffer[MAX_LINE];
char name[CH_LIMIT];  // This variable holds the name
char pass[CH_LIMIT];  // This variable holds the password
char email[CH_LIMIT]; // This variable holds the email address
char line[MAX_LINE];

// Main Function
int main()
{
    clrs();
    checkuserfile();
    int choice, choice2;
    char enteredpass[CH_LIMIT];
    char enteredeaddy[CH_LIMIT];
    // Extract the username, password and email address.
    FILE *file;
    file = fopen("Program_files/user_info.dat", "r");
    fscanf(file, "%s %s %s", name, pass, email);
    fclose(file); // File handling STOPs.

    //  Login Page
    printf("\t\tWelcome, %s\n", name);
    while (1)
    {
        printf("\n\tEnter the password => ");
        scanf("%s", enteredpass);
        if (strcmp(enteredpass, pass) == 0)
        {
            clrs();
            UI();
        }
        else if (strcmp(enteredpass, "RESET") == 0)
        {
            clrs();
            int trys = 5;
        try_email:
            printf("\nEnter your email address entered during the login or enter 'EXIT' to exit:\n=> ");
            scanf("%s", enteredeaddy);
            if (strcmp(enteredeaddy, email) == 0)
            {
                clrs();
                editpassword();
                main();
            }
            else if (strcmp(enteredeaddy, "EXIT") == 0)
            {
                main();
            }
            else
            {
                clrs();
                trys--;
                printf("\nIncorrect email address. Please try again. Tries left: %d\n", trys);
                if (trys == 0) // if wrong password is entered more than '5' times the program will terminate.
                {
                    notriesleft();
                }
                goto try_email;
                break;
            }
        }
        else
        {
            tries--;
            clrs();
            printf("\nIncorrect, please try again or if you forgot your password enter 'RESET'. Tries left: %d", tries);
            if (tries == 0) // if wrong password is entered more than '5' times the program will terminate.
            {
                notriesleft();
            }
            continue;
        }
    }
    return 0;
}

void UI()
{
    int choice;
    while (1)
    {
        int choice;
        clrs();
        reminders();
        menu();
        choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            clrs();
            if (addrecord() == 0)
            {
                break;
            }
            clrs();
            break;

        case 2:
            while (1)
            {
                clrs();
                printf("\t|Open a record|\n");
                if (records() == 0)
                {
                    press();
                    break;
                }
                else
                {
                    if (openrecord() == 1)
                    {
                        break;
                    }
                }
            }
            break;

        case 3:
            while (1)
            {
                clrs();
                printf("\t|Edit a record|\n");
                if (records() == 0)
                {
                    press();
                    break;
                }
                else
                {
                    if (editrecord() == 1)
                    {
                        break;
                    }
                }
            }
            break;

        case 4:
            while (1)
            {
                clrs();
                printf("\t|Delete a record|\n");
                if (records() == 0)
                {
                    press();
                    break;
                }
                else
                {
                    if (deleterecord() == 1)
                    {
                        break;
                    }
                }
            }

            break;

        case 5:
            clrs();
            while (1)
            {
                clrs();
                int choice2;
                submenu_userdata();
                choice2 = getMenuChoice();
                switch (choice2)
                {
                case 1:
                    editusername();
                    continue;
                case 2:
                    editpassword();
                    continue;
                case 3:
                    editemailaddress();
                    continue;
                case 4:
                    clrs();
                    break;
                default:
                    clrs();
                    printf("\tInvalid input. Please enter a valid option.");
                    getchar();
                    clrs();
                    continue;
                }
                break;
            }
            break;

        case 6:
            clrs();
            while (1)
            {
                clrs();
                int choice3;
                submenu_reminders();
                choice3 = getMenuChoice();
                switch (choice3)
                {
                case 1:
                    clrs();
                    addreminder();
                    continue;
                case 2:
                    clrs();
                    if (reminders() == 0)
                    {
                        press();
                        continue;
                        ;
                    }
                    deletereminder();
                    continue;
                case 3:
                    clrs();
                    if (reminders() == 0)
                    {
                        press();
                        continue;
                    }
                    clearreminders();
                    continue;
                case 4:
                    clrs();
                    break;
                default:
                    clrs();
                    printf("\tInvalid input. Please enter a valid option.");
                    getchar();
                    clrs();
                    continue;
                }
                break;
            }
            break;
        case 7:
            clrs();
            FILE *file;
            file = fopen("README.pdf", "r");
            if (file == NULL)
            {
                perror("Error! ");
                getchar();
            }
            else
            {
                system("README.pdf");
            }
            fclose(file);
            break;
        case 8:
            clrs();
            printf("\tHave a great Day.");
            nap(1.7);
            exit(0);
        default:
            clrs();
            printf("\tInvalid input. Please enter a valid option.");
            getchar();
            clrs();
            break;
        }
    }
}

// Function Definitions
void checkuserfile()
{
    FILE *file;
    file = fopen("Program_files/user_info.dat", "r+"); // Opens the file the holds user info to read
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
            printf("Error in the user file. Please Signup\n");
            printf("\nPress any key to continue !\n");
            getchar();
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
void clrs()
{
    system("cls");
    printf("\033[H\033[J");
}
void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}
void press()
{
    printf("\nPress any key to continue !\n");
    getchar();
    clrs();
}
void menu()
{
    printf("1. Add a new record\n");
    printf("2. Open a record\n");
    printf("3. Edit a record\n");
    printf("4. Delete a record\n");
    printf("5. Edit User data\n");
    printf("6. Reminders\n");
    printf("7. Help/About\n");
    printf("8. Exit\n");
}
void submenu_userdata()
{
    printf("1. Edit Username\n");
    printf("2. Edit Password\n");
    printf("3. Edit Email Address\n");
    printf("4. Exit\n");
}
void submenu_reminders()
{
    printf("1. Add reminder\n");
    printf("2. Remove reminder\n");
    printf("3. Clear reminders\n");
    printf("4. Exit\n");
}
int getMenuChoice()
{
    int choice;
    printf("=> ");
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
int wanttocontinue()
{
    while (1)
    {
        clrs();
        char yn[2];
        printf("Enter 'y' to continue and 'n' to exit.\n=> ");
        scanf("%1s", yn);
        clearInputBuffer();
        if (strcmp(yn, "y") == 0)
        {
            return 0;
        }
        else if (strcmp(yn, "n") == 0)
        {
            return 1;
        }
        else
        {
            clrs();
            printf("\tInvalid input. Please enter a valid option.");
            getchar();
            continue;
        }
    }
}
void notriesleft()
{
    clrs();
    printf("\n\t********** No tries left. **********");
    nap(2);
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
    printf("Reminders:\n");
    printf("\n");
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
    printf("Sign up successful!\n");
    press();
    // system("PDMS.exe");
}

int addrecord()
{
    FILE *file;
    dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);
    char record_name[50];
    printf("Record name: ");
    scanf("%s", record_name);
    if (exit_module(record_name))
    {
        return 0;
    }
    file = fopen("Program_files/Records.dat", "a");
    fprintf(file, "(%d-%02d-%02d) %s \n", dt.year, dt.month, dt.day, record_name);
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
        scanf(" %[^\n]", record_data); // Read input until newline is encountered
        if (exit_module(record_data))
        {
            return 1;
        }
        // Add the new record to the record file
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
    char when[2];
    FILE *file;
    dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);
    char reminder_title[50], date[15];
    int day, hour, minute;
    int intid;
    char stringid[5];
    printf("Reminder Id: ");
    scanf("%d", &intid);
    sprintf(stringid, "%d", intid);
    if (exit_module(stringid))
    {
        return 0;
    }
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
    printf("5. Full date\n");
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
        break;
    case '2':
        strcpy(date, "Tommorrow");
        break;
    case '3':
        printf("Enter Day: ");
        scanf("%d", day);
        if (day > 30)
        {
            printf("Please enter a valid day.");
            addreminder();
        }
        sprintf(date, "%d/%d", day, dt.month);
        break;
    case '.':
        return 0;
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
    if (exit_module(reminder_title))
    {
        return 0;
    }
    file = fopen("Program_files/Reminders.dat", "a");
    fprintf(file, "%d (%s) (%d:%d) %s \n", intid, date, hour, minute, reminder_title);
    fclose(file);
    printf("\nNew reminder added successfully.");
    hold();
}

int deletereminder()
{
    char idtodelete[5];
    printf("\tEnter the id of the reminder to be deleted.\n");
    printf("=> ");
    scanf("%s", idtodelete);
    if (exit_module(idtodelete))
    {
        return 0;
    }
    FILE *originalFile, *tempFile;

    // Open the original record file in read mode
    originalFile = fopen("Program_files/Reminders.dat", "r");
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
    char line[256];
    while (fgets(line, sizeof(line), originalFile))
    {
        // Check if the line contains the ID to be deleted
        if (strstr(line, idtodelete) == NULL)
        {
            // If not, write it to the temporary file
            fputs(line, tempFile);
        }
    }

    // Close both files
    fclose(originalFile);
    fclose(tempFile);

    // Delete the original file
    remove("Program_files/Reminders.dat");

    // Rename the temporary file to the original file name
    if (rename("temp.dat", "Program_files/Reminders.dat") != 0)
    {
        printf("Error renaming the temporary file.\n");
    }
    printf("\nThe reminder has been deleted successfully.");
    hold();
    clrs();
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
