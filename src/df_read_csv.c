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
 * @brief initializes a dataframe structure from CSV file metadata
 *
 * this function:
 * 1. opens the CSV file and reads the header row
 * 2. extracts column names and counts from the header
 * 3. counts the number of data rows in the file
 * 4. allocates memory for the dataframe's data structures
 * 5. cleans up and closes the file
 *
 * This function only initializes the structure, does not read the actual data
 *
 * @param filename Path to the CSV file
 * @param df Pointer to the dataframe to initialize
 * @param separator The character(s) used to separate columns in the CSV
 *
 * @note Returns silently if the file cannot be opened
 * @note Caller must ensure df is allocated before calling this function
 * @note This function allocate memory for column_names, data, and column_types
 *       which the caller is responsible for freeing
 */
void initialize_dataframe_from_csv(const char *filename,
    dataframe_t *df, const char *separator)
{
    FILE *file = fopen(filename, "r");
    size_t len = 0;
    char *line = NULL;
    int read;

    if (file == NULL)
        return;
    read = getline(&line, &len, file);
    df->column_names = get_column_names(line, separator);
    df->nb_columns = get_column_count(line, separator);
    df->nb_rows = get_row_count(file);
    df->data = malloc(df->nb_rows * sizeof(void **));
    for (int i = 0; i < df->nb_rows; i++)
        df->data[i] = malloc(df->nb_columns * sizeof(void *));
    df->column_types = malloc(df->nb_columns * sizeof(column_type_t));
    df->separator = strdup(separator ? separator : ",");
    rewind(file);
    getline(&line, &len, file);
    free(line);
    fclose(file);
}

/**
 * @brief deads and parses data from a CSV file into an initialized dataframe
 *
 * this function:
 * 1. opens the CSV file
 * 2. skips the header row
 * 3. reads each data row and calls parse_and_store_csv_line() to process it
 * 4. displays dataframe information after loading
 * 5. cleans up resources
 *
 * @param filename Path to the CSV file
 * @param df Pointer to the initialized dataframe structure
 * @param separator The character(s) used to separate columns in the CSV
 *
 * @note Returns silently if the file cannot be opened
 * @note Expects dataframe to be initialized by initialize_dataframe_from_csv()
 */
void read_csv_data(const char *filename,
    dataframe_t *df, const char *separator)
{
    FILE *file = fopen(filename, "r");
    size_t len = 0;
    char *line = NULL;
    int read;
    int row_count = 0;

    if (file == NULL)
        return;
    read = getline(&line, &len, file);
    while (read != -1 && row_count < df->nb_rows) {
        read = getline(&line, &len, file);
        if (read != -1) {
            parse_and_store_csv_line(line, separator, df);
            row_count++;
        }
    }
    free(line);
    fclose(file);
}

/**
 * @brief complete procedure to read a CSV file into a dataframe
 *
 * this function combines the initialization and data reading steps
 * into a single call for convenience
 *
 * @param filename Path to the CSV file
 * @param df Pointer to the dataframe to populate
 * @param separator The character(s) used to separate columns in the CSV
 *
 * @note Caller must ensure df is allocated before calling this function
 * @note Wrapper that calls initialize_dataframe_from_csv() & read_csv_data()
 */
void read_csv(const char *filename, dataframe_t *df, const char *separator)
{
    initialize_dataframe_from_csv(filename, df, separator);
    read_csv_data(filename, df, separator);
}

/**
 * @brief creates and populates a new dataframe from a CSV file
 *
 * this function:
 * 1. allocates memory for a new dataframe structure
 * 2. checks if the specified file exists and is readable
 * 3. reads the CSV data into the dataframe if the file is accessible
 * 4. returns the populated dataframe or NULL on failure
 *
 * @param filename Path to the CSV file
 * @param separator The character(s) used to separate columns in the CSV
 * @return Pointer to the created dataframe, or NULL if no access to the file
 *
 * @note Caller is responsible for freeing the dataframe and its components
 * @note Uses access() to check file permissions before attempting to read
 */
dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    dataframe_t *dataframe = malloc(sizeof(dataframe_t));

    if (!dataframe)
        return NULL;
    dataframe->separator = strdup(separator ? separator : ",");
    if (!dataframe->separator) {
        free(dataframe);
        return NULL;
    }
    if (access(filename, R_OK) != -1) {
        read_csv(filename, dataframe, dataframe->separator);
    } else {
        free(dataframe->separator);
        free(dataframe);
        return NULL;
    }
    return dataframe;
}
