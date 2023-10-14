//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "extract_info.h"
#include <string.h>
int conv_str_to_int(char *s)
{
	int n = 0;
	int len = strlen(s);
	for (int i = 0; i < len; i++)
		n = n * 10 + s[i] - '0';
	return n;
}

void get_format(FILE *img_rd, char *format)
{
	char c;
	int cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		format[cnt++] = c;
		if (c == '\n')
			break;
	}
	format[cnt - 1] = '\0';
}

void extract_info_rgb_bin(FILE *img_rd, image_t_rgb *img, char *format)
{
	char c, *maxv, *sizex, *sizey;
	img->format = (char *)malloc(4 * sizeof(char));
	strcpy(img->format, format);
	maxv = (char *)malloc(4 * sizeof(char));
	sizex = (char *)malloc(10 * sizeof(char));
	sizey = (char *)malloc(10 * sizeof(char));
	int cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		sizex[cnt] = c;
		cnt++;
		if (c == ' ')
			break;
	}
	sizex[cnt - 1] = '\0';
	img->sizey = conv_str_to_int(sizex);
	cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		sizey[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	sizey[cnt - 1] = '\0';
	img->sizex = conv_str_to_int(sizey);
	cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		maxv[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	maxv[cnt - 1] = '\0';
	img->maxv = conv_str_to_int(maxv);
	free(sizex);
	free(sizey);
	free(maxv);
	img->x1 = 0;
	img->x2 = img->sizex;
	img->y1 = 0;
	img->y2 = img->sizey;
	img->px = (rgb_t **)malloc(img->sizex * sizeof(rgb_t *));
	if (!img->px) {
		printf("Error!\n");
		return;
	}
	unsigned char ch;
	for (int i = 0; i < img->sizex; i++) {
		img->px[i] = (rgb_t *)malloc(img->sizey * sizeof(rgb_t));
		if (!img->px[i]) {
			printf("Error!\n");
			for (int j = 0; j < i; j++)
				free(img->px[j]);
			return;
		}
		for (int j = 0; j < img->sizey; j++) {
			fread(&ch, sizeof(unsigned char), 1, img_rd);
			img->px[i][j].r = (int)ch;
			fread(&ch, sizeof(unsigned char), 1, img_rd);
			img->px[i][j].g = (int)ch;
			fread(&ch, sizeof(unsigned char), 1, img_rd);
			img->px[i][j].b = (int)ch;
		}
	}
}

void ignore_comm(FILE *img_rd)
{
	unsigned char c;
	fscanf(img_rd, "%c", &c);
	if (c == '#') {
		while (1) { // ignore all lines with comments
			while (fscanf(img_rd, "%c", &c))
				if (c == '\n')
					break;
			fscanf(img_rd, "%c", &c);
			if (c != '#')
				break;
		}
	}
}

void extract_info_rgb_asc(FILE *img_rd, image_t_rgb *img, char *format)
{
	char c, *maxv, *sizex, *sizey;
	img->format = (char *)malloc(4 * sizeof(char));
	strcpy(img->format, format);
	maxv = (char *)malloc(4 * sizeof(char));
	sizex = (char *)malloc(10 * sizeof(char));
	sizey = (char *)malloc(10 * sizeof(char));
	int cnt = 0;
	ignore_comm(img_rd);
	fseek(img_rd, -1, SEEK_CUR); // move the cursor one position to left
	while (fscanf(img_rd, "%c", &c)) {
		sizex[cnt++] = c;
		if (c == ' ')
			break;
	}
	sizex[cnt - 1] = '\0';
	img->sizey = conv_str_to_int(sizex);
	cnt = 0;
	while (fscanf(img_rd, "%c", &c)) {
		sizey[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	sizey[cnt - 1] = '\0';
	img->sizex = conv_str_to_int(sizey);
	cnt = 0;
	ignore_comm(img_rd); // move the cursor one position to left
	fseek(img_rd, -1, SEEK_CUR);
	while (fscanf(img_rd, "%c", &c)) {
		maxv[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	maxv[cnt - 1] = '\0';
	img->maxv = conv_str_to_int(maxv);
	ignore_comm(img_rd); // move the cursor one position to left
	fseek(img_rd, -1, SEEK_CUR);
	free(sizex);
	free(sizey);
	free(maxv);
	img->x1 = 0;
	img->x2 = img->sizex;
	img->y1 = 0;
	img->y2 = img->sizey;
	img->px = (rgb_t **)malloc(img->sizex * sizeof(rgb_t *));
	if (!img->px) {
		printf("Error!\n");
		return;
	}
	for (int i = 0; i < img->sizex; i++) {
		img->px[i] = (rgb_t *)malloc(img->sizey * sizeof(rgb_t));
		if (!img->px[i]) {
			printf("Error!\n");
			for (int j = 0; j < i; j++)
				free(img->px[j]);
			return;
		}
		for (int j = 0; j < img->sizey; j++) {
			fscanf(img_rd, "%d", &img->px[i][j].r);
			fscanf(img_rd, "%d", &img->px[i][j].g);
			fscanf(img_rd, "%d", &img->px[i][j].b);
		}
	}
}

void extract_info_gs_bin(FILE *img_rd, image_t_gs *img, char *format)
{
	char c, *maxv, *sizex, *sizey;
	img->format = (char *)malloc(4 * sizeof(char));
	strcpy(img->format, format);
	maxv = (char *)malloc(4 * sizeof(char));
	sizex = (char *)malloc(10 * sizeof(char));
	sizey = (char *)malloc(10 * sizeof(char));
	int cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		sizex[cnt] = c;
		cnt++;
		if (c == ' ')
			break;
	}
	sizex[cnt - 1] = '\0';
	img->sizey = conv_str_to_int(sizex);
	cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		sizey[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	sizey[cnt - 1] = '\0';
	img->sizex = conv_str_to_int(sizey);
	cnt = 0;
	while (fread(&c, sizeof(char), 1, img_rd)) {
		maxv[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	maxv[cnt - 1] = '\0';
	img->maxv = conv_str_to_int(maxv);
	free(sizex);
	free(sizey);
	free(maxv);
	img->x1 = 0;
	img->x2 = img->sizex;
	img->y1 = 0;
	img->y2 = img->sizey;
	img->px = (int **)malloc(img->sizex * sizeof(int *));
	if (!img->px) {
		printf("Error!\n");
		return;
	}
	unsigned char ch;
	for (int i = 0; i < img->sizex; i++) {
		img->px[i] = (int *)malloc(img->sizey * sizeof(int));
		if (!img->px[i]) {
			printf("Error!\n");
			for (int j = 0; j < i; j++)
				free(img->px[j]);
			return;
		}
		for (int j = 0; j < img->sizey; j++) {
			fread(&ch, sizeof(unsigned char), 1, img_rd);
			img->px[i][j] = (int)ch;
		}
	}
}

void extract_info_gs_asc(FILE *img_rd, image_t_gs *img, char *format)
{
	char c, *maxv, *sizex, *sizey;
	img->format = (char *)malloc(4 * sizeof(char));
	strcpy(img->format, format);
	maxv = (char *)malloc(4 * sizeof(char));
	sizex = (char *)malloc(10 * sizeof(char));
	sizey = (char *)malloc(10 * sizeof(char));
	int cnt = 0;
	ignore_comm(img_rd); // move the cursor one position to left
	fseek(img_rd, -1, SEEK_CUR);
	while (fscanf(img_rd, "%c", &c)) {
		sizex[cnt++] = c;
		if (c == ' ')
			break;
	}
	sizex[cnt - 1] = '\0';
	img->sizey = conv_str_to_int(sizex);
	cnt = 0;
	while (fscanf(img_rd, "%c", &c)) {
		sizey[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	sizey[cnt - 1] = '\0';
	img->sizex = conv_str_to_int(sizey);
	cnt = 0;
	ignore_comm(img_rd); // move the cursor one position to left
	fseek(img_rd, -1, SEEK_CUR);
	while (fscanf(img_rd, "%c", &c)) {
		maxv[cnt] = c;
		cnt++;
		if (c == '\n')
			break;
	}
	maxv[cnt - 1] = '\0';
	img->maxv = conv_str_to_int(maxv);
	ignore_comm(img_rd); // move the cursor one position to left
	fseek(img_rd, -1, SEEK_CUR);
	free(sizex);
	free(sizey);
	free(maxv);
	img->x1 = 0;
	img->x2 = img->sizex;
	img->y1 = 0;
	img->y2 = img->sizey;
	img->px = (int **)malloc(img->sizex * sizeof(int *));
	if (!img->px) {
		printf("Error!\n");
		return;
	}
	for (int i = 0; i < img->sizex; i++) {
		img->px[i] = (int *)malloc(img->sizey * sizeof(int));
		if (!img->px[i]) {
			printf("Error!\n");
			for (int j = 0; j < i; j++)
				free(img->px[j]);
			return;
		}
		for (int j = 0; j < img->sizey; j++)
			fscanf(img_rd, "%d", &img->px[i][j]);
	}
}

void free_img_rgb(image_t_rgb *img)
{
	free(img->format);
	for (int i = 0; i < img->sizex; i++)
		free(img->px[i]);
	free(img->px);
}

void free_img_gs(image_t_gs *img)
{
	free(img->format);
	for (int i = 0; i < img->sizex; i++)
		free(img->px[i]);
	free(img->px);
}

int check_string(char *src, char *dest)
{
	if (strlen(src) != strlen(dest))
		return 0;
	int len = strlen(src);
	for (int i = 0; i < len; i++)
		if (src[i] != dest[i])
			return 0;
	return 1;
}

void swap_int(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int *get_arr(int n)
{
	int *v = (int *)calloc(n, sizeof(int));
	return v;
}

