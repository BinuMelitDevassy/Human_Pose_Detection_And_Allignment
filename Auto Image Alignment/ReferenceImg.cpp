#include "stdafx.h"
#include "ReferenceImg.h"
#include "FrontalPoseEstimator.h"
#include "SidePoseEstimator.h"
#include "TiltedPoseEstimator.h"

namespace Auto_Allign
{
	ReferenceImg::ReferenceImg()
	{
	}


	ReferenceImg::~ReferenceImg()
	{
		if (mPose_Estimator != nullptr)
		{
			delete mPose_Estimator;
		}
	}

	bool ReferenceImg::InitFacePose(FACE_POS face_pos)
	{
		if (mPose_Estimator != nullptr)
		{
			delete mPose_Estimator;
		}
		switch (face_pos)
		{
		case FACE_POS::FRONTAL:
			mPose_Estimator = new FrontalPoseEstimator();
			break;
		case FACE_POS::TILTED:
			//mPose_Estimator = new TiltedPoseEstimator();
			break;
		case FACE_POS::SIDE:
			//mPose_Estimator = new SidePoseEstimator();
			break;
		default:
			mPose_Estimator = nullptr;
			break;
		}

		if (mPose_Estimator != nullptr)
		{
			mPose_Estimator->Init();
		}

		return true;
	}

	bool ReferenceImg::ProcessRefImage(std::string img_path)
	{
		cv::Mat img_i = cv::imread(img_path);
		if (mPose_Estimator != nullptr)
		{
			mNosePos = mPose_Estimator->GetNoseLoc( img_i);
			mZAngle = mPose_Estimator->GetZRotation(img_i);
		}

		mRefImg = img_i;
		return true;
	}
}
