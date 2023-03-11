//Copyright 2021 Arpasanu Emilia-Oana 311 CA (emilia.arpasanu@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "octave.h"

int main(void)
{
	int rows, columns, ***v, nr = 0, i, pos, pos1, pos2, **dim;
	char c, commands[] = "LPDCMOTFQ\n ";
	scanf("%c", &c);

	//alocarea memoriei pentru vectorul de matrice
	//si pentru matricea dimensiunilor pentru un element
	v = malloc(sizeof(int **));
	dim = malloc(sizeof(int *));

	while (c != 'Q') {
		if (strchr(commands, c)) {
			if (c == 'M') {
				scanf("%d%d", &pos1, &pos2);
				if (can_multiply(pos1, pos2, nr, dim)) {
					//marirea capacitatii vectorului + a matricei dimensiunilor
					v = realloc(v, (nr + 1) * sizeof(int **));
					dim = realloc(dim, (nr + 1) * sizeof(int *));

					//alocarea de memorie pentru noua matrice (+ linia din dim)
					dim[nr] = malloc(2 * sizeof(int));
					v[nr] = malloc(dim[pos1][0] * sizeof(int *));
					for (i = 0; i < dim[pos1][0]; i++)
						v[nr][i] = calloc(dim[pos2][1], sizeof(int));

					multiply_matrix(pos1, pos2, dim, v, v[nr]); //inmultirea

					//actualizarea dimensiunilor
					dim[nr][0] = dim[pos1][0];
					dim[nr][1] = dim[pos2][1];

					nr++; //marirea numarului de elemente ale vectorului
				}
			} else if (c == 'L') {
				scanf("%d%d", &rows, &columns);
				//marirea capacitatii vectorului + a matricei dimensiunilor
				v = realloc(v, (nr + 1) * sizeof(int **));
				dim = realloc(dim, (nr + 1) * sizeof(int *));

				//alocarea de memorie pentru noua matrice (+ linia din dim)
				dim[nr] = malloc(2 * sizeof(int));
				v[nr] = alloc_matrix(rows, columns);

				//memorarea dimensiunilor
				dim[nr][0] = rows;
				dim[nr][1] = columns;

				read_matrix(rows, columns, v[nr]); //citirea elementelor

				nr++; //marirea numarului de elemente ale vectorului
			} else if (c == 'P') {
				scanf("%d", &pos);
				print_matrix(pos, nr, dim, v);
			} else if (c == 'D') {
				scanf("%d", &pos);
				matrix_dimensions(pos, nr, dim);
			} else if (c == 'C') {
				scanf("%d", &pos);
				redimension_matrix(pos, nr, dim, v);
			} else if (c == 'O') {
				sort_matrix(nr, dim, v);
			} else if (c == 'T') {
				scanf("%d", &pos);
				transpose_matrix(pos, nr, dim, v);
			} else if (c == 'F') {
				scanf("%d", &pos);
				remove_matrix(pos, &nr, dim, v);
			}
		} else {
			printf("Unrecognized command\n");
		}
		scanf("%c", &c);
	}
	//dealocarea memoriei utilizate (a vectorului si a matricei dimensiunilor)
	for (i = 0; i < nr; i++)
		dealloc_matrix(dim[i][0], v[i]);
	free(v);
	dealloc_matrix(nr, dim);
}
