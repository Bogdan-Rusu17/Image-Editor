//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "rotate.h"

void rotate_rgb(image_t_rgb *img, int angle)
{
	if (img->x2 - img->x1 == img->sizex && img->y2 - img->y1 == img->sizey) {
		rotate_full_rgb(img, angle);
		return;
	}
	if (img->x2 - img->x1 != img->y2 - img->y1) {
		printf("The selection must be square\n");
		return;
	}
	int angle_cpy = angle;
	if (angle < 0)
		angle = 360 + angle;
	int sel_size_x = img->x2 - img->x1;
	int sel_size_y = img->y2 - img->y1;
	rgb_t **a = get_rgb_mat(sel_size_x, sel_size_y);
	if (!a) {
		printf("Could not perform rotation\n");
		return;
	}
	rgb_t **b = get_rgb_mat(sel_size_x, sel_size_y);
	if (!b) {
		for (int i = 0; i < sel_size_x; i++)
			free(a[i]);
		free(a);
		printf("Could not perform rotation\n");
		return;
	}
	for (int rot = 0; rot < angle / 90; rot++) {
		int cnt = 0;
		for (int i = img->x1; i < img->x2; i++)
			for (int j = img->y1; j < img->y2; j++) {
				a[cnt / sel_size_y][cnt % sel_size_y] = img->px[i][j];
				cnt++;
			}
		for (int i = 0; i < sel_size_x; i++)
			for (int j = 0; j < sel_size_y; j++)
				b[j][sel_size_x - i - 1] = a[i][j];
		cnt = 0;
		for (int i = img->x1; i < img->x2; i++)
			for (int j = img->y1; j < img->y2; j++) {
				img->px[i][j] = b[cnt / sel_size_y][cnt % sel_size_y];
				cnt++;
			}
	}
	for (int i = 0; i < sel_size_x; i++)
		free(a[i]);
	free(a);
	for (int i = 0; i < sel_size_x; i++)
		free(b[i]);
	free(b);
	printf("Rotated %d\n", angle_cpy);
}

void rotate_gs(image_t_gs *img, int angle)
{
	if (img->x2 - img->x1 == img->sizex && img->y2 - img->y1 == img->sizey) {
		rotate_full_gs(img, angle);
		return;
	}
	if (img->x2 - img->x1 != img->y2 - img->y1) {
		printf("The selection must be square\n");
		return;
	}
	int angle_cpy = angle;
	if (angle < 0)
		angle = 360 + angle;
	int sel_size_x = img->x2 - img->x1;
	int sel_size_y = img->y2 - img->y1;
	int **a = get_gs_mat(sel_size_x, sel_size_y);
	if (!a) {
		printf("Could not perform rotation\n");
		return;
	}
	int **b = get_gs_mat(sel_size_x, sel_size_y);
	if (!b) {
		for (int i = 0; i < sel_size_x; i++)
			free(a[i]);
		free(a);
		printf("Could not perform rotation\n");
		return;
	}
	for (int rot = 0; rot < angle / 90; rot++) {
		int cnt = 0;
		for (int i = img->x1; i < img->x2; i++)
			for (int j = img->y1; j < img->y2; j++) {
				a[cnt / sel_size_y][cnt % sel_size_y] = img->px[i][j];
				cnt++;
			}
		for (int i = 0; i < sel_size_x; i++)
			for (int j = 0; j < sel_size_y; j++)
				b[j][sel_size_x - i - 1] = a[i][j];
		cnt = 0;
		for (int i = img->x1; i < img->x2; i++)
			for (int j = img->y1; j < img->y2; j++) {
				img->px[i][j] = b[cnt / sel_size_y][cnt % sel_size_y];
				cnt++;
			}
	}
	for (int i = 0; i < sel_size_x; i++)
		free(a[i]);
	free(a);
	for (int i = 0; i < sel_size_x; i++)
		free(b[i]);
	free(b);
	printf("Rotated %d\n", angle_cpy);
}

void rotate_full_rgb(image_t_rgb *img, int angle)
{
	int angle_cpy = angle;
	if (angle < 0)
		angle = 360 + angle;
	for (int rot = 0; rot < angle / 90; rot++) {
		int new_size_x = img->sizey;
		int new_size_y = img->sizex;
		rgb_t **a = get_rgb_mat(new_size_x, new_size_y);
		if (!a) {
			printf("Could not perform rotation\n");
			return;
		}
		for (int i = 0; i < img->sizex; i++)
			for (int j = 0; j < img->sizey; j++)
				a[j][img->sizex - i - 1] = img->px[i][j];
		for (int i = 0; i < img->sizex; i++)
			free(img->px[i]);
		free(img->px);
		img->px = get_rgb_mat(new_size_x, new_size_y);
		img->sizex = new_size_x;
		img->sizey = new_size_y;
		img->x1 = 0;
		img->x2 = img->sizex;
		img->y1 = 0;
		img->y2 = img->sizey;
		for (int i = 0; i < img->sizex; i++)
			for (int j = 0; j < img->sizey; j++)
				img->px[i][j] = a[i][j];
		for (int i = 0; i < new_size_x; i++)
			free(a[i]);
		free(a);
	}
	printf("Rotated %d\n", angle_cpy);
}

void rotate_full_gs(image_t_gs *img, int angle)
{
	int angle_cpy = angle;
	if (angle < 0)
		angle = 360 + angle;
	for (int rot = 0; rot < angle / 90; rot++) {
		int new_size_x = img->sizey;
		int new_size_y = img->sizex;
		int **a = get_gs_mat(new_size_x, new_size_y);
		if (!a) {
			printf("Could not perform rotation\n");
			return;
		}
		for (int i = 0; i < img->sizex; i++)
			for (int j = 0; j < img->sizey; j++)
				a[j][img->sizex - i - 1] = img->px[i][j];
		for (int i = 0; i < img->sizex; i++)
			free(img->px[i]);
		free(img->px);
		img->px = get_gs_mat(new_size_x, new_size_y);
		img->sizex = new_size_x;
		img->sizey = new_size_y;
		img->x1 = 0;
		img->x2 = img->sizex;
		img->y1 = 0;
		img->y2 = img->sizey;
		for (int i = 0; i < img->sizex; i++)
			for (int j = 0; j < img->sizey; j++)
				img->px[i][j] = a[i][j];
		for (int i = 0; i < new_size_x; i++)
			free(a[i]);
		free(a);
	}
	printf("Rotated %d\n", angle_cpy);
}
