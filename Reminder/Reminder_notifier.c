#include <stdio.h>
#include <windows.h>

// Define structures
struct datetime
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} dt;

// Global variables
char message[256]; // Assuming a larger buffer for messages

// Function to retrieve date and time
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

// Function to show reminder notification
void showReminderNotification(const char *msg)
{
    NOTIFYICONDATA nid;
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = NULL; // This will be set when we create the icon
    nid.uID = 1;     // Unique ID for the icon
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_USER + 1; // Custom message for notifications
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    strcpy(nid.szTip, "Reminder");

    Shell_NotifyIcon(NIM_ADD, &nid);

    MessageBox(NULL, msg, "Reminder", MB_ICONINFORMATION | MB_OK);

    Shell_NotifyIcon(NIM_DELETE, &nid);
}

// Function to check for reminder
void checkReminder()
{
    int hour, minute;

    FILE *fp = fopen("Program_files/Today.txt", "r");
    if (fp == NULL)
    {
        perror("Error! \n");
        return;
    }

    fscanf(fp, "%d %d %[^\n]", &hour, &minute, message);
    fclose(fp);

    dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);

    if (hour == dt.hour && minute == dt.min)
    {
        showReminderNotification(message);
        // Optionally add logic to reset the reminder or handle repetitions
    }
}

// Main function
int main()
{
    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop to check for reminders
    while (1)
    {
        checkReminder();
        Sleep(1000); // Check every second (adjust as needed)
    }

    return 0;
}
