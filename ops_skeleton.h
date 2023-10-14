//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#pragma once
#include "extract_info.h"
#include <string.h>
#include "save_image.h"
#include "select_crop.h"
#include "histogram_equalize.h"
#include "rotate.h"
#include "apply_effects.h"

void load_op(image_t_gs * imgs, image_t_rgb * imrgb, int *gs,
			 int *rgb, char *format, char *argument);

void exit_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			 int *rgb, char *format, char *argument,
			 char *input_op);

void apply_op(image_t_rgb *imrgb, int *gs,
			  int *rgb, char *argument);

void save_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			 int *rgb, char *argument);

void select_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			   int *rgb, char *argument);

void crop_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			 int *rgb);

void rotate_op(image_t_gs *imgs, image_t_rgb *imrgb, int *gs,
			   int *rgb);

void histogram_op(image_t_gs imgs, int gs, int rgb, char *argument);

void equalize_op(image_t_gs *imgs, int gs, int rgb);
