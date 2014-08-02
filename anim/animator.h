#ifndef ANIMATOR_H
#define ANIMATOR_H

class Animator {
	public:
		/** Simple constructor **/
		Animator();

		/** Set animation duration
		  * @param [in] ms Duration in milliseconds
		  */
		void set_duration(unsigned int ms);

		/** Activate loop mode or not
		  * @param [in] active Loop active (true) or not (false)
		  */
		void loop(bool active);

		/** Activate up/down mode or not
		  * @param [in] active Up/down mode active (true) or not (false)
		  */
		void updown(bool active);

		/** Start/restart animation from 0 **/
		void start();

		/** Stop/Pause animation **/
		void stop();

		/** Resume from pause **/
		void resume();

		/** Is animation running ?
		  * @return true if running
		  */
		bool running();

		/** Initialize function **/
		void init();

		/** Animate function **/
		void animate();

		/** Get current value
		  * @return Current value
		  */
		float get_value();

		operator float() { return get_value(); }

	private:
		/** Function to call for initialization **/
		virtual void init_animator() {}

		/** Transfert function of the animation
		  * @param [in] percent progression from 0 to 1
		  * @return Output, generally from 0 to 1 but not mandatory
		  */
		virtual float transfert(float percent) = 0;

		bool looped; /// Is animation looped ?
		bool upndown; /// Is animation up/down ?
		bool run; /// Is animation looped ?
		float delta; /// Delta percentage at each frame
		float percent; /// Current percentage
		float out; /// Current output
};

#endif
