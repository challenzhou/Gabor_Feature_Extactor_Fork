#include "gaborfeature.h"
#include <iostream>

std::vector<cv::Mat> GaborFeature::getFeature(cv::Mat & inputImage)
{
	if (inputImage.channels() > 1)
	{
		cv::cvtColor(inputImage, inputImage, CV_BGR2GRAY);
	}

	int k = 1; 	
	int scaleSize = 4;
	int orientSize = 2;

	int R = inputImage.rows;
	int C = inputImage.cols;

	cv::Mat tar;
	std::vector<cv::Mat> G_img;

	inputImage.copyTo(tar);

	for (int v = 0; v < scaleSize; v++)
	{
		for (int u = 1; u <= orientSize; u++)
		{
			// Get gabor feature by convolving with Gabor wavelet
			cv::Mat GW = gWavelet.run(R, C, Kmax, f, u, v, Delt);
			cv::Mat chann[2], filterMat, Regabout;
      
      std::cout << "GW size:" << GW.size() << std::endl;

			cv::split(GW, chann);
			cv::copyMakeBorder(chann[0], filterMat, 0, 0, 0, 0, cv::BORDER_CONSTANT);
			cv::filter2D(tar, Regabout, -1, filterMat);
			G_img.push_back(Regabout);

		} // end of u-loop
	} // end of v-loop
	
	return G_img;

} // end of function definition
