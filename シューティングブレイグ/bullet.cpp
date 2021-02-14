#include "stdio.h"
#include "math.h"

#include "DxLib.h"

#include "main.h"
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "frame.h"
#include "level.h"

#if false


static bullet_t* bp = NULL;

bullet_t* getBulletPtr( void ) {
	return bp;
}

int bullet_Go( int initX, int initY,int interval) {
	if ( bp == NULL ) {
		bp = ( bullet_t* )malloc( sizeof( bullet_t ) );
		bullet_init( bp, initX, initY );
	} else {
		return -1;
	}
	return 0;
}

int bullet_update( void ) {
	if ( bp ) {
		switch ( bp->state ) {
		case kBULLETSTATE_NOMAL:
		{
			bp->scrn_x = bp->scrn_x + bp->velo_x;
			bp->scrn_y = bp->scrn_y + bp->velo_y;

			int x1 = bp->scrn_x - 2;
			int x2 = bp->scrn_x + 2;
			int x3 = bp->scrn_x;
			int y1 = bp->scrn_y + 2;
			int y2 = bp->scrn_y + 2;
			int y3 = bp->scrn_y - 2;
			unsigned int col = 0xf00f0f;
			DrawTriangle( x1, y1, x2, y2, x3, y3, col, true );
			DrawCircle( bp->scrn_x, bp->scrn_y, bp->radius, 0xffc000, false );
			bp->bcnt = 128;
		}
		break;

		case kBULLETSTATE_CRASH:
			bp->bcnt--;
			if ( bp->bcnt ) {
				int x1 = bp->scrn_x - 1 * ( bp->bcnt & 8 );
				int x2 = bp->scrn_x + 1 * ( bp->bcnt & 8 );
				int x3 = bp->scrn_x;
				int y1 = bp->scrn_y;
				int y2 = bp->scrn_y;
				int y3 = bp->scrn_y - 1 * ( bp->bcnt & 8 );
				if ( bp->c_radius < FrameWidth ) {
					DrawCircle( bp->scrn_x, bp->scrn_y, bp->radius, 0xffc000, false );
					bp->c_radius = pow( bp->c_radius, 1.05 );
				} else {
					free( bp );
					bp = NULL;
					goto _finish;
				}
			} else {
				free( bp );
				bp = NULL;
				goto _finish;
			}
		break;
		}
		if ( bp->scrn_y < 35 ) {
			free( bp );
			bp = NULL;
		}
	} else {
	}
	_finish:
	return 0;
}

int bullet_init( bullet_t* p, int baseX, int baseY ) {
	p->scrn_x = baseX;
	p->scrn_y = baseY;
	p->velo_x = 0;
	p->velo_y = -8;
	p->state = kBULLETSTATE_NOMAL;
	p->radius = 15.0;
	p->c_radius = 15.0;
	return 0;
}

int bullet_disp( void ) {
	return 0;
}

int bullet_finish( void ) {
	if ( bp ) {
		free( bp );
		bp = NULL;
	}

	return 0;
}

int goBullet( int x, int y ) {
	return 0;
}

#endif


//#if BULLET_TYPE_2

static int Cr;

static unsigned long id = 0;

static bullet_t* bp = NULL;

static int level;

bullet_t* getBulletPtr( void ) {
	return bp;
}

bullet_t* getBulletLink( void ) {
	return bp;
}

bullet_t* setBulletLink( bullet_t* bn ) {
	bp = bn;
	return bp;
}

bullet_t* getBulletNext( bullet_t* bp ) {
	return bp->nextBullet;
}


static bullet_t* getNewPb( void ) {
	bullet_t* en;
	en = ( bullet_t* )malloc( sizeof( bullet_t ) );
	if ( en == NULL ) return NULL;
	en->nextBullet = NULL;
	en->id = id++;
	en->cnt = 0;
	en->state = kBULLETSTATE_NOMAL;
	en->c_radius = en->radius = 8;
	return en;
}

static bullet_t* appendEp( bullet_t* et ) {
	bullet_t* en = getBulletLink( );/* 先頭のポインタをもらう */
	if ( en == NULL ) {
		et = setBulletLink( et );
		return et;
	}
	do {
		if ( en->nextBullet == NULL ) {
			en->nextBullet = et;
			et->nextBullet = NULL;
			break;
		}
		en = en->nextBullet;
	} while ( 1 );
	return en;
}

static bullet_t* linkOutEp( bullet_t* en ) {
	bullet_t* ep = getBulletLink( );
	if ( ep == en ) {/*先頭だ */
		return setBulletLink( en->nextBullet );
	}
	do {
		if ( ep->nextBullet == en ) {
			ep->nextBullet = en->nextBullet;
			free( en );
			break;
		}
		ep = ep->nextBullet;
		if ( ep == NULL ) {
			break;
		}
	} while ( 1 );
	return ep;
}


int bullet_Go( int initX, int initY,int interval ) {
	level = getLevelPtr( );
 	switch ( level ) {
	case Level1:
		if ( interval % 55 == 0 ) {
			bullet_t* et = getNewPb( );
			appendEp( et );/* Bullet Linkに加える */

			player_t* pt = getPlayerPtr( );

			et->tag.x = pt->baseX;/* playerの位置を記憶 */
			et->tag.y = -20;
			et->scrn.x = initX;/* 初期位置 */
			et->scrn.y = initY;

			/* 弾の軌道を計算する */
			float x, y, r;
			float nx, ny;
			x = et->tag.x - et->scrn.x;
			y = et->tag.y - et->scrn.y;
			r = sqrt( x * x + y * y );
			/* 正規化 Normalize */
			nx = ( et->tag.x - et->scrn.x ) / r;
			ny = ( et->tag.y - et->scrn.y ) / r;
			/* 速さ　*/
			et->velo.x = 8 * nx;
			et->velo.y = 8 * ny;
		}

		Cr = GetColor( 255, 0, 255 );

		break;
	case Level2:
		if ( interval % 15== 0 ) {
			bullet_t* et = getNewPb( );
			appendEp( et );/* Bullet Linkに加える */

			player_t* pt = getPlayerPtr( );

			et->tag.x = pt->baseX;/* playerの位置を記憶 */
			et->tag.y = -20;
			et->scrn.x = initX;/* 初期位置 */
			et->scrn.y = initY;

			/* 弾の軌道を計算する */
			float x, y, r;
			float nx, ny;
			x = et->tag.x - et->scrn.x;
			y = et->tag.y - et->scrn.y;
			r = sqrt( x * x + y * y );
			/* 正規化 Normalize */
			nx = ( et->tag.x - et->scrn.x ) / r;
			ny = ( et->tag.y - et->scrn.y ) / r;
			/* 速さ　*/
			et->velo.x = 8 * nx;
			et->velo.y = 8 * ny;
		}

		Cr = GetColor( 255, 255, 255 );

		break;
	case Level3:
		if ( interval % 20 == 0 ) {
			bullet_t* et = getNewPb( );
			appendEp( et );/* Bullet Linkに加える */

			player_t* pt = getPlayerPtr( );

			et->tag.x = pt->baseX;/* playerの位置を記憶 */
			et->tag.y = -20;
			et->scrn.x = initX;/* 初期位置 */
			et->scrn.y = initY;

			/* 弾の軌道を計算する */
			float x, y, r;
			float nx, ny;
			x = et->tag.x - et->scrn.x;
			y = et->tag.y - et->scrn.y;
			r = sqrt( x * x + y * y );
			/* 正規化 Normalize */
			nx = ( et->tag.x - et->scrn.x ) / r;
			ny = ( et->tag.y - et->scrn.y ) / r;
			/* 速さ　*/
			et->velo.x = 8 * nx;
			et->velo.y = 8 * ny;
		}

		Cr = GetColor( 255, 255, 255 );
		break;
	}

	return 0;
}


/*
		  LOGICAL | BIT
	INV             ~
	NOT   !
	AND		&&		&
	OR		||		|
	XOR				^

*/


void Bullet_draw( bullet_t* ef ) {
	if ( ef->nextBullet != NULL ) {
		Bullet_draw( ef->nextBullet );
	}

	switch ( ef->state ) {
	case kBULLETSTATE_NOMAL:
	{
		if ( ef->scrn.y > ( ScreenHeight - 120 ) ) {
			//ef->velo.y = -1 * ef->velo.y;
		}
		if ( ( ef->scrn.y < ( 0 ) ) || ( ef->scrn.y > ScreenHeight ) ) {
			linkOutEp( ef );/* temination */
			return;
		}

		ef->scrn.x += ef->velo.x;
		ef->scrn.y += ef->velo.y;
		DrawCircle( ef->scrn.x, ef->scrn.y, ef->c_radius, Cr, true );
	}
	break;
	case kBULLETSTATE_CRASH:
	{
		linkOutEp( ef );/* temination */
		return;
	}
	break;
	}
}


int bullet_update( void ) {
	bullet_t* en = getBulletLink( );/* 先頭のポインタをもらう */
	if ( en != NULL ) {
		Bullet_draw( en );
	}
	return 0;
}


int Bullet_init( ) {
	setBulletLink( NULL );
	id = 0;
	return 0;
}

static void Bullet_free( bullet_t* ef ) {
	if ( ef->nextBullet != NULL ) {
		Bullet_free( ef->nextBullet );
	}
	free( ef );
}

int bullet_finish( void )/* 敵の終了化 */
{
	bullet_t* en = getBulletLink( );/* 先頭のポインタをもらう */
	if ( en != NULL ) {/* 解放 */
		Bullet_free( en );
	}
	setBulletLink( NULL );
	return 0;
}

int goBullet( int x, int y )/* 敵の放出 */
{
	return 0;
}

//#endif