#pragma once
#include "ReferenceImg.h"
#include "ImageAligner.h"
namespace Auto_Allign
{
	class AutoAlignController
	{
	public:
		AutoAlignController();
		~AutoAlignController();
		bool Allign(std::string img_path, ReferenceImg& ref_img );

	private:
		ImageAligner allign;
	};
}

