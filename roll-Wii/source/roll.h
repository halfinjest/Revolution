#define CONF_PIP "000100010001101111"
#define CONF_ROW "020103123404424444"
#define INST_PIP pips[3 * (INST_ROW) + k] - '0'
#define INST_ROW rows[3 * dice[j] + i] - '0'

void roll(int count)
{
	char *pips = CONF_PIP, *rows = CONF_ROW;
	int i, j, k, *dice = malloc(sizeof(int) * count);
	for (i = 0; i < count; i++)
	{
		dice[i] = rand() % 6;
		printf(" __________   ");
	}
	printf("\n");
	for (i = 0; i < count; i++) printf("|          |  ");
	printf("\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < count; j++)
		{
			printf("|  ");
			for (k = 0; k < 3; k++) printf(INST_PIP ? "* " : "  ");
			printf("  |  ");
		}
		printf("\n");
	}
	for (i = 0; i < count; i++) printf("|__________|  ");
	free(dice);
}
