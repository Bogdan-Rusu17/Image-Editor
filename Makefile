# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c extract_info.c apply_effects.c save_image.c select_crop.c histogram_equalize.c rotate.c ops_skeleton.c
	$(CC) $(CFLAGS) -o image_editor image_editor.c extract_info.c apply_effects.c save_image.c select_crop.c histogram_equalize.c rotate.c ops_skeleton.c -g -lm

pack:
	zip -FSr 312CA_RusuBogdan_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
