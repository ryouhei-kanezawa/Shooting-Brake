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
	modeseq_Thuru = 0,/* mode�J�ڕύX�Ȃ� */
	modeseq_Exit = -1,/* mode�J�ڏI�� */
	modeseq_Increase = 1,/* mode�J�ڎ��� */
	modeseq_Game = 2,/* mode�J�ڃQ�[����*/
};

int modeCtrl(int foo);