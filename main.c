#include "include/cuddle.h"

// int main()
// {
//     dataframe_t *dataframe = df_read_csv("test.csv", ",");
//     df_write_csv(dataframe, "prueba.csv");
//     // for (int i = 0; i < data->nb_rows; ++i) {
//     //     for (int j = 0; j < data->nb_columns; ++j) {
//     //         if (data->data[i][j] == NULL)
//     //             printf("NULL ");
//     //         else if (data->column_types[j] == INT)
//     //             printf("%d ", *(int *)data->data[i][j]);
//     //         else if (data->column_types[j] == UINT)
//     //             printf("%u ", *(unsigned int *)data->data[i][j]);
//     //         else if (data->column_types[j] == FLOAT)
//     //             printf("%f ", *(float *)data->data[i][j]);
//     //         else if (data->column_types[j] == BOOL)
//     //             printf("%s ", (*(bool *)data->data[i][j]) ? "true" : "false");
//     //         else
//     //             printf("%s ", (char *)data->data[i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     return 0;
// }

// bool filter_func ( void * value )
// {
//     return *( int *) value > 30;
// }

// int main ( void )
// {
//     dataframe_t *dataframe = df_read_csv ("test.csv", ",");
//     printf("Dataframe: %d rows, %d columns\n", dataframe->nb_rows, dataframe->nb_columns);
//     dataframe_t *filtered = df_filter(dataframe, "age", filter_func);
//     df_write_csv(filtered ,"filtered.csv");
//     return 0;
// }


// bool filter_func(void *value)
// {
//     if (!value)
//         return false;
//     return *(int *)value > 30;
// }

// int main(void)
// {
//     dataframe_t *dataframe = df_read_csv("test.csv", NULL);
//     printf("Dataframe: %d rows, %d columns\n", dataframe->nb_rows, dataframe->nb_columns);
//     dataframe_t *filtered = df_filter(dataframe, "Age", filter_func);
//     df_write_csv(filtered, "filtered.csv");
//     df_free(dataframe);
//     df_free(filtered);
//     return 0;
// }

// void *apply_func(void *value)
// {
//     char *str = (char *)value;
//     if (str[strlen(str) - 1] == 'e')
//         str[strlen(str) - 1] = '\0';
//     return str;
// }

// int main(void)
// {
//     dataframe_t *dataframe = df_read_csv("money.csv", NULL);
//     dataframe = df_apply(dataframe , "amount", apply_func);
//     dataframe_t *new_dataframe = df_to_type(dataframe, "num", INT);
//     df_info(new_dataframe);
//     df_write_csv(new_dataframe, "money.csv");
//     return 0;
// }
// int main ( void )
// {
//     dataframe_t * dataframe = df_read_csv ("test.csv", NULL) ;
//     dataframe_t * head = df_head ( dataframe , 8) ;
//     df_write_csv ( head , "head.csv") ;
//     return 0;
// }

// void * agg_func ( void ** values , int nb_values )
// {
//     int *sum = malloc (sizeof(int));
//     *sum = 0;
//     for (int i = 0; i < nb_values ; i++) {
//     *sum += *(int *) values[i];
//     }
//     return sum ;
// }

// int main(void)
// {
//     dataframe_t *dataframe = df_read_csv("test.csv", NULL) ;
//     dataframe_t *grouped = df_groupby(dataframe , "city", ( const char *[]) {"age", NULL } , agg_func ) ;
//     df_write_csv ( grouped , "grouped.csv") ;
//     return 0;
// }

void * apply_func ( void * value )
{
    char * str = ( char *) value ;
    if ( str [ strlen ( str ) - 1] == 'e')
    str [ strlen ( str ) - 1] = '\0';
    return str ;
}
int main ( void )
{
    dataframe_t * dataframe = df_read_csv ("head.csv", NULL ) ;
    dataframe = df_apply ( dataframe , "amount", apply_func ) ;
    dataframe_t * new_dataframe = df_to_type ( dataframe , "num", INT ) ;
    df_info(new_dataframe);
    df_write_csv (new_dataframe, "money.csv") ;
    return 0;
}

// void * apply_func ( void * value )
// {
//     int * new_value = malloc ( sizeof (int) ) ;
//     * new_value = *( int *) value * 2;
//     return new_value ;
// }

// int main ( void )
// {
//     dataframe_t * dataframe = df_read_csv ("test.csv", NULL ) ;
//     dataframe_t * applied = df_apply ( dataframe , "age", apply_func ) ;
//     df_write_csv ( applied , "applied.csv") ;
//     return 0;
// }
