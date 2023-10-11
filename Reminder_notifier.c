#include <stdio.h>
#include <windows.h>

struct datetime
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} dt;

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

int reminder_notification()
{
    int hour;
    int minute;
    char message[21];

    while (1)
    {
        FILE *fp;
        fp = fopen("Program_files/Today.txt", "r");
        if (fp == NULL)
        {
            perror("Error! \n");
        }
        fscanf(fp, "%d %d  %[^\n]", &hour, &minute, message);
        dtime(&dt.year, &dt.month, &dt.day, &dt.hour, &dt.min, &dt.sec);
        if (hour == dt.hour && minute == dt.min)
        {
            MessageBox(NULL, message, "Reminder", MB_ICONINFORMATION | MB_OK);
            Sleep(59000);
        }
        fclose(fp);
        Sleep(1000);
    }
}

int main()
{
    reminder_notification();
    return 0;
}
