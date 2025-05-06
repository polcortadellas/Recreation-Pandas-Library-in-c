/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_get_value.c
*/

#include "../include/cuddle.h"

//castea los valores de void data a float pero para hacerlo se castea a cada
//tipo en especifico
static float get_value(void *data, column_type_t type)
{
    if (type == INT)
        return (float)(*(int *)data);
    if (type == UINT)
        return (float)(*(unsigned int *)data);
    if (type == FLOAT)
        return *(float *)data;
    return 0.0;
}

static float calculate_mean(void **values, int count, column_type_t type)
{
    float sum = 0.0;

    for (int i = 0; i < count; i++) {
        sum += get_value(values[i], type);
    }
    return sum / count;
}

float calculate_std(void **values, int count, column_type_t type, float mean)
{
    float sum_squared_diff = 0.0;
    float value;

    for (int i = 0; i < count; i++) {
        value = get_value(values[i], type);
        sum_squared_diff += pow(value - mean, 2);
    }
    return sqrt(sum_squared_diff / count);
}

float find_min(void **values, int count, column_type_t type)
{
    float min = get_value(values[0], type);
    float value;

    for (int i = 1; i < count; i++) {
        value = get_value(values[i], type);
        if (value < min)
            min = value;
    }
    return min;
}

float find_max(void **values, int count, column_type_t type)
{
    float max = get_value(values[0], type);
    float value;

    for (int i = 1; i < count; i++) {
        value = get_value(values[i], type);
        if (value > max)
            max = value;
    }
    return max;
}

void calculate_stats(dataframe_t *data, describe_t *stats, int columns)
{
    void **values = malloc(data->nb_rows * sizeof(void *));

    for (int i = 0; i < data->nb_rows; i++) {
        values[i] = data->data[i][columns];
    }
    stats->column = strdup(data->column_names[columns]);
    stats->count = data->nb_rows;
    stats->mean = calculate_mean(values, data->nb_rows,
        data->column_types[columns]);
    stats->min = find_min(values, data->nb_rows, data->column_types[columns]);
    stats->max = find_max(values, data->nb_rows, data->column_types[columns]);
    stats->std = calculate_std(values, data->nb_rows,
        data->column_types[columns], stats->mean);
    free(values);
}

void df_describe(dataframe_t *dataframe)
{
    column_type_t type;
    describe_t stats = {0};

    if (!dataframe)
        return;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        type = dataframe->column_types[i];
        if (type == INT || type == UINT || type == FLOAT) {
            calculate_stats(dataframe, &stats, i);
            printf("Column: %s\n", stats.column);
            printf("Count: %d\n", stats.count);
            printf("Mean: %.2f\n", stats.mean);
            printf("Std: %.2f\n", stats.std);
            printf("Min: %.2f\n", stats.min);
            printf("Max: %.2f\n", stats.max);
            printf("\n");
            free(stats.column);
        }
    }
}
