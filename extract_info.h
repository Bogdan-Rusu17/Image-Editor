// COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct { // struct for rgb pixel
	int r;
	int g;
	int b;
} rgb_t;

typedef struct { // struct for rgb image
	char *format; // the format, magic word
	int sizex; // height of image
	int sizey; // width of image
	int maxv; // max value of the pixels in the image
	rgb_t **px; // matrix of pixels
	int x1, x2, y1, y2; // selection parameters
} image_t_rgb;

typedef struct { // struct for grayscale image
	char *format; // the format, the magic word
	int sizex; // height of image
	int sizey; // width of image
	int maxv; // max value of the pixels in the image
	int **px; // matrix of pixels
	int x1, x2, y1, y2; // selection parameters
} image_t_gs;

void extract_info(FILE *img_rd, image_t_rgb *img);

void extract_info_rgb_bin(FILE *img_rd, image_t_rgb *img, char *format);

void extract_info_rgb_asc(FILE *img_rd, image_t_rgb *img, char *format);

void extract_info_gs_bin(FILE *img_rd, image_t_gs *img, char *format);

void extract_info_gs_asc(FILE *img_rd, image_t_gs *img, char *format);

int conv_str_to_int(char *s); // function to convert a string to a number

void free_img_rgb(image_t_rgb *img); // free the rgb image

void free_img_gs(image_t_gs *img); // free the grayscale image

int check_string(char *src, char *dest); // compare to strings

void get_format(FILE *img_rd, char *format); // get magic word of an image

void ignore_comm(FILE *img_rd); // ignore comments on a line

void swap_int(int *a, int *b); // swap to integers

int *get_arr(int n); // alloc an array
