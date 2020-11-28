#include <stdio.h>                 //FILE *fopen(const char *fname, const char *mode)
#include <stdlib.h>                //Открытие файла осуществляется с помощью функции fopen(),
#include <sys/stat.h>              //которая возвращает указатель на структуру типа FILE,
#include <sys/types.h>             //который можно использовать для последующих операций с файлом.
#include <unistd.h>                //int stat(const char *file_name, struct stat *buf);
                                   //size_t fread(void *буфер, size_t число_байту size_t объем, FILE *fp);
int read_file (char* file_name, int* line_counter);
int counter_line (int f_size, char* file_buffer);

int main ()
{
    char file_name[] = "";
    int size_of_file = 0;
    int number_line  = 0;

    printf ("Please enter the name of the file you want to read: ");
    scanf  ("%s", file_name);
    printf ("You want read \"%s\"\n", file_name);

    size_of_file = read_file (file_name, &number_line);
    printf ("%d", number_line);
}

int read_file (char* file_name, int* line_counter)
{
    FILE* file = fopen (file_name, "r");

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

    printf ("Size of \"%s\" is: %d bytes.\n", file_name, information_buffer.st_size);

    char* file_buffer = (char*) calloc (information_buffer.st_size + 1, sizeof(char));

    if (file_buffer == NULL)
    {
        printf ("Error failed to allocate memory!\n");
    }

    fread (file_buffer, sizeof(char), information_buffer.st_size, file);
    fclose (file);

    *line_counter = counter_line (information_buffer.st_size, file_buffer);

    free (file_buffer);
    
    return information_buffer.st_size;
}

int counter_line (int f_size, char* file_buffer)
{
    int line_counter = 0;

    for (int i = 0; i < f_size + 1; i++)
    {
        if (*(file_buffer + i) == '\n')
        {
            line_counter++;
        }
    }
    printf ("%d", line_counter);

    return line_counter;
}

