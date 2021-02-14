#pragma once

int Block2_draw( float fall );
void Block2_make( );

#define BLOCK2_WIDTH 65
#define BLOCK2_HEIGHT 30
#define BLOCK2_INDEX_Y 6
#define BLOCK2_INDEX_X 14
#define TOTAL_BLOCK 84

extern struct BLOCKS block2[ ];

BLOCKS* getBlockIdx2Ptr( void );
