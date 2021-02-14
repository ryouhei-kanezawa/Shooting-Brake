#include "DxLib.h"
#include "input.h"
#include "mode.h"
#include "main.h"
#include "block.h"
#include "block2.h"
#include "frame.h"

int count2;
int remain2;
int n, k;

struct BLOCKS block2[ TOTAL_BLOCK ];
static int Font02 = CreateFontToHandle( NULL, 40, 3 );

//block_t* bp[ MAX_BLOCK ] = { NULL };

static unsigned int BLOCK_Cr1 = GetColor( 255, 0, 0 );
static unsigned int BLOCK_Cr2 = GetColor( 0, 255, 0 );
static unsigned int BLOCK_Cr3 = GetColor( 0, 0, 255 );
static unsigned int BLOCK_Cr4 = GetColor( 125, 125, 125 );
static unsigned int BLOCK_CrB = GetColor( 0, 0, 0 );

int block_map[ BLOCK2_INDEX_Y ][ BLOCK2_INDEX_X ] = {
{1,2,3,1,2,3,1,2,3,1,2,3,1,2 },
{3,1,2,3,1,2,3,1,2,3,1,2,3,1 },
{2,3,1,2,3,1,2,3,1,2,3,1,2,3 },
{1,2,3,1,2,3,1,2,3,1,2,3,1,2 },
{4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
{4,4,4,4,4,4,4,4,4,4,4,4,4,4 }
};

void Block2_make( ) {
	count2 = 0;
	for ( n = 0; n < BLOCK2_INDEX_Y; n++ ) {
		for ( k = 0; k < BLOCK2_INDEX_X; k++ ) {
			if ( block_map[ n ][ k ] != 0 ) {
				block2[ count2 ].x = BLOCK_GAP + ( BLOCK2_WIDTH * k );
				block2[ count2 ].y = BLOCK_GAP + ( BLOCK2_HEIGHT * n );
				switch ( block_map[ n ][ k ] ) {
				case 1:
					block2[ count2 ].state = BLOCK_NORMAL;
					block2[ count2 ].color = BLOCK_Cr1;
					break;
				case 2:
					block2[ count2 ].state = BLOCK_NORMAL;
					block2[ count2 ].color = BLOCK_Cr2;
					break;
				case 3:
					block2[ count2 ].state = BLOCK_NORMAL;
					block2[ count2 ].color = BLOCK_Cr3;
					break;
				case 4:
					block2[ count2 ].state = BLOCK_HARD;
					block2[ count2 ].color = BLOCK_Cr4;
					break;
				default:
					break;
				}
			}
			count2++;
		}
	}
	Font02 = CreateFontToHandle( NULL, 40, 3 );
}

BLOCKS* getBlockIdx2Ptr( void ) {
	return block2;
}

int Block2_draw( float fall ) {
	count2 = 0;
	remain2 = TOTAL_BLOCK;
	for ( count2 = 0; count2 < TOTAL_BLOCK; count2++ ) {
		if ( block2[ count2 ].state == BLOCK_NORMAL||block2[count2].state==BLOCK_HARD ) {
			DrawBox( block2[ count2 ].x, block2[ count2 ].y + fall, block2[ count2 ].x + BLOCK2_WIDTH,
					 block2[ count2 ].y + BLOCK2_HEIGHT + fall, block2[ count2 ].color, TRUE );
			DrawBox( block2[ count2 ].x, block2[ count2 ].y + fall, block2[ count2 ].x + BLOCK2_WIDTH,
					 block2[ count2 ].y + BLOCK2_HEIGHT + fall, BLOCK_CrB, FALSE );
		} else {
			remain2--;
		}
	}

	if ( remain2 == 0 ) {
		DrawStringToHandle( FrameWidth / 2 - 90, ScreenHeight / 3, "STAGE CLEAR", GetColor( 255, 210, 192 ), Font02 );
		DrawString( FrameWidth / 2 - 105, ScreenHeight / 2 - 90, "PRESS ENTER TO STAGE3", GetColor( 255, 210, 100 ) );
		if ( getKeyboardOnTrigger( KEY_INPUT_RETURN ) ) {
			return -1;
		}
	}

	return 0;
}
