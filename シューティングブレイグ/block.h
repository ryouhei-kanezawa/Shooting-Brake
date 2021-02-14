#pragma once

int Block_draw( float fall );
void Block_make( );
//void Block_init( );

#define BLOCK_WIDTH 130
#define BLOCK_HEIGHT 30
#define BLOCK_GAP 40
#define BLOCK_INDEX_Y 6
#define BLOCK_INDEX_X 7
#define MAX_BLOCK 42
#define Color_Rand GetRand(255)


enum {
	BLOCK_CRASH = 0,
	BLOCK_NORMAL = 1,
	BLOCK_HARD = 2,
};

typedef struct BLOCKS {
	float x;
	float y;
	int state;
	int color;
}block_t;

extern struct BLOCKS block[];

BLOCKS* getBlockIdxPtr( void );
//BLOCKS setBlockPtr( BLOCKS bp, int idx );

int Font_Init( );