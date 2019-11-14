// Makeup.cpp : Defines the entry point for the console application.
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "gaborfeature.h"

int main(int argc, char* argv[])
{
	cv::Mat image_src = cv::imread("women.png");
  cv::Mat image;
	cv::cvtColor(image_src, image, CV_BGR2GRAY);
  cv::imshow("orig", image);
	
	cv::Mat source;
	image.convertTo(source, CV_32F);

	// Get Gabor features
	GaborFeature gFeature;
	std::vector<cv::Mat> gaborFeatures = gFeature.getFeature(source);

	// Final feature vector  of the obtained Gabbor features
	std::vector<double> feature;

	for (int x = 0; x < gaborFeatures.size(); x++)
	{
		cv::Mat gaborMat = gaborFeatures[x];
		for (int y = 0; y < gaborMat.rows; y++)
		{
			const double* My = gaborMat.ptr<double>(y);
			for (int z = 0; z < gaborMat.cols; z++)
			{
				feature.push_back(My[z]);
			} // end of z-loop
		} // end of y-loop
    cv::imshow(std::to_string(x), gaborMat);
	} // end of x-loop

	std::cout << "feature size: " << feature.size() << std::endl;

	// Use the obtained Gabor feature for further steps based on your goal,
	// such as send it to classifier.
  while(true)
  {
    int key = cv::waitKey(10);
    if (key == ' ')
      break;
  }

	return 0;
}

