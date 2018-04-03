#include "Minesweeper.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void generateRandomMap(Game *game)
{
	unsigned int i;
	int j, k;
	unsigned int size;
	srand((unsigned)time(NULL));
	size = game->width * game->height;
	for (i = 0; i < game->mine_total_count; i++)
	{
		int pos = rand() % size;
		if (game->map[pos] >= 0)
		{
			game->count--;
			game->map[pos] = -1;
		}
	}
	for (i = 0; i < size; i++)
	{
		int count = 0;
		if (game->map[i] == -1)
			continue;
		for (j = -1; j <= 1; j++)
		{
			for (k = -1; k <= 1; k++)
			{
				unsigned int posX = i % game->width;
				unsigned int posY = i / game->width;
				if (posX + j < 0 || posX + j >= game->width)
					continue;
				if (posY + k < 0 || posY + k >= game->height)
					continue;
				if (game->map[i + k * game->width + j] == -1)
					count++;
			}
		}
		game->map[i] = count;
	}
}

void init(Game **game, unsigned int width, unsigned int height, unsigned int mine_count)
{
	*game = (Game *)malloc(sizeof(Game));
	(*game)->width = width;
	(*game)->height = height;
	(*game)->map = (int *)malloc(sizeof(int *) * (*game)->width * (*game)->height);
	memset((*game)->map, 0, sizeof(int) * (*game)->width * (*game)->height);
	(*game)->mine_total_count = mine_count;
	(*game)->count = (*game)->width * (*game)->height;
	(*game)->used = (unsigned int *)malloc(sizeof(unsigned int *) * (*game)->width * (*game)->height);
	memset((*game)->used, 0, sizeof(unsigned int) * (*game)->width * (*game)->height);
	(*game)->status = 0;
	generateRandomMap(*game);
}

void destroy(Game *game)
{
	free(game->map);
	free(game->used);
	free(game);
}

void doit(Game *game, unsigned int x, unsigned int y)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return;
	unsigned int pos = y * game->height + x;
	if (game->used[pos])
		return;
	game->used[pos] = 1;
	if (game->map[pos] == -1)
	{
		game->status = -1;
		return;
	}
	game->count--;
	if (game->count <= 0)
	{
		game->status = 1;
		return;
	}
	if (game->map[pos] == 0)
	{
		int i, j;
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				if (i != 0 || j != 0)
				{
					doit(game, x + i, y + j);
					if (game->status != 0)
						break;
				}
			}
			if (game->status != 0)
				break;
		}
	}
}