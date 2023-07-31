#pragma once

//Interface class to the DLL

#ifdef  EXPORT_Auto_Image_Alignment 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

namespace Auto_Allign
{
	class AutoAlignMgr;
}
class DLLEXPORT Auto_Image_Alignment
{
	//APIs Exposed
public:

	Auto_Image_Alignment();
	~Auto_Image_Alignment();
	bool InitReference();
	bool ProcessImage(const char* path);
	bool ShutDown();

private:

	Auto_Allign::AutoAlignMgr * mAuto = nullptr;
};


