/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_read_csv.c
*/

#include "../../include/cuddle.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief updates current column type based on a new value type
 *
 * this function implements type conversion rules to ensure columns
 * can properly represent all their contained values:
 * - if current is BOOL and value is not BOOL, upgrades to value's type
 * - if current is UINT and value is INT, upgrades to INT
 * - if current is numeric (UINT or INT) and value is FLOAT, upgrades to FLOAT
 *
 * @param current Pointer to the current column type (modified if needed)
 * @param value_type The type of the new value being analyzed
 */
void column_utils(column_type_t *current, column_type_t value_type)
{
    if (*current == BOOL && value_type != BOOL)
        *current = value_type;
    if (*current == UINT && value_type == INT)
        *current = INT;
    if ((*current == UINT || *current == INT) && value_type == FLOAT)
        *current = FLOAT;
}

/**
 * @brief determines the most appropriate type for a column based on its values
 *
 * this function analyzes all values in a column to find the minimum type
 * that can represent all data. It follows a type promotion hierarchy:
 * BOOL -> UINT -> INT -> FLOAT -> STRING
 *
 * the type with the highest precedence encountered in the column will be used.
 * if any value is a STRING, the entire column will be treated as STRING.
 *
 * @param values Array of string values from the column
 * @param row_count Number of rows (values) in the column
 * @return The determined column_type_t that can represent all values
 */
column_type_t determine_column_type(char **values, int row_count)
{
    column_type_t value_type;
    column_type_t current;

    if (row_count == 0 || values[0] == NULL)
        return STRING;
    current = get_value_type(values[0]);
    if (current == STRING)
        return STRING;
    for (int i = 1; i < row_count; i++) {
        if (values[i] == NULL)
            continue;
        value_type = get_value_type(values[i]);
        if (value_type == STRING)
            return STRING;
        column_utils(&current, value_type);
    }
    return current;
}

/**
 * @brief allocates memory for temporary storage of CSV data
 *
 * creates a 2D array of string pointers with dimensions [columns][rows]
 * to store the raw string values from the CSV before type conversion.
 *
 * @param columns number of columns in the CSV
 * @param rows number of rows in the CSV
 * @return a newly allocated 3D array for temporary data storage
 *
 * @note Caller is responsible for freeing this memory
 */
static char ***initialize_temp_storage(int columns, int rows)
{
    char ***temp_data = malloc(columns * sizeof(char **));

    for (int i = 0; i < columns; i++)
        temp_data[i] = malloc(rows * sizeof(char *));
    return temp_data;
}

/**
 * @brief removes newline character from the end of a string
 *
 * this function sanitizes input lines by removing trailing newlines
 * that may be present from file reading operations.
 *
 * @param line the string to be cleaned
 */
static void clean_line(char *line)
{
    int len = strlen(line);

    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}

/**
 * @brief parses a single CSV line into columns and stores in temp data struct
 *
 * tokenizes the line using the provided separator and stores each column value
 * if there are fewer tokens than expected columns, empty strings are used as
 * fillers.
 *
 * @param line The CSV line to parse
 * @param separator The character(s) used to separate columns
 * @param temp_data The temporary storage array for column values
 * @param params Struct containing parsing params (row index and column count)
 * @return The number of columns successfully parsed
 */
int parse_csv_line(char *line, const char *separator,
    char ***temp_data, parse_csv_line_params_t *params)
{
    int col_idx = 0;
    char *token = strtok(line, separator);

    while (token && col_idx < params->columns) {
        temp_data[col_idx][params->row_idx] = strdup(token);
        token = strtok(NULL, separator);
        col_idx++;
    }
    for (; col_idx < params->columns; col_idx++) {
        temp_data[col_idx][params->row_idx] = strdup("");
    }
    return col_idx;
}

/**
 * @brief converts temporary data to types and populates the dataframe
 *
 * this function:
 * 1. determines the best type for each column
 * 2. converts each string value to the appropriate type
 * 3. stores the converted values in the dataframe's linear storage
 * 4. frees all temporary storage
 *
 * @param temp_data The temporary string data storage
 * @param df The dataframe to be populated
 */
void finalize_dataframe(char ***temp_data, dataframe_t *df)
{
    for (int col = 0; col < df->nb_columns; col++) {
        df->column_types[col] = determine_column_type(temp_data[col],
        df->nb_rows);
    }
    for (int row = 0; row < df->nb_rows; row++) {
        for (int col = 0; col < df->nb_columns; col++) {
            df->data[row][col] = convert_value(
                temp_data[col][row],
                df->column_types[col]
            );
            free(temp_data[col][row]);
        }
    }
    for (int col = 0; col < df->nb_columns; col++) {
        free(temp_data[col]);
    }
    free(temp_data);
}

/**
 * @brief parses and stores a line from a CSV file
 *
 * this function manages the entire CSV parsing process:
 * - initializes temporary storage on first call
 * - cleans input lines
 * - parses each line into columns
 * - tracks parsing progress with static variables
 * - finalizes the dataframe when all rows are processed
 *
 * @param line the csv line to parse
 * @param separator the character(s) used to separate columns
 * @param df the dataframe being constructed
 *
 * @note uses static variables to maintain state between calls
 * @note automatically finalizes the dataframe once all rows are processed
 */
void parse_and_store_csv_line(char *line,
    const char *separator, dataframe_t *df)
{
    static int row_idx = 0;
    static char ***temp_data = NULL;
    parse_csv_line_params_t params = {row_idx, df->nb_columns};

    if (temp_data == NULL) {
        temp_data = initialize_temp_storage(df->nb_columns, df->nb_rows);
    }
    if (row_idx >= df->nb_rows)
        return;
    clean_line(line);
    params.row_idx = row_idx;
    params.columns = df->nb_columns;
    parse_csv_line(line, separator, temp_data, &params);
    row_idx++;
    if (row_idx == df->nb_rows) {
        finalize_dataframe(temp_data, df);
        temp_data = NULL;
        row_idx = 0;
    }
}
