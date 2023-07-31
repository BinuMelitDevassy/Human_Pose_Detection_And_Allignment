#pragma once

#include "Reference_Mgr.h"
#include "Reference_Detector.h"
#include "AutoAlignController.h"
#include <string>

namespace Auto_Allign
{
	// Controller of DLL
	class AutoAlignMgr
	{
	public:

		AutoAlignMgr();
		~AutoAlignMgr();
		bool InitReferenceImages();
		bool ProcessImage(std::string img_path);
		//bool Shutdown();

	private:

		Reference_Mgr mRefMgr;
		Reference_Detector mRefDetector;
		AutoAlignController mAutoAlign;
	};
}

