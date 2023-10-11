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

    while (fgets(line, sizeof(line), originalFile) != NULL)
    {
        if (strncmp(idtodelete, line, strlen(idtodelete)) == 0)
        {
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