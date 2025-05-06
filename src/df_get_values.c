/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_get_values.c
*/

#include "../include/cuddle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief returns an array of all values in the specified column
 *
 * this function extracts all values from a specified column in the dataframe
 * and returns them as a NULL-terminated array of void pointers
 *
 * @param dataframe Pointer to the dataframe to extract values from
 * @param column Name of the column to extract values from
 *
 * @return NULL-terminated array of pointers to values, or NULL if column not
 *         found or if dataframe is NULL
 *
 * @note The caller is responsible for freeing the returned array
 *       (but not the values themselves, as they are still owned by dataframe)
 * @note Returns NULL if the column name is not found
 */
void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int col_index = -1;
    void **values = NULL;

    if (!dataframe || !column)
        return NULL;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0) {
            col_index = i;
            break;
        }
    }
    if (col_index == -1)
        return NULL;
    values = malloc((dataframe->nb_rows + 1) * sizeof(void *));
    if (!values)
        return NULL;
    for (int i = 0; i < dataframe->nb_rows; i++)
        values[i] = dataframe->data[i][col_index];
    values[dataframe->nb_rows] = NULL;
    return values;
}
