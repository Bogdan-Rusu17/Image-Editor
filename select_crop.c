//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "select_crop.h"
#include "extract_info.h"
#include "apply_effects.h"
#include <string.h>

void select_all_rgb(image_t_rgb *imrgb)
{
	imrgb->x1 = 0;
	imrgb->x2 = imrgb->sizex;
	imrgb->y1 = 0;
	imrgb->y2 = imrgb->sizey;
	printf("Selected ALL\n");
}

void select_all_gs(image_t_gs *imgs)
{
	imgs->x1 = 0;
	imgs->x2 = imgs->sizex;
	imgs->y1 = 0;
	imgs->y2 = imgs->sizey;
	printf("Selected ALL\n");
}

void select_zone_rgb(char *file_name, image_t_rgb *imrgb)
{
	int x1, x2, y1, y2;
	char *p;
	p = strtok(file_name, "\n ");
	int cnt = 0;
	while (p) {
		if (p[0] != '-' && (p[0] < '0' || p[0] > '9')) {
			printf("Invalid command\n");
			return;
		}
		for (int i = 1; p[i]; i++)
			if (p[i] < '0' || p[i] > '9') {
				printf("Invalid command\n");
				return;
			}
		if (cnt == 0)
			y1 = conv_str_to_int(p);
		else if (cnt == 1)
			x1 = conv_str_to_int(p);
		else if (cnt == 2)
			y2 = conv_str_to_int(p);
		else if (cnt == 3)
			x2 = conv_str_to_int(p);
		cnt++;
		p = strtok(NULL, "\n ");
	}
	if (cnt != 4) {
		printf("Invalid command\n");
		return;
	}
	if (x2 < x1)
		swap_int(&x1, &x2);
	if (y2 < y1)
		swap_int(&y1, &y2);
	if (x1 < 0 || x2 > imrgb->sizex || y1 < 0 || y2 > imrgb->sizey ||
		x2 == x1 || y2 == y1) {
		printf("Invalid set of coordinates\n");
	} else {
		imrgb->x1 = x1;
		imrgb->x2 = x2;
		imrgb->y1 = y1;
		imrgb->y2 = y2;
		printf("Selected %d %d %d %d\n", y1, x1, y2, x2);
	}
}

void select_zone_gs(char *file_name, image_t_gs *imgs)
{
	int x1, x2, y1, y2;
	char *p;
	p = strtok(file_name, "\n ");
	int cnt = 0;
	while (p) {
		if (p[0] != '-' && (p[0] < '0' || p[0] > '9')) {
			printf("Invalid command\n");
			return;
		}
		for (int i = 1; p[i]; i++)
			if (p[i] < '0' || p[i] > '9') {
				printf("Invalid command\n");
				return;
			}
		if (cnt == 0)
			y1 = conv_str_to_int(p);
		else if (cnt == 1)
			x1 = conv_str_to_int(p);
		else if (cnt == 2)
			y2 = conv_str_to_int(p);
		else if (cnt == 3)
			x2 = conv_str_to_int(p);
		cnt++;
		p = strtok(NULL, "\n ");
	}
	if (cnt != 4) {
		printf("Invalid command\n");
		return;
	}
	if (x2 < x1)
		swap_int(&x1, &x2);
	if (y2 < y1)
		swap_int(&y1, &y2);
	if (x1 < 0 || x2 > imgs->sizex || y1 < 0 || y2 > imgs->sizey || x2 == x1 ||
		y2 == y1) {
		printf("Invalid set of coordinates\n");
	} else {
		imgs->x1 = x1;
		imgs->x2 = x2;
		imgs->y1 = y1;
		imgs->y2 = y2;
		printf("Selected %d %d %d %d\n", y1, x1, y2, x2);
	}
}

void crop_rgb(image_t_rgb *img)
{
	rgb_t **a = get_rgb_mat(img->x2 - img->x1, img->y2 - img->y1);
	if (!a) {
		printf("Could not crop image\n");
		return;
	}
	int temp = img->sizex;
	img->sizex = img->x2 - img->x1;
	img->sizey = img->y2 - img->y1;
	int cnt = 0;
	for (int i = img->x1; i < img->x2; i++)
		for (int j = img->y1; j < img->y2; j++) {
			a[cnt / img->sizey][cnt % img->sizey] = img->px[i][j];
			cnt++;
		}
	for (int i = 0; i < temp; i++)
		free(img->px[i]);
	free(img->px);
	img->px = get_rgb_mat(img->sizex, img->sizey);
	if (!img->px) {
		printf("Could not crop image\n");
		return;
	}
	img->x1 = 0;
	img->x2 = img->sizex;
	img->y1 = 0;
	img->y2 = img->sizey;
	for (int i = 0; i < img->sizex; i++)
		for (int j = 0; j < img->sizey; j++)
			img->px[i][j] = a[i][j];
	for (int i = 0; i < img->sizex; i++)
		free(a[i]);
	free(a);
	printf("Image cropped\n");
}

void crop_gs(image_t_gs *img)
{
	int **a = get_gs_mat(img->x2 - img->x1, img->y2 - img->y1);
	if (!a) {
		printf("Could not crop image\n");
		return;
	}
	int temp = img->sizex;
	img->sizex = img->x2 - img->x1;
	img->sizey = img->y2 - img->y1;
	int cnt = 0;
	for (int i = img->x1; i < img->x2; i++)
		for (int j = img->y1; j < img->y2; j++) {
			a[cnt / img->sizey][cnt % img->sizey] = img->px[i][j];
			cnt++;
		}
	for (int i = 0; i < temp; i++)
		free(img->px[i]);
	free(img->px);
	img->px = get_gs_mat(img->sizex, img->sizey);
	if (!img->px) {
		printf("Could not crop image\n");
		return;
	}
	img->x1 = 0;
	img->x2 = img->sizex;
	img->y1 = 0;
	img->y2 = img->sizey;
	for (int i = 0; i < img->sizex; i++)
		for (int j = 0; j < img->sizey; j++)
			img->px[i][j] = a[i][j];
	for (int i = 0; i < img->sizex; i++)
		free(a[i]);
	free(a);
	printf("Image cropped\n");
}
