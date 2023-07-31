#include "stdafx.h"
#include "AutoAlignController.h"


namespace Auto_Allign
{
	AutoAlignController::AutoAlignController()
	{
	}


	AutoAlignController::~AutoAlignController()
	{
	}

	bool AutoAlignController::Allign(std::string img_path, ReferenceImg& ref_img)
	{
		cv::Mat img = cv::imread(img_path);

		//correcting translation
		cv::Point nos_cur = ref_img.GetPosEstimator()->GetNoseLoc(img);
		cv::Point nos_diff = ref_img.GetNosPos() - nos_cur;

		//ref img dim is not equal to cur img
		cv::Size sCur = img.size();
		cv::Size sRef = ref_img.GetImg().size();
		if (sCur != sRef)
		{
			nos_diff.x -= (sRef.width - sCur.width ) / 2;
			nos_diff.y -= (sRef.height - sCur.height) / 2;
		}


		cv::Mat img_out;
		if ((nos_diff.x > 2) || (nos_diff.y > 2))
		{
			allign.TrnaslateImg(img, nos_diff, BK_COLOR::BLACK, img_out);
		}
		else
		{
			img_out = img;
		}

		//correcting skew
		double z_cur = ref_img.GetPosEstimator()->GetZRotation(img);
		double z_diff = z_cur - ref_img.GetZAngle();
		cv::Mat img_out_final;

		if (abs(z_diff) > 1.5)
		{
			allign.RoateImg(img, z_diff, BK_COLOR::BLACK, img_out_final);
		}
		else
		{
			img_out_final = img_out;
		}
		cv::imwrite("Processed.jpg", img_out_final);
		return true;
	}
}
