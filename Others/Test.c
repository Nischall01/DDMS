#include <stdio.h>
#include "lib/sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_open("User_file.db", &db);
    sqlite3_close(db);
    return 0;
}