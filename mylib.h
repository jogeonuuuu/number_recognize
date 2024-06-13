#ifndef __MYLIB_H__
#define __MYLIB_H__
#define INPUT_WINDOW 500
#define FUNCT_WINDOW_W 200
#define FUNCT_WINDOW_H 100
#define LINE_THICKNESS 2
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
namespace jgw {
	//기능 개수에 따른 src 사이즈 조정
	void src_resize(Mat& src, int array_size);

	//라인 그리기 함수
	void draw_line(Mat& src, int array_size = 0);

	//기능에 대한 문자열 입력창에 삽입
	void putText_function(Mat& src, String* text, int array_size);

	//function(각 기능들의 대한 함수)
	void save_function(Mat& src, Rect& area);
	void load_function(Mat& src, Rect& area);
	void clear_function(Mat& src, Rect& area);

	int contours(Mat& src, Rect& area);
	Point center_of_gravity(Mat& dst, Rect& area);
	void center(Mat& src, Rect& area);
	void run_function(Mat& src, Rect& area);
}
#endif // !__MYLIB_H__
