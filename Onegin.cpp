#include <stdio.h>
#include <sys/types.h>             //Открытие файла осуществляется с помощью функции fopen(),
#include <sys/stat.h>              //которая возвращает указатель на структуру типа FILE,
#include <stdlib.h>                //который можно использовать для последующих операций с файлом.
#include <unistd.h>                //int stat(const char *file_name, struct stat *buf);

int main ()
{
    char file_name[20] = {};

    printf ("Please enter the name of the file you want to read: ");
    scanf  ("%s", file_name);
    printf ("You want read %s\n", &file_name);

    FILE *file = fopen (file_name, "r");

    struct stat information_buffer = {};

    if (file == NULL)
    {
        printf ("Error! The file cannot be opened.\n");
    }

    else
    {
        printf ("The file is opened successfully.\n");
    }

    stat (file_name, &information_buffer);

    int size_of_file = information_buffer.st_size;
    printf ("Size of the file is: %ld\n", size_of_file);

    fclose (file);



    return 0;
}
