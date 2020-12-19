#include <stdio.h>                 // FILE *fopen(const char *fname, const char *mode)
#include <stdlib.h>                // Открытие файла осуществляется с помощью функции fopen(),
#include <string.h>                // которая возвращает указатель на структуру типа FILE,
#include <sys/stat.h>              // который можно использовать для последующих операций с файлом.
#include <sys/types.h>             // int stat(const char *file_name, struct stat *buf);
#include <locale.h>                // size_t fread(void *буфер, size_t число_байту size_t объем, FILE *fp);
#include <ctype.h>

char* read_file (char* file_name, int size_of_file);

struct str* place_pointers (struct file* inform, struct str* data);

int counter_line       (int f_size, char* file_buffer);
int file_size          (char* file_name);
int direct_comparator (const void* data1, const void* data2);
int reverse_comporator (struct str* data, int j);

void input_inform  (char* file_name, struct file* inform);
void free_memory   (struct file* inform, struct str* data);
void swap_pointers (struct str* data, int j);
void bubble_sort   (struct str* data, struct file* inform);
void print_text    (struct str* data, struct file* inform);

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

int main (/*int argc, char* argv[]*/)
{
    char* file_name = "hamlet.txt";
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

    input_inform (file_name, inform);
    data = place_pointers (inform, data);

    bubble_sort (data, inform);
   // qsort (data, inform -> number_line, sizeof (struct str), (int(*) (const void *, const void *)) direct_comparator);
    print_text  (data, inform);
    free_memory (inform, data);
}

//------------------------------------------------------------------------------------------------

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "rb");

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

    fread  (file_buffer, sizeof (char), size_of_file, file);
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

    line_counter++;

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
    int  size_of_file = file_size (file_name);
    char* file_buffer = read_file (file_name, size_of_file);
    int   number_line = counter_line (size_of_file, file_buffer);

    inform -> size_of_file = size_of_file;
    inform -> number_line  = number_line;
    inform -> file_buffer  = file_buffer;
}

//------------------------------------------------------------------------------------------------

struct str* place_pointers (struct file* inform, struct str* data)
{
    data = (struct str*) calloc (inform -> number_line, sizeof (struct str));

    char* p_beg_str = (inform -> file_buffer);
    char* p_end_str = NULL;

    for (int i = 0; i < (inform -> number_line); i++)
    {
        p_end_str = strchr (p_beg_str, '\n');

        if (p_end_str != NULL) *p_end_str = '\0';
        else p_end_str = strchr (p_beg_str, '\0') + 1;

        (data + i) -> p_begin_str = p_beg_str;
        (data + i) -> str_length  = p_end_str - p_beg_str - 1;

        p_beg_str = p_end_str + 1;
    }

    return data;
}

//------------------------------------------------------------------------------------------------

void free_memory (struct file* inform, struct str* data)
{
    free (inform);
    free (inform -> file_buffer);
    free (data);
}

//------------------------------------------------------------------------------------------------

int direct_comparator (const void* data1, const void* data2)
{
    char* line1_begin = ((struct str*) data1) -> p_begin_str;
    char* line2_begin = ((struct str*) data2) -> p_begin_str;

    char* line1_end = line1_begin + (((struct str*) data1) -> str_length);
    char* line2_end = line2_begin + (((struct str*) data2) -> str_length);

    while ((!isalpha(*line1_begin)) && (line1_begin != line1_end))
    {
        line1_begin++;
    }

    while ((!isalpha(*line2_begin)) && (line2_begin != line2_end))
    {
        line2_begin++;
    }

    while ((*line1_begin == *line2_begin) && (line1_begin != line1_end)
                                          && (line2_begin != line2_end))
    {
        line1_begin++;
        line2_begin++;

        while ((!isalpha(*line1_begin)) && (*line1_begin == ' ')
                                        && (line1_begin  != line1_end))
        {
            line1_begin++;
        }

        while ((!isalpha(*line2_begin)) && (*line2_begin == ' ')
                                        && (line2_begin  != line2_end))
        {
            line2_begin++;
        }
    }

    return ((int)(*line1_begin) - (int)(*line2_begin));
}

//------------------------------------------------------------------------------------------------

int reverse_comporator (struct str* data, int j)
{
    char* line1_begin = (data + j) -> p_begin_str;
    char* line2_begin = (data + j + 1) -> p_begin_str;

    char* line1_end = line1_begin + (data + j) -> str_length;
    char* line2_end = line2_begin + (data + j + 1) -> str_length;

    while ((!isalpha(*line1_end)) && (line1_end != line1_begin))
    {
        line1_end--;
    }

    while ((!isalpha(*line2_end)) && (line2_end != line2_begin))
    {
        line2_end--;
    }

    while ((*line1_end == *line2_end) && (line1_end != line1_begin)
                                      && (line2_end != line2_begin))
    {
        line1_end--;
        line2_end--;

        while ((!isalpha(*line1_end)) && (*line1_end == ' ')
                                      && (line1_end  != line1_begin))
        {
            line1_end--;
        }

        while ((!isalpha(*line2_end)) && (*line2_end == ' ')
                                      && (line2_end  != line2_begin))
        {
            line2_end--;
        }
    }

    return ((*line2_end) - (*line1_end));
}

//------------------------------------------------------------------------------------------------

void bubble_sort (struct str* data, struct file* inform)
{
    for (int i = 0; i < (inform -> number_line) - 2; i++)
    {
        for (int j = 0; j < (inform -> number_line) - i - 2; j++)
        {
            if ((direct_comparator((data + j), (data + j + 1)) > 0))
            {
                swap_pointers (data, j);
            }
        }
    }
    printf ("TEXT has been sorted\n");
}

//------------------------------------------------------------------------------------------------

void swap_pointers (struct str* data, int j)
{
    struct str temp = *(data + j + 1);

    *(data + j + 1) = *(data + j);
    *(data + j) = temp;
}

//------------------------------------------------------------------------------------------------

void print_text (struct str* data, struct file* inform)
{
    char* sorted_filename = "hamlet_sorted.txt";
    FILE* finish_file = fopen (sorted_filename, "wb");

    for (int i = 0; i < (inform -> number_line); i++)
    {
        fwrite (((data + i) -> p_begin_str), sizeof(char), (data + i) -> str_length, finish_file);
        fprintf (finish_file, "\n");
    }

    fclose (finish_file);
    free (finish_file);
}

//-----------------------------------------------------------------------------------------------
