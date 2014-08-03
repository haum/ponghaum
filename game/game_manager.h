#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

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

/** Game persistent data **/
struct GameData {
	GamePlayer last_winner; /// Last winner player
	int p1score; /// Score of player 1
	int p2score; /// Score of player 2
};


/** Class that manages the game **/
class GameManager {
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

		/** Show scores **/
		void show_scores();

		/** HardwareTest screen **/
		void test_hardware();

		GameData data;

	private:
		GameState state; /// Current game phase
};

extern GameManager game;

#endif
