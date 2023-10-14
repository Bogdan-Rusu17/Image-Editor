//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "apply_effects.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "extract_info.h"
double **get_gauss_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = 0.0625;
	ker[0][1] = 0.125;
	ker[0][2] = 0.0625;
	ker[1][0] = 0.125;
	ker[1][1] = 0.25;
	ker[1][2] = 0.125;
	ker[2][0] = 0.0625;
	ker[2][1] = 0.125;
	ker[2][2] = 0.0625;
	return ker;
}

double **get_box_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = 0.111111;
	ker[0][1] = 0.111111;
	ker[0][2] = 0.111111;
	ker[1][0] = 0.111111;
	ker[1][1] = 0.111111;
	ker[1][2] = 0.111111;
	ker[2][0] = 0.111111;
	ker[2][1] = 0.111111;
	ker[2][2] = 0.111111;
	return ker;
}

double **get_edge_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = -1;
	ker[0][1] = -1;
	ker[0][2] = -1;
	ker[1][0] = -1;
	ker[1][1] = 8;
	ker[1][2] = -1;
	ker[2][0] = -1;
	ker[2][1] = -1;
	ker[2][2] = -1;
	return ker;
}

double **get_sharp_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = 0;
	ker[0][1] = -1;
	ker[0][2] = 0;
	ker[1][0] = -1;
	ker[1][1] = 5;
	ker[1][2] = -1;
	ker[2][0] = 0;
	ker[2][1] = -1;
	ker[2][2] = 0;
	return ker;
}

double **get_emboss_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = 0;
	ker[0][1] = 1;
	ker[0][2] = 0;
	ker[1][0] = -1;
	ker[1][1] = 0;
	ker[1][2] = 1;
	ker[2][0] = 0;
	ker[2][1] = -1;
	ker[2][2] = 0;
	return ker;
}

double **get_laplacian_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = 0;
	ker[0][1] = 1;
	ker[0][2] = 0;
	ker[1][0] = 1;
	ker[1][1] = 4;
	ker[1][2] = 1;
	ker[2][0] = 0;
	ker[2][1] = 1;
	ker[2][2] = 0;
	return ker;
}

double **get_motion_ker(void)
{
	double **ker;
	ker = (double **)malloc(3 * sizeof(double *));
	if (!ker) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < 3; i++) {
		ker[i] = (double *)malloc(3 * sizeof(double));
		if (!ker[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(ker[j]);
			return NULL;
		}
	}
	ker[0][0] = 1;
	ker[0][1] = 1;
	ker[0][2] = 1;
	ker[1][0] = 0;
	ker[1][1] = 0;
	ker[1][2] = 0;
	ker[2][0] = -1;
	ker[2][1] = -1;
	ker[2][2] = -1;
	return ker;
}

int *get_dx(void)
{
	int *dx;
	dx = (int *)malloc(9 * sizeof(int));
	dx[0] = -1;
	dx[1] = -1;
	dx[2] = -1;
	dx[3] = 0;
	dx[4] = 0;
	dx[5] = 0;
	dx[6] = 1;
	dx[7] = 1;
	dx[8] = 1;
	return dx;
}

int *get_dy(void)
{
	int *dx;
	dx = (int *)malloc(9 * sizeof(int));
	dx[0] = -1;
	dx[1] = 0;
	dx[2] = 1;
	dx[3] = -1;
	dx[4] = 0;
	dx[5] = 1;
	dx[6] = -1;
	dx[7] = 0;
	dx[8] = 1;
	return dx;
}

rgb_t **get_rgb_mat(int sizex, int sizey)
{
	rgb_t **a;
	a = (rgb_t **)malloc(sizex * sizeof(rgb_t *));
	if (!a) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < sizex; i++) {
		a[i] = (rgb_t *)malloc(sizey * sizeof(rgb_t));
		if (!a[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}
	}
	for (int i = 0; i < sizex; i++)
		for (int j = 0; j < sizey; j++) {
			a[i][j].r = 0;
			a[i][j].g = 0;
			a[i][j].b = 0;
		}
	return a;
}

int **get_gs_mat(int sizex, int sizey)
{
	int **a;
	a = (int **)malloc(sizex * sizeof(int *));
	if (!a) {
		printf("Error allocating\n");
		return NULL;
	}
	for (int i = 0; i < sizex; i++) {
		a[i] = (int *)malloc(sizey * sizeof(int));
		if (!a[i]) {
			printf("Error allocating\n");
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}
	}
	for (int i = 0; i < sizex; i++)
		for (int j = 0; j < sizey; j++)
			a[i][j] = 0;
	return a;
}

int inside(int x, int y, int sizex, int sizey, int stx, int sty)
{
	if (x >= stx && x < sizex && y >= sty && y < sizey)
		return 1;
	return 0;
}

int clamp(int x)
{
	if (x < 0)
		x = 0;
	if (x > 255)
		x = 255;
	return x;
}

void apply_effect_rgb(image_t_rgb *img, char *eff)
{
	double **ker;
	if (check_string(eff, "GAUSSIAN_BLUR")) // get corresponding kernel
		ker = get_gauss_ker();
	else if (check_string(eff, "BLUR"))
		ker = get_box_ker();
	else if (check_string(eff, "EDGE"))
		ker = get_edge_ker();
	else if (check_string(eff, "LAPLACIAN"))
		ker = get_laplacian_ker();
	else if (check_string(eff, "EMBOSS"))
		ker = get_emboss_ker();
	else if (check_string(eff, "MOTION_BLUR"))
		ker = get_motion_ker();
	else
		ker = get_sharp_ker();
	double sumr = 0, sumg = 0, sumb = 0;
	int *dx, *dy;
	dx = get_dx();
	if (!dx) {
		for (int i = 0; i < 3; i++)
			free(ker[i]);
		free(ker);
		printf("Error allocating\n");
		return;
	}
	dy = get_dy();
	if (!dy) {
		for (int i = 0; i < 3; i++)
			free(ker[i]);
		return;
	}
	rgb_t **a;
	a = get_rgb_mat(img->sizex, img->sizey);
	if (!a) {
		for (int i = 0; i < 3; i++)
			free(ker[i]);
		free(ker);
		free(dx);
		free(dy);
		printf("Error allocating\n");
		return;
	}
	for (int i = img->x1; i < img->x2; i++)
		for (int j = img->y1; j < img->y2; j++) {
			sumr = 0.0;
			sumg = 0.0;
			sumb = 0.0;
			int neighbours = 0;
			for (int w = 0; w < 9; w++) {
				int newi = i + dx[w], newj = j + dy[w];
				if (inside(newi, newj, img->sizex, img->sizey, 0, 0)) {
					double red = img->px[i + dx[w]][j + dy[w]].r;
					double green = img->px[i + dx[w]][j + dy[w]].g;
					double blue = img->px[i + dx[w]][j + dy[w]].b;
					sumr += ker[1 + dx[w]][1 + dy[w]] * red;
					sumg += ker[1 + dx[w]][1 + dy[w]] * green;
					sumb += ker[1 + dx[w]][1 + dy[w]] * blue;
					neighbours++;
				}
			}
			a[i][j].r = round(sumr); // rounding results to nearest integer
			a[i][j].g = round(sumg);
			a[i][j].b = round(sumb);
			a[i][j].r = clamp(a[i][j].r); // clamping as said in the text
			a[i][j].g = clamp(a[i][j].g);
			a[i][j].b = clamp(a[i][j].b);
			if (neighbours < 9)
				a[i][j] = img->px[i][j];
		}
	for (int i = img->x1; i < img->x2; i++)
		for (int j = img->y1; j < img->y2; j++) {
			img->px[i][j].r = a[i][j].r;
			img->px[i][j].g = a[i][j].g;
			img->px[i][j].b = a[i][j].b;
		}
	for (int i = 0; i < 3; i++)
		free(ker[i]);
	free(ker);
	free(dx);
	free(dy);
	for (int i = 0; i < img->sizex; i++)
		free(a[i]);
	free(a);
	printf("APPLY %s done\n", eff);
}
