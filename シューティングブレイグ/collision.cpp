
#include "stdio.h"
#include "DxLib.h"
#include "main.h"

#include "bullet.h"
#include "level.h"
#include "player.h"
#include "block.h"
#include "block2.h"
#include "block3.h"
#include "collision.h"
#include "score.h"
#include "math.h"


void collisionDetect( float fall,int stage ) {
	static double n = 1.20;
	bullet_t* bp = getBulletPtr( );
	BLOCKS* bk = getBlockIdxPtr( );

#if false
	if ( bk && bp ) {
		int i = 0;
		int pointX = bp->scrn_x;
		int pointY = bp->scrn_y;
		int radius = bp->radius;
		do {
			if ( bk[ i ].state == BLOCK_NORMAL ) {

				if ( pointY - radius > bk[ i ].y + fall && pointY - radius<bk[ i ].y + fall + BLOCK_HEIGHT
					 && pointX>bk[ i ].x && pointX < bk[ i ].x + BLOCK_WIDTH
					 ) {
					bk[ i ].state = BLOCK_CRASH;
					bp->state = kBULLETSTATE_CRASH;
				}
			}
			i++;
			if ( i >= MAX_BLOCK ) { break; }
		} while ( bk != NULL );
	}
#endif

//#if BULLET_TYPE_2
	bp = getBulletLink( );  //æ“ª‚Ìƒ|ƒCƒ“ƒ^‚ð‚à‚ç‚¤
	switch ( stage ) {
	case 1:
		bk = getBlockIdxPtr( );
		break;
	case 2:
		bk = getBlockIdx2Ptr( );
		break;
	case 3:
		bk = getBlockIdx3Ptr( );
		break;
	}
	if ( bk && bp ) {
		do {
 			int i = 0;
			int pointX = bp->scrn.x;// scrn_x;
			int pointY = bp->scrn.y;// scrn_y;
			int radius = bp->radius;
			//DrawCircle( pointX, pointY, radius, 0x00ff00, true );

			do {
				if ( bk[ i ].state == BLOCK_NORMAL || bk[ i ].state == BLOCK_HARD ) {

					switch ( stage ) {
					case 1:
						if ( pointY - radius > bk[ i ].y + fall
							 && pointY - radius<bk[ i ].y + fall + BLOCK_HEIGHT
							 && pointX>bk[ i ].x && pointX < bk[ i ].x + BLOCK_WIDTH
							 ) {
							bk[ i ].state--;
							bp->state = kBULLETSTATE_CRASH;
							score_add( 100 );
							LevelBullet( );
						}
						break;
					default:
						if ( pointY - radius > bk[ i ].y + fall
							 && pointY - radius<bk[ i ].y + fall + BLOCK2_HEIGHT
							 && pointX>bk[ i ].x - 5 && pointX < bk[ i ].x + BLOCK2_WIDTH + 5
							 ) {
							bk[ i ].state--;
							bp->state = kBULLETSTATE_CRASH;
							score_add( 100 );
							LevelBullet( );
						}
						break;
					}
				}
				i++;
				if ( i >= MAX_BLOCK && stage == 1 ) { break; }
				if ( i >= TOTAL_BLOCK && ( stage == 2 || stage == 3 ) ) { break; }
			} while ( bk != NULL );
			bp = getBulletNext( bp );
		} while ( bp != NULL );
	}
//#endif
}