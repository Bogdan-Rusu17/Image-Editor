//COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023
#include "histogram_equalize.h"
#include <string.h>
void histogram(image_t_gs img, char *arg)
{
	int bins, stars;
	char *p;
	p = strtok(arg, "\n "); // splitting into tokens
	int cnt = 0;
	while (p) {
		for (int i = 0; p[i]; i++)
			if (p[i] > '9' || p[i] < '0') {
				printf("Invalid command\n");
				return;
			}
		if (cnt == 0)
			stars = conv_str_to_int(p);
		if (cnt == 1)
			bins = conv_str_to_int(p);
		cnt++;
		p = strtok(NULL, "\n ");
	}
	if (cnt != 2) {
		printf("Invalid command\n");
		return;
	}
	if (256 % bins) {
		printf("Invalid set of parameters\n");
		return;
	}
	int *freq;
	freq = get_arr(256);
	if (!freq) {
		printf("Error doing histogram\n");
		return;
	}
	for (int i = img.x1; i < img.x2; i++)
		for (int j = img.y1; j < img.y2; j++)
			freq[img.px[i][j]]++;
	int bin_length = 256 / bins, max_stars = -1;
	int *interval_fr = get_arr(bins);
	if (!interval_fr) {
		free(freq);
		printf("Error doing histogram\n");
		return;
	}
	for (int i = 0; i <= 256 - bin_length; i += bin_length) {
		for (int val = i; val < i + bin_length; val++)
			interval_fr[i / bin_length] += freq[val];
		if (max_stars < interval_fr[i / bin_length])
			max_stars = interval_fr[i / bin_length];
	}
	for (int i = 0; i <= 256 - bin_length; i += bin_length) {
		double stars_count = (stars * interval_fr[i / bin_length]) / max_stars;
		int floor_count = (int)stars_count;
		printf("%d\t|\t", floor_count);
		for (int j = 0; j < floor_count; j++)
			printf("*");
		printf("\n");
	}
	free(freq);
	free(interval_fr);
}

void equalize(image_t_gs *img)
{
	int area = img->sizex * img->sizey;
	int *freq, *s_part;
	freq = get_arr(256);
	if (!freq) {
		printf("Error doing histogram\n");
		return;
	}
	s_part = get_arr(256);
	if (!s_part) {
		printf("Error doing histogram\n");
		free(freq);
		return;
	}
	for (int i = 0; i < img->sizex; i++)
		for (int j = 0; j < img->sizey; j++)
			freq[img->px[i][j]]++;
	s_part[0] = freq[0];
	for (int i = 1; i < 256; i++)
		s_part[i] += s_part[i - 1] + freq[i]; // bit of dynprog to optimise
	for (int i = 0; i < img->sizex; i++)
		for (int j = 0; j < img->sizey; j++) {
			double new_val = (255 * s_part[img->px[i][j]]) / area;
			img->px[i][j] = (int)new_val;
		}
	free(s_part);
	free(freq);
	printf("Equalize done\n");
}
