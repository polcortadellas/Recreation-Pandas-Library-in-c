/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_read_csv.c
*/

#include "../include/cuddle.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief converts a column_type_t enum value to its string representation
 *
 * this function maps each column type enumeration value to a human-readable
 * string for display and debugging purposes
 *
 * @param type the column_type_t enum value to convert
 * @return String representation of the column type
 *
 * @note Returns "undefined" for unrecognized type values
 * @note The returned string is statically allocated and should not be freed
 */
const char *type_to_string(column_type_t type)
{
    switch (type) {
        case BOOL:
            return "bool";
        case INT:
            return "int";
        case UINT:
            return "unsigned int";
        case FLOAT:
            return "float";
        case STRING:
            return "string";
        default:
            return "undefined";
    }
}

/**
 * @brief prints information about a dataframe to stdout
 *
 * this function displays a summary of the dataframe structure, including:
 * - number of columns
 * - name of each column
 * - data type of each column
 *
 * @param dataframe Pointer to the dataframe to display information about
 *
 * @note Handles NULL dataframe input gracefully with an error message
 */
void df_info(dataframe_t *dataframe)
{
    if (dataframe == NULL) {
        printf("Dataframe is NULL\n");
        return;
    }
    printf("%d columns:\n", dataframe->nb_columns);
    for (int i = 0; i < dataframe->nb_columns; i++) {
        printf("- %s: %s\n",
                dataframe->column_names[i],
                type_to_string(dataframe->column_types[i]));
    }
}
