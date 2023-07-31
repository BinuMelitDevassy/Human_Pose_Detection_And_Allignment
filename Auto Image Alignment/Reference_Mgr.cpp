#include "stdafx.h"
#include "Reference_Mgr.h"


namespace Auto_Allign
{
	Reference_Mgr::Reference_Mgr()
	{
	}


	Reference_Mgr::~Reference_Mgr()
	{
	}

	bool Reference_Mgr::InitReferenceImages()
	{
		//create list of reference images from folder structure
		//init all images
		//call process reference image

		mRefImg.InitFacePose(FACE_POS::FRONTAL);
		mRefImg.ProcessRefImage("ReferenceImages\\zoom1\\head_frontal.jpg");
		return true;
	}
}
