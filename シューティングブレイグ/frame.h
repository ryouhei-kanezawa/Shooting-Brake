#pragma once

#define FrameWidth 950
#define FrameHeight 1000
#define FrameWidth2 900
#define X_Posi 20;

void frame_make( void );
void endvar_make( void );
int endvar_over( float fall,int stage);
void FrameFont_Init( void );
void interval_bulet( int interval );
void Description_Disp( void );