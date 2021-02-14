#include "stdafx.h"
#include "DxLib.h"
#include "main.h"
#include "frame.h"
#include "score.h"

static int score = 0;
static int target_score = 0;
static int disp_score = 0;
static int game = 0;

void score_update( void ) {
	if ( disp_score < target_score ) {
		disp_score++;
	}

	char buf[ 64 ];
	DrawString( FrameWidth + 70, 170, "SCORE: ", GetColor( 255, 255, 255 ) );
	sprintf_s( buf, "%08d", disp_score );
	int l = GetDrawStringWidth( buf, strlen( buf ) );
	DrawFormatString( FrameWidth + 130, 170, GetColor( 255, 255, 255 ), ( const TCHAR* )buf, disp_score );
}

void score_add( int add ) {
	score = score + add;
	target_score = score;
}

void score_init( void ) {
	score = 0;
	target_score = 0;
	disp_score = 0;
}

int score_get( void ) {
	if ( score != target_score ) {
		return target_score;
	}
	return score;
}

void setStageCrea( int stage ) {
	game = stage;
	return;
}

int getStageCrea( void ) {
	return game;
}