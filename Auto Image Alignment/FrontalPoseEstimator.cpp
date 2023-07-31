#include "stdafx.h"
#include "FrontalPoseEstimator.h"

namespace Auto_Allign
{
	double K[9] = { 6.5308391993466671e+002, 0.0, 3.1950000000000000e+002, 0.0, 6.5308391993466671e+002, 2.3950000000000000e+002, 0.0, 0.0, 1.0 };
	double D[5] = { 7.0834633684407095e-002, 6.9140193737175351e-002, 0.0, 0.0, -1.3073460323689292e+000 };

	FrontalPoseEstimator::FrontalPoseEstimator()
	{
		cam_matrix = cv::Mat(3, 3, CV_64FC1, K);
		dist_coeffs = cv::Mat(5, 1, CV_64FC1, D);
	}


	FrontalPoseEstimator::~FrontalPoseEstimator()
	{
	}

	bool FrontalPoseEstimator::Init()
	{
		dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> predictor;
		object_pts.push_back(cv::Point3d(6.825897, 6.760612, 4.402142));     //#33 left brow left corner
		object_pts.push_back(cv::Point3d(1.330353, 7.122144, 6.903745));     //#29 left brow right corner
		object_pts.push_back(cv::Point3d(-1.330353, 7.122144, 6.903745));    //#34 right brow left corner
		object_pts.push_back(cv::Point3d(-6.825897, 6.760612, 4.402142));    //#38 right brow right corner
		object_pts.push_back(cv::Point3d(5.311432, 5.485328, 3.987654));     //#13 left eye left corner
		object_pts.push_back(cv::Point3d(1.789930, 5.393625, 4.413414));     //#17 left eye right corner
		object_pts.push_back(cv::Point3d(-1.789930, 5.393625, 4.413414));    //#25 right eye left corner
		object_pts.push_back(cv::Point3d(-5.311432, 5.485328, 3.987654));    //#21 right eye right corner
		object_pts.push_back(cv::Point3d(2.005628, 1.409845, 6.165652));     //#55 nose left corner
		object_pts.push_back(cv::Point3d(-2.005628, 1.409845, 6.165652));    //#49 nose right corner
		object_pts.push_back(cv::Point3d(2.774015, -2.080775, 5.048531));    //#43 mouth left corner
		object_pts.push_back(cv::Point3d(-2.774015, -2.080775, 5.048531));   //#39 mouth right corner
		object_pts.push_back(cv::Point3d(0.000000, -3.116408, 6.097667));    //#45 mouth central bottom corner
		object_pts.push_back(cv::Point3d(0.000000, -7.415691, 4.070434));    //#6 chin corner

		reprojectsrc.push_back(cv::Point3d(10.0, 10.0, 10.0));
		reprojectsrc.push_back(cv::Point3d(10.0, 10.0, -10.0));
		reprojectsrc.push_back(cv::Point3d(10.0, -10.0, -10.0));
		reprojectsrc.push_back(cv::Point3d(10.0, -10.0, 10.0));
		reprojectsrc.push_back(cv::Point3d(-10.0, 10.0, 10.0));
		reprojectsrc.push_back(cv::Point3d(-10.0, 10.0, -10.0));
		reprojectsrc.push_back(cv::Point3d(-10.0, -10.0, -10.0));
		reprojectsrc.push_back(cv::Point3d(-10.0, -10.0, 10.0));
		reprojectdst.resize(8);
		return true;
	}

	cv::Point FrontalPoseEstimator::GetNoseLoc(cv::Mat& img_i)
	{
		dlib::cv_image<dlib::bgr_pixel> cimg(img_i);

		// Detect faces
		std::vector<dlib::rectangle> faces = detector(cimg);
		//std::vector<dlib::mmod_rect> faces = cnndetector.detect(cimg,1);
		cv::Point cenfull(img_i.cols / 2, img_i.rows / 2);

		// Find the pose of each face
		if (faces.size() > 0)
		{
			//track features
			dlib::full_object_detection shape = predictor(cimg, faces[0]);

			//draw features
			/*for (unsigned int i = 31; i < 36; ++i)
			{
			cv::circle(temp, cv::Point(shape.part(i).x(), shape.part(i).y()), 2, cv::Scalar(0, 0, 255), -1);
			}*/

			cv::Point cen(shape.part(33).x(), shape.part(33).y());
			return cen;
		}

		return cenfull;

	}

	double FrontalPoseEstimator::GetZRotation(cv::Mat& img_i)
	{
		dlib::cv_image<dlib::bgr_pixel> cimg(img_i);

		// Detect faces
		std::vector<dlib::rectangle> faces = detector(cimg);
		//std::vector<dlib::mmod_rect> faces = cnndetector.detect(cimg,1);


		// Find the pose of each face
		if (faces.size() > 0)
		{
			//track features
			dlib::full_object_detection shape = predictor(cimg, faces[0]);

			//draw features
			/*	for (unsigned int i = 31; i < 36; ++i)
			{
			cv::circle(temp, cv::Point(shape.part(i).x(), shape.part(i).y()), 2, cv::Scalar(0, 0, 255), -1);
			}*/

			//fill in 2D ref points, annotations follow https://ibug.doc.ic.ac.uk/resources/300-W/
			image_pts.push_back(cv::Point2d(shape.part(17).x(), shape.part(17).y())); //#17 left brow left corner
			image_pts.push_back(cv::Point2d(shape.part(21).x(), shape.part(21).y())); //#21 left brow right corner
			image_pts.push_back(cv::Point2d(shape.part(22).x(), shape.part(22).y())); //#22 right brow left corner
			image_pts.push_back(cv::Point2d(shape.part(26).x(), shape.part(26).y())); //#26 right brow right corner
			image_pts.push_back(cv::Point2d(shape.part(36).x(), shape.part(36).y())); //#36 left eye left corner
			image_pts.push_back(cv::Point2d(shape.part(39).x(), shape.part(39).y())); //#39 left eye right corner
			image_pts.push_back(cv::Point2d(shape.part(42).x(), shape.part(42).y())); //#42 right eye left corner
			image_pts.push_back(cv::Point2d(shape.part(45).x(), shape.part(45).y())); //#45 right eye right corner
			image_pts.push_back(cv::Point2d(shape.part(31).x(), shape.part(31).y())); //#31 nose left corner
			image_pts.push_back(cv::Point2d(shape.part(35).x(), shape.part(35).y())); //#35 nose right corner
			image_pts.push_back(cv::Point2d(shape.part(48).x(), shape.part(48).y())); //#48 mouth left corner
			image_pts.push_back(cv::Point2d(shape.part(54).x(), shape.part(54).y())); //#54 mouth right corner
			image_pts.push_back(cv::Point2d(shape.part(57).x(), shape.part(57).y())); //#57 mouth central bottom corner
			image_pts.push_back(cv::Point2d(shape.part(8).x(), shape.part(8).y()));   //#8 chin corner

																					  //calc pose
			cv::solvePnP(object_pts, image_pts, cam_matrix, dist_coeffs, rotation_vec, translation_vec);

			//reproject
			cv::projectPoints(reprojectsrc, rotation_vec, translation_vec, cam_matrix, dist_coeffs, reprojectdst);

			//calc euler angle
			cv::Rodrigues(rotation_vec, rotation_mat);
			cv::hconcat(rotation_mat, translation_vec, pose_mat);
			cv::decomposeProjectionMatrix(pose_mat, out_intrinsics, out_rotation, out_translation, cv::noArray(), cv::noArray(), cv::noArray(), euler_angle);

			image_pts.clear();
		}

		return euler_angle.at<double>(2);
	}
}
