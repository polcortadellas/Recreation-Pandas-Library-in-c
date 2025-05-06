/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_tail.c
*/

#include "../../include/cuddle.h"
#include <stdlib.h>
#include <string.h>

int copy_column_types(dataframe_t *src, dataframe_t *dst)
{
    dst->column_types = malloc(dst->nb_columns * sizeof(column_type_t));
    if (!dst->column_types)
        return -1;
    memcpy(dst->column_types, src->column_types,
            dst->nb_columns * sizeof(column_type_t));
    return 0;
}

int allocate_data_rows(dataframe_t *dst)
{
    dst->data = malloc(dst->nb_rows * sizeof(void **));
    if (!dst->data)
        return -1;
    return 0;
}

// why size_t? i'm trying to understand when and when not to use it.
// ref: questions/502856/whats-the-difference-between-size-t-and-int-in-c
//      ^ is from stack overflow
static size_t get_type_size(column_type_t type)
{
    switch (type) {
        case BOOL:
            return sizeof(bool);
        case INT:
            return sizeof(int);
        case UINT:
            return sizeof(unsigned int);
        case FLOAT:
            return sizeof(float);
        default:
            return 0;
    }
}

static void *copy_primitive_value(void *src, size_t size)
{
    void *dest;

    if (size == 0)
        return NULL;
    dest = malloc(size);
    if (dest)
        memcpy(dest, src, size);
    return dest;
}

void *copy_value_by_type(void *src_value, column_type_t type)
{
    if (!src_value)
        return NULL;
    if (type == STRING)
        return strdup((char *)src_value);
    return copy_primitive_value(src_value, get_type_size(type));
}

void copy_row_values(dataframe_t *src, dataframe_t *dst, int dst_r, int st_r)
{
    for (int j = 0; j < dst->nb_columns; j++)
        dst->data[dst_r][j] = copy_value_by_type(src->data[st_r + dst_r][j],
                                                    src->column_types[j]);
}

static int free_allocated_rows(dataframe_t *dst, int last_row)
{
    for (int j = 0; j <= last_row; j++)
        free(dst->data[j]);
    return -1;
}

int copy_data_values(dataframe_t *src, dataframe_t *dst, int start_row)
{
    for (int i = 0; i < dst->nb_rows; i++) {
        dst->data[i] = malloc(dst->nb_columns * sizeof(void *));
        if (!dst->data[i])
            return free_allocated_rows(dst, i - 1);
        copy_row_values(src, dst, i, start_row);
    }
    return 0;
}
