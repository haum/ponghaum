#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

/** Game phases enumeration **/
enum GameState {
	GameState_SIMPLE_DEMO, /// Only a simple demo
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
