#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to delete a reminder by ID
int deleteReminder()
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
        return 1;
    }

    // Open a temporary record file in write mode
    tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL)
    {
        perror("Error opening the temporary file");
        fclose(originalFile);
        return 1;
    }

    char line[256];  // Adjust the buffer size as needed
    int deleted = 0; // Flag to track if a reminder was deleted

    while (fgets(line, sizeof(line), originalFile) != NULL)
    {
        // Check if the line contains the ID to be deleted
        if (strncmp(idToDelete, line, strlen(idToDelete)) != 0)
        {
            fputs(line, tempFile);
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
        printf("No reminder with ID '%s' found.\n", idToDelete);
        remove(tempFileName); // Delete the temporary file
        return 1;
    }

    // Delete the original file
    if (remove("Program_files/Reminders.dat") != 0)
    {
        perror("Error deleting the original file");
        return 1;
    }

    // Rename the temporary file to the original file name
    if (rename(tempFileName, "Program_files/Reminders.dat") != 0)
    {
        perror("Error renaming the temporary file");
        return 1;
    }

    printf("The reminder with ID '%s' has been deleted successfully.\n", idToDelete);
    return 0;
}

int main()
{

    if (deleteReminder() == 0)
    {
        printf("Reminder deletion completed successfully.\n");
    }
    else
    {
        printf("Reminder deletion failed.\n");
    }

    return 0;
}
