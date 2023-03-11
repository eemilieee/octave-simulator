//Copyright 2021 Arpasanu Emilia-Oana 311 CA (emilia.arpasanu@stud.acs.upb.ro)
#ifndef OCTAVE_H_
#define OCTAVE_H_

int **alloc_matrix(int rows, int columns);
void dealloc_matrix(int rows, int **matrix);
void read_matrix(int rows, int columns, int **matrix);
void matrix_dimensions(int pos, int el, int **dim);
void print_matrix(int pos, int el, int **dim, int ***v);
void redimension_matrix(int pos, int el, int **dim, int ***v);
int can_multiply(int pos1, int pos2, int el, int **dim);
void multiply_matrix(int pos1, int pos2, int **dim, int ***v, int **matrix);
int sum_matrix(int rows, int columns, int **matrix);
void sort_matrix(int el, int **dim, int ***v);
void transpose_matrix(int pos, int el, int **dim, int ***v);
void remove_matrix(int poz, int *el, int **dim, int ***v);

#endif
