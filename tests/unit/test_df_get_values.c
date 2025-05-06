#include <criterion/criterion.h>
#include <stdlib.h>
#include "../../include/cuddle.h"
#include "../../include/tests.h"

Test(df_get_values_suite, test_valid_string_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "celestial_object");
    cr_assert_not_null(values, "df_get_values returned NULL for a valid string column");
    cr_assert_str_eq((char *)values[0], "Gliese 581g", "First string value doesn't match expected value");
    cr_assert_str_eq((char *)values[3], "TRAPPIST-1e", "Fourth string value doesn't match expected value");
    cr_assert_null(values[df->nb_rows], "Array should be NULL-terminated");

    free(values);
    cleanup_df(df);
}

Test(df_get_values_suite, test_valid_bool_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "is_habitable");
    cr_assert_not_null(values, "df_get_values returned NULL for a valid bool column");
    cr_assert_eq(*(bool *)values[0], true, "First bool value doesn't match expected value");
    cr_assert_null(values[df->nb_rows], "Array should be NULL-terminated");

    free(values);
    cleanup_df(df);
}

Test(df_get_values_suite, test_valid_float_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "light_years_distance");
    cr_assert_not_null(values, "df_get_values returned NULL for a valid float column");
    cr_assert_float_eq(*(float *)values[0], 20.4f, 0.0001, "First float value doesn't match expected value");
    cr_assert_null(values[df->nb_rows], "Array should be NULL-terminated");

    free(values);
    cleanup_df(df);
}

Test(df_get_values_suite, test_valid_int_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "discovery_year");
    cr_assert_not_null(values, "df_get_values returned NULL for a valid int column");
    cr_assert_eq(*(int *)values[0], 2010, "First int value doesn't match expected value");
    cr_assert_null(values[df->nb_rows], "Array should be NULL-terminated");

    free(values);
    cleanup_df(df);
}

Test(df_get_values_suite, test_all_rows_present)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "celestial_object");
    cr_assert_not_null(values, "df_get_values returned NULL for a valid string column");
    cr_assert_not_null(values[df->nb_rows - 1], "Last row value should not be NULL");
    cr_assert_null(values[df->nb_rows], "Array should be NULL-terminated");

    free(values);
    cleanup_df(df);
}

Test(df_get_values_suite, test_null_dataframe)
{
    void **values = df_get_values(NULL, "celestial_object");
    cr_assert_null(values, "df_get_values should return NULL for a NULL dataframe");
}

Test(df_get_values_suite, test_null_column_name)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, NULL);
    cr_assert_null(values, "df_get_values should return NULL for a NULL column name");

    cleanup_df(df);
}

Test(df_get_values_suite, test_invalid_column_name)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "nonexistent_column");
    cr_assert_null(values, "df_get_values should return NULL for an invalid column name");

    cleanup_df(df);
}

Test(df_get_values_suite, test_empty_column_name)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "");
    cr_assert_null(values, "df_get_values should return NULL for an empty string column name");

    cleanup_df(df);
}

Test(df_get_values_suite, test_empty_dataframe)
{
    // Create an empty dataframe with columns but no rows
    dataframe_t *df = malloc(sizeof(dataframe_t));
    df->nb_rows = 0;
    df->nb_columns = 3;
    df->column_names = malloc(3 * sizeof(char *));
    df->column_names[0] = strdup("celestial_object");
    df->column_names[1] = strdup("discovery_year");
    df->column_names[2] = strdup("light_years_distance");
    df->data = NULL; // No rows

    void **values = df_get_values(df, "celestial_object");
    cr_assert_not_null(values, "df_get_values should return an empty array for a valid column in an empty dataframe");
    cr_assert_null(values[0], "First element should be NULL in an empty dataframe");

    free(values);
    free(df->column_names[0]);
    free(df->column_names[1]);
    free(df->column_names[2]);
    free(df->column_names);
    free(df);
}

Test(df_get_values_suite, test_consistency_with_df_get_value)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void **values = df_get_values(df, "celestial_object");
    cr_assert_not_null(values, "df_get_values returned NULL for a valid string column");

    for (int i = 0; i < df->nb_rows; i++) {
        void *single_value = df_get_value(df, i, "celestial_object");
        cr_assert_str_eq((char *)values[i], (char *)single_value, 
                         "Value from df_get_values doesn't match df_get_value at row %d", i);
    }

    free(values);
    cleanup_df(df);
}
