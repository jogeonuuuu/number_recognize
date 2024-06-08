#ifndef __MYLIB_H__
#define __MYLIB_H__
#define INPUT_WINDOW 500
#define LINE_THICKNESS 2
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
namespace jgw {
	//각 기능들 영역 라인 그리기 함수
	void draw_line(Mat& src, int str_size = 0);
	//기능에 대한 문자열 입력창에 삽입
	void putText_function(Mat& src, String* text);

	//function(각 기능들의 대한 함수)
	void save_function(Mat& src, Rect& area);
	void load_function(Mat& src, Rect& area);
	void clear_function(Mat& src, Rect& area);
	void run_function(Mat& src, Rect& area);
}
#endif // !__MYLIB_H__
