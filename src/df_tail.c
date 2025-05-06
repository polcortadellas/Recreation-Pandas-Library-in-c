/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_tail.c
*/

#include "../include/cuddle.h"
#include <stdlib.h>
#include <string.h>

static int free_column_names_partial(char **names, int count)
{
    for (int j = 0; j < count; j++)
        free(names[j]);
    free(names);
    return -1;
}

int copy_column_names(dataframe_t *src, dataframe_t *dst)
{
    dst->column_names = malloc(dst->nb_columns * sizeof(char *));
    if (!dst->column_names)
        return -1;
    for (int i = 0; i < dst->nb_columns; i++) {
        dst->column_names[i] = strdup(src->column_names[i]);
        if (!dst->column_names[i])
            return free_column_names_partial(dst->column_names, i);
    }
    return 0;
}

static void free_data_matrix(dataframe_t *df)
{
    for (int i = 0; i < df->nb_rows; i++) {
        if (!df->data[i])
            continue;
        for (int j = 0; j < df->nb_columns; j++)
            free(df->data[i][j]);
        free(df->data[i]);
    }
    free(df->data);
}

static void free_column_names(dataframe_t *df)
{
    for (int i = 0; i < df->nb_columns; i++)
        free(df->column_names[i]);
    free(df->column_names);
}

static void cleanup_dataframe(dataframe_t *df, int cleanup_level)
{
    if (cleanup_level >= 3 && df->data)
        free_data_matrix(df);
    if (cleanup_level >= 2 && df->column_types)
        free(df->column_types);
    if (cleanup_level >= 1 && df->column_names)
        free_column_names(df);
    free(df);
}

static dataframe_t *cleanup_and_return_null(dataframe_t *df, int cleanup_level)
{
    cleanup_dataframe(df, cleanup_level);
    return NULL;
}

static dataframe_t *setup_tail_dataframe(dataframe_t *src,
    dataframe_t *tail, int start_row)
{
    if (copy_column_names(src, tail) != 0)
        return cleanup_and_return_null(tail, 0);
    if (copy_column_types(src, tail) != 0)
        return cleanup_and_return_null(tail, 1);
    if (allocate_data_rows(tail) != 0)
        return cleanup_and_return_null(tail, 2);
    if (copy_data_values(src, tail, start_row) != 0)
        return cleanup_and_return_null(tail, 3);
    return tail;
}

dataframe_t *df_tail(dataframe_t *df, int nb_rows)
{
    dataframe_t *tail = malloc(sizeof(dataframe_t));
    int start_row;

    if (!df || nb_rows <= 0)
        return NULL;
    tail = malloc(sizeof(dataframe_t));
    if (!tail)
        return NULL;
    nb_rows = (nb_rows > df->nb_rows) ? df->nb_rows : nb_rows;
    start_row = df->nb_rows - nb_rows;
    tail->nb_columns = df->nb_columns;
    tail->nb_rows = nb_rows;
    tail->separator = strdup(df->separator ? df->separator : ",");
    return setup_tail_dataframe(df, tail, start_row);
}
