#include "Onegin.h"

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "rb");
    assert (file != nullptr);

    char* file_buffer = (char*) calloc (size_of_file, sizeof(char));
    assert (file_buffer);

    fread  (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    return file_buffer;
}

//------------------------------------------------------------------------------------------------

int counter_line (int f_size, char* file_buffer)
{
    char* beg_line     = file_buffer;
    char* end_line     = NULL;
    int   line_counter = 0;

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
    printf ("Size of \"%s\" is: %ld bytes.\n", file_name, information_buffer.st_size);

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
    assert (data != nullptr);

    char* p_beg_str = (inform -> file_buffer);
    char* p_end_str = NULL;

    for (int i = 0; i < (inform -> number_line); i++)
    {
        p_end_str = strchr (p_beg_str, '\n');

        if (p_end_str != NULL)
            *p_end_str = '\0';
        else 
            p_end_str = strchr (p_beg_str, '\0') + 1;

        (data + i) -> p_begin_str = p_beg_str;
        (data + i) -> str_length  = p_end_str - p_beg_str;

        p_beg_str = p_end_str + 1;
    }

    return data;
}

//------------------------------------------------------------------------------------------------

void free_memory (struct file* inform, struct str* data)
{
    free (inform -> file_buffer);   
    
    free (inform);
    inform = nullptr;

    free (data);
    data = nullptr;
}

//------------------------------------------------------------------------------------------------