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

struct file
{
    int  size_of_file;
    int   number_line;
    char* file_buffer;
};

struct str
{
    char* p_begin_str;
    int   str_length;
};

//------------------------------------------------------------------------------------------------

char* read_file (char* file_name, int size_of_file);

struct str* place_pointers (struct file* inform, struct str* data);

int counter_line       (int f_size, char* file_buffer);
int file_size          (char* file_name);
int direct_comparator  (const void* data1, const void* data2);
int reverse_comparator (const void* data1, const void* data2);

void input_inform  (char* file_name, struct file* inform);
void free_memory   (struct file* inform, struct str* data);
void swap_pointers (struct str* data1, struct str* data2);
void bubble_sort   (struct str* data, struct file* inform);
void print_text    (struct str* data, struct file* inform, FILE* finish_file);
void quick_sort    (struct str* data, struct file* inform);

//------------------------------------------------------------------------------------------------

#endif 