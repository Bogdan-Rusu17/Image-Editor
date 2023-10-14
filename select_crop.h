//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#pragma once
#include "extract_info.h"
#include "extract_info.h"

void select_all_rgb(image_t_rgb * imrgb);

void select_all_gs(image_t_gs *imgs);

void select_zone_rgb(char *file_name, image_t_rgb *imrgb);

void select_zone_gs(char *file_name, image_t_gs *imgs);

void crop_rgb(image_t_rgb *img);

void crop_gs(image_t_gs *img);
