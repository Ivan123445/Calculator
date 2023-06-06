#include "s21_calculate.h"

int create_coordinate_file(char *str, int start, int end, int steps) {
    int status = OK;
    double* coordinates;

    FILE *coord_file = fopen("coordinates.txt", "w");
    if (coord_file) {
        status = calculate_coordinates(str, start, end, steps, &coordinates);
        if (status == OK) {
            double step = (double)(end - start) / (steps - 1);
            double x = (double)start;
            for (int i = 0; i < steps; ++i) {
                fprintf(coord_file, "%f %f\n", x, coordinates[i]);
                x += step;
            }
            free(coordinates);
        }
        fclose(coord_file);
    } else {
        status = ERROR;
    }

    return status;
}