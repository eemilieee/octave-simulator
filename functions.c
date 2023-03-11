//Copyright 2021 Arpasanu Emilia-Oana 311 CA (emilia.arpasanu@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "octave.h"

//functia returneaza un pointer catre o noua zona continua de memorie
//care reprezinta o matrice
int **alloc_matrix(int rows, int columns)
{
	int i, **matrix;
	matrix = malloc(rows * sizeof(int *));

	for (i = 0; i < rows; i++)
		matrix[i] = malloc(columns * sizeof(int));

	return matrix;
}

//functia dealoca zona de memorie a unei matrice: liniile si matricea in sine
void dealloc_matrix(int rows, int **matrix)
{
	int i;
	for (i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

//functia citeste elementele unei matrice
void read_matrix(int rows, int columns, int **matrix)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++)
			scanf("%d", *(matrix + i) + j);
}

//functia afiseaza dimensiunile unei matrice din vector:
//nuamrul de linii si de coloane ale acesteia
void matrix_dimensions(int pos, int el, int **dim)
{
	if (pos < 0 || pos >= el)
		printf("No matrix with the given index");
	else
		printf("%d %d", dim[pos][0], dim[pos][1]);
	printf("\n");
}

//functia afiseaza elementele unei matrice din vector
void print_matrix(int pos, int el, int **dim, int ***v)
{
	int i, j;
	if (pos >= 0 && pos < el) {
		for (i = 0; i < dim[pos][0]; i++) {
			for (j = 0; j < dim[pos][1]; j++)
				printf("%d ", v[pos][i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

//functia efectueaza redimensionarea unei matrice din vector
void redimension_matrix(int pos, int el, int **dim, int ***v)
{
	int i, j, nr_rows, nr_columns, *rows, *columns, **arrange;

	//memorarea liniilor dupa care se efectueaza redimensionarea
	scanf("%d", &nr_rows);
	rows = malloc(nr_rows * sizeof(int));

	for (i = 0; i < nr_rows; i++)
		scanf("%d", rows + i);

	//memorarea coloanelor dupa care se efectueaza redimensionarea
	scanf("%d", &nr_columns);
	columns = malloc(nr_columns * sizeof(int));

	for (i = 0; i < nr_columns; i++)
		scanf("%d", columns + i);

	if (pos < 0 || pos >= el) {
		printf("No matrix with the given index\n");
	} else {
		//alocarea memoriei matricei redimensionate
		arrange = alloc_matrix(nr_rows, nr_columns);

		//construirea matricei redimensionate
		for (i = 0; i < nr_rows; i++)
			for (j = 0; j < nr_columns; j++)
				arrange[i][j] = v[pos][rows[i]][columns[j]];

		//dealocarea matricei initiale (pentru evitarea pierderilor de memorie)
		//in urma modificarii dimensiunilor acesteia
		dealloc_matrix(dim[pos][0], v[pos]);

		//modificarea adresei matricei initiale din vector
		v[pos] = arrange;

		//actualizarea dimensiunilor matricei redimensionate
		dim[pos][0] = nr_rows;
		dim[pos][1] = nr_columns;

		//ruperea legaturii dintre adresa matricei auxiliare
		//si memoria nou alocata (nu mai este necesara
		//caci a fost plasata in vector; evitarea redundantei)
		arrange = NULL;
	}

	//eliberarea memoriei vectorilor ce retin
	//liniile si coloanele redimensionarii
	free(columns);
	free(rows);
}

//functia determina daca inmultirea a doua matrice poate avea loc
int can_multiply(int pos1, int pos2, int el, int **dim)
{
	if ((pos1 < 0 || pos1 >= el) || (pos2 < 0 || pos2 >= el)) {
		printf("No matrix with the given index\n");
		return 0;
	}
	if (dim[pos1][1] != dim[pos2][0]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

//functia efectueaza inmultirea a doua matrice
void multiply_matrix(int pos1, int pos2, int **dim, int ***v, int **matrix)
{
	int i, j, k, a, b;
	for (k = 0; k < dim[pos2][0]; k++)
		for (i = 0; i < dim[pos1][0]; i++)
			for (j = 0; j < dim[pos2][1]; j++) {
				a = v[pos1][i][k] % 10007;
				b = v[pos2][k][j] % 10007;

				matrix[i][j] += (a * b) % 10007;
				matrix[i][j] = matrix[i][j] % 10007;

				if (matrix[i][j] < 0)
					matrix[i][j] += 10007;
			}
}

//functia returneaza suma elementelor unei matrice
int sum_matrix(int rows, int columns, int **matrix)
{
	int i, j, sum = 0;

	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++)
			sum += matrix[i][j] % 10007;

	sum = sum % 10007;
	if (sum < 0)
		sum += 10007;
	return sum;
}

//functia efectueaza sortarea vectorului de matrice
void sort_matrix(int el, int **dim, int ***v)
{
	int **aux, i, j, *sums, *tmpp, tmp;

	//memorarea sumelor matricelor din vector
	sums = (int *)malloc(el * sizeof(int));

	for (i = 0; i < el; i++)
		sums[i] = sum_matrix(dim[i][0], dim[i][1], v[i]);

	for (i = 0; i < el - 1; i++)
		for (j = i + 1; j < el; j++)
			if (sums[i] > sums[j]) {
				//insterschimbarea adreselor matricelor
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				//interschimbarea adreselor liniilor din matricea dimensiunilor
				tmpp = dim[i];
				dim[i] = dim[j];
				dim[j] = tmpp;
				//interchimbarea sumelor in vectorul auxiliar
				tmp = sums[i];
				sums[i] = sums[j];
				sums[j] = tmp;
			}

	//eliberarea memoriei vectorului auxiliar
	free(sums);
}

//functia efectueaza transpunerea unei matrice din vector
void transpose_matrix(int pos, int el, int **dim, int ***v)
{
	int i, j, **transform, rows, cols;
	if (pos < 0 || pos >= el) {
		printf("No matrix with the given index\n");
	} else {
		//memorarea dimensiunilor matricei ce se transpune
		rows = dim[pos][0];
		cols = dim[pos][1];

		//alocarea memoriei pentru matricea transpusa
		transform = alloc_matrix(cols, rows);

		//construirea matricei transpuse
		for (i = 0; i < rows; i++)
			for (j = 0; j < cols; j++)
				transform[j][i] = v[pos][i][j];

		//dealocarea matricei initiale (pentru evitarea pierderilor de memorie)
		//in urma modificarii dimensiunilor acesteia
		dealloc_matrix(dim[pos][0], v[pos]);

		//modificarea adresei matricei initiale din vector
		v[pos] = transform;

		//actualizarea dimensiunilor matricei redimensionate
		dim[pos][0] = cols;
		dim[pos][1] = rows;

		//ruperea legaturii dintre adresa matricei auxiliare
		//si memoria nou alocata (nu mai este necesara
		//caci a fost plasata in vector; evitarea redundantei)
		transform = NULL;
	}
}

//functia efectueaza stergerea unei matrice din vector
void remove_matrix(int poz, int *el, int **dim, int ***v)
{
	int i;
	if (poz < 0 || poz >= *el) {
		printf("No matrix with the given index\n");
	} else {
		//dealocarea matricei initiale si a liniei din matricea dimensiunilor
		//pentru evitarea pierderilor de memorie
		dealloc_matrix(dim[poz][0], v[poz]);
		free(dim[poz]);

		//permutare circulara la stanga a adreselor matricelor
		//si a liniilor dimensiunilor pentru umplerea golului matricei sterse
		for (i = poz; i < *el - 1; i++) {
			v[i] = v[i + 1];
			dim[i] = dim[i + 1];
		}

		//ruperea legaturii dintre adresa ultimei matrice (duplicat)
		//si memoria aferenta (nu mai este necesara caci ar fi redundanta)
		//precum si a adresei liniei dimensiunilor ultimei matrice
		v[*el - 1] = NULL;
		dim[*el - 1] = NULL;

		//numarul total de elemente scade cu o unitate in urma stergerii
		(*el)--;
	}
}
