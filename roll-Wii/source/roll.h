#define CONF_PIP "000100010001101111"
#define CONF_ROW "020103123404424444"
#define INST_PIP pips[3 * (INST_ROW) + k] - '0'
#define INST_ROW rows[3 * dice[j] + i] - '0'

void roll(int length, int *dice)
{
	char *pips = CONF_PIP, *rows = CONF_ROW;
	int i, j, k;
	for (i = 0; i < length; i++) printf(" __________   ");
	printf("\n");
	for (i = 0; i < length; i++) printf("|          |  ");
	printf("\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < length; j++)
		{
			printf("|  ");
			for (k = 0; k < 3; k++) printf(INST_PIP ? "* " : "  ");
			printf("  |  ");
		}
		printf("\n");
	}
	for (i = 0; i < length; i++) printf("|__________|  ");
	printf("\n\n");
}
