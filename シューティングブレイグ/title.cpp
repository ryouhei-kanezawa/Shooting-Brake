#include "stdafx.h"
#include "DxLib.h"
#include "input.h"

#include "time.h"
#include "main.h"
#include "mode.h"
#include "title.h"

int Font_ti;
int Sound_ti;
int Graph_ti;
int num;
static time_t startTM;

int Font00, Font01;

int title_Init( void ) {
	num = 0;
	//Sound_ti = LoadSoundMem( "nhk.mp3" );
	Graph_ti = LoadGraph( "index2.png" );

	Font_ti = CreateFontToHandle( NULL, 150, 3 );
	startTM = clock( );
	return modeseq_Increase;
}

int title_Disp( void ) {
	clock_t elaps = ( clock( ) - startTM ) / CLOCKS_PER_SEC;

	//PlaySoundMem( Sound_ti, DX_PLAYTYPE_BACK );
	DrawGraph( 0, 0, Graph_ti, TRUE );

	DrawStringToHandle( ScreenWidth / 2, ScreenHeight / 2 - 200, "Shooting", GetColor( 255, 255, 255 ), Font_ti );
	DrawStringToHandle( ScreenWidth / 2, ScreenHeight / 2 - 50,  "   Break", GetColor( 190, 190, 190 ), Font_ti );

	num++;
	if ( ( num & 63 ) < ( 63 / 2 ) ) {
		DrawFormatString( 300, 600, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS ESC KEY TO EXIT" );
	} else {
		DrawFormatString( 300 - 15, 600, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS ENTER KEY TO GAME" );
	}
	if ( getKeyboardOnTrigger( KEY_INPUT_ESCAPE ) ) {
		return modeseq_Exit;
	}
	if ( getKeyboardOnTrigger( KEY_INPUT_RETURN ) ) {
		return modeseq_Game;
	}

	return 0;
	return modeseq_Increase;
}

int title_Finish( void ) {
	//DeleteSoundMem( Sound_ti );
	DeleteGraph( Graph_ti );

	return modeseq_Increase;
}