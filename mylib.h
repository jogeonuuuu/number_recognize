#ifndef __MYLIB_H__
#define __MYLIB_H__
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
namespace jgw {
	//static bool ox = true;
	extern bool ox;

	//function
	void clear_function(Mat& src, Rect& area);
	void save_function(Mat& src, Rect& area);
	void load_function(Mat& src, Rect& area);
}
#endif // !__MYLIB_H__
