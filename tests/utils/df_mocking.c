#include "../../include/tests.h"

dataframe_t *helper_setup_df()
{
    dataframe_t *df = malloc(sizeof(dataframe_t));
    if (!df)
        return NULL;

    df->nb_rows = 13;
    df->nb_columns = 5;

    df->column_names = malloc(df->nb_columns * sizeof(char *));
    df->column_types = malloc(df->nb_columns * sizeof(column_type_t));
    df->data = malloc(df->nb_rows * sizeof(void **));

    if (!df->column_names || !df->column_types || !df->data) {
        free(df->column_names);
        free(df->column_types);
        free(df->data);
        free(df);
        return NULL;
    }

    char *columns[] = {"celestial_object", "is_habitable", "description", "light_years_distance", "discovery_year"};
    column_type_t types[] = {STRING, BOOL, STRING, FLOAT, INT};

    for (int i = 0; i < df->nb_columns; i++) {
        df->column_names[i] = strdup(columns[i]);
        df->column_types[i] = types[i];
    }

    char *data[][5] = {
        {"Gliese 581g", "true", "Rocky exoplanet in habitable zone with unusual orbital patterns", "20.4", "2010"},
        {"HD 209458b", "false", "Hot Jupiter with evidence of atmospheric water vapor", "153", "1999"},
        {"TOI-700d", "true", "Earth-sized planet orbiting a small, cool M dwarf star", "101.5", "2020"},
        {"TRAPPIST-1e", "true", "Potentially water-rich world with permanent day-night boundary", "39.6", "2017"},
        {"Kepler-186f", "true", "First Earth-sized planet discovered in habitable zone", "582", "2014"},
        {"PSR B1257+12 c", "false", "Rocky planet orbiting millisecond pulsar in cosmic dance", "980", "1994"},
        {"TDC-248b", "false", "Gas giant with peculiar rings reminiscent of ancient treasures", "1200", "2018"},
        {"Miller-3721", "false", "Ocean planet with extreme gravitational time dilation", "907", "2008"},
        {"K-23RN", "true", "Desert exoplanet with valuable mineral deposits", "816", "2015"},
        {"NGC 7293", "false", "Nebula with structures resembling complex neural pathways", "650", "1824"},
        {"51 Pegasi b", "false", "First exoplanet discovered orbiting a Sun-like star", "50.9", "1995"},
        {"Wolf 359", "false", "Red dwarf with unusual electromagnetic signature", "7.9", "1918"},
        {"Epsilon Eridani", "true", "Nearby star system with promising planetary formation", "10.5", "2000"},
        {"Proxima Centauri b", "true", "Our closest potentially habitable exoplanet neighbor", "4.2", "2016"}
    };

    for (int i = 0; i < df->nb_rows; i++) {
        df->data[i] = malloc(df->nb_columns * sizeof(void *));
        if (!df->data[i]) {
            for (int j = 0; j < i; j++) free(df->data[j]);
            free(df->column_names);
            free(df->column_types);
            free(df->data);
            free(df);
            return NULL;
        }

        for (int j = 0; j < df->nb_columns; j++) {
            if (df->column_types[j] == STRING) {
                df->data[i][j] = strdup(data[i][j]);
            } else if (df->column_types[j] == BOOL) {
                df->data[i][j] = malloc(sizeof(bool));
                *(bool *)df->data[i][j] = strcmp(data[i][j], "true") == 0;
            } else if (df->column_types[j] == FLOAT) {
                df->data[i][j] = malloc(sizeof(float));
                *(float *)df->data[i][j] = strtof(data[i][j], NULL);
            } else if (df->column_types[j] == INT) {
                df->data[i][j] = malloc(sizeof(int));
                *(int *)df->data[i][j] = atoi(data[i][j]);
            }
        }
    }

    return df;
}

void cleanup_df(dataframe_t *df)
{
    if (!df)
        return;

    for (int i = 0; i < df->nb_rows; i++) {
        if (df->data[i]) {
            for (int j = 0; j < df->nb_columns; j++) {
                if (df->data[i][j]) {
                    free(df->data[i][j]);
                }
            }
            free(df->data[i]);
        }
    }

    for (int i = 0; i < df->nb_columns; i++) {
        if (df->column_names[i]) {
            free(df->column_names[i]);
        }
    }

    free(df->column_names);
    free(df->column_types);
    free(df->data);
    free(df);
}
