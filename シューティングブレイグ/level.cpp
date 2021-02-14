#include "stdio.h"
#include "DxLib.h"
#include "main.h"
#include "frame.h"
#include "level.h"

int bleak = 0;
static int lev = 0;

int getLevelPtr( void ) {
	return lev;
}

void LevelInit( void ) {
	lev = Level1;
	bleak = 0;
}

void LevelBullet( void ) {
	bleak++;
	if ( bleak == 20 ) {
		lev = Level2;
	} else if ( bleak == 100 ) {
		//lev = Level3;
	}
}

void DrawLevel(int lev) {
	DrawBox(FrameWidth + 70, 110, FrameWidth + 180, 160, GetColor(0, 153, 253), TRUE);
	DrawFormatString(FrameWidth + 90, 125, GetColor(255, 255, 255), (const TCHAR*)"Level: %d", lev);


	return;
}