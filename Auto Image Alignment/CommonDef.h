#pragma once

namespace Auto_Allign
{
	enum class BK_COLOR
	{
		BLACK,
		WHITE
	};

	enum class FACE_POS
	{
		FRONTAL,
		TILTED,
		SIDE
	};

	//Intrisics can be calculated using opencv sample code under opencv/sources/samples/cpp/tutorial_code/calib3d
	//Normally, you can also apprximate fx and fy by image width, cx by half image width, cy by half image height instead
}
