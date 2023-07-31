#pragma once

#include "PoseEstimator.h"
#include "CommonDef.h"
#include <opencv\cv.hpp>

namespace Auto_Allign
{
	class ReferenceImg
	{
	public:
		ReferenceImg();
		~ReferenceImg();
		bool InitFacePose( FACE_POS face_pos );
		bool ProcessRefImage(std::string img_path);
		double GetZAngle() { return mZAngle; };
		cv::Point GetNosPos() { return mNosePos; };
		PoseEstimator* GetPosEstimator() { return mPose_Estimator; };
		cv::Mat GetImg() { return mRefImg; };

	private:

		PoseEstimator* mPose_Estimator = nullptr;
		double mZAngle = 0.0;
		cv::Point mNosePos;
		cv::Mat mRefImg;

	};
}

