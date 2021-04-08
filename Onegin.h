#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include <stdio.h>                 // FILE *fopen(const char *fname, const char *mode)
#include <stdlib.h>                // Открытие файла осуществляется с помощью функции fopen(),
#include <string.h>                // которая возвращает указатель на структуру типа FILE,
#include <sys/stat.h>              // который можно использовать для последующих операций с файлом.
#include <sys/types.h>             // int stat(const char *file_name, struct stat *buf);
#include <locale.h>                // size_t fread(void *буфер, size_t число_байту size_t объем, FILE *fp);
#include <ctype.h>
#include <assert.h>

//------------------------------------------------------------------------------------------------

struct text 
{
    int  size_of_file;
    int   number_line;
    char* file_buffer;

    struct str*     strings;
   // struct lexem* lexemes;
};
//сделать флаг который будет выбирать структуру по надобности

struct str
{
    char* p_begin_str;
    int   str_length;
};

/*struct lexem
{

};*/
//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);

char* read_file (char* file_name, int size_of_file);

int counter_line (char* file_buffer);
int file_size      (char* file_name);

int direct_comparator  (const void* data1, const void* data2);
int reverse_comparator (const void* data1, const void* data2);
void swap_pointers     (struct str* data1, struct str* data2);

void place_pointers (struct text* text_info);
void free_memory    (struct text* text_info);
void bubble_sort    (struct text* text_info);
void quick_sort     (struct text* text_info);
void output         (struct text* text_info);
void print_text     (struct text* text_info, FILE* finish_file);

void input_inform  (char* file_name, struct text* text_info);

//------------------------------------------------------------------------------------------------

#endif 