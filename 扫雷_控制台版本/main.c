/*
 * ���ƣ�ɨ��
 * ���ߣ���ʷ��
 * ʱ�䣺2016-08-14
 * ������һ���ַ������ɨ����Ϸ
 */

#include <stdio.h>
#include <stdlib.h>
#include "Minesweeper.h"

void show(Game *game)
{
	int i, size;
	size = game->width * game->height;
	printf("count: %d\n", game->count);
	for (i = 0; i < size; i++)
	{
		printf("%c", game->used[i] ? game->map[i] + '0' : '+');
		if ((i + 1) % game->width == 0)
			printf("\n");
	}
}

int main()
{
	Game *game;
	unsigned int posX, posY;
	init(&game, 10, 10, 5);
	do
	{
		system("cls");
		printf("��Ϸ��ɨ��\n���ߣ���ʷ��\n�汾��v1.0\n\n");
		show(game);
		printf("���꣺");
		scanf_s("%u%u", &posX, &posY);					// modify by jishichao on 2017.10.15
		if (posX == -1 && posY == -1)
			game->status = -1;
		else
			doit(game, posX, posY);
	} while (!game->status);
	if (game->status > 0)
		printf("ʤ����\n");
	else
		printf("ʧ�ܣ�\n");

	system("pause");
	destroy(game);
	return 0;
}