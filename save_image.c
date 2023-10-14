//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "save_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void save_rgb_bin(char *file_name, image_t_rgb img)
{
	FILE *out = fopen(file_name, "wb");
	fwrite("P6", sizeof(char), 2, out);
	fwrite("\n", sizeof(char), strlen("\n"), out);
	int *dig = (int *)malloc(10 * sizeof(int));
	if (!dig) {
		printf("Error allocating\n");
		return;
	}
	int cnt = 0, cop = img.sizey;
	unsigned char c;
	while (cop) {
		dig[cnt++] = cop % 10;
		cop /= 10;
	}
	for (int i = cnt - 1; i >= 0; i--) {
		c = '0' + dig[i];
		fwrite(&c, sizeof(char), 1, out);
	}
	fwrite(" ", sizeof(char), strlen(" "), out);
	cnt = 0;
	cop = img.sizex;
	while (cop) {
		dig[cnt++] = cop % 10;
		cop /= 10;
	}
	for (int i = cnt - 1; i >= 0; i--) {
		c = '0' + dig[i];
		fwrite(&c, sizeof(char), 1, out);
	}
	fwrite("\n", sizeof(char), strlen("\n"), out);
	cnt = 0;
	cop = img.maxv;
	while (cop) {
		dig[cnt++] = cop % 10;
		cop /= 10;
	}
	for (int i = cnt - 1; i >= 0; i--) {
		c = '0' + dig[i];
		fwrite(&c, sizeof(char), 1, out);
	}
	fwrite("\n", sizeof(char), strlen("\n"), out);
	for (int i = 0; i < img.sizex; i++)
		for (int j = 0; j < img.sizey; j++) {
			c = (unsigned char)img.px[i][j].r;
			fwrite(&c, sizeof(unsigned char), 1, out);
			c = (unsigned char)img.px[i][j].g;
			fwrite(&c, sizeof(unsigned char), 1, out);
			c = (unsigned char)img.px[i][j].b;
			fwrite(&c, sizeof(unsigned char), 1, out);
		}
	free(dig);
	fclose(out);
}

void save_rgb_asc(char *file_name, image_t_rgb img)
{
	FILE *out = fopen(file_name, "wt");
	fprintf(out, "P3\n");
	fprintf(out, "%d %d\n", img.sizey, img.sizex);
	fprintf(out, "%d\n", img.maxv);
	for (int i = 0; i < img.sizex; i++)
		for (int j = 0; j < img.sizey; j++) {
			fprintf(out, "%d %d ", img.px[i][j].r, img.px[i][j].g);
			fprintf(out, "%d\n", img.px[i][j].b);
		}
	fclose(out);
}

void save_gs_bin(char *file_name, image_t_gs img)
{
	FILE *out = fopen(file_name, "wb");
	fwrite("P5", sizeof(char), 2, out);
	fwrite("\n", sizeof(char), strlen("\n"), out);
	int *dig = (int *)malloc(10 * sizeof(int));
	if (!dig) {
		printf("Error allocating\n");
		return;
	}
	int cnt = 0, cop = img.sizey;
	unsigned char c;
	while (cop) {
		dig[cnt++] = cop % 10;
		cop /= 10;
	}
	for (int i = cnt - 1; i >= 0; i--) {
		c = '0' + dig[i];
		fwrite(&c, sizeof(char), 1, out);
	}
	fwrite(" ", sizeof(char), strlen(" "), out);
	cnt = 0;
	cop = img.sizex;
	while (cop) {
		dig[cnt++] = cop % 10;
		cop /= 10;
	}
	for (int i = cnt - 1; i >= 0; i--) {
		c = '0' + dig[i];
		fwrite(&c, sizeof(char), 1, out);
	}
	fwrite("\n", sizeof(char), strlen("\n"), out);
	cnt = 0;
	cop = img.maxv;
	while (cop) {
		dig[cnt++] = cop % 10;
		cop /= 10;
	}
	for (int i = cnt - 1; i >= 0; i--) {
		c = '0' + dig[i];
		fwrite(&c, sizeof(char), 1, out);
	}
	fwrite("\n", sizeof(char), strlen("\n"), out);
	for (int i = 0; i < img.sizex; i++)
		for (int j = 0; j < img.sizey; j++) {
			c = (unsigned char)img.px[i][j];
			fwrite(&c, sizeof(unsigned char), 1, out);
		}
	free(dig);
	fclose(out);
}

void save_gs_asc(char *file_name, image_t_gs img)
{
	FILE *out = fopen(file_name, "wt");
	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n", img.sizey, img.sizex);
	fprintf(out, "%d\n", img.maxv);
	for (int i = 0; i < img.sizex; i++) {
		for (int j = 0; j < img.sizey; j++)
			fprintf(out, "%d\n", img.px[i][j]);
	}
	fclose(out);
}
