#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

void clrs()
{
    system("cls");
}

void displayMenu()
{
    printf("Menu:\n");
    printf("1. Option 1\n");
    printf("2. Option 2\n");
    printf("3. Option 3\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    int choice;

    while (1)
    {
        displayMenu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            getch();
            clrs();
            // Clear the input buffer
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("You selected Option 1.\n");
            getch();
            clrs();
            break;
        case 2:
            printf("You selected Option 2.\n");
            getch();
            clrs();
            break;
        case 3:
            printf("You selected Option 3.\n");
            getch();
            clrs();
            break;
        case 4:
            clrs();
            printf("\tHave a great day.");
            sleep(1.75);
            return 0;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
            getch();
            clrs();
            break;
        }
    }
    return 0;
}
