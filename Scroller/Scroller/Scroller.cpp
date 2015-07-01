// Scroller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>
#include <math.h>

#include "LibCorsairRGB\LibCorsairRGB.h"
#include "LibCorsairRGB\keymaps.h"

int _tmain(int argc, _TCHAR* argv[])
{
	lcrgb_set_verbosity_level(99);

	int status = lcrgb_initialise();
	if (status != 0) {
		printf("Failed to intialise LibCorsairRGB\n");
		return status;
	}

	atexit(lcrgb_deinitialise);

	lcrgb_set_keymap(lcrgb_ANSI_US);

	while (1) {
		Sleep(1000);
	}
	return 0;
}

