#pragma once

#include "CommonDef.h"
#include <opencv\cv.hpp>

namespace Auto_Allign
{
	//class deals with basic image operations using OpenCV
	class ImageAligner
	{

	public:

		ImageAligner();
		~ImageAligner();

		bool TrnaslateImg(cv::Mat& img_i, cv::Point trans_i, BK_COLOR color_i, cv::Mat& img_o);
		bool RoateImg(cv::Mat& img_i, double angle_i, BK_COLOR color_i, cv::Mat& img_o);
	};

}

