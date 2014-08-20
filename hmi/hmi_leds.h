#ifndef HMI_LEDS_H
#define HMI_LEDS_H

/** Leds interface **/
class HmiLeds {
	public:
		/** Init leds controller **/
		void init();

		/** Clears all leds **/
		void clear();

		/** Set a led color
		  * @param [in] led Led number
		  * @param [in] r   Red intensity   [0-255]
		  * @param [in] g   Green intensity [0-255]
		  * @param [in] b   Blue intensity  [0-255]
		  */
		void set(int led, unsigned char r, unsigned char g, unsigned char b);

		/** Update leds status **/
		void update();
};

#endif
