#include "stdafx.h"
#include "DxLib.h"
#include "mode.h"
#include "mode.h"
#include "title.h"
#include "game.h"
#include "result.h"

static int modeNum = 0;
static int inGame = false;
int modeCtrl(int foo) {
	int ret = FALSE;

	switch (modeNum){
	case mode_TitleInit:{
		ret = title_Init( );
	}break;
	case mode_TitleDisp:{
		ret = title_Disp( );
	}break;
	case mode_TitleFinish:{
		ret = title_Finish( );
	}break;
	case mode_GameInit: {
		inGame = false;
		ret = Game_Init();
	}break;
	case mode_GameDisp: {
		ret = Game_disp();
	}break;
	case mode_GameFinish: {
		ret = Game_finish();
	}break;
	case mode_ResultInit:{
		ret = result_Init( );
	}break;
	case mode_ResultDisp:{
		ret = result_disp( );
	}break;
	case mode_ResultFinish:{
		ret = result_finish( );
	}break;
	default: 
		modeNum = mode_TitleInit;
	break;
	}

#if DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), (const TCHAR*)"MODE: %d", modeNum);
#endif

	if (ret > modeseq_Thuru) {
		modeNum = modeNum + ret;
		ret = 0;
	}
	else if (ret < modeseq_Thuru) {
		return ret;
	}

	return ret;
}