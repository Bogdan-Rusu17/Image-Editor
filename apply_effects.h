//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#pragma once
#include "extract_info.h"

double **get_gauss_ker(void); // gauss kernel

double **get_sharp_ker(void); // sharpen kernel

double **get_edge_ker(void); // edge kernel

double **get_box_ker(void); // box blur kernel

double **get_emboss_ker(void);

double **get_laplacian_ker(void);

double **get_motion_ker(void);

int *get_dx(void); // get the vector for the 8th directions for moving on row

int *get_dy(void); // get the vector for the 8th directions for moving on column

rgb_t **get_rgb_mat(int sizex, int sisey); // alloc an rgb matrix

int **get_gs_mat(int sizex, int sizey); // alloc a grayscale matrix

// check if a position is inside the matrix from stx to sizex and sty to sizey
int inside(int x, int y, int sizex, int sizey, int stx, int sty);

void apply_effect_rgb(image_t_rgb *img, char *eff);

int clamp(int x);
