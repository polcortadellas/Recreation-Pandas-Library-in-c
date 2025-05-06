/*
** EPITECH PROJECT, 2025
** G-AIA-200 cuddle
** File description:
** df_shape.c
*/

#include "../include/cuddle.h"

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape;

    if (!dataframe || !dataframe->nb_columns || !dataframe->nb_rows)
        return shape;
    shape.nb_columns = dataframe->nb_columns;
    shape.nb_rows = dataframe->nb_rows;
    return shape;
}
