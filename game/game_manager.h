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

/** Class that manages the game **/
class GameManager {
	public:
		/** Constructor **/
		GameManager();

		/** Initialize game **/
		void init();

		/** Animate outputs and treat inputs **/
		void animate();

	private:
		GameState state; /// Current game phase
};

extern GameManager game;

#endif
