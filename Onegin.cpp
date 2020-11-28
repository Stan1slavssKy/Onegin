#include <stdio.h>                 //FILE *fopen(const char *fname, const char *mode)
#include <stdlib.h>                //Открытие файла осуществляется с помощью функции fopen(),
#include <sys/stat.h>              //которая возвращает указатель на структуру типа FILE,
#include <sys/types.h>             //который можно использовать для последующих операций с файлом.
#include <unistd.h>                //int stat(const char *file_name, struct stat *buf);

int read_file (char*);

int main ()
{
    char file_name[] = "";
    int size_of_file = 0;

    printf ("Please enter the name of the file you want to read: ");
    scanf  ("%s", file_name);
    printf ("You want read \"%s\"\n", file_name);

    size_of_file = read_file (file_name);


}

int read_file (char* file_name)
{
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
    printf ("Size of \"%s\" is: %d bytes.\n", file_name, size_of_file);

    char *file_buffer = (char*) calloc (size_of_file + 1, sizeof(char));

    if (file_buffer == NULL)
    {
        printf ("Error failed to allocate memory!\n");
    }

    fread (file_buffer, sizeof(char), size_of_file, file);
    fclose (file);

    free (file_buffer);

}
