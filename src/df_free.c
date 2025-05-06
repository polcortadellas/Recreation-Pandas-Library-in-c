/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_free.c
*/

#include "../include/cuddle.h"

void free_utils(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_rows; i++) {
        if (dataframe->data[i]) {
            free_data_row(dataframe->data[i], dataframe->nb_columns);
        }
    }
    free(dataframe->data);
}

void df_free(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    if (dataframe->data) {
        free_utils(dataframe);
    }
    if (dataframe->column_names) {
        free_col_names(dataframe->column_names, dataframe->nb_columns);
    }
    if (dataframe->column_types) {
        free(dataframe->column_types);
    }
    if (dataframe->separator) {
        free(dataframe->separator);
    }
    free(dataframe);
}
