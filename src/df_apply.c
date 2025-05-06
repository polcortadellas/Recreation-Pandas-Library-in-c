/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_apply.c
*/
#include "../include/cuddle.h"
#include <string.h>

void ***copy_data(void ***src_data, column_type_t *column_types,
    int rows, int nb_columns)
{
    void ***new_data = malloc(sizeof(void **) * rows);
    int i = 0;

    if (!new_data)
        return NULL;
    for (i = 0; i < rows; i++) {
        new_data[i] = copy_row(src_data[i], column_types, nb_columns);
        if (!new_data[i])
            break;
    }
    if (i < rows) {
        for (int j = 0; j < i; j++)
            free_data_row(new_data[j], nb_columns);
        free(new_data);
        return NULL;
    }
    return new_data;
}

static dataframe_t *create_and_initialize_df(dataframe_t *src_df)
{
    dataframe_t *new_df = create_empty_dataframe(src_df->nb_rows,
                                                    src_df->nb_columns);

    if (!new_df)
        return NULL;
    if (!init_new_dataframe(new_df, src_df, src_df->nb_rows)) {
        free(new_df);
        return NULL;
    }
    return new_df;
}

static int copy_dataframe_data(dataframe_t *new_df, dataframe_t *src_df)
{
    if (src_df->nb_rows > 0) {
        new_df->data = copy_data(src_df->data, src_df->column_types,
                                    src_df->nb_rows, new_df->nb_columns);
        if (!new_df->data)
            return 0;
    } else {
        new_df->data = NULL;
    }
    return 1;
}

dataframe_t *df_copy(dataframe_t *src_df)
{
    dataframe_t *new_df;

    if (!src_df)
        return NULL;
    new_df = create_and_initialize_df(src_df);
    if (!new_df)
        return NULL;
    if (!copy_dataframe_data(new_df, src_df)) {
        free_col_names(new_df->column_names, new_df->nb_columns);
        free(new_df->column_types);
        free(new_df);
        return NULL;
    }
    new_df->separator = strdup(src_df->separator ? src_df->separator : ",");
    return new_df;
}

static int find_column_index(dataframe_t *dataframe, const char *column)
{
    if (!dataframe || !column)
        return -1;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0)
            return i;
    }
    return -1;
}

static int validate_apply_inputs(dataframe_t *dataframe,
    const char *column, void *(*apply_func)(void *))
{
    if (!dataframe || !column || !apply_func)
        return -1;
    return find_column_index(dataframe, column);
}

static int apply_function_to_column(dataframe_t *new_df,
    int col_index, void *(*apply_func)(void *))
{
    void *old_value;
    void *new_value;

    for (int i = 0; i < new_df->nb_rows; i++) {
        old_value = new_df->data[i][col_index];
        new_value = apply_func(old_value);
        if (!new_value)
            return 0;
        free(old_value);
        new_df->data[i][col_index] = new_value;
    }
    return 1;
}

dataframe_t *df_apply(dataframe_t *dataframe,
    const char *column, void *(*apply_func)(void *))
{
    int col_index = validate_apply_inputs(dataframe, column, apply_func);
    dataframe_t *new_df = df_copy(dataframe);

    if (col_index == -1)
        return NULL;
    if (!new_df)
        return NULL;
    if (!apply_function_to_column(new_df, col_index, apply_func)) {
        df_free(new_df);
        return NULL;
    }
    return new_df;
}
