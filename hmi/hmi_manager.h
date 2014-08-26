#ifndef HMI_MANAGER_H
#define HMI_MANAGER_H

#define HMI_WIDTH 74 /// Number of leds of each side [-HMI_WIDTH:HMI_WIDTH]
#define HMI_DTMS 15 /// Delta time in milliseconds

class HmiManager;

#include "hmi_button.h"
#include "hmi_leds.h"
#include "hmi_alim.h"

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

		/** Send number to console
		  * @param [in] msg Number to send
		  */
		void log(int msg);

		HmiAlim alim; /// Alim
		HmiButton btn1; /// Button 1
		HmiButton btn2; /// Button 2
		HmiLeds leds; /// Leds

	private:
		long last_frame_time; /// Time of last frame
		long last_btn_time; /// Time of last button computation
		bool can_animate_flag; /// Flag indicating if we can animate
};

extern HmiManager hmi;

#endif
