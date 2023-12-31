// Auto Image Alignment.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "AutoImageAlignment.h"
#include "AutoAlignMgr.h"

using namespace Auto_Allign;

Auto_Image_Alignment::Auto_Image_Alignment()
{
	mAuto = new Auto_Allign::AutoAlignMgr();
}
Auto_Image_Alignment::~Auto_Image_Alignment()
{
	delete mAuto;
}

bool Auto_Image_Alignment::InitReference()
{
	mAuto->InitReferenceImages();
	return true;
}
bool Auto_Image_Alignment::ProcessImage(const char* path)
{
	mAuto->ProcessImage(path);
	return true;
}
bool Auto_Image_Alignment::ShutDown()
{
	return true;
}


