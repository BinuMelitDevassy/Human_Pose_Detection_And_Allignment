#pragma once

#include <opencv\cv.hpp>

namespace Auto_Allign
{
	class PoseEstimator
	{
	public:
		PoseEstimator();
		virtual ~PoseEstimator();
		virtual bool Init() = 0;
		virtual cv::Point GetNoseLoc(cv::Mat& img_i) = 0;
		virtual double GetZRotation(cv::Mat& img_i) = 0;
	};
}

