#ifndef HMI_ALIM_H
#define HMI_ALIM_H

/** Alim interface **/
class HmiAlim {
	public:
		/** Init alim controller **/
		void init();

		/** Power alim on **/
		void poweron();

		/** Power alim off **/
		void poweroff();
};

#endif
