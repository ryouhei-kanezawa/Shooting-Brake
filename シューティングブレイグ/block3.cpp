#include "DxLib.h"
#include "input.h"
#include "mode.h"
#include "main.h"
#include "block.h"
#include "block2.h"
#include "block3.h"
#include "frame.h"


int count3;
int remain3;
int c, s;

struct BLOCKS block3[ TOTAL_BLOCK ];
static int Font03;

//block_t* bp[ MAX_BLOCK ] = { NULL };

static int BLOCK_Cr1 = GetColor( 255, 0, 0 );
static int BLOCK_Cr2 = GetColor( 0, 255, 0 );
static int BLOCK_Cr3 = GetColor( 0, 0, 255 );
static int BLOCK_Cr4 = GetColor( 125, 125, 125 );
static int BLOCK_CrB = GetColor( 0, 0, 0 );

int block3_map[ BLOCK2_INDEX_Y ][ BLOCK2_INDEX_X ] = {
{1,4,4,4,4,4,4,4,4,4,4,4,4,1 },
{1,1,4,2,2,2,2,2,2,2,2,4,1,1 },
{1,1,1,4,2,2,2,2,2,2,4,1,1,1 },
{1,1,4,1,4,2,2,2,2,4,1,4,1,1 },
{1,1,4,1,1,4,4,4,4,1,1,4,1,1 },
{1,1,4,1,1,1,4,4,1,1,1,4,1,1 }
};

void Block3_make( ) {
	count3 = 0;
	for ( c = 0; c < BLOCK2_INDEX_Y; c++ ) {
		for ( s = 0; s < BLOCK2_INDEX_X; s++ ) {
			if ( block3_map[ c ][ s ] != 0 ) {
				block3[ count3 ].x = BLOCK_GAP + ( BLOCK2_WIDTH * s );
				block3[ count3 ].y = BLOCK_GAP + ( BLOCK2_HEIGHT * c );
				switch ( block3_map[ c ][ s ] ) {
				case 1:
					block3[ count3 ].state = BLOCK_NORMAL;
					block3[ count3 ].color = BLOCK_Cr3;
					break;
				case 2:
					block3[ count3 ].state = BLOCK_NORMAL;
					block3[ count3 ].color = BLOCK_Cr1;
					break;
				case 4:
					block3[ count3 ].state = BLOCK_HARD;
					block3[ count3 ].color = BLOCK_Cr4;
					break;
				}
			}
			count3++;
		}
	}
	Font03 = CreateFontToHandle( NULL, 40, 3 );
}

BLOCKS* getBlockIdx3Ptr( void ) {
	return block3;
}

/*
int Rondom_color( void ) {
	int color_num = GetRand( 2 );

	switch ( color_num ) {
	case 0:
		return BLOCK_Cr1;
	case 1:
		return BLOCK_Cr2;
	case 2:
		return BLOCK_Cr3;
	}
	return 0;
}
*/

int Block3_draw( float fall ) {
	count3 = 0;
	remain3 = TOTAL_BLOCK;
	for ( count3 = 0; count3 < TOTAL_BLOCK; count3++ ) {
		if ( block3[ count3 ].state == BLOCK_NORMAL || block3[ count3 ].state == BLOCK_HARD ) {
			DrawBox( block3[ count3 ].x, block3[ count3 ].y + fall, block3[ count3 ].x + BLOCK2_WIDTH,
					 block3[ count3 ].y + BLOCK2_HEIGHT + fall, block3[ count3 ].color, TRUE );
			DrawBox( block3[ count3 ].x, block3[ count3 ].y + fall, block3[ count3 ].x + BLOCK2_WIDTH,
					 block3[ count3 ].y + BLOCK2_HEIGHT + fall, BLOCK_CrB, FALSE );
		} else {
			remain3--;
		}
	}

	if ( remain3 == 0 ) {
		DrawStringToHandle( FrameWidth / 2 - 90, ScreenHeight / 3, "STAGE CLEAR", GetColor( 255, 210, 192 ), Font03 );
		DrawString( FrameWidth / 2 - 105, ScreenHeight / 2 - 90, "PRESS ENTER TO STAGE3", GetColor( 255, 210, 100 ) );
		if ( getKeyboardOnTrigger( KEY_INPUT_RETURN ) ) {
			return -1;
		}
	}

	return 0;
}
