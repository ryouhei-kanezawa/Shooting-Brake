#pragma once


#define BULLET_TYPE_1 false
#define BULLET_TYPE_2 false

enum {
	kBULLETSTATE_NOMAL = 0,
	kBULLETSTATE_CRASH = 1,
};

typedef struct pb {
	int scrn_x, scrn_y;
	int velo_x, velo_y;
	int radius;
	unsigned int cnt;
	unsigned int bcnt;
	int state;
	float c_radius;

	Vector2f scrn;
	Vector2f velo;
	Vector2f tag;
	int id;

	pb* nextBullet;
}bullet_t;

bullet_t* getBulletPtr( void );
bullet_t* getBulletLink( void );



int bullet_Go( int initX, int initY,int interval );
int bullet_update( void );

int bullet_init( bullet_t* p, int baseX, int baseY );
int bullet_disp( void );
int bullet_finish( void );
int goBullet( int x, int y );

bullet_t* getBulletNext( bullet_t* bp );
void LevelBullet( void );