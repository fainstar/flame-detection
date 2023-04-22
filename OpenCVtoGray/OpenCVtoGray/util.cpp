#include "util.h"


//測試
void test(void){
	printf("test\n");
}

/*框選(I - 1通道 O - 3通道)*/
cv::Mat circle(cv::Mat Input, int range) {
	int x, y, Max_x = 0, Min_x = 10000, Max_y = 0, Min_y = 10000;
	int Rows = Input.rows;
	int	Cols = Input.cols;
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC3);
	uchar* data_I = Input.data;
	uchar* data_O = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			if (data_I[0] == white) {
				if (x < Min_x) Min_x = x;
				if (x > Max_x) Max_x = x;
				if (y < Min_y) Min_y = y;
				if (y > Max_y) Max_y = y;
			}
			data_I += 1;
		}
	}
	data_I = Input.data;
	data_O = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			if ((x < Min_x && x > Min_x - range || x > Max_x && x < Max_x + range) && y > Min_y - range && y < Max_y + range) {
				data_O[0] = 0;
				data_O[1] = 0;
				data_O[2] = 255;
			}
			else
				if ((y < Min_y && y > Min_y - range || y > Max_y && y < Max_y + range) && x >= Min_x && x <= Max_x) {
					data_O[0] = 0;
					data_O[1] = 0;
					data_O[2] = 255;
				}
				else {
					if (data_I[0] == black) {
						data_O[0] = 0;
						data_O[1] = 0;
						data_O[2] = 0;
					}
					else {
						data_O[0] = 255;
						data_O[1] = 255;
						data_O[2] = 255;
					}
				}
			data_I += 1;
			data_O += 3;
		}
	}
	Output = Output.clone();
	return Output;
}

//還原
cv::Mat reduction(cv::Mat Input, cv::Mat limit) {
	int x, y;
	int Rows = Input.rows;
	int	Cols = Input.cols;
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC3);
	uchar* data_I = Input.data;
	uchar* data_O = Output.data;
	uchar* data_T = limit.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			if (data_T[0] == white) {
				data_O[0] = data_I[0];
				data_O[1] = data_I[1];
				data_O[2] = data_I[2];
			}else {
				data_O[0] = black;
				data_O[1] = black;
				data_O[2] = black;
			}
			data_I += 3;
			data_O += 3;
			data_T += 1;
		}
	}
	Output = Output.clone();
	return Output;
}

//灰階
cv::Mat Gray(cv::Mat Input) {
	if (Input.channels() == 1) return Input;
	int pixel, x, y;
	int Rows = Input.rows;
	int	Cols = Input.cols;
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC1);
	uchar* data_I = Input.data;
	uchar* data_O = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			pixel = 0.114 * data_I[0] + 0.587 * data_I[1] + 0.299 * data_I[2];
			data_O[0] = pixel;
			data_I += 3;
			data_O += 1;
		}
	}
	Output = Output.clone();
	return Output;
}

//火焰(I - 3通道 O - 3通道)*/
cv::Mat fire(cv::Mat Input,cv::Mat limit) {
	int x, y, Rows, Cols;
	float H, S, I, R, G, B, delta, cmax, cmin, RT, ST, IT;
	RT = 150.0;
	ST = 80.0;
	IT = 210.0;
	Rows = Input.rows;
	Cols = Input.cols;
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC3);
	uchar* T1_data = Input.data;
	uchar* T2_data = limit.data;
	uchar* O1_data = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			/*移動物*/
			if (T2_data[0] == black) {
				O1_data[0] = black;
				O1_data[1] = black;
				O1_data[2] = black;
				T2_data += 3;
				T1_data += 3;
				O1_data += 3;
				continue;
			}
			/*RGB TO HSI -----------*/
			B = T1_data[0] / 255.0;
			G = T1_data[1] / 255.0;
			R = T1_data[2] / 255.0;
			cmin = fmin(fmin(R, G), B);
			cmax = fmax(fmax(R, G), B);
			delta = cmax - cmin;
			if (delta == 0) H = 0;
			else if (cmax == R) H = 60 * fmod((G - B) / delta, 6);
			else if (cmax == G) H = 60 * ((B - R) / delta + 2);
			else H = 60 * ((R - G) / delta + 4);
			if (H < 0) H += 360;
			if (cmax == 0) S = 0;
			S = delta / cmax;
			I = (R + G + B) / 3.0;
			/*LOGIC --------------*/
			bool a, b, c, d,flag=0;
			a = (R > (RT / 255.0)) ? 1 : 0;
			b = (R >= G && G > B) ? 1 : 0;
			c = (S >= (1.0 - R) * ST / RT) ? 1 : 0;
			d = (I > IT) ? 1 : 0;
			if      (I > 0.3 && a && b && c) flag = 1;
			else if (I > 0.2 && a && b && c || d) flag = 1;
			if (flag) {
				O1_data[0] = T1_data[0];
				O1_data[1] = T1_data[1];
				O1_data[2] = T1_data[2];
			}else {
				O1_data[0] = black;
				O1_data[1] = black;
				O1_data[2] = black;
			}
			/*----------------------*/
			T2_data += 3;
			T1_data += 3;
			O1_data += 3;
		}
	}
	Output = Output.clone();
	return Output;
}

//相鄰相減法
cv::Mat FD(cv::Mat Input) {
	int pixel, x, y;
	int Rows = Input.rows;
	int Cols = Input.cols;
	static cv::Mat Temp = cv::Mat(Rows, Cols, CV_8UC1);
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC1);
	uchar* T1_data = Input.data;
	uchar* T2_data = Temp.data;
	uchar* O1_data = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			pixel = abs(T2_data[0] - T1_data[0]);
			O1_data[0] = pixel;
			T1_data += 1;
			T2_data += 1;
			O1_data += 1;
		}
	}
	Temp = Input.clone();
	Output = Output.clone();
	return Output;
}

//背景相減法
cv::Mat BS(cv::Mat Input) {
	int pixel, x, y;
	int Rows = Input.rows;
	int Cols = Input.cols;
	static cv::Mat Temp = Input.clone();
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC1);
	uchar* T1_data = Input.data;
	uchar* T2_data = Temp.data;
	uchar* O1_data = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			int pixel = abs(T2_data[0] - T1_data[0]);
			O1_data[0] = pixel;
			T1_data += 1;
			T2_data += 1;
			O1_data += 1;
		}
	}
	Output = Output.clone();
	return Output;
}

/*膨脹(I-1通道 O-1通道)*/
cv::Mat dilate(cv::Mat Input, int scope) {
	int blank = (scope - 1) / 2;
	int Rows = Input.rows;
	int Cols = Input.cols;
	cv::Mat Output = cv::Mat::zeros(Input.size(), Input.type());
	for (int x = 1; x < Cols - 1; x++) {
		for (int y = 1; y < Rows - 1; y++) {
			uchar pixel = *(Input.data + y * Input.step + x);
			*(Output.data + y * Output.step + x) = pixel;
			if (pixel == 0) { //如果输入像素是黑色
				for (int i = x - blank; i <= x + blank; i++) {//檢查九宮格
					for (int j = y - blank; j <= y + blank; j++) {
						if (i > blank && j > blank && i < (Cols - blank) && j < (Rows - blank)) {//避開邊緣
							uchar neighbor_pixel = *(Input.data + j * Input.step + i);
							if (neighbor_pixel == 255) { //如果附近像素是白色
								*(Output.data + y * Output.step + x) = 255;
								break;
							}
						}
					}
				}
			}
		}
	}
	return Output;
}

/*侵蝕(I-1通道 O-1通道)*/
cv::Mat erode(cv::Mat Input, int scope) {
	int blank = (scope - 1) / 2;
	int Rows = Input.rows;
	int Cols = Input.cols;
	cv::Mat Output = cv::Mat::zeros(Input.size(), Input.type());
	for (int x = 1; x < Cols - 1; x++) {
		for (int y = 1; y < Rows - 1; y++) {
			uchar pixel = *(Input.data + y * Input.step + x);
			*(Output.data + y * Output.step + x) = pixel;
			if (pixel == 255) { //如果输入像素是白色
				for (int i = x - blank; i <= x + blank; i++) {//檢查九宮格
					for (int j = y - blank; j <= y + blank; j++) {
						if (i > blank && j > blank && i < (Cols - blank) && j < (Rows - blank)) {//避開邊緣
							uchar neighbor_pixel = *(Input.data + j * Input.step + i);
							if (neighbor_pixel == 0) { //如果附近像素是黑色
								*(Output.data + y * Output.step + x) = 0;
								break;
							}
						}
					}
				}
			}
		}
	}
	return Output;
}

//二值化(I-1通道 O-1通道)
cv::Mat binarization(cv::Mat Input, int norm) {
	int x, y;
	int Rows = Input.rows;
	int	Cols = Input.cols;
	cv::Mat Output = cv::Mat(Rows, Cols, CV_8UC1);
	uchar* data_I = Input.data;
	uchar* data_O = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			if (data_I[0] > norm) data_O[0] = white;
			else data_O[0] = black;
			data_I += 1;
			data_O += 1;
		}
	}
	Output = Output.clone();
	return Output;
}

//高斯濾波(I-1通道 O-1通道)
cv::Mat GaussianFilter(cv::Mat Input) {
	float kernel[3][3] = { 
		{1, 2, 1},				   
		{2, 4, 2},		   
		{1, 2, 1} 
	};
	float sum = 16.0; 
	int Rows = Input.rows;
	int Cols = Input.cols;
	int border = 1;
	cv::Mat output(Input.size(), Input.type());
	for (int i = border; i < Rows - border; i++) {
		for (int j = border; j < Cols - border; j++) {
			float sum2 = 0.0;
			for (int u = -border; u <= border; u++) {
				for (int v = -border; v <= border; v++) {
					int ii = i + u;
					int jj = j + v;
					float w = kernel[u + border][v + border];
					sum2 += w * Input.at<uchar>(ii, jj);
				}
			}
			output.at<uchar>(i, j) = sum2 / sum;
		}
	}
	return output;
}

//灰階２
void Gray2(cv::Mat& Input, cv::Mat& Output) {
	if (Input.channels() == 1) {
		Input.copyTo(Output);
		return;
	}
	int pixel, x, y;
	int Rows = Input.rows;
	int Cols = Input.cols;
	Output = cv::Mat(Rows, Cols, CV_8UC1);
	uchar* data_I = Input.data;
	uchar* data_O = Output.data;
	for (y = 0; y < Rows; y++) {
		for (x = 0; x < Cols; x++) {
			pixel = 0.114 * data_I[0] + 0.587 * data_I[1] + 0.299 * data_I[2];
			data_O[0] = pixel;
			data_I += 3;
			data_O += 1;
		}
	}
}

//膨脹２
void dilate2(cv::Mat& Input, cv::Mat& Output, int scope) {
	int blank = (scope - 1) / 2;
	int Rows = Input.rows;
	int Cols = Input.cols;
	Output = cv::Mat::zeros(Input.size(), Input.type());
	for (int x = 1; x < Cols - 1; x++) {
		for (int y = 1; y < Rows - 1; y++) {
			uchar pixel = *(Input.data + y * Input.step + x);
			*(Output.data + y * Output.step + x) = pixel;
			if (pixel == 0) { //如果输入像素是黑色
				for (int i = x - blank; i <= x + blank; i++) {//檢查九宮格
					for (int j = y - blank; j <= y + blank; j++) {
						if (i > blank && j > blank && i < (Cols - blank) && j < (Rows - blank)) {//避開邊緣
							uchar neighbor_pixel = *(Input.data + j * Input.step + i);
							if (neighbor_pixel == 255) { //如果附近像素是白色
								*(Output.data + y * Output.step + x) = 255;
								break;
							}
						}
					}
				}
			}
		}
	}
}

