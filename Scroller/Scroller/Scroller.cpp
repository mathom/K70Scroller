// Scroller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>
#include <math.h>

#include "LibCorsairRGB\LibCorsairRGB.h"
#include "LibCorsairRGB\keymaps.h"
#include "SOIL.h"

int width, height, channels;
unsigned char *ht_map = 0;

int k_width = 22;
int k_height = 7;

int sx = 0, sy = 0;
int dx = 1, dy = 1;

void cleanup()
{
	lcrgb_deinitialise();
	if (ht_map) {
		SOIL_free_image_data(ht_map);
	}
}

unsigned char get_pixel(int x, int y, int c)
{
	if (channels > 3) {
		c += 1;
	}
	return ht_map[(y*width + x)*channels + c];
}

void display() {
	for (int x = 0; x < 22; x++) {
		for (int y = 0; y < 7; y++) {
			lcrgb_set_position(x, y, get_pixel(sx+x, sy+y, 0), get_pixel(sx+x, sy+y, 1), get_pixel(sx+x, sy+y, 2));
		}
	}
	lcrgb_flush_light_buffer();
}

void scroll() {
	if (sx < 0 || sx + k_width > width)
		dx = -dx;
	if (sy < 0 || sy + k_height > height)
		dy = -dy;

	sx += dx;
	sy += dy;
}

int main(int argc, char *argv[])
{
	lcrgb_set_verbosity_level(99);

	int status = lcrgb_initialise();
	if (status != 0) {
		printf("Failed to intialise LibCorsairRGB\n");
		return status;
	}

	atexit(cleanup);

	lcrgb_set_keymap(lcrgb_ANSI_US);

	// clear keyboard
	for (unsigned char key = 0; key < 144; key++) {
		lcrgb_set_key_code(key, 0, 0, 0);
	}
	lcrgb_flush_light_buffer();

	char *image = "image.png";
	if (argc > 1) {
		image = argv[1];
	}

	ht_map = SOIL_load_image(
		image,
		&width, &height, &channels,
		SOIL_LOAD_RGB
	);

	if (0 == ht_map)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		getchar();
		return -1;
	}

	while (1) {
		Sleep(50);
		display();
		scroll();
	}
	return 0;
}

