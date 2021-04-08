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

void bubble_sort (struct text* text_info)
{
    for (int i = 0; i < (text_info -> number_line) - 2; i++)
    {
        for (int j = 0; j < (text_info -> number_line) - i - 2; j++)
        {
            if ((direct_comparator((text_info -> strings + j), (text_info -> strings + j + 1)) > 0))
            {
                swap_pointers ((text_info -> strings + j), (text_info -> strings + j + 1));
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

void print_text (struct text* text_info, FILE* finish_file)
{
    for (int i = 0; i < (text_info -> number_line); i++)
    {
        fwrite (((text_info -> strings + i) -> p_begin_str), sizeof(char), (text_info -> strings + i) -> str_length, finish_file);
        fprintf (finish_file, "\n");
    }
}

//-----------------------------------------------------------------------------------------------

void output (struct text* text_info)
{
    FILE* finish_file = fopen ("hamlet_sorted.txt", "wb");
    fprintf (finish_file, "\nORIGINAL TEXT\n\n");
    print_text  (text_info, finish_file);

    fclose (finish_file);

    qsort (text_info -> strings, text_info -> number_line, sizeof (struct str), &direct_comparator);

    finish_file = fopen ("hamlet_sorted.txt", "a");
    fprintf (finish_file, "\nDIRECT SORTED TEXT\n\n");
    print_text  (text_info, finish_file);

    fclose (finish_file);

    qsort (text_info -> strings, text_info -> number_line, sizeof (struct str), &reverse_comparator);

    finish_file = fopen ("hamlet_sorted.txt", "a");
    fprintf (finish_file, "\n\n\nREVERSE SORTED TEXT\n\n");
    print_text  (text_info, finish_file);

    fclose (finish_file);
}

//-----------------------------------------------------------------------------------------------