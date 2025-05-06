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
 * @brief converts a string value to a boolean type
 *
 * this function allocates memory for a boolean value and populates it based
 * on the input string. string "true" (case-insensitive) is converted to true,
 * while any other value is converted to false.
 *
 * @param value The string to convert
 * @return Pointer to newly allocated boolean value, or NULL on failure
 *
 * @note Caller is responsible for freeing the returned memory
 * @note Returns NULL if the input is NULL or if memory allocation fails
 */
static void *convert_to_bool(char *value)
{
    bool *b;

    if (value == NULL)
        return NULL;
    b = malloc(sizeof(bool));
    if (b == NULL)
        return NULL;
    *b = (strcasecmp(value, "true") == 0) ? true : false;
    return b;
}

/**
 * @brief converts a string value to an integer type
 *
 * this function allocates memory for an integer value and populates it
 * by parsing the input string using base 10.
 *
 * @param value The string to convert
 * @return Pointer to newly allocated integer value, or NULL on failure
 *
 * @note Caller is responsible for freeing the returned memory
 * @note Returns NULL if the input is NULL or if memory allocation fails
 * @note Uses strtol() for conversion
 */
static void *convert_to_int(char *value)
{
    int *i;

    if (value == NULL)
        return NULL;
    i = malloc(sizeof(int));
    if (i == NULL)
        return NULL;
    *i = (int)strtol(value, NULL, 10);
    return i;
}

/**
 * @brief converts a string value to an unsigned integer type
 *
 * this function allocates memory for an unsigned int value and populates it
 * by parsing the input string using base 10.
 *
 * @param value The string to convert
 * @return Pointer to newly allocated unsigned integer value, or NULL on fail
 *
 * @note Caller is responsible for freeing the returned memory
 * @note Returns NULL if the input is NULL or if memory allocation fails
 * @note Uses strtoul() for conversion
 */
static void *convert_to_uint(char *value)
{
    unsigned int *ui;

    if (value == NULL)
        return NULL;
    ui = malloc(sizeof(unsigned int));
    if (ui == NULL)
        return NULL;
    *ui = (unsigned int)strtoul(value, NULL, 10);
    return ui;
}

/**
 * @brief converts a string value to a float type
 *
 * this function allocates memory for a float value and populates it
 * by parsing the input string.
 *
 * @param value The string to convert
 * @return Pointer to newly allocated float value, or NULL on failure
 *
 * @note Caller is responsible for freeing the returned memory
 * @note Returns NULL if the input is NULL or if memory allocation fails
 * @note Uses strtof() for conversion, which handles scientific notation
 */
static void *convert_to_float(char *value)
{
    float *f;

    if (value == NULL)
        return NULL;
    f = malloc(sizeof(float));
    if (f == NULL)
        return NULL;
    *f = strtof(value, NULL);
    return f;
}

/**
 * @brief converts a string value to a duplicated string
 *
 * this function duplicates the input string, allocating memory for the copy
 *
 * @param value The string to duplicate
 * @return Pointer to the newly allocated string, or NULL on failure
 *
 * @note Caller is responsible for freeing the returned memory
 */
static void *convert_to_string(char *value)
{
    char *s;

    if (value == NULL)
        return NULL;
    s = strdup(value);
    return s;
}

/**
 * @brief converts a string value to the specified column type
 *
 * this function serves as a dispatcher who calls the appropriate type-specific
 * conversion function based on the requested column type
 *
 * @param value The string value to convert
 * @param type The target column type to convert to
 * @return Pointer to newly allocated value of specified type, or NULL on fail
 *
 * @note Caller is responsible for freeing the returned memory
 * @note Falls back to string conversion for unrecognized types
 */
void *convert_value(char *value, column_type_t type)
{
    if (value == NULL)
        return NULL;
    switch (type) {
        case BOOL:
            return convert_to_bool(value);
        case INT:
            return convert_to_int(value);
        case UINT:
            return convert_to_uint(value);
        case FLOAT:
            return convert_to_float(value);
        case STRING:
        default:
            return convert_to_string(value);
    }
}

/**
 * @brief determines the most appropriate type for a string value
 *
 * this function analyzes a string to determine what data type it represents:
 * - "true" or "false" (case-insensitive) -> BOOL
 * - integers >= 0 -> UINT
 * - negative integers -> INT
 * - floating point numbers -> FLOAT
 * - any other string -> STRING
 *
 * type detection is performed in order of increasing flexibility
 *
 * @param value The string value to analyze
 * @return The determined column_type_t that best represents the value
 *
 * @note Empty strings or NULL values are treated as STRING type
 * @note Uses strtol() and strtod() to detect numeric formats
 */
column_type_t get_value_type(char *value)
{
    double float_val;
    long int_val;
    char *endptr;

    if (value == NULL || *value == '\0')
        return STRING;
    if (strcasecmp(value, "true") == 0 || strcasecmp(value, "false") == 0)
        return BOOL;
    int_val = strtol(value, &endptr, 10);
    if (*endptr == '\0') {
        if (int_val >= 0)
            return UINT;
        return INT;
    }
    float_val = strtod(value, &endptr);
    if (*endptr == '\0')
        return FLOAT;
    return STRING;
}
