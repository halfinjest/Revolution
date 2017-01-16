#include <gccore.h>
#include <math.h>
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
	int i, j, length = 4, place = 0, rolls, getDice = 0, newDice = 0;
	int *dice = malloc(sizeof(int) * length);
	u32 button;
	setup();
	for (i = 0; i < length; i++) dice[i] = 0;
	srand(time(NULL));
	printf("\x1b[2;0HSpecify a permutation, and press A to roll.");
	while (true)
	{
		for (i = 0; i < length; i++)
		{
			printf("\x1b[4;%dH%c", i * 2,
				(dice[i] == 0) ? '_' : dice[i] + '0');
			for (j = 0; j < length; j++)
				printf("\x1b[5;%dH%c", j * 2, (place == j ? '^' : ' '));
		}
		WPAD_ScanPads();
		button = WPAD_ButtonsDown(0);
		if (button & WPAD_BUTTON_UP)
		{
			if (dice[place] == 0) dice[place] = 1;
			else if (dice[place] < 6) dice[place]++;
		}
		else if (button & WPAD_BUTTON_DOWN)
		{
			if (dice[place] == 1) dice[place] = 0;
			else if (dice[place] > 1) dice[place]--;
		}
		else if (button & WPAD_BUTTON_RIGHT && place < length - 1) place++;
		else if (button & WPAD_BUTTON_LEFT && place > 0) place--;
		else if (button & WPAD_BUTTON_A)
		{
			for (i = 0; i < length; i++)
				getDice += (int)pow((double)10, (double)i) * dice[i];
			if (getDice >= 1111 && getDice <= 6666) break;
		}
		else if (button & WPAD_BUTTON_HOME) exit(0);
		VIDEO_WaitVSync();
	}
	printf("\n");
	for (rolls = 0; getDice != newDice; rolls++)
	{
		newDice = 0;
		for (i = 0; i < length; i++)
			newDice += (int)pow((double)10, (double)i) * (rand() % 6 + 1);
	}
	for (i = 0; i < length; i++) dice[i]--;
	roll(length, dice);
	printf("%d rolls. Press HOME to return.", rolls);
	while (true)
	{
		WPAD_ScanPads();
		button = WPAD_ButtonsDown(0);
		if (button & WPAD_BUTTON_HOME) exit(0);
		VIDEO_WaitVSync();
	}
	return 0;
}
