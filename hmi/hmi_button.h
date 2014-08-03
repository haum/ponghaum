#ifndef HMI_BUTTON_H
#define HMI_BUTTON_H

class HmiManager; // Forward declaration

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

#endif
