//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extract_info.h"
#include "apply_effects.h"
#include "save_image.h"
#include "select_crop.h"
#include "histogram_equalize.h"
#include "rotate.h"
#include "ops_skeleton.h"

int main(void)
{
	int gs = 0, rgb = 0;
	image_t_gs imgs;
	image_t_rgb imrgb;
	char *input_op;
	char *argument;
	input_op = (char *)malloc(40 * sizeof(char));
	if (!input_op) {
		fprintf(stderr, "Error allocating!\n");
		return 1;
	}
	argument = (char *)malloc(100 * sizeof(char));
	if (!argument) {
		fprintf(stderr, "Error allocating!\n");
		free(input_op);
		return 1;
	}
	char *format = (char *)malloc(4 * sizeof(char));
	if (!format) {
		fprintf(stderr, "Error allocating!\n");
		free(input_op);
		free(argument);
		return 1;
	}
	while (1) {
		scanf("%s", input_op);
		if (check_string(input_op, "EXIT")) {
			exit_op(&imgs, &imrgb, &gs, &rgb, format, argument, input_op);
			break;
		} else if (check_string(input_op, "LOAD")) {
			load_op(&imgs, &imrgb, &gs, &rgb, format, argument);
		} else if (check_string(input_op, "APPLY")) {
			apply_op(&imrgb, &gs, &rgb, argument);
		} else if (check_string(input_op, "SAVE")) {
			save_op(&imgs, &imrgb, &gs, &rgb, argument);
		} else if (check_string(input_op, "SELECT")) {
			select_op(&imgs, &imrgb, &gs, &rgb, argument);
		} else if (check_string(input_op, "CROP")) {
			crop_op(&imgs, &imrgb, &gs, &rgb);
		} else if (check_string(input_op, "ROTATE")) {
			rotate_op(&imgs, &imrgb, &gs, &rgb);
		} else if (check_string(input_op, "HISTOGRAM")) {
			histogram_op(imgs, gs, rgb, argument);
		} else if (check_string(input_op, "EQUALIZE")) {
			equalize_op(&imgs, gs, rgb);
		} else {
			fgets(argument, 100, stdin);
			printf("Invalid command\n");
		}
	}
	return 0;
}
