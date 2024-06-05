#include "mylib.h"
using namespace jgw;
void onMouse(int event, int x, int y, int flags, void* userdata);
int main(void) {
	Mat src(500, 900, CV_8UC3, Scalar(255, 255, 255));

	//영역 라인
	rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 0, 0), LINE_THICKNESS);
	line(src, Point(INPUT_WINDOW - 1, 0), Point(INPUT_WINDOW - 1, src.rows - 1), Scalar(0, 0, 0), LINE_THICKNESS);
	for (int y = src.rows / 5; y < src.rows; y += src.rows / 5) { //기능 영역 분리(세로로 5개씩 자르기)
		line(src, Point(INPUT_WINDOW, y), Point(src.cols - 1, y), Scalar(0, 0, 0), LINE_THICKNESS);

	}

	//기능에 대한 문자열 입력창에 삽입
	String function_text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	putText_function(src, function_text);

	namedWindow("src");
	setMouseCallback("src", onMouse, &src);

	while (true) {
		imshow("src", src);
		waitKey(1);
	}
	cout << "프로그램 종료" << endl;
	return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata) {
	Mat src = *(Mat*)userdata;

	//숫자 입력창 영역
	Rect num_input_area = Rect(LINE_THICKNESS, LINE_THICKNESS, INPUT_WINDOW - 2 * LINE_THICKNESS, INPUT_WINDOW - 2 * LINE_THICKNESS);

	vector<Rect> function_area; //각 기능들의 영역
	//[0]: "Save" // [1]: "Load" // [2]: "Clear" // [3]: "Run" // [4]: "Exit"
	//[5]: 
	for (int i = 0; i < 5; i++) {
		Rect x = Rect(INPUT_WINDOW, src.rows * i / 5, src.cols - INPUT_WINDOW, src.rows / 5);
		function_area.push_back(x);
	}
		
	static Point old_pixel;
	switch (event) {
	case EVENT_LBUTTONDOWN:
		//line을 그리기위한 pixel value
		old_pixel = Point(x, y);
		break;

	case EVENT_LBUTTONUP:
		if (Point(x, y) == old_pixel) {
			//Save
			if (function_area[0].contains(old_pixel))
				save_function(src, num_input_area);
			//Load
			else if (function_area[1].contains(old_pixel))
				load_function(src, num_input_area);
			//Clear
			else if (function_area[2].contains(old_pixel))
				clear_function(src, num_input_area);
			//Run
			else if (function_area[3].contains(old_pixel))
				run_function(src, num_input_area);
			//Exit
			else if (function_area[4].contains(old_pixel))
				exit(1);
		}
		break;

	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) { //왼쪽 마우스가 눌린 상태에서 움직이는지
			if (num_input_area.contains(Point(x, y)) && num_input_area.contains(old_pixel)) { //500x500 영역 안에 움직이는지
				line(src, old_pixel, Point(x, y), Scalar::all(0), 5);
				old_pixel = Point(x, y);
			}
		}
		break;

	default:
		break;
	}
}
