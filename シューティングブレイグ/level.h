#pragma once

enum {
	Level1 = 0,
	Level2,
	Level3,
};

void LevelBullet( void );
int getLevelPtr(void);
void LevelInit( void );
void DrawLevel(int lev);