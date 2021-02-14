#include "DxLib.h"
#include "main.h"
#include "game.h"
#include "mode.h"
#include "input.h"
#include "frame.h"
#include "block.h"
#include "block2.h"
#include "block3.h"
#include "player.h"
#include "bullet.h"
#include "time.h"
#include "collision.h"
#include "score.h"
#include "level.h"

unsigned int Cr = GetColor( 160, 255, 255 );
static int gameTime;
int level;
static int game;
int bd;
int tam = 0;
static float fall = 0;
int timer = 0;
int font_ga;


int Game_Init(void ) {
	gameTime = clock( );
	fall = 0;
	tam = 0;
	bd = 0;
	game = block01;
	font_ga = CreateFontToHandle( NULL, 40, 3 );

	LevelInit( );
	score_init( );
	player_init( );
	Block_make( );
	Font_Init( );
	FrameFont_Init( );
	//bullet_init( );
	return modeseq_Increase;
}

int Game_disp( void ) {
	int player_state;
	int block_state;
	clock_t elaps = ( clock( ) - gameTime ) / CLOCKS_PER_SEC;

	level = getLevelPtr();
	frame_make();
	endvar_make( );

	player_state = player_disp( );
	bullet_update( );

	timer++;

	switch ( game ) {
	case block01:
		bd = Block_draw( fall );
		break;
	case block02:
		bd = Block2_draw( fall );
		break;
	case block03:
		bd = Block3_draw( fall );
		break;
	}
	if ( elaps % 2 == 0&&elaps!=0 )
		fall += 0.5;
	DrawLevel( level + 1 );
	score_update( );

	int ed = endvar_over( fall, game );
	collisionDetect( fall, game );

	if ( ed < 0 ) {
		setStageCrea( game );
		return modeseq_Increase;
	}
	if ( bd < 0 ) {
		game++;
		fall = 0;
		bd = 0;
		if ( game == block02 ) {
			bullet_finish( );
			Block2_make( );
		}
		if ( game == block03 ) {
			bullet_finish( );
			Block3_make( );
		}
		if ( game == blockEnd ) {

			int valid_time = 500;
			int rate = 1;
			int add = ( ( valid_time * 60 ) - timer ) * rate;
			if ( add > 0 ) {
				score_add( add );
			}

			setStageCrea( game );
			return modeseq_Increase;
		}
	}

	tam++;
	if ((tam & 20) < 1)
	{
		DrawFormatString(ScreenWidth - 300, 30,
			GetColor(255, 255, 255),
			(const TCHAR*)"PRESS ESC KEY TO EXIT");
	}
	if (getKeyboardOnTrigger(KEY_INPUT_ESCAPE))
	{
		return modeseq_Exit;
	}

	if ( player_state > 0 ) {
		return modeseq_Increase;
	}
	Description_Disp( );


	double sec = timer / 60.0;
	int s = ( int )sec;
	int d = ( int )( ( sec - ( int )sec ) * 100 );
	DrawFormatStringToHandle( FrameWidth + 70, 300, GetColor( 255, 255, 255 ),font_ga, "TIME %02d:%02d", s, d );


	return 0;

	//return modeseq_Increase;
}

int Game_finish(void) {

	bullet_finish( );
	player_finish( );
	return modeseq_Increase;
}