/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_head.c
*/

#include "../../include/cuddle.h"

void free_col_names(char **column_names, int nb_columns)
{
    for (int i = 0; i < nb_columns; i++)
        free(column_names[i]);
    free(column_names);
}

void free_data_row(void **row, int nb_columns)
{
    for (int i = 0; i < nb_columns; i++)
        free(row[i]);
    free(row);
}

dataframe_t *create_empty_dataframe(int nb_rows, int nb_columns)
{
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!df)
        return NULL;
    df->nb_rows = nb_rows;
    df->nb_columns = nb_columns;
    df->column_names = NULL;
    df->column_types = NULL;
    df->data = NULL;
    return df;
}

int init_new_dataframe(dataframe_t *new_df,
    dataframe_t *dataframe, int nb_rows)
{
    new_df->column_names = copy_col_names(dataframe->column_names,
        new_df->nb_columns);
    if (!new_df->column_names)
        return 0;
    new_df->column_types = copy_col_types(dataframe->column_types,
        new_df->nb_columns);
    if (!new_df->column_types) {
        free_col_names(new_df->column_names, new_df->nb_columns);
        return 0;
    }
    new_df->separator = strdup(dataframe->separator);
    if (!new_df->separator) {
        free_col_names(new_df->column_names, new_df->nb_columns);
        free(new_df->column_types);
        return 0;
    }
    return 1;
}

void **copy_row(void **src_row, column_type_t *column_types,
    int nb_columns)
{
    void **new_row = malloc(sizeof(void *) * nb_columns);
    int j = 0;

    if (!new_row)
        return NULL;
    for (j = 0; j < nb_columns; j++) {
        new_row[j] = copy_value(src_row[j], column_types[j]);
        if (!new_row[j])
            break;
    }
    if (j < nb_columns) {
        for (int k = 0; k < j; k++)
            free(new_row[k]);
        free(new_row);
        return NULL;
    }
    return new_row;
}
