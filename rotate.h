//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#pragma once
#include "extract_info.h"
#include "apply_effects.h"

void rotate_rgb(image_t_rgb * img, int angle);

void rotate_gs(image_t_gs *img, int angle);

void rotate_full_gs(image_t_gs *img, int angle); // rotate full image

void rotate_full_rgb(image_t_rgb *img, int angle); // rotate full image
