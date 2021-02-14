#pragma once


enum {
	mode_TitleInit=1,
	mode_TitleDisp,
	mode_TitleFinish,

	//mode_AdvertiseInit,
	//mode_AdvertiseDisp,
	//mode_AdvertiseFinish,

	mode_GameInit,
	mode_GameDisp,
	mode_GameFinish,

	mode_ResultInit,
	mode_ResultDisp,
	mode_ResultFinish,
};

enum
{
	modeseq_Thuru = 0,/* mode‘JˆÚ•ÏX‚È‚µ */
	modeseq_Exit = -1,/* mode‘JˆÚI—¹ */
	modeseq_Increase = 1,/* mode‘JˆÚŸ‚Ö */
	modeseq_Game = 2,/* mode‘JˆÚƒQ[ƒ€‚Ö*/
};

int modeCtrl(int foo);