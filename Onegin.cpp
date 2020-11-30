#include <stdio.h>                 //FILE *fopen(const char *fname, const char *mode)
#include <stdlib.h>                //Открытие файла осуществляется с помощью функции fopen(),
#include <sys/stat.h>              //которая возвращает указатель на структуру типа FILE,
#include <sys/types.h>             //который можно использовать для последующих операций с файлом.
#include <unistd.h>                //int stat(const char *file_name, struct stat *buf);
                                   //size_t fread(void *буфер, size_t число_байту size_t объем, FILE *fp);
char* read_file (char* file_name, int size_of_file);
int counter_line (int f_size, char* file_buffer, char** massive);
int file_size (char* file_name);
void Input_inform (char* file_name, struct file* inform);

struct file
{
    int size_of_file;
    int number_line;
    char* file_buffer;
};

//------------------------------------------------------------------------------------------------

int main ()
{
    char file_name[50] = "";
    char* file_buffer  = "";

    int size_of_file = 0;
    int number_line  = 0;

    struct file* inform = {};

    printf ("Please enter the name of the file you want to read: ");
    scanf  ("%s", file_name);
    printf ("You want read \"%s\"\n", file_name);

    Input_inform (file_name, inform);

    free (file_buffer);
}

//------------------------------------------------------------------------------------------------

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "r");

    if (file == NULL)
    {
        printf ("Error! The file cannot be opened.\n");
    }

    else
    {
        printf ("The file is opened successfully.\n");
    }

    char* file_buffer = (char*) calloc (size_of_file + 1, sizeof(char));

    if (file_buffer == NULL)
    {
        printf ("Error failed to allocate memory!\n");
    }

    fread (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

      ///free//////////////!!!!!!!!!!!!!!!!!

    return file_buffer;
}

//------------------------------------------------------------------------------------------------

int counter_line (int f_size, char* file_buffer, char** massive)
{
    int line_counter = 0;

    for (int i = 0; i < f_size + 1; i++)
    {
        if (*(file_buffer + i) == '\n')
        {
            line_counter++;
             for (int k = 0; k < 250; k++) massive[k] = (file_buffer + i + 1);
        }
    }
    printf ("%d", line_counter);

    return line_counter;
}

//------------------------------------------------------------------------------------------------

int file_size (char* file_name)
{
    struct stat information_buffer = {};

    stat (file_name, &information_buffer);
    printf ("Size of \"%s\" is: %d bytes.\n", file_name, information_buffer.st_size);

    return information_buffer.st_size;
}

//------------------------------------------------------------------------------------------------

void Input_inform (char* file_name, struct file* inform)
{
    char* massive[250] = {};

    int size_of_file  = file_size (file_name);

    char* file_buffer = read_file (file_name, size_of_file);

    int number_line   = counter_line (size_of_file, file_buffer, massive);

    inform -> size_of_file;
    inform -> number_line;
    inform -> file_buffer;
}

