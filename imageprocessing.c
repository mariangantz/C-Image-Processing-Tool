#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

void fr(int ***image, int N, int M) {
    if (image != NULL) {
        int i = 0, j = 0;
        for (i = 0; i < N; ++i) {
            for (j = 0; j < M; ++j)
                free(image[i][j]);
            free(image[i]);
        }
        free(image);
    }
}

int ***aloc(int N, int M) {
    int cul = 3, i = 0, j = 0;
    int ***image = (int ***)malloc(N * sizeof(int **));
    for (i = 0; i < N; ++i) {
        image[i] = (int **)malloc(M * sizeof(int *));
        for (j = 0; j < M; ++j)
            image[i][j] = (int *)malloc(cul * sizeof(int));
    }
    return image;
}

int ***flip_horizontal(int ***image, int N, int M) {
    int cul = 3;
    int i = 0, j = 0, c = 0;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M / 2; ++j) {
            for (c = 0; c < cul; c++) {
                int aux = image[i][j][c];
                image[i][j][c] = image[i][M - j - 1][c];
                image[i][M - j - 1][c] = aux;
            }
        }
    }
    return image;
}

int ***rotate_left(int ***image, int N, int M) {
    int cul = 3;
    int ***copy = (int ***)malloc(M * sizeof(int **));
    int i = 0, j = 0, c = 0;
    for (i = 0; i < M; ++i) {
        copy[i] = (int **)malloc(N * sizeof(int *));
        for (j = 0; j < N; ++j)
            copy[i][j] = (int *)malloc(cul * sizeof(int));
    }
    for (i = 0; i < M; ++i)
        for (j = 0; j < N; ++j)
            for (c = 0; c < cul; ++c)
                copy[i][j][c] = image[j][M - i - 1][c];
    fr(image, N, M);
    return copy;
}
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***mat = aloc(h, w);
    int i = 0, j = 0, c = 0, cul = 3;
    for (i = y; i < y + h; ++i)
        for (j = x; j < x + w; ++j)
            for (c = 0; c < cul; c++)
                mat[i - y][j - x][c] = image[i][j][c];
    fr(image, N, M);
    return mat;
}

int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int new_rows = 2 * rows + N;
    int new_cols = 2 * cols + M;
    int ***new_image = aloc(new_rows, new_cols);
    int i = 0, j = 0, c = 0, cul = 3;
    for (i = 0; i < new_rows; ++i)
        for (j = 0; j < new_cols; ++j) {
            new_image[i][j][0] = new_R;
            new_image[i][j][1] = new_G;
            new_image[i][j][2] = new_B;
        }
    for (i = rows; i < N + rows; ++i)
        for (j = cols; j < M + cols; ++j)
            for (c = 0; c < cul; ++c)
                new_image[i][j][c] = image[i - rows][j - cols][c];
    fr(image, N, M);
    return new_image;
}

int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    int aux = x;
    x = y;
    y = aux;
    int i = 0, j = 0, cul = 3, c = 0;
    for (i = x; i < N_dst; ++i)
        for (j = y; j < M_dst; ++j)
            for (c = 0; c < cul; ++c)
                if (i - x < N_src && j - y < M_src)
                    image_dst[i][j][c] = image_src[i - x][j - y][c];
    return image_dst;
}

int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    const int maximul = 255, minimul = 0;
    int ***aux = aloc(N, M);
    int i = 0, j = 0, c = 0, cul = 3, i1 = 0, j1 = 0;
    for (i = 0; i < N; ++i)
        for (j = 0; j < M; ++j)
            for (c = 0; c < cul; ++c)
                aux[i][j][c] = image[i][j][c];
    for (i = 0; i < N; ++i)
        for (j = 0; j < M; ++j) {
            for (c = 0; c < cul; ++c) {
                float rasp = 0;
                for (i1 = 0; i1 < filter_size; ++i1)
                    for (j1 = 0; j1 < filter_size; ++j1)
                        if (i - (filter_size / 2) + i1 >= 0 && j - (filter_size / 2) + j1 >= 0 &&
                            i - (filter_size / 2) + i1 < N && j - (filter_size / 2) + j1 < M)
                            rasp += (float)aux[i - (filter_size / 2) + i1][j - (filter_size / 2) + j1][c] *
                                    filter[i1][j1];
                image[i][j][c] = (int)rasp;
                if (image[i][j][c] > maximul)
                    image[i][j][c] = maximul;
                if (image[i][j][c] < minimul)
                    image[i][j][c] = minimul;
            }
        }
    fr(aux, N, M);
    return image;
}
