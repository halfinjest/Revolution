#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiiuse/wpad.h>
#include "roll.h"

static void *xfb = NULL;

static GXRModeObj *rmode = NULL;

void setup()
{
	VIDEO_Init();
	WPAD_Init();
	rmode = VIDEO_GetPreferredMode(NULL);
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight,
		rmode->fbWidth * VI_DISPLAY_PIX_SZ);
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

int main()
{
	setup();
	int i, digit, length = 4, rolls,
	*dice = malloc(sizeof(int) * length);
	char *getDice = malloc(sizeof(char) * length),
		*newDice = malloc(sizeof(char) * length);
	getDice = "6666";
	for (i = 0; i < length; i++)
	{
		digit = getDice[i] - '0';
		if (digit >= 1 && digit <= 6) getDice[i] = digit - 1 + '0';
		else 
		{
			printf("Error: Invalid Integer\n");
			exit(0);
		}
	}
	srand(time(NULL));
	printf("\x1b[2;0HPress A to roll or HOME to return.\n");
	while (true)
	{
		WPAD_ScanPads();
		u32 button = WPAD_ButtonsDown(0);
		if (button & WPAD_BUTTON_A)
		{
			for (rolls = 0; strcmp(getDice, newDice); rolls++)
				for (i = 0; i < length; i++) newDice[i] = (rand() % 6) + '0';
			for (i = 0; i < length; i++) dice[i] = getDice[i] - '0';
			roll(length, dice);
			memset(newDice, 0, strlen(newDice));
			printf("%d rolls\n\n", rolls);
		}
		else if (button & WPAD_BUTTON_HOME) exit(0);
		VIDEO_WaitVSync();
	}
	return 0;
}
