#include <stdio.h>
#include <math.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#define black  0
#define white  255

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

void test(void);

cv::Mat circle(cv::Mat Input, int range);
cv::Mat reduction(cv::Mat Input, cv::Mat limit);
cv::Mat Gray(cv::Mat Input);
cv::Mat fire(cv::Mat Input, cv::Mat limit);
cv::Mat FD(cv::Mat Input);
cv::Mat BS(cv::Mat Input);
cv::Mat BS(cv::Mat Input);
cv::Mat dilate(cv::Mat Input, int scope);
cv::Mat erode(cv::Mat Input, int scope);
cv::Mat binarization(cv::Mat Input, int norm);
cv::Mat GaussianFilter(cv::Mat Input);

void Gray2(cv::Mat& Input, cv::Mat& Output);
void dilate2(cv::Mat& Input, cv::Mat& Output, int scope);