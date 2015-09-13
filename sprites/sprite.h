#ifndef SPRITE_H
#define SPRITE_H

#include "../khroma.h"

class Sprite {
	public:
		/** Simple constructor **/
		Sprite();

		/** Initialize sprite **/
		void init();

		/** Link to another sprite
		  * @param [in] l Sprite to link to
		  */
		void link_to(Sprite * linked_to);

		/** Revese coordinate system
		  * @param [in] active Reverse (true) or not (false)
		  */
		void reverse(bool active);

		/** Set position (in linked_to if any)
		  * @param [in] pos New position
		  */
		void set_position(float pos);

		/** Get position (in linked_to if any)
		  * @return Position
		  */
		float get_position();

		/** Get absolute position
		  * @return Position
		  */
		float get_abs_position();

		/** Get reverse property
		  * @return Reverse property
		  */
		bool get_reversed();

		/** Function to call for animation **/
		virtual void animate() = 0;

	protected:
		/* Draw led in relative coordinates
		  * @param [in] led Led number (relative)
		  * @param [in] r   Red intensity   [0-255]
		  * @param [in] g   Green intensity [0-255]
		  * @param [in] b   Blue intensity  [0-255]
		  */
		void draw(int led, unsigned char r, unsigned char g, unsigned char b);

	private:
		/** Function to call for initialization **/
		virtual void init_sprite() {}

		Sprite * linked_to; // Pointer to sprite it is linked to
		bool reversed; // Is coordinate system reversed ?
		float position; // Current position
};

#endif
