#pragma once

#include "ReferenceImg.h"

namespace Auto_Allign
{
	class Reference_Mgr
	{
	public:
		Reference_Mgr();
		~Reference_Mgr();
		bool InitReferenceImages();
		ReferenceImg& GetRefImg() { return mRefImg; };

	private:
		//Will be replaced with map in future versions
		ReferenceImg mRefImg;
	};
}

