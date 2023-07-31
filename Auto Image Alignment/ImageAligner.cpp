#include "stdafx.h"
#include "ImageAligner.h"


namespace Auto_Allign
{
	ImageAligner::ImageAligner()
	{
	}


	ImageAligner::~ImageAligner()
	{
	}

	bool ImageAligner::TrnaslateImg(cv::Mat& img_i, cv::Point trans_i, BK_COLOR color_i, cv::Mat& img_o)
	{
		cv::Scalar bk_color(255, 255, 255);

		if (color_i == BK_COLOR::BLACK)
		{
			bk_color = cv::Scalar(0, 0, 0);
		}

		cv::Mat trans_mat = (cv::Mat_<double>(2, 3) << 1, 0, trans_i.x, 0, 1, trans_i.y);
		cv::warpAffine( img_i, img_o, trans_mat, img_i.size(), 1, 0, bk_color );

		return true;
	}
	bool ImageAligner::RoateImg(cv::Mat& img_i, double angle_i, BK_COLOR color_i, cv::Mat& img_o)
	{
		cv::Scalar bk_color(255, 255, 255);

		if (color_i == BK_COLOR::BLACK)
		{
			bk_color = cv::Scalar(0, 0, 0);
		}

		double thetaRad = angle_i * CV_PI / 180;
		double nw = abs(sin(thetaRad))*img_i.rows + abs(cos(thetaRad))*img_i.cols;
		double nh = abs(cos(thetaRad))*img_i.rows + abs(sin(thetaRad))*img_i.cols;
		cv::Mat rot_mat = cv::getRotationMatrix2D(cv::Point2d(nw*.5, nh*.5), thetaRad * 180 / CV_PI, 1);
		cv::Mat pos = cv::Mat::zeros(cv::Size(1, 3), CV_64FC1);
		pos.at<double>(0) = (nw - img_i.cols)*.5;
		pos.at<double>(1) = (nh - img_i.rows)*.5;
		cv::Mat res = rot_mat * pos;
		rot_mat.at<double>(0, 2) += res.at<double>(0);
		rot_mat.at<double>(1, 2) += res.at<double>(1);
		cv::warpAffine(img_i, img_o, rot_mat, cv::Size((int)nw, (int)nh), cv::INTER_LANCZOS4, 0, bk_color);

		return true;
	}
}
