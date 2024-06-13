
#include "mylib.h"
using namespace jgw;
void onMouse(int event, int x, int y, int flags, void* userdata);
int main(void) {
	Mat src(500, 500, CV_8UC3, Scalar(255, 255, 255));
	String function_text[] = { "Save", "Load", "Clear", "Run", "Exit", "Contours", "center_gravity", "center" };

	int array_size = sizeof(function_text) / sizeof(function_text[0]); //기능 개수
	src_resize(src, array_size);
	draw_line(src, array_size);
	putText_function(src, function_text, array_size);

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
	for (int w = INPUT_WINDOW; w < src.cols; w += FUNCT_WINDOW_W) {
		for (int h = 0; h < FUNCT_WINDOW_H * 5; h += FUNCT_WINDOW_H) { //기능 영역 분리(세로로 5개씩 자르기)
			Rect n = Rect(w, h, FUNCT_WINDOW_W, FUNCT_WINDOW_H);
			function_area.push_back(n);
		}
	}

	static Point old_pixel;
	switch (event) {
	case EVENT_LBUTTONDOWN:
		//line을 그리기위한 pixel value
		old_pixel = Point(x, y);
		break;

	case EVENT_LBUTTONUP:
		if (Point(x, y) == old_pixel) { //마우스 왼쪽 버튼을 누른 좌표와 땠을 때의 좌표가 일치했을 때
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
			//Contours
			else if (function_area[5].contains(old_pixel)) {
				int x = contours(src, num_input_area);

				cout << "결과 예상 값: ";
				if (x == 1)
					cout << "1, 2, 3, 4, 5, 7" << endl;
				else if (x == 2)
					cout << "0, 4, 6, 9" << endl;
				else if (x == 3)
					cout << "8" << endl;
				else cout << "다시 한 번 그려보시오" << endl;
				cout << "외곽선 개수: " << x << endl << endl;

			}
			//Center of gravity
			else if (function_area[6].contains(old_pixel))
				cout << "무게 중심: " << center_of_gravity(src, num_input_area) << endl << endl;
			//Center
			else if (function_area[7].contains(old_pixel))
				center(src, num_input_area);
		}
		break;

	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) { //왼쪽 마우스가 눌린 상태에서 움직이는지
			if (num_input_area.contains(Point(x, y)) && num_input_area.contains(old_pixel)) { //500x500 영역 안에 움직이는지
				line(src, old_pixel, Point(x, y), Scalar::all(0), 5); //검정색으로 그리기
				old_pixel = Point(x, y);
			}
		}
		break;

	default:
		break;
	}
}

double num_resize(Mat& src, Mat& dst, Rect& area) {
	cvtColor(src(area), dst, COLOR_BGR2GRAY);
	threshold(dst, dst, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	vector<vector<Point>> contours;
	findContours(dst, contours, RETR_LIST, CHAIN_APPROX_NONE); //외곽선 개수
	//외부 외곽선 정보
	if (contours.size() == 0)
		cerr << "탐색할 객체가 없음." << endl;
	int max_index = contours.size() - 1;
	Rect outside = boundingRect(contours[max_index]);

	resize(dst(outside), dst, Size(300, 300));
	//모폴로지 연산에 사용되는 반복횟수(iterations) 계산
	//그림의 비율을 이용하여 반복횟수 설정
	double iterations = 1;
	int i = 1;
	while (true) {
		if (outside.width < (dst.cols * i / 10) || outside.height < (dst.rows * i / 10))
			return iterations;
		iterations += 0.2;
		i++;
	}
}
