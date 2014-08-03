#ifndef HMI_BUTTON_H
#define HMI_BUTTON_H

class HmiManager; // Forward declaration

/** Button interface **/
class HmiButton {
	public:
		/** Initialize button **/
		void init();

		/** Is button released ?
		  * @return Released status
		  */
		bool released();

		/** Has button be single clicked ? (brief touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @return Status of this click kind
		  */
		bool sclicked();

		/** Has button be single pressed ? (not so brief touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool spressed(bool still = false);

		/** Has button be single touched ? (bief or not so brief touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool stouched(bool still = false);

		/** Has button be single long pressed ? (long touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @note Pressed event is fired before
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool slpressed(bool still = false);

		/** Has button be double clicked ? (two brief touches)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @return Status of this click kind
		  */
		bool dclicked();

		/** Has button be double pressed ? (brief touch + not so brief touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool dpressed(bool still = false);

		/** Has button be double touched ? (bief touch + brief or not so brief touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool dtouched(bool still = false);

		/** Has button be double long pressed ? (brief touch + long touch)
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @note Pressed event is fired before
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool dlpressed(bool still = false);

		/** Has button be touched or double touched ?
		  * @note Is true only one animate frame after the click
		  * @note Is false if another kind of click occured
		  * @param [in] still Return true if still pressed
		  * @return Status of this click kind
		  */
		bool touched(bool still = false);

	private:
		/** Indicate end of frame to reset output **/
		void endframe();

		/** Compute button state
		  * @param [in] value Present value
		  */
		void compute(bool value);

		enum HmiButtonState {
			HmiButtonState_NOTHING,
			HmiButtonState_HT1,
			HmiButtonState_HB1,
			HmiButtonState_HT2,
			HmiButtonState_HB2,
			HmiButtonState_FT1,
			HmiButtonState_FT2,
			HmiButtonState_WT1,
			HmiButtonState_WT2,
		};

		enum HmiButtonPress {
			HmiButtonPress_NOTHING,
			HmiButtonPress_CLICKED1,
			HmiButtonPress_PRESSED1,
			HmiButtonPress_LONGPRESSED1,
			HmiButtonPress_CLICKED2,
			HmiButtonPress_PRESSED2,
			HmiButtonPress_LONGPRESSED2,
		};

		HmiButtonState state;
		HmiButtonPress press;
		int timer;

	friend class HmiManager;
};

#endif
