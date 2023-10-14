//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "ops_skeleton.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void load_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs, int *rgb,
			 char  *format, char *argument)
{
	FILE *input_rd;
	scanf("%s", argument);
	input_rd = fopen(argument, "rb");
	if (!input_rd) {
		printf("Failed to load %s\n", argument);
		if (*gs == 1)
			free_img_gs(imgs);
		if (*rgb == 1)
			free_img_rgb(imrgb);
		*gs = 0;
		*rgb = 0;
	} else {
		get_format(input_rd, format);
		if (*gs == 1) {
			free_img_gs(imgs);
			*gs = 0;
		}
		if (*rgb == 1) {
			free_img_rgb(imrgb);
			*rgb = 0;
		}
		if (format[1] == '6') { //rgb binary
			*rgb = 1;
			extract_info_rgb_bin(input_rd, imrgb, format);
		} else if (format[1] == '3') { //rgb ascii
			*rgb = 1;
			extract_info_rgb_asc(input_rd, imrgb, format);
		} else if (format[1] == '5') { //grayscale binary
			*gs = 1;
			extract_info_gs_bin(input_rd, imgs, format);
		} else if (format[1] == '2') { //grayscale ascii
			*gs = 1;
			extract_info_gs_asc(input_rd, imgs, format);
		}
		printf("Loaded %s\n", argument);
		fclose(input_rd);
	}
}

void exit_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			 int *rgb, char *format, char *argument,
			 char *input_op)
{
	free(input_op);
	free(argument);
	free(format);
	if (*gs == 1)
		free_img_gs(imgs);
	else if (*rgb == 1)
		free_img_rgb(imrgb);
	else
		printf("No image loaded\n");
}

void apply_op(image_t_rgb *imrgb, int *gs,
			  int *rgb, char *argument)
{
	fgets(argument, 100, stdin);
	char *p = strtok(argument, "\n "), *eff = argument;
	int cnt = 0;
	while (p) {
		cnt++;
		p = strtok(NULL, "\n ");
	}
	if (*rgb == 0 && *gs == 0) {
		printf("No image loaded\n");
	} else if (*rgb == 1) {
		if (cnt != 1) {
			printf("Invalid command\n");
		} else { // we put a space because we read with a space with fgets
			if (check_string(eff, " GAUSSIAN_BLUR"))
				apply_effect_rgb(imrgb, "GAUSSIAN_BLUR");
			else if (check_string(eff, " BLUR"))
				apply_effect_rgb(imrgb, "BLUR");
			else if (check_string(eff, " EDGE"))
				apply_effect_rgb(imrgb, "EDGE");
			else if (check_string(eff, " SHARPEN"))
				apply_effect_rgb(imrgb, "SHARPEN");
			else if (check_string(eff, " MOTION_BLUR"))
				apply_effect_rgb(imrgb, "MOTION_BLUR");
			else if (check_string(eff, " LAPLACIAN"))
				apply_effect_rgb(imrgb, "LAPLACIAN");
			else if (check_string(eff, " EMBOSS"))
				apply_effect_rgb(imrgb, "EMBOSS");
			else
				printf("APPLY parameter invalid\n");
		}
	} else {
		if (cnt != 1)
			printf("Invalid command\n");
		else
			printf("Easy, Charlie Chaplin\n");
	}
}

void save_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			 int *rgb, char *argument)
{
	fgets(argument, 100, stdin);
	int cnt = 0;
	int ascii = 0;
	char *p = strtok(argument, "\n "), *out_name;
	while (p) {
		if (cnt == 0)
			out_name = p;
		else
			ascii = 1;
		cnt++;
		p = strtok(NULL, "\n ");
	}
	if (*rgb == 1) {
		if (!ascii)
			save_rgb_bin(out_name, *imrgb);
		else
			save_rgb_asc(out_name, *imrgb);
		printf("Saved %s\n", out_name);
	} else if (*gs == 1) {
		if (!ascii)
			save_gs_bin(out_name, *imgs);
		else
			save_gs_asc(out_name, *imgs);
		printf("Saved %s\n", out_name);
	} else {
		printf("No image loaded\n");
	}
}

void select_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			   int *rgb, char *argument)
{
	char c;
	scanf("%c", &c);
	fgets(argument, 100, stdin);
	if (argument[0] == 'A') { //select ALL
		if (*rgb == 1) {
			select_all_rgb(imrgb);
		} else if (*gs == 1) {
			select_all_gs(imgs);
		} else {
			char *p;
			p = strtok(argument, " ");
			while (p)
				p = strtok(NULL, " ");
			printf("No image loaded\n");
		}
	} else { // potential select zones of image
		if (*rgb == 1)
			select_zone_rgb(argument, imrgb);
		else if (*gs == 1)
			select_zone_gs(argument, imgs);
		else
			printf("No image loaded\n");
	}
}

void crop_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			 int *rgb)
{
	if (*rgb == 1)
		crop_rgb(imrgb);
	else if (*gs == 1)
		crop_gs(imgs);
	else
		printf("No image loaded\n");
}

void rotate_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			   int *rgb)
{
	int angle;
	scanf("%d", &angle);
	if (*rgb == 0 && *gs == 0) {
		printf("No image loaded\n");
	} else {
		if (abs(angle) > 360 || angle % 90) {
			printf("Unsupported rotation angle\n");
		} else {
			if (*rgb == 1)
				rotate_rgb(imrgb, angle);
			else
				rotate_gs(imgs, angle);
		}
	}
}

void histogram_op(image_t_gs imgs, int gs, int rgb, char *argument)
{
	fgets(argument, 100, stdin);
	if (rgb == 0 && gs == 0) {
		printf("No image loaded\n");
	} else {
		if (rgb == 1) {
			int invalid = 0, cnt = 0;
			char *p = strtok(argument, "\n ");
			while (p) {
				for (int i = 0; p[i]; i++)
					if (!(p[i] >= '0' && p[i] <= '9')) // check if it's digit
						invalid = 1;
				cnt++;
				p = strtok(NULL, "\n ");
			}
			if (invalid == 1 || cnt != 2)
				printf("Invalid command\n");
			else
				printf("Black and white image needed\n");
		} else {
			histogram(imgs, argument);
		}
	}
}

void equalize_op(image_t_gs *imgs, int gs, int rgb)
{
	if (rgb == 0 && gs == 0) {
		printf("No image loaded\n");
	} else {
		if (rgb == 1)
			printf("Black and white image needed\n");
		else
			equalize(imgs);
	}
}
