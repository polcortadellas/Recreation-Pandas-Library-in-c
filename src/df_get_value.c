/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_get_value.c
*/

#include "../include/cuddle.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief retrieves a single value from a specific row and column in the df
 *
 * this function provides direct access to a specific cell in the dataframe by
 * identifying the column by name and the row by index. it returns a pointer to
 * the value stored at that location
 *
 * @param df Pointer to the dataframe
 * @param row Index of the row (zero-based)
 * @param column Name of the column to retrieve the value from
 *
 * @return Pointer to the value at the specified location, or NULL if:
 *         - The dataframe pointer is NULL
 *         - The row index is out of bounds
 *         - The column name is NULL
 *         - The column name does not exist in the dataframe
 *
 * @note the returned pointer points directly to the data within the dataframe
 *       structure. the caller should not free this memory
 * @note to access the actual value, the caller must cast the returned pointer
 *       to the appropriate type based on the column's data type
 *
 * @example
 *    // For an integer column
 *    int *value = (int *)df_get_value(df, 0, "Age");
 *    if (value) printf("Age: %d\n", *value);
 *
 *    // For a string column
 *    char *name = (char *)df_get_value(df, 0, "Name");
 *    if (name) printf("Name: %s\n", name);
 */
void *df_get_value(dataframe_t *df, int row, const char *column)
{
    if (!df || row < 0 || row >= df->nb_rows || !column)
        return NULL;
    for (int col = 0; col < df->nb_columns; col++) {
        if (strcmp(df->column_names[col], column) == 0)
            return df->data[row][col];
    }
    return NULL;
}
