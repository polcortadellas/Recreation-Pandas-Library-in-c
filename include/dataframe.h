/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** dataframe.h
*/

#ifndef DATAFRAME_H
    #define DATAFRAME_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <string.h>
    #include <math.h>


typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_types;
    void ***data;
    char *separator;
} dataframe_t;

typedef struct parse_csv_line_params_s {
    int row_idx;
    int columns;
} parse_csv_line_params_t;

int get_column_count(const char *line, const char *separator);
int get_row_count(FILE *file);
char **get_column_names(char *line, const char *separator);

void *convert_value(char *value, column_type_t type);
column_type_t get_value_type(char *value);

void parse_and_store_csv_line(char *line,
    const char *separator, dataframe_t *df);

dataframe_t *df_read_csv(const char *filename, const char *separator);
void df_info(dataframe_t *dataframe);

//lib:
int df_write_csv(dataframe_t *dataframe, const char *filename);

//head
typedef struct column_s {
    char *name;
    column_type_t type;
} column_t;
char **copy_col_names(char **src_names, int nb_columns);
void free_dataframe_partial(dataframe_t *df, int rows);
void free_data_row(void **row, int nb_columns);
void free_col_names(char **column_names, int nb_columns);
dataframe_t *create_empty_dataframe(int nb_rows, int nb_columns);
int init_new_dataframe(dataframe_t *new_df,
    dataframe_t *dataframe, int nb_rows);
void **copy_row(void **src_row, column_type_t *column_types,
    int nb_columns);
column_type_t *copy_col_types(column_type_t *src_types,
    int nb_columns);
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
void *copy_value(void *src, column_type_t type);

//shape
typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

dataframe_shape_t df_shape(dataframe_t *dataframe);

//describe
typedef struct describe_values_s {
    char *column;
    int count;
    float mean;
    float std;
    float min;
    float max;
} describe_t;
void df_describe(dataframe_t *dataframe);

//filter
dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value));
void *df_get_value(dataframe_t *df, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
// free
void df_free(dataframe_t *dataframe);

int copy_column_types(dataframe_t *src, dataframe_t *dst);
int copy_column_names(dataframe_t *src, dataframe_t *dst);
int allocate_data_rows(dataframe_t *dst);
int copy_data_values(dataframe_t *src, dataframe_t *dst, int start_row);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);


void **df_get_unique_values(dataframe_t *dataframe, const char *column);
void ***copy_data(void ***src_data, column_type_t *column_types,
    int rows, int nb_columns);
dataframe_t *df_apply(dataframe_t *dataframe,
    const char *column, void *(*apply_func)(void *value));


#endif
