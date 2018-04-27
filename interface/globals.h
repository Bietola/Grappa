#pragma once

namespace gr {

///enumerations
//universal orientation concept
enum class Orientation {
	Horizontal,
	Vertical
};
//possible button click states
enum CLICKSTATUS{
	CLICKST_DEFAULT,	//fallback for when other click states are not defined
	CLICKST_OUTSIDE,    //mouse outside bounds
	CLICKST_HOVERING,   //mouse inside bounds
	CLICKST_CLICKING,   //mouse inside bounds and clicking
	CLICKST_MAX
};

}
