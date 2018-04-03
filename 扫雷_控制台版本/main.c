/*
 * 名称：扫雷
 * 作者：纪史超
 * 时间：2016-08-14
 * 描述：一个字符界面的扫雷游戏
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
		printf("游戏：扫雷\n作者：纪史超\n版本：v1.0\n\n");
		show(game);
		printf("坐标：");
		scanf_s("%u%u", &posX, &posY);					// modify by jishichao on 2017.10.15
		if (posX == -1 && posY == -1)
			game->status = -1;
		else
			doit(game, posX, posY);
	} while (!game->status);
	if (game->status > 0)
		printf("胜利！\n");
	else
		printf("失败！\n");

	system("pause");
	destroy(game);
	return 0;
}