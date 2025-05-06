/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_head.c
*/

#include "../include/cuddle.h"

void free_dataframe_partial(dataframe_t *df, int rows)
{
    for (int i = 0; i < rows; i++)
        free_data_row(df->data[i], df->nb_columns);
    free(df->data);
    free_col_names(df->column_names, df->nb_columns);
    free(df->column_types);
    free(df);
}

char **copy_col_names(char **src_names, int nb_columns)
{
    char **new_names = malloc(sizeof(char *) * nb_columns);
    int i = 0;

    if (!new_names)
        return NULL;
    for (i = 0; i < nb_columns; i++) {
        new_names[i] = strdup(src_names[i]);
        if (!new_names[i])
            break;
    }
    if (i < nb_columns) {
        for (int j = 0; j < i; j++)
            free(new_names[j]);
        free(new_names);
        return NULL;
    }
    return new_names;
}

column_type_t *copy_col_types(column_type_t *src_types,
    int nb_columns)
{
    column_type_t *new_types = malloc(sizeof(column_type_t) * nb_columns);

    if (!new_types)
        return NULL;
    for (int i = 0; i < nb_columns; i++)
        new_types[i] = src_types[i];
    return new_types;
}

static void *copy_int_float_value(void *src, column_type_t type)
{
    void *dest = NULL;

    if (type == INT) {
        dest = malloc(sizeof(int));
        if (dest)
            *(int *)dest = *(int *)src;
    } else if (type == FLOAT) {
        dest = malloc(sizeof(float));
        *(float *)dest = *(float *)src;
    }
    return dest;
}

static void *copy_uint_bool_value(void *src, column_type_t type)
{
    void *dest = NULL;

    if (type == UINT) {
        dest = malloc(sizeof(unsigned int));
        if (dest)
            *(unsigned int *)dest = *(unsigned int *)src;
    } else if (type == BOOL) {
        dest = malloc(sizeof(bool));
        *(bool *)dest = *(bool *)src;
    }
    return dest;
}

void *copy_value(void *src, column_type_t type)
{
    if (type == STRING) {
        return strdup((char *)src);
    } else if (type == INT || type == FLOAT) {
        return copy_int_float_value(src, type);
    } else {
        return copy_uint_bool_value(src, type);
    }
}

static int copy_data_for_head(dataframe_t *new_df,
    dataframe_t *dataframe, int nb_rows)
{
    new_df->data = copy_data(dataframe->data, dataframe->column_types,
        nb_rows, new_df->nb_columns);
    if (!new_df->data) {
        free_col_names(new_df->column_names, new_df->nb_columns);
        free(new_df->column_types);
        return 0;
    }
    return 1;
}

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *new_df;

    if (!dataframe)
        return NULL;
    if (nb_rows > dataframe->nb_rows)
        nb_rows = dataframe->nb_rows;
    new_df = create_empty_dataframe(nb_rows, dataframe->nb_columns);
    if (!new_df)
        return NULL;
    if (!init_new_dataframe(new_df, dataframe, nb_rows)) {
        free(new_df);
        return NULL;
    }
    if (!copy_data_for_head(new_df, dataframe, nb_rows)) {
        free(new_df);
        return NULL;
    }
    return new_df;
}
