#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"

#define a 100

typedef struct {
    int ***image;
    int n, m;
} Imagini;

typedef struct {
    float **filtru;
    int n;
} Filtre;

void frri(int ***image, int N, int M) {
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

float **alocarefiltru(int n) {
    float **filtru = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; ++i)
        filtru[i] = (float *)malloc(n * sizeof(float));
    return filtru;
}

void dezaloc(float **filtru, int n) {
    if (filtru != NULL) {
        for (int i = 0; i < n; i++)
            free(filtru[i]);
        free(filtru);
    }
}

int ***alocare(int N, int M) {
    int i = 0, j = 0, cul = 3;
    int ***image = (int ***)malloc(N * sizeof(int **));
    for (i = 0; i < N; ++i) {
        image[i] = (int **)malloc(M * sizeof(int *));
        for (j = 0; j < M; ++j)
            image[i][j] = (int *)malloc(cul * sizeof(int));
    }
    return image;
}

int main() {
    const int cul = 3;
    Imagini *imagini = NULL;
    Filtre *filtre = NULL;
    int nri = 0, nrf = 0;
    char cale[a], comanda[a];
    scanf("%s", comanda);
    while (strcmp(comanda, "e")) {
        if (!strcmp(comanda, "l")) {
            nri++;
            int n = 0, m = 0;
            scanf("%d%d%s", &n, &m, cale);
            imagini = (Imagini *)realloc(imagini, nri * sizeof(Imagini));
            imagini[nri - 1].n = n;
            imagini[nri - 1].m = m;
            imagini[nri - 1].image = alocare(n, m);
            read_from_bmp(imagini[nri - 1].image, n, m, cale);
        }
        if (!strcmp(comanda, "s")) {
            int indice = 0;
            scanf("%d%s", &indice, cale);
            write_to_bmp(imagini[indice].image, imagini[indice].n, imagini[indice].m, cale);
        }
        if (!strcmp(comanda, "ah")) {
            int indice = 0;
            scanf("%d", &indice);
            imagini[indice].image = flip_horizontal(imagini[indice].image, imagini[indice].n, imagini[indice].m);
        }
        if (!strcmp(comanda, "ar")) {
            int indice = 0;
            scanf("%d", &indice);
            int m = imagini[indice].m;
            int n = imagini[indice].n;
            int i = 0, j = 0, c = 0;
            int ***aux = alocare(n, m);
            for (i = 0; i < n; ++i)
                for (j = 0; j < m; ++j)
                    for (c = 0; c < cul; ++c)
                        aux[i][j][c] = imagini[indice].image[i][j][c];

            frri(imagini[indice].image, n, m);
            imagini[indice].image = rotate_left(aux, n, m);
            imagini[indice].m = n;
            imagini[indice].n = m;
        }
        if (!strcmp(comanda, "ac")) {
            int indice = 0, x = 0, y = 0, h = 0, w = 0;
            scanf("%d%d%d%d%d", &indice, &x, &y, &w, &h);
            int m = imagini[indice].m;
            int n = imagini[indice].n;
            int i = 0, j = 0, c = 0;
            int ***aux = alocare(n, m);
            for (i = 0; i < n; ++i)
                for (j = 0; j < m; ++j)
                    for (c = 0; c < cul; ++c)
                        aux[i][j][c] = imagini[indice].image[i][j][c];
            frri(imagini[indice].image, n, m);
            imagini[indice].image = crop(aux, n, m, x, y, h, w);
            imagini[indice].m = w;
            imagini[indice].n = h;
        }
        if (!strcmp(comanda, "ae")) {
            int indice = 0, rows = 0, cols = 0, r = 0, g = 0, b = 0;
            scanf("%d%d%d%d%d%d", &indice, &rows, &cols, &r, &g, &b);
            int m = imagini[indice].m;
            int n = imagini[indice].n;
            int i = 0, j = 0, c = 0;
            int ***aux = alocare(n, m);
            for (i = 0; i < n; ++i)
                for (j = 0; j < m; ++j)
                    for (c = 0; c < cul; ++c)
                        aux[i][j][c] = imagini[indice].image[i][j][c];
            frri(imagini[indice].image, n, m);
            imagini[indice].image = extend(aux, n, m, rows, cols, r, g, b);
            imagini[indice].m = 2 * cols + m;
            imagini[indice].n = 2 * rows + n;
        }
        if (!strcmp(comanda, "ap")) {
            int indice = 0, indice2 = 0, x = 0, y = 0;
            scanf("%d%d%d%d", &indice, &indice2, &x, &y);
            int m = imagini[indice].m;
            int n = imagini[indice].n;
            int n2 = imagini[indice2].n;
            int m2 = imagini[indice2].m;
            imagini[indice].image = paste(imagini[indice].image, n, m, imagini[indice2].image, n2, m2, x, y);
        }
        if (!strcmp(comanda, "cf")) {
            int n = 0, i = 0, j = 0;
            float x = 0;
            scanf("%d", &n);
            ++nrf;
            filtre = (Filtre *)realloc(filtre, nrf * sizeof(Filtre));
            filtre[nrf - 1].filtru = (float **)malloc(n * sizeof(float *));
            for (i = 0; i < n; ++i)
                filtre[nrf - 1].filtru[i] = (float *)malloc(n * sizeof(float));
            filtre[nrf - 1].n = n;
            for (i = 0; i < n; ++i)
                for (j = 0; j < n; ++j)
                    scanf("%f", &x), filtre[nrf - 1].filtru[i][j] = x;
        }
        if (!strcmp(comanda, "af")) {
            int indexi = 0, indexf = 0;
            scanf("%d%d", &indexi, &indexf);
            int n = imagini[indexi].n;
            int m = imagini[indexi].m;
            int nf = filtre[indexf].n;
            imagini[indexi].image = apply_filter(imagini[indexi].image, n, m, filtre[indexf].filtru, nf);
        }
        if (!strcmp(comanda, "df")) {
            int index = 0;
            scanf("%d", &index);
            for (int i = index; i < nrf - 1; ++i) {
                dezaloc(filtre[i].filtru, filtre[i].n);
                filtre[i].filtru = alocarefiltru(filtre[i + 1].n);
                for (int k = 0; k < filtre[i + 1].n; k++)
                    for (int q = 0; q < filtre[i + 1].n; q++)
                        filtre[i].filtru[k][q] = filtre[i + 1].filtru[k][q];
                filtre[i].n = filtre[i + 1].n;
            }
            dezaloc(filtre[nrf - 1].filtru, filtre[nrf - 1].n);
            nrf--;
            filtre = (Filtre *)realloc(filtre, nrf * sizeof(Filtre));
        }
        if (!strcmp(comanda, "di")) {
            int index = 0;
            scanf("%d", &index);
            for (int i = index; i < nri - 1; ++i) {
                frri(imagini[i].image, imagini[i].n, imagini[i].m);
                imagini[i].image = alocare(imagini[i + 1].n, imagini[i + 1].m);

                for (int k = 0; k < imagini[i + 1].n; k++)
                    for (int q = 0; q < imagini[i + 1].m; q++)
                        for (int c = 0; c < cul; c++)
                            imagini[i].image[k][q][c] = imagini[i + 1].image[k][q][c];

                imagini[i].n = imagini[i + 1].n;
                imagini[i].m = imagini[i + 1].m;
            }
            frri(imagini[nri - 1].image, imagini[nri - 1].n, imagini[nri - 1].m);
            nri--;
            imagini = (Imagini *)realloc(imagini, nri * sizeof(Imagini));
        }
        scanf("%s", comanda);
    }
    for (int i = 0; i < nri; ++i)
        frri(imagini[i].image, imagini[i].n, imagini[i].m);
    for (int i = 0; i < nrf; i++) {
        for (int j = 0; j < filtre[i].n; j++)
            free(filtre[i].filtru[j]);
        free(filtre[i].filtru);
    }
    free(filtre);
    free(imagini);
    return 0;
}
