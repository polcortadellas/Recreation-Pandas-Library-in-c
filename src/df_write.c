/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_head.c
*/
#include "../include/cuddle.h"

void define_type(dataframe_t *df, int row, int col, FILE *f)
{
    switch (df->column_types[col]) {
        case BOOL:
            fprintf(f, "%s", (*(bool *)df->data[row][col]) ? "true" : "false");
            return;
        case INT:
            fprintf(f, "%d", *((int *)df->data[row][col]));
            return;
        case UINT:
            fprintf(f, "%u", *((unsigned int *)df->data[row][col]));
            return;
        case FLOAT:
            fprintf(f, "%f", *((float *)df->data[row][col]));
            return;
        case STRING:
            fprintf(f, "%s", (char *)df->data[row][col]);
            return;
        default:
            return;
    }
}

void print_data(dataframe_t *df, int row, FILE *file)
{
    for (int col = 0; col < df->nb_columns; col++) {
        if (df->data[row][col] != NULL) {
            define_type(df, row, col, file);
        } else {
            fprintf(file, "NULL");
        }
        if (col < df->nb_columns - 1) {
            fprintf(file, "%s", df->separator);
        }
    }
    fprintf(file, "\n");
}

int df_write_csv(dataframe_t *df, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (df == NULL || !df->column_types || !df->data || file == NULL)
        return 84;
    for (int i = 0; i < df->nb_columns; i++) {
        fprintf(file, "%s", df->column_names[i]);
        if (i < df->nb_columns - 1)
            fprintf(file, "%s", df->separator);
    }
    fprintf(file, "\n");
    for (int i = 0; i < df->nb_rows; i++) {
        print_data(df, i, file);
    }
    fclose(file);
    return 0;
}
