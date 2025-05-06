/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_get_unique_values.c
*/

#include "../include/cuddle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_string_values(char *value1, char *value2)
{
    return strcmp(value1, value2) == 0;
}

static int compare_int_values(int *value1, int *value2)
{
    return *value1 == *value2;
}

static int compare_float_values(float *value1, float *value2)
{
    return *value1 == *value2;
}

static int compare_values(void *value1, void *value2, column_type_t type)
{
    switch (type) {
        case STRING:
            return compare_string_values((char *)value1, (char *)value2);
        case BOOL:
        case INT:
        case UINT:
            return compare_int_values((int *)value1, (int *)value2);
        case FLOAT:
            return compare_float_values((float *)value1, (float *)value2);
        default:
            return 0;
    }
}

static int value_exists(void **values, void *value,
    int count, column_type_t type)
{
    for (int i = 0; i < count; i++) {
        if (!values[i])
            continue;
        if (compare_values(values[i], value, type))
            return 1;
    }
    return 0;
}

static int find_column_index(dataframe_t *dataframe,
    const char *column, column_type_t *type)
{
    int name_matches;

    for (int i = 0; i < dataframe->nb_columns; i++) {
        name_matches = strcmp(dataframe->column_names[i], column) == 0;
        if (!name_matches)
            continue;
        if (type)
            *type = dataframe->column_types[i];
        return i;
    }
    return -1;
}

static void **init_unique_values_array(int size)
{
    void **unique_values = malloc((size + 1) * sizeof(void *));

    if (!unique_values)
        return NULL;
    for (int i = 0; i <= size; i++)
        unique_values[i] = NULL;
    return unique_values;
}

void **collect_unique_values(dataframe_t *dataframe, int col_index,
    column_type_t col_type)
{
    void **unique_vs = init_unique_values_array(dataframe->nb_rows);
    int unique_count = 0;
    void *current_value;

    if (!unique_vs)
        return NULL;
    for (int i = 0; i < dataframe->nb_rows; i++) {
        current_value = dataframe->data[i][col_index];
        if (!value_exists(unique_vs, current_value, unique_count, col_type)) {
            unique_vs[unique_count] = current_value;
            unique_count++;
        }
    }
    return unique_vs;
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    column_type_t col_type;
    int col_index;

    if (!dataframe || !column)
        return NULL;
    col_index = find_column_index(dataframe, column, &col_type);
    if (col_index == -1)
        return NULL;
    return collect_unique_values(dataframe, col_index, col_type);
}
