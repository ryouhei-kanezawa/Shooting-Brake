#include "stdio.h"
#include "DxLib.h"
#include "time.h"
#include "main.h"
#include "frame.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "level.h"

static int baseX, baseY;
player_t* pt = NULL;
void player_body( player_t* pt );
int interval = 0;
//static clock_t time;


player_t* getPlayerPtr( void ) {
	return pt;
}

int player_init( void ) {
	pt = ( player_t* )malloc( sizeof( player_t ) );
	//time = clock( );

	interval = 1;
	pt->baseX = FrameWidth / 2 + 20;
	pt->baseY = FrameHeight - 50;
	return 0;
}

int player_disp( void ) {
	//clock_t interval = ( clock( ) - time ) / CLOCKS_PER_SEC;

	if ( getKeyboardState( KEY_INPUT_LEFT ) ) {
		if ( pt->baseX <= 55 ) {
			pt->baseX -= 0;
		} else {
			pt->baseX = pt->baseX - 10;
		}
	}
	if ( getKeyboardState( KEY_INPUT_RIGHT ) ) {
		if ( pt->baseX >= 935 ) {
			pt->baseX += 0;
		} else {
			pt->baseX = pt->baseX + 10;
		}
	}

	if ( getKeyboardState( KEY_INPUT_SPACE ) ) {/* bullet go! */
		bullet_Go( pt->baseX, pt->baseY, interval );/* ’e”­ŽË */
		interval++;
	}

	interval_bulet( interval );
	player_body( pt );

	return 0;
}

void player_body( player_t* pt ) {
	float x1 = pt->baseX - 35;
	float x2 = pt->baseX + 35;
	float y1 = pt->baseY - 22.5;
	float y2 = pt->baseY + 22.5;
	unsigned int col = 0xf0ffff;
	DrawBox( x1, y1, x2, y2, col, true );
}

int player_finish( void ) {
	free( pt ); pt = NULL;
	interval = 0;

	return 0;
}