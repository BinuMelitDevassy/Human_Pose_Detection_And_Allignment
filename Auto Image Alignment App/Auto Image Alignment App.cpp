// Auto Image Alignment App.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoImageAlignment.h"
#include <iostream>

using namespace std;

int main()
{
    
	Auto_Image_Alignment auto_allign;
	auto_allign.InitReference();
	auto_allign.ProcessImage("test.jpg");
	cout << "finished processing" << endl;
	return 0;
}

