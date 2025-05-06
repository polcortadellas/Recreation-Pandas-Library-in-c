/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** dataframe_utils.c
*/

#include "../../include/cuddle.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * @brief Counts the number of columns in a string based on the given separator
 *
 * This function creates a temporary copy of the input line to avoid modifying
 * the original string while tokenizing it.
 *
 * @param line The string to analyze
 * @param separator The character(s) that separate columns in the line
 * @return Number of columns (tokens) found in the line
 *
 */
int get_column_count(const char *line, const char *separator)
{
    char *temp_line = strdup(line);
    char *token = strtok(temp_line, separator);
    int count = 0;

    while (token != NULL) {
        count++;
        token = strtok(NULL, separator);
    }
    free(temp_line);
    return count;
}

/**
 * @brief counts the number of data rows in a file, excluding the header row
 *
 * this function preserves the original file pointer position by:
 * 1. saving the current position using ftell()
 * 2. rewinding to the start of the file for counting
 * 3. restoring the original position with fseek() when done
 *
 * @param file pointer to an open file (must not be null)
 * @return number of data rows (excluding header), or 0 if empty/invalid file
 *
 * @note the function allocates memory internally with getline() which is
 *       properly freed before returning.
 */
int get_row_count(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    int count = -1;
    long original_position;

    if (file == NULL)
        return 0;
    original_position = ftell(file);
    rewind(file);
    while (getline(&line, &len, file) != -1)
        count++;
    if (line)
        free(line);
    fseek(file, original_position, SEEK_SET);
    return count > 0 ? count : 0;
}

/**
 * @brief removes a trailing newline character from a string if present
 *
 * @param str The string to modify.
 */
static void remove_bkslhn(char *str)
{
    int len = strlen(str);

    if (str) {
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

/**
 * @brief extracts column names from a header line using the given separator
 *
 * this function:
 * 1. counts the number of columns in the line
 * 2. allocates memory for an array of column name strings
 * 3. tokenizes the line and copies each column name
 *
 * @param line the header line containing column names
 * @param separator the character(s) that separate columns in the line
 * @return Array of strings containing column names, or NULL if malloc fails
 *
 * @note The caller is responsible for freeing the array and each string in it
 */
char **get_column_names(char *line, const char *separator)
{
    int count = get_column_count(line, separator);
    char **column_names = malloc(count * sizeof(char *));
    char *temp_line = strdup(line);
    char *t = strtok(temp_line, separator);

    if (column_names == NULL)
        return NULL;
    temp_line = strdup(line);
    if (temp_line == NULL) {
        free(column_names);
        return NULL;
    }
    t = strtok(temp_line, separator);
    for (int i = 0; i < count && t != NULL; i++) {
        column_names[i] = strdup((i == count - 1 ? (remove_bkslhn(t), t) : t));
        t = strtok(NULL, separator);
    }
    free(temp_line);
    return column_names;
}
