#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#define MAX_POINTS 5

#include "../khroma.h"

/** Game phases enumeration **/
enum GameState {
	GameState_WAIT_PLAYERS, // Wait for players
	GameState_PLAY, // Actual game
	GameState_SCORE_DISPLAY, // Display score
};

/** Generic game screen **/
class GameScreen {
	public:
		virtual void init() {}
		virtual void animate() = 0;
};

/** Players enumeraction **/
enum GamePlayer {
	PLAYER1,
	PLAYER2
};

/** Game Modes Enumeration **/

enum GameMode {
	NORMAL,
	CONQUER
};

/** Game persistent data **/
struct GameData {
	GamePlayer last_winner; /// Last winner player
	int p1score; /// Score of player 1
	int p2score; /// Score of player 2
	int old_p1score; /// Old score of player 1
	int old_p2score; /// Old score of player 2
};


/** Class that manages the game **/
class GameManager {
	private:
		/** Power-on detector helper **/
		bool was_powered;
		/** Player 1 attack ready **/
		bool attack1;
		/** Player 2 attack ready **/
		bool attack2;

	public:
		/** Constructor **/
		GameManager();

		/** Initialize game **/
		void init();

		/** Animate outputs and treat inputs **/
		void animate();

		/** Restart a game **/
		void restart_game();

		/** Play again **/
		void play();

		/** Launch init screen **/
		void initscreen();

		/** Launch rainbow screen **/
		void rainbow();

		/** Show scores **/
		void show_scores();

		/** HardwareTest screen **/
		void test_hardware();

		/** Check if attacks are ready **/
		bool check_attack1();
		bool check_attack2();

		/** Set attacks not ready **/
		void attack1_used();
		void attack2_used();

		GameData data;
		GameMode mode;

	private:
		GameState state; /// Current game phase
		LinearAnimator sleeptimer; /// Autoshutdown timer
};

extern GameManager game;

#endif
