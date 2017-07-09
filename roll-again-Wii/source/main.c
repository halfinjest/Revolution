#include <gccore.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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
	int display, getDice = 0, i, j, count = 4, newDice, place = 0, rolls,
		*dice = malloc(sizeof(int) * count);
	u32 button;
	setup();
	srand(time(NULL));
	printf("\x1b[2;0HSpecify a permutation, and press A or B to roll.");
	while (true)
	{
		dice = realloc(dice, sizeof(int) * count);
		for (i = 0; i < count; i++)
		{
			if (dice[i] < 1 || dice[i] > 6) dice[i] = 0;
			printf("\x1b[4;%dH%c\x1b[5;%dH%c", i * 2,
				dice[i] ? dice[i] + '0' : '_', i * 2, i == place ? '^' : ' ');
		}
		WPAD_ScanPads();
		button = WPAD_ButtonsDown(0);
		if (button & WPAD_BUTTON_A)
		{
			for (i = 0, j = 0; i < count; i++)
				if (dice[i] >= 1 && dice[i] <= 6) j++;
			if (j == count)
			{
				for (i = 0; i < count; i++) getDice += dice[i] * pow(10, i);
				display = 1;
				break;
			}
		}
		else if (button & WPAD_BUTTON_B)
		{
			for (i = 0, j = 0; i < count; i++)
				if (dice[i] >= 1 && dice[i] <= 6) j++;
			if (j == count)
			{
				for (i = 0; i < count; i++) getDice += dice[i] * pow(10, i);
				display = 0;
				break;
			}
		}
		else if (button & WPAD_BUTTON_DOWN && dice[place] >= 1) dice[place]--;
		else if (button & WPAD_BUTTON_HOME)
		{
			free(dice);
			exit(0);
		}
		else if (button & WPAD_BUTTON_LEFT && place > 0) place--;
		else if (button & WPAD_BUTTON_MINUS && place < count - 1)
		{
			count--;
			dice[count] = 0;
			printf("\x1b[4;%dH ", count * 2);
		}
		else if (button & WPAD_BUTTON_PLUS) count++;
		else if (button & WPAD_BUTTON_RIGHT && place < count - 1) place++;
		else if (button & WPAD_BUTTON_UP && dice[place] < 6) dice[place]++;
		VIDEO_WaitVSync();
	}
	printf("\n");
	for (rolls = 0; newDice != getDice; rolls++)
	{
		newDice = 0;
		for (i = 0; i < count; i++) newDice += (rand() % 6 + 1) * pow(10, i);
	}
	if (display)
	{
		for (i = 0; i < count; i++) dice[i]--;
		roll(count, dice);
		printf("\n\n");
	}
	free(dice);
	printf("%d rolls. Press HOME to exit.", rolls);
	while (true)
	{
		WPAD_ScanPads();
		button = WPAD_ButtonsDown(0);
		if (button & WPAD_BUTTON_HOME) exit(0);
		VIDEO_WaitVSync();
	}
	return 0;
}
