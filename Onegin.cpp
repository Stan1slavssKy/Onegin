#include <stdio.h>                 // FILE *fopen(const char *fname, const char *mode)
#include <stdlib.h>                // Открытие файла осуществляется с помощью функции fopen(),
#include <string.h>                // которая возвращает указатель на структуру типа FILE,
#include <sys/stat.h>              // который можно использовать для последующих операций с файлом.
#include <sys/types.h>             // int stat(const char *file_name, struct stat *buf);
#include <locale.h>                // size_t fread(void *буфер, size_t число_байту size_t объем, FILE *fp);


char *read_file        (char* file_name, int size_of_file);
int  counter_line      (int f_size, char* file_buffer);
int  file_size         (char* file_name);
void place_pointers    (struct file* inform, struct str* data);
void input_inform      (char* file_name, struct file* inform);
void free_memory       (struct file* inform);
void direct_comparator (struct* data);

struct file
{
    int size_of_file;
    int number_line;
    char* file_buffer;
};

struct str
{
    char* p_begin_str;
    int   str_length;
};

//------------------------------------------------------------------------------------------------

int main (int argc, char* argv[])
{
    char* file_name = "Hamlet.txt";
    struct str*    data = NULL;
    struct file* inform = (struct file*) calloc (1, sizeof (struct file));

  /*  if (argc == 2)
    {
        file_name = argv[1]; 
        printf ("You want read \"%s\"\n", file_name);   
    }
    else if (argc == 1)
    {
        printf ("You didn't enter the file name. Please return program and enter file name.\n");
        return 0;
    }
    else 
    {
        printf ("Error to few or too many arguments.\n");
        return 0;
    }*/

    input_inform     (file_name, inform);
    place_pointers   (inform, data);
    direct_comparator(data);
    free_memory      (inform);

    free (data);
}

//------------------------------------------------------------------------------------------------

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "r");

    if (file == NULL)
    {
        printf ("Error! The file cannot be opened.\n");
        return NULL;
    }

    else
    {
        printf ("The file is opened successfully.\n");
    }

    char* file_buffer = (char*) calloc (size_of_file, sizeof(char));

    if (file_buffer == NULL)
    {
        printf ("Error failed to allocate memory!\n");
        return NULL;
    }

    fread (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    return file_buffer;
}

//------------------------------------------------------------------------------------------------

int counter_line (int f_size, char* file_buffer)
{
    char* beg_line   = file_buffer;
    char* end_line   = NULL;
    int line_counter = 0;

    while ((end_line = strchr (beg_line, '\n')) != NULL)
    {
        beg_line = end_line + 1;
        line_counter++;
    }

    printf ("The number of rows is %d\n", line_counter);

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

void input_inform (char* file_name, struct file* inform)
{
    int size_of_file  = file_size (file_name);

    char* file_buffer = read_file (file_name, size_of_file);

    int number_line   = counter_line (size_of_file, file_buffer);

    inform -> size_of_file = size_of_file;
    inform -> number_line  = number_line;
    inform -> file_buffer  = file_buffer;
}

//------------------------------------------------------------------------------------------------

void place_pointers (struct file* inform, struct str* data)
{
    data = (struct str*) calloc (inform -> number_line, sizeof(struct str));

    char* p_beg_str = inform -> file_buffer - 1;
    char* p_end_str = NULL;

    for (int i = 0; i < inform -> number_line; i++)
    {
        p_end_str = strchr (p_beg_str, '\n');

        (data + i) -> p_begin_str = p_beg_str;
        (data + i) -> str_length  = p_end_str - p_beg_str;

        p_beg_str = p_end_str + 1;
    }
}

//------------------------------------------------------------------------------------------------

void free_memory (struct file* inform)
{
  //  free (data_mem);
    free (inform);
    free (inform -> file_buffer);
}

//------------------------------------------------------------------------------------------------

void direct_comparator (struct* data)
{
    char* line_beg = (data + i) -> p_begin;
    char* line_end = (data + i) -> p_begin;          
}

void quicksort ()
{

}
