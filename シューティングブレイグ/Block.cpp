#include "DxLib.h"
#include "input.h"
#include "mode.h"
#include "main.h"
#include "block.h"
#include "frame.h"

int count;
int remain;
int i, j;

struct BLOCKS block[ MAX_BLOCK ];
static int Font01;

//block_t* bp[ MAX_BLOCK ] = { NULL };

unsigned int BLOCK_Cr1 = GetColor( 255, 0, 0 );
unsigned int BLOCK_Cr2 = GetColor( 0, 255, 0 );
unsigned int BLOCK_Cr3 = GetColor( 0, 0, 255 );
unsigned int BLOCK_CrB = GetColor( 0, 0, 0 );

int block_map[ BLOCK_INDEX_Y ][ BLOCK_INDEX_X ] = {
{1,2,3,1,2,3,1 },
{2,3,1,2,3,1,2 },
{3,1,2,3,1,2,3 },
{1,2,3,1,2,3,1 },
{2,3,1,2,3,1,2 },
{3,1,2,3,1,2,3 }
};

void Block_make( ) {
	count = 0;
	for ( i = 0; i < BLOCK_INDEX_Y; i++ ) {
		for ( j = 0; j < BLOCK_INDEX_X; j++ ) {
			if ( block_map[ i ][ j ] != 0 ) {
				block[ count ].x = BLOCK_GAP + ( BLOCK_WIDTH * j );
				block[ count ].y = BLOCK_GAP + ( BLOCK_HEIGHT * i );
				block[ count ].state = BLOCK_NORMAL;
				switch ( block_map[i][j] ) {
				case 1:
					block[ count ].color = BLOCK_Cr1;
					break;
				case 2:
					block[ count ].color = BLOCK_Cr2;
					break;
				case 3:
					block[ count ].color = BLOCK_Cr3;
					break;
				default:
					break;
				}
			}
			count++;
		}
	}
}

/*
block_t* getBlockPtr( void ) {
	return 0;
	//return bp;
}
*/

BLOCKS* getBlockIdxPtr( void ) 
{
	return block;
}

int Block_draw( float fall ) {
	count = 0;
	remain = MAX_BLOCK;
	for ( count = 0; count < MAX_BLOCK; count++ ) {
		if ( block[ count ].state == BLOCK_NORMAL ) {
			DrawBox( block[ count ].x, block[ count ].y + fall, block[ count ].x + BLOCK_WIDTH,
					 block[ count ].y + BLOCK_HEIGHT + fall, block[ count ].color, TRUE );
			DrawBox( block[ count ].x, block[ count ].y + fall, block[ count ].x + BLOCK_WIDTH,
					 block[ count ].y + BLOCK_HEIGHT + fall, BLOCK_CrB, FALSE );
		} else {
			remain--;
		}
	}

	if ( remain == 0 ) {
		DrawStringToHandle( FrameWidth / 2 - 90, ScreenHeight / 3, "STAGE CLEAR", GetColor( 255, 210, 192 ), Font01 );
		DrawString( FrameWidth / 2 - 105, ScreenHeight / 2 - 90, "PRESS ENTER TO STAGE2", GetColor( 255, 210, 100 ) );
		if ( getKeyboardOnTrigger( KEY_INPUT_RETURN ) ) {
			return -1;
		}
	}

	return 0;
}

int Font_Init( void ) {
	Font01 = CreateFontToHandle( NULL, 40, 3 );
	return 0;
}

