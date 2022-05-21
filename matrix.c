#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char *lower(char *string)
{
    for (int i = 0; string[i]; i++)
        string[i] = tolower(string[i]);

    return string;
}

double get_random_value(int size)
{
    return rand() % size + 1;
}

double *instantiate_vector(int vector_size)
{
    return (double *)malloc((vector_size + 1) * sizeof(double));
}

double *zero_vector(int vector_size)
{
    double *vector = instantiate_vector(vector_size);
    for (int i = 0; i <= vector_size; i++)
        vector[i] = 0;

    return vector;
}

double *generate_random_vector(int vector_size)
{
    double *vector = instantiate_vector(vector_size);
    for (int i = 0; i <= vector_size; i++)
        vector[i] = get_random_value(vector_size);

    return vector;
}

double **instantiate_matrix(int matrix_size)
{
    double **matrix = (double **)malloc((matrix_size + 1) * sizeof(double *));
    for (int i = 0; i <= matrix_size; i++)
        matrix[i] = instantiate_vector(matrix_size);

    return matrix;
}

void fill_matrix_line(int current_line, int matrix_size, double **matrix)
{
    for (int j = 0; j <= matrix_size; j++)
        matrix[current_line][j] = get_random_value(matrix_size);
}

double **generate_random_matrix(int matrix_size)
{
    double **matrix = instantiate_matrix(matrix_size);
    for (int i = 0; i <= matrix_size; i++)
        fill_matrix_line(i, matrix_size, matrix);

    return matrix;
}

void line_product_ij(int size, int line_index, double *result, double **matrix, double *vector)
{
    for (int j = 0; j <= size; j++)
        result[line_index] += matrix[line_index][j] * vector[j];
}

double *matrix_vector_product_ij(int size, double **matrix, double *vector)
{
    double *result = zero_vector(size);

    for (int i = 0; i <= size; i++)
        line_product_ij(size, i, result, matrix, vector);

    return result;
}

void line_product_ji(int size, int column_index, double *result, double **matrix, double *vector)
{
    for (int i = 0; i <= size; i++)
        result[i] += matrix[i][column_index] * vector[column_index];
}

double *matrix_vector_product_ji(int size, double **matrix, double *vector)
{
    double *result = zero_vector(size);
    for (int j = 0; j <= size; j++)
        line_product_ji(size, j, result, matrix, vector);

    return result;
}

void free_matrix(double **matrix, int matrix_size)
{
    for (int i = 0; i <= matrix_size; i++)
        free(matrix[i]);

    free(matrix);
}

int main(int argc, char *argv[])
{
    clock_t antes, depois;
    double *result;
    if (argc != 3 || (atoi(argv[2]) != 0 && atoi(argv[2]) != 1))
    {
        printf("Argumentos inválidos.\n");
        return 0;
    }

    int size = atoi(argv[1]);
    int type_of_function = atoi(argv[2]);

    srand(time(NULL));

    double **matrix = generate_random_matrix(size);
    double *vector = generate_random_vector(size);

    if (type_of_function == 1)
    {
        antes = clock();
        result = matrix_vector_product_ij(size, matrix, vector);
        depois = clock();
    }

    else
    {
        antes = clock();
        result = matrix_vector_product_ji(size, matrix, vector);
        depois = clock();
    }

    free_matrix(matrix, size);
    free(vector);
    free(result);

    printf("%d;%.6f\n", size, ((double)(depois - antes)) / CLOCKS_PER_SEC);

    return 0;
}
