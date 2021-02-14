#include "stdafx.h"
#include "DxLib.h"
#include "main.h"
#include "input.h"
#include "time.h"

#include "score.h"
#include "mode.h"
#include "result.h"

int Font_re, Fontre2, Fontre3, Fontre4;
static int high_score = 0;
int now_score = 0;
static int game = 0;

static clock_t startTm;

int result_Init( void ) {

	int n = score_get( );/* 今のゲームのスコアを取得 */
	game = getStageCrea( );

	Font_re = CreateFontToHandle( NULL, 60, 3 );
	Fontre2 = CreateFontToHandle( NULL, 30, 3 );
	Fontre3 = CreateFontToHandle( NULL, 50, 3 );
	Fontre4 = CreateFontToHandle( NULL, 60, 3 );

	now_score = n;
	if ( n > high_score ) {
		high_score = n;
	}
	startTm = clock( );

	return modeseq_Increase;
}

int result_disp( void ) {
	clock_t elaps = ( clock( ) - startTm ) / CLOCKS_PER_SEC;

	DrawStringToHandle( 70, 70, "RESULT", GetColor( 255, 210, 100 ), Fontre3 );

	DrawFormatStringToHandle( 70, 230, GetColor( 255, 255, 255 ),
							  Fontre4, ( const TCHAR* )"HIGH SCORE: %d", high_score );
	DrawFormatStringToHandle( 70, 290, GetColor( 255, 255, 255 ),
							  Fontre4, ( const TCHAR* )"YOUR SCORE: %d", now_score );

	switch ( game ) {
	case 1:
		DrawStringToHandle( 950, 230, "Stage1:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 250, "Failured", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 330, "Stage2:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 350, "Failured", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 430, "Stage3:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 450, "Failured", GetColor( 255, 255, 255 ), Font_re );
		break;
	case 2:
		DrawStringToHandle( 950, 230, "Stage1:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 250, "Crea", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 330, "Stage2:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 350, "Failured", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 430, "Stage3:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 450, "Failured", GetColor( 255, 255, 255 ), Font_re );
		break;
	case 3:
		DrawStringToHandle( 950, 230, "Stage1:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 250, "Crea", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 330, "Stage2:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 350, "Crea", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 430, "Stage3:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 450, "Failured", GetColor( 255, 255, 255 ), Font_re );
		break;
	case 4:
		DrawStringToHandle( 950, 230, "Stage1:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 250, "Crea", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 330, "Stage2:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 350, "Crea", GetColor( 255, 255, 255 ), Font_re );
		DrawStringToHandle( 950, 430, "Stage3:", GetColor( 255, 210, 100 ), Fontre2 );
		DrawStringToHandle( 1200, 450, "Crea", GetColor( 255, 255, 255 ), Font_re );
		break;
	}

	if ( getKeyboardOnTrigger( KEY_INPUT_ESCAPE ) ) {
		return modeseq_Exit;
	}
	if ( getKeyboardOnTrigger( KEY_INPUT_SPACE ) ) {
		return modeseq_Increase;
	}

	if ( elaps < 10 ) {
		return 0;
	}
	return modeseq_Increase;
}

int result_finish( void ) {

	return modeseq_Increase;
}