#include "Onegin.h"

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

int reverse_comparator (const void* data1, const void* data2)
{
    char* line1_begin = ((struct str*) data1) -> p_begin_str;
    char* line2_begin = ((struct str*) data2) -> p_begin_str;

    char* line1_end = line1_begin + (((struct str*) data1) -> str_length);
    char* line2_end = line2_begin + (((struct str*) data2) -> str_length);

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

    return ((int)(*line1_end) - (int)(*line2_end));
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
                swap_pointers ((data + j), (data + j + 1));
            }
        }
    }
    printf ("TEXT has been sorted\n");
}

//------------------------------------------------------------------------------------------------

void swap_pointers (struct str* data1, struct str* data2)
{
    struct str temp = *data2;

    *data2 = *data1;
    *data1 = temp;
}

//------------------------------------------------------------------------------------------------

void print_text (struct str* data, struct file* inform, FILE* finish_file)
{
    for (int i = 0; i < (inform -> number_line); i++)
    {
        fwrite (((data + i) -> p_begin_str), sizeof(char), (data + i) -> str_length, finish_file);
        fprintf (finish_file, "\n");
    }
}

//-----------------------------------------------------------------------------------------------