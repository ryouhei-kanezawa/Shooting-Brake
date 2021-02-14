
#include "stdio.h"
#include "DxLib.h"
#include "main.h"
#include "mode.h"
#include "input.h"
#include "frame.h"
#include "level.h"
#include "player.h"
#include "block.h"
#include "block2.h"
#include "block3.h"

static int BoxWidth = FrameWidth2 + FrameWidth + 40;
static int Font01;
static int Graph_fr = LoadGraph( "Description.png" );
int tank = 0;
int before_lv = 1;
BLOCKS* bp;

void frame_make(void) {
	unsigned int Cr;

	Cr = GetColor(223, 220, 177);

	DrawBox( 20, 20, FrameWidth + 20, FrameHeight + 20, Cr, FALSE );
	DrawBox( FrameWidth + 40, 20, BoxWidth, FrameHeight + 20, Cr, FALSE );

	return ;
}

void endvar_make( void ) {
	unsigned int Cr;

	Cr = GetColor( 255, 0, 0 );

	DrawLine( 20, FrameHeight - 150, FrameWidth + 20, FrameHeight - 150, Cr );

	return;
}

void interval_bulet( int interval ) {
	int lv = getLevelPtr( );

	if ( lv != before_lv ) {
		tank = 0;
	}
	before_lv = lv;

	if ( getKeyboardState( KEY_INPUT_SPACE ) ) { 

	switch ( lv ) {
	case Level1:
		if ( interval % 55 != 0 ) {
			tank += 12;
		} else {
			tank = 0;
		}
		if ( tank >= 630 ) {
			tank += 0;
		}
		break;
	case Level2:
		if ( interval % 15 != 0 ) {
			tank += 42;
		} else {
			tank = 0;
		}
		if ( tank >= 630 ) {
			tank += 0;
		}
		break;
	}

	}

	DrawString( FrameWidth + 70, 45, "interval", GetColor( 125, 125, 125 ) );
	DrawBox( FrameWidth + 70, 60, FrameWidth + tank + 70, 70, GetColor( 45, 65, 255 ), true );
	DrawBox( FrameWidth + 70, 60, FrameWidth + 700, 70, GetColor( 255, 255, 255 ), false );
}

void Description_Disp( void ) {

	//DrawString( FrameWidth + 70, 700, "左右キーで移動", GetColor( 255, 255, 255 ) );
	//DrawString( FrameWidth + 70, 730, "スペースキー長押しで発射", GetColor( 255, 255, 255 ) );
	DrawGraph( FrameWidth + 70, 700, Graph_fr, TRUE );

}

int endvar_over( float fall,int stage ) {
	switch ( stage ) {
	case 1:
		bp = getBlockIdxPtr( );
		for ( int i = 0; i < MAX_BLOCK; i++ ) {
			if ( bp->state == BLOCK_NORMAL ) {
				if ( FrameHeight - 150 < bp->y + fall + BLOCK_HEIGHT ) {
					DrawStringToHandle( FrameWidth / 2 - 90, ScreenHeight / 3, "GAME OVER", GetColor( 255, 210, 192 ), Font01 );
					DrawString( FrameWidth / 2 - 100, ScreenHeight / 2 - 90, "PRESS ENTER KEY TO RESULT", GetColor( 255, 210, 100 ) );
					if ( getKeyboardOnTrigger( KEY_INPUT_RETURN ) ) {
						return -1;
					}
				}
			}
			bp++;
		}
		return 0;
	default:
		if ( stage == 2 ) {
			bp = getBlockIdx2Ptr( );
		} else {
			bp = getBlockIdx3Ptr( );
		}
		for ( int i = 0; i < TOTAL_BLOCK; i++ ) {
			if ( bp->state == BLOCK_NORMAL||bp->state==BLOCK_HARD ) {
				if ( FrameHeight - 150 < bp->y + fall + BLOCK2_HEIGHT ) {
					DrawStringToHandle( FrameWidth / 2 - 90, ScreenHeight / 3, "GAME OVER", GetColor( 255, 210, 192 ), Font01 );
					DrawString( FrameWidth / 2 - 100, ScreenHeight / 2 - 90, "PRESS ENTER KEY TO RESULT", GetColor( 255, 210, 100 ) );
					if ( getKeyboardOnTrigger( KEY_INPUT_RETURN ) ) {
						return -1;
					}
				}
			}
			bp++;
		}
		return 0;
	}

}

void FrameFont_Init( void ) {
	Font01 = CreateFontToHandle( NULL, 40, 3 );
}