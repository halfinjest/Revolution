#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "roll.h"

#define FALSE 0
#define LENGTH 4
#define TRUE 1

void setup()
{
	static void *xfb = NULL;
	static GXRModeObj *rmode = NULL;
	VIDEO_Init();
	WPAD_Init();
	rmode = VIDEO_GetPreferredMode(NULL);
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb, 20, 20, rmode -> fbWidth, rmode -> xfbHeight,
		rmode -> fbWidth * VI_DISPLAY_PIX_SZ);
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode -> viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

int main()
{
	srand(time(NULL));
	setup();
	printf("\x1b[2;0H");
	roll(LENGTH);
	printf("Press the HOME button to return, or press the A button to roll again.\n");
	while(TRUE)
	{
		WPAD_ScanPads();
		u32 button = WPAD_ButtonsDown(0);
		if (button & WPAD_BUTTON_HOME) exit(0);
		else if (button & WPAD_BUTTON_A) roll(LENGTH);
		VIDEO_WaitVSync();
	}
	return 0;
}
