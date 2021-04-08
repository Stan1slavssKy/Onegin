#include "Onegin.h"

int main (int argc, char* argv[])
{
    struct text text_info = {};

    char*  file_name = nullptr;
    
    file_name = console_input (argc, argv); 
    if (file_name == nullptr)
        return 0;

    input_inform   (file_name, &text_info);
    place_pointers (&text_info);
    output (&text_info);

    free_memory (&text_info);

    return 0;
}