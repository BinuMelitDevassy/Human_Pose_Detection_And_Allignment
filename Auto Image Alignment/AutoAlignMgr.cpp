#include "stdafx.h"
#include "AutoAlignMgr.h"


namespace Auto_Allign
{
	AutoAlignMgr::AutoAlignMgr()
	{
	}


	AutoAlignMgr::~AutoAlignMgr()
	{
	}

	bool AutoAlignMgr::InitReferenceImages()
	{
		mRefMgr.InitReferenceImages();
		return true;
	}

	bool AutoAlignMgr::ProcessImage(std::string img_path)
	{
		//Reference_Detector mRefDetector;
		mAutoAlign.Allign(img_path, mRefMgr.GetRefImg());
		return true;
	}
}
