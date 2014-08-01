#ifndef HMI_MANAGER_H
#define HMI_MANAGER_H

#define HMI_NB_LEDS 150 /// Number of leds of the interface
#define HMI_DTMS 15 /// Delta time in milliseconds

class HmiManager;

/** Button interface **/
class HmiButton {
	public:
		/** Initialize button **/
		void init();

		/** Is button pressed currently ? 
		  * @return true when button is pressed, false otherwise
		  */
		bool pressed();

		/** Was button clicked recently ?
		  * @note Is true only one animate frame after the click
		  * @note Is false if double-click occured
		  * @return true when button is clicked, false otherwise
		  */
		bool clicked();

	private:
		/** Compute button state
		  * @param [in] value Present value
		  */
		void compute(bool value);

		bool is_pressed; /// Is button currently pressed ?
		bool is_clicked; /// Is button clicked ?
		bool is_clickedWait; /// Should buttun release be waited

	friend class HmiManager;
};

/** Leds interface **/
class HmiLeds {
	public:
		/** Clears all leds **/
		void clear();

		/** Set a led color
		  * @param [in] led Led number
		  * @param [in] r   Red intensity   [0-255]
		  * @param [in] g   Green intensity [0-255]
		  * @param [in] b   Blue intensity  [0-255]
		  */
		void set(int led, unsigned char r, unsigned char g, unsigned char b);
};

/** Interface to real world **/
class HmiManager {
	public:
		/** Initialize the class **/
		void init();

		/** Is it the right time to animate output ?
		  * @return true if animaton should be updated, false otherwise
		  */
		bool can_animate();

		/** Update inputs and outputs
		  * Should be called frequently
		  */
		void loop_step();

		/** Send message to console
		  * @param [in] msg Null-terminated c-string to send
		  */
		void log(const char *msg);

		HmiButton btn1; /// Button 1
		HmiButton btn2; /// Button 2
		HmiLeds leds; /// Leds

	private:
		long last_frame_time; /// Time of last frame
		bool can_animate_flag; /// Flag indicating if we can animate
};

extern HmiManager hmi;

#endif
