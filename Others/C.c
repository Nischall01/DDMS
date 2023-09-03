#include <stdio.h>
#include <stdbool.h> // Include the standard library for boolean type
#include <string.h>  // Include the standard library for string functions

// Function to check if a file exists
bool fileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true; // File exists
    }
    return false; // File doesn't exist
}

int main()
{
    char fname[256]; // Declare a character array to store the filename

    printf("Enter the filename to check: ");
    scanf("%255s", fname); // Read the filename from the user, limited to 255 characters
    strcat(fname, ".txt");

    if (fileExists(fname))
    {
        printf("The file '%s' exists.\n", fname);
    }
    else
    {
        printf("The file '%s' does not exist.\n", fname);
    }

    return 0;
}
