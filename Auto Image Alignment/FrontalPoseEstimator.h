#pragma once
#include "PoseEstimator.h"
#include "CommonDef.h"
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/cnn/cnn_face_detector.h>

namespace Auto_Allign
{
	class FrontalPoseEstimator : public PoseEstimator
	{
	public:
		FrontalPoseEstimator();
		~FrontalPoseEstimator();

		bool Init() override;
		cv::Point GetNoseLoc(cv::Mat& img_i) override;
		double GetZRotation(cv::Mat& img_i) override;

	private:

		dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
		//	cnn_face_detection_model_v1 cnndetector("mmod_human_face_detector.dat");

		dlib::shape_predictor predictor;

		//fill in cam intrinsics and distortion coefficients
		cv::Mat cam_matrix;
		cv::Mat dist_coeffs;

		//fill in 3D ref points(world coordinates), model referenced from http://aifi.isr.uc.pt/Downloads/OpenGL/glAnthropometric3DModel.cpp
		std::vector<cv::Point3d> object_pts;

		//2D ref points(image coordinates), referenced from detected facial feature
		std::vector<cv::Point2d> image_pts;

		//result
		cv::Mat rotation_vec;                           //3 x 1
		cv::Mat rotation_mat;                           //3 x 3 R
		cv::Mat translation_vec;                        //3 x 1 T
		cv::Mat pose_mat = cv::Mat(3, 4, CV_64FC1);     //3 x 4 R | T
		cv::Mat euler_angle = cv::Mat(3, 1, CV_64FC1);

		//reproject 3D points world coordinate axis to verify result pose
		std::vector<cv::Point3d> reprojectsrc;



		//reprojected 2D points
		std::vector<cv::Point2d> reprojectdst;


		//temp buf for decomposeProjectionMatrix()
		cv::Mat out_intrinsics = cv::Mat(3, 3, CV_64FC1);
		cv::Mat out_rotation = cv::Mat(3, 3, CV_64FC1);
		cv::Mat out_translation = cv::Mat(3, 1, CV_64FC1);

	};
}

