#include "Onegin.h"

int main (int argc, char* argv[])
{
    char* file_name     = "";
    struct str*    data = NULL;
    
    struct file* inform = (struct file*) calloc (1, sizeof (struct file));
    assert (inform != nullptr);
    
    if (argc == 2)
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
    }

    input_inform (file_name, inform);
    data = place_pointers (inform, data);

    FILE* finish_file = fopen ("hamlet_sorted.txt", "wb");
    fprintf (finish_file, "\nORIGINAL TEXT\n\n");
    print_text  (data, inform, finish_file);

    fclose (finish_file);

    //bubble_sort (data, inform);
    qsort (data, inform -> number_line, sizeof (struct str), &direct_comparator);

    finish_file = fopen ("hamlet_sorted.txt", "a");
    fprintf (finish_file, "\nDIRECT SORTED TEXT\n\n");
    print_text  (data, inform, finish_file);

    fclose (finish_file);

    qsort (data, inform -> number_line, sizeof (struct str), &reverse_comparator);

    finish_file = fopen ("hamlet_sorted.txt", "a");
    fprintf (finish_file, "\n\n\nREVERSE SORTED TEXT\n\n");
    print_text  (data, inform, finish_file);

    fclose (finish_file);

    free_memory (inform, data);
}