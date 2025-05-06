#include <criterion/criterion.h>
#include <stdlib.h>
#include "../../include/cuddle.h"
#include "../../include/tests.h"

Test(df_get_value_suite, test_valid_string_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 0, "celestial_object");
    cr_assert_not_null(value, "df_get_value returned NULL for a valid string column");
    cr_assert_str_eq((char *)value, "Gliese 581g", "Retrieved string value doesn't match expected value");

    cleanup_df(df);
}

Test(df_get_value_suite, test_valid_bool_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 0, "is_habitable");
    cr_assert_not_null(value, "df_get_value returned NULL for a valid bool column");
    cr_assert_eq(*(bool *)value, true, "Retrieved bool value doesn't match expected value");

    cleanup_df(df);
}

Test(df_get_value_suite, test_valid_float_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 0, "light_years_distance");
    cr_assert_not_null(value, "df_get_value returned NULL for a valid float column");
    cr_assert_float_eq(*(float *)value, 20.4f, 0.0001, "Retrieved float value doesn't match expected value");

    cleanup_df(df);
}

Test(df_get_value_suite, test_valid_int_column)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 0, "discovery_year");
    cr_assert_not_null(value, "df_get_value returned NULL for a valid int column");
    cr_assert_eq(*(int *)value, 2010, "Retrieved int value doesn't match expected value");

    cleanup_df(df);
}

Test(df_get_value_suite, test_different_row)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 3, "celestial_object");
    cr_assert_not_null(value, "df_get_value returned NULL for a valid string column at row 3");
    cr_assert_str_eq((char *)value, "TRAPPIST-1e", "Retrieved string value doesn't match expected value");

    cleanup_df(df);
}

Test(df_get_value_suite, test_last_row)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    int last_idx = df->nb_rows - 1;
    void *value = df_get_value(df, last_idx, "celestial_object");
    cr_assert_not_null(value, "df_get_value returned NULL for a valid string column at last row");

    cleanup_df(df);
}

Test(df_get_value_suite, test_null_dataframe)
{
    void *value = df_get_value(NULL, 0, "celestial_object");
    cr_assert_null(value, "df_get_value should return NULL for a NULL dataframe");
}

Test(df_get_value_suite, test_null_column_name)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 0, NULL);
    cr_assert_null(value, "df_get_value should return NULL for a NULL column name");

    cleanup_df(df);
}

Test(df_get_value_suite, test_invalid_column_name)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, 0, "nonexistent_column");
    cr_assert_null(value, "df_get_value should return NULL for an invalid column name");

    cleanup_df(df);
}

Test(df_get_value_suite, test_negative_row)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, -1, "celestial_object");
    cr_assert_null(value, "df_get_value should return NULL for a negative row index");

    cleanup_df(df);
}

Test(df_get_value_suite, test_out_of_bounds_row)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    void *value = df_get_value(df, df->nb_rows, "celestial_object");
    cr_assert_null(value, "df_get_value should return NULL for an out of bounds row index");

    cleanup_df(df);
}

Test(df_get_value_suite, test_edge_cases)
{
    dataframe_t *df = helper_setup_df();
    cr_assert_not_null(df, "DataFrame initialization failed");

    // Test with empty string column name
    void *value = df_get_value(df, 0, "");
    cr_assert_null(value, "df_get_value should return NULL for an empty string column name");

    cleanup_df(df);
}
