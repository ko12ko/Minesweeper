#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

typedef struct
{
	int *map;				// -1 - mine, >=0 mine_count around
	unsigned int *used;		// 0 - not used, 1 - used
	unsigned int height;
	unsigned int width;
	unsigned int mine_total_count;
	unsigned int count;

	int status;				// -1 - fail, 0 - running, 1 - win
} Game;

void init(Game **game, unsigned int width, unsigned int height, unsigned int mine_count);
void destroy(Game *game);
void doit(Game *game, unsigned int x, unsigned int y);

#endif