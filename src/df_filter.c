/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_free.c
*/

#include "../include/cuddle.h"
#include <string.h>

static int count_filtered_rows(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value))
{
    int column_index = -1;
    int count = 0;

    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0) {
            column_index = i;
            break;
        }
    }
    if (column_index == -1)
        return -1;
    for (int i = 0; i < dataframe->nb_rows; i++) {
        if (filter_func(dataframe->data[i][column_index]))
            count++;
    }
    return count;
}

int row_indices_utils(dataframe_t *dataframe, const char *col,
    int *indices, int column_index)
{
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], col) == 0) {
            column_index = i;
            break;
        }
    }
    if (column_index == -1) {
        free(indices);
        return 84;
    }
    return column_index;
}

static int *get_filtered_row_indices(dataframe_t *dataframe, const char *col,
    bool (*filter_func)(void *value), int filtered_rows)
{
    int column_index = -1;
    int *indices = malloc(sizeof(int) * filtered_rows);
    int index = 0;

    if (!indices)
        return NULL;
    column_index = row_indices_utils(dataframe, col, indices, column_index);
    if (column_index == 84)
        return NULL;
    for (int i = 0; i < dataframe->nb_rows; i++) {
        if (filter_func(dataframe->data[i][column_index])) {
            indices[index] = i;
            index++;
        }
    }
    return indices;
}

static void free_filtered_data(dataframe_t *new_df, int filtered_rows)
{
    for (int i = 0; i < filtered_rows; i++)
        free_data_row(new_df->data[i], new_df->nb_columns);
    free(new_df->data);
}

static int copy_filtered_data(dataframe_t *new_df, dataframe_t *dataframe,
    int *row_indices, int filtered_rows)
{
    int src_row;

    new_df->data = malloc(sizeof(void **) * filtered_rows);
    if (!new_df->data)
        return 0;
    for (int i = 0; i < filtered_rows; i++) {
        src_row = row_indices[i];
        new_df->data[i] = copy_row(dataframe->data[src_row],
            dataframe->column_types, dataframe->nb_columns);
        if (!new_df->data[i]) {
            free_filtered_data(new_df, i);
            return 0;
        }
    }
    return 1;
}

dataframe_t *df_filter_utils(dataframe_t *new_df, dataframe_t *dataframe,
    int filtered_rows, int *row_indices)
{
    if (!new_df)
        return NULL;
    if (!init_new_dataframe(new_df, dataframe, filtered_rows)) {
        free(new_df);
        return NULL;
    }
    if (!copy_filtered_data(new_df, dataframe, row_indices, filtered_rows)) {
        free(new_df);
        return NULL;
    }
    return new_df;
}

dataframe_t *df_filter(dataframe_t *df, const char *col,
    bool (*filter_func)(void *value))
{
    dataframe_t *new_df;
    int filter_rows;
    int *row_indices;

    if (!df || !col || !filter_func)
        return NULL;
    filter_rows = count_filtered_rows(df, col, filter_func);
    if (filter_rows <= 0)
        return create_empty_dataframe(0, df->nb_columns);
    row_indices = get_filtered_row_indices(df, col, filter_func, filter_rows);
    if (!row_indices)
        return NULL;
    new_df = create_empty_dataframe(filter_rows, df->nb_columns);
    new_df = df_filter_utils(new_df, df, filter_rows, row_indices);
    free(row_indices);
    new_df->separator = strdup(df->separator ? df->separator : ",");
    return new_df;
}
