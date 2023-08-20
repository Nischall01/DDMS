#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

#define FILENAME_SIZE 1024 // Defining value for FILENAME_SIZE
#define MAX_LINE 2048      // Defining value for MAX_LINE
#define CH_LIMIT 40        // Defining value for CH_LIMIT
#define USERNAME_LINE 1;
#define PASSWORD_LINE 2;
#define EMAIL_LINE 3;
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

// Functions
void clrs()
{
    printf("\x1B[2J\x1B[H");
}
void press()
{
    printf("\nPress any key to continue !\n");
    getch();
    clrs();
}
void menu()
{
    printf("1. Add a new record\n");
    printf("2. Open a record\n");
    printf("3. Edit a record\n");
    printf("4. Delete a record\n");
    printf("5. Edit username, password, email address\n");
    printf("6. Exit\n");
    printf("=>");
}
void submenu()
{

    printf("1. Edit Username\n");
    printf("2. Edit Password\n");
    printf("3. Edit Email Address\n");
    printf("4. Exit\n");
    printf("=>");
}

// Function Declarations
void UI();
void dtime(int *, int *, int *, int *, int *, int *);
void sign_up();
void addrecord();
void viewrecord();
void editrecord();
void deleterecord();
void editusername();
void editpassword();
void editemailaddress();
int records();
void check();

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
    check();
    int choice, choice2;
    char enteredpass[CH_LIMIT];
    char enteredeaddy[CH_LIMIT];
    // Extract the username, password and email address.
    FILE *file;
    file = fopen("user_info.dat", "r");
    fscanf(file, "%s %s %s", name, pass, email);
    fclose(file); // File handling STOPs.

    //  Login Page
    printf("\t\tWelcome, %s\n", name);
    while (1)
    {
        printf("\n\tEnter the password ==> ");
        scanf("%s", enteredpass);
        if (strcmp(enteredpass, pass) == 0)
        {
            clrs();
            UI();
        }
        else if (strcmp(enteredpass, "RESET") == 0)
        {
            int trys = 5;
        try_email:
            printf("\nEnter your email address entered during the login or enter 'EXIT' to exit:\n==> ");
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
                printf("\nIncorrect email address. Please try again. Tries left: %d", trys);
                if (trys == 0) // if wrong password is entered more than '5' times the program will terminate.
                {
                    clrs();
                    printf("\n\t********** Entered too many incorrect entries. **********");
                    return 0;
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
                clrs();
                printf("\n\t********** Entered too many incorrect entries. **********");
                return 0;
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
        clrs();
        records();
        menu();
        isnotint = scanf("%d", &choice);
        if (isnotint == 0)
        {
            printf("\tInvalid input. Please enter a valid option.");
            getch();
            clrs();
            while (getchar() != '\n')
                ;
            clrs();
            continue;
        }

        switch (choice)
        {
        case 1:
            clrs();
            addrecord();
            clrs();
            break;
        case 2:
            clrs();
            printf("\t|Open a record|\n");
            if (records() == 0)
            {
                printf("Press any key to continue!\n");
                getch();
                break;
            }
            else
            {
                viewrecord();
            }
            break;
        case 3:
            clrs();
            printf("\t|Edit a record|\n");
            if (records() == 0)
            {
                printf("Press any key to continue!\n");
                getch();
                break;
            }
            else
            {
                editrecord();
            }
            break;
        case 4:
            clrs();
            printf("\t|Delete a record|\n");
            if (records() == 0)
            {
                printf("Press any key to continue!\n");
                getch();
                break;
            }
            else
            {
                deleterecord();
            }
            break;
        case 5:
            clrs();
            while (1)
            {
                clrs();
                int choice2;
                submenu();
                isnotint = scanf("%d", &choice2);
                if (isnotint == 0)
                {
                    printf("\t\tInvalid input. Please enter a valid option.");
                    getch();
                    clrs();
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                switch (choice2)
                {
                case 1:
                    editusername();
                    break;
                case 2:
                    editpassword();
                    break;
                case 3:
                    editemailaddress();
                    break;
                case 4:
                    clrs();
                    break;
                default:
                    printf("\t\tPlease enter a valid option.");
                    getch();
                    clrs();
                    break;
                }
                break;
            }
            break;
        case 6:
            exit(0);
        default:
            clrs();
            printf("\tPlease enter a valid option.");
            getch();
            clrs();
            break;
        }
    }
}

// Function Definitions
void check()
{
    char buffer[MAX_LINE];

    int name_line = 1;   // as Line 1 in the txt file holds username
    char name[CH_LIMIT]; // This variable holds the name

    // File handling STARTs.
    FILE *file;
    file = fopen("user_info.dat", "r"); // Opens the file the holds user info to read
    fseek(file, 0, SEEK_END);           // Move the file pointer to the end of the file
    long file_size = ftell(file);       // Get the position of the file pointer (i.e., the file size)
    if (file_size == 0 || file == 0)    // Checks if the file exists or not & if it does, checks if it's empty or not.
    {
        fclose(file);
        printf("Error in the user file. Please Signup\n");
        printf("\nPress any key to continue !\n");
        getch();
        sign_up();
    }
    if (file)
    {
        bool keep_reading = true;
        int current_line = 1;
        do
        {
            fgets(buffer, MAX_LINE, file);
            buffer[strcspn(buffer, "\n")] = 0;
            if (current_line <= 3)
            {
                if (current_line == 1)
                {
                    size_t length = strlen(buffer);
                    if (length == 0)
                    {
                        fclose(file);
                        printf("The name field is empty.\n");
                        sign_up();
                    }
                }
                else if (current_line == 2)
                {
                    size_t length = strlen(buffer);
                    if (length == 0)
                    {
                        fclose(file);
                        printf("The password feild is empty.\n");
                        sign_up();
                    }
                }
                else if (current_line == 3)
                {
                    keep_reading = false;
                    size_t length = strlen(buffer);
                    if (length == 0)
                    {
                        fclose(file);
                        printf("The email feild is empty.\n");
                        sign_up();
                    }
                }
            }
            current_line++;
        } while (keep_reading);
    }
    fclose(file);
}

int records()
{
    FILE *file;
    file = fopen("Records.dat", "r");
    if (file == NULL)
    {
        fclose(file);
        clrs();
        file = fopen("Records.dat", "w");
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
        file = fopen("Records.dat", "r");
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
    file = fopen("user_info.dat", "w"); // Open the file in "write" mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    printf("\nPlease enter your username, password, and email address to SIGN UP. [NOTE] - No fields can be empty nor can it contain spaces.\n");

    // Input username
    while (1)
    {
    loop:
        printf("\nUsername: ");
        if (fgets(buffer, MAX_LINE, stdin) == NULL)
        {
            printf("Error reading input.\n");
            exit(1);
        }
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) == 0)
        {
            printf("!!Invalid Input!! This field cannot be empty.\n");
            getch();
            fclose(file);
        }
        else
        {
            for (int i = 0; buffer[i] != '\0'; i++)
            {
                if (buffer[i] == ' ')
                {
                    printf("!!Invalid Input!! Username cannot contain spaces.\n");
                    getch();
                    goto loop;
                }
            }
            break;
        }
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
            printf("!!Invalid Input!! Username cannot contain spaces.\n");
            getch();
            fclose(file);
            sign_up();
        }
    }
    if (strlen(buffer) == 0)
    {
        printf("!!Invalid Input!! This field cannot be empty.\n");
        getch();
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
            printf("!!Invalid Input!! Username cannot contain spaces.\n");
            getch();
            fclose(file);
            sign_up();
        }
    }
    if (strlen(buffer) == 0)
    {
        printf("!!Invalid Input!! This field cannot be empty.\n");
        getch();
        fclose(file);
        sign_up();
    }
    fputs(buffer, file);
    fclose(file);
    printf("Sign up successful!\n");
    system("Diary_Management_System.exe");
}

void addrecord()
{
    FILE *file;
    dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);
    char record_name[50];
    printf("Record name: ");
    scanf("%s", record_name);
    file = fopen("Records.dat", "a");
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
        printf("==> ");
        scanf(" %[^\n]", record_data); // Read input until newline is encountered

        // Write the additional record data to the file
        fprintf(file, "\n%s", record_data);
        fclose(file);
        printf("\nNew record added successfully.\n");
        printf("\nPress any key to continue !\n");
        getch();
        clrs();
    }
    else
    {
        printf("Error: Unable to create the record file.\n");
        getch();
        clrs();
    }
    fclose(file);
}

void viewrecord()
{
    char record[50];
    printf("==> ");
    scanf("%s", record);
    strcat(record, ".txt");
    FILE *file;
    file = fopen(record, "r");
    if (file == NULL)
    {
        perror("\nError! ");
    }
    // Read and print the contents character by character until the end of file (EOF) is reached
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }
    fclose(file);
    printf("\n");
    printf("\nPress any key to continue !\n");
    getch();
    clrs();
}

void editrecord()
{
    char record[50];
    printf("==> ");
    scanf("%s", record);
    strcat(record, ".txt");
    FILE *file;
    file = fopen(record, "r");
    printf("%s\n", record);
    if (file == NULL)
    {
        perror("\nError! ");
    }
    else
    {
        system(record);
        printf("The record is sucessfully edited.\n");
        getch();
        clrs();
    }
    fclose(file);
}

void deleterecord()
{
    char recordToDelete[100];
    char record[100];

    printf("==>");
    scanf("%s", recordToDelete); // Reading user input, limiting the word to 99 characters
    strcpy(record, recordToDelete);
    strcat(record, ".txt");
    remove(record);
    FILE *originalFile, *tempFile;
    char line[256];

    // Open the original file in read mode
    originalFile = fopen("Records.dat", "r");
    if (originalFile == NULL)
    {
        printf("Error opening the file.\n");
    }

    // Open a temporary file in write mode
    tempFile = fopen("temp.dat", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file.\n");
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
    remove("Records.dat");

    // Rename the temporary file to the original file name
    if (rename("temp.dat", "Records.dat") != 0)
    {
        printf("Error renaming the temporary file.\n");
    }
    printf("The record has been deleted successfully.\n");
    getch();
    clrs();
}

void editusername() // Edit username function
{
    char replacement[50];
    printf("Enter the new username: ");
    scanf("%s", replacement);

    FILE *original;
    FILE *temp;
    original = fopen("user_info.dat", "r");
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
    if (remove("user_info.dat") != 0)
    {
        perror("Error removing the file!");
        printf("\nError no.%d\n", errno);
    }
    if (rename("temp.dat", "user_info.dat") != 0)
    {
        perror("Error renaming the file!");
        printf("\nError no.%d\n", errno);
    }
    clrs();
    printf("\tUsername replaced successfully.\n");
    getch();
}

void editpassword() // Edit password function
{
    char replacement[50];
    printf("Enter the replacement: ");
    scanf("%s", replacement);

    FILE *original;
    FILE *temp;
    original = fopen("user_info.dat", "r");
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
    if (remove("user_info.dat") != 0)
    {
        perror("Error removing the file!");
        printf("\nError no.%d\n", errno);
    }
    if (rename("temp.dat", "user_info.dat") != 0)
    {
        perror("Error renaming the file!");
        printf("\nError no.%d\n", errno);
    }
    clrs();
    printf("\tPassword replaced successfully.\n");
    printf("\nPress any key to continue !\n");
    getch();
}

void editemailaddress() // Edit email address function
{
    char replacement[50];
    printf("Enter the replacement: ");
    scanf("%s", replacement);

    FILE *original;
    FILE *temp;
    original = fopen("user_info.dat", "r");
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
    if (remove("user_info.dat") != 0)
    {
        perror("Error removing the file!");
        printf("\nError no.%d\n", errno);
    }
    if (rename("temp.dat", "user_info.dat") != 0)
    {
        perror("Error renaming the file!");
        printf("\nError no.%d\n", errno);
    }
    printf("Email address replaced successfully.\n");
}

void dtime(int *y, int *m, int *d, int *h, int *mi, int *s) // DateTime function
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
