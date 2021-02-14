#pragma once


typedef struct pt {
	int state;
	float baseX, baseY;


}player_t;

int player_init( void );
int player_disp( void );
int player_finish( void );
int Get_interval( void );
player_t* getPlayerPtr( void );

