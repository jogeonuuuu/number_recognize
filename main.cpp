#include "mylib.h"
#define INPUT_WINDOW 500
#define LINE_EXCEPT 2
using namespace jgw;
void onMouse(int event, int x, int y, int flags, void* userdata);
int main(void) {
	Mat src(500, 500, CV_8UC3, Scalar(255, 255, 255));
	resize(src, src, Size(700, 500)); //��� ����� ��(��� �߰�)

	int thickness = 2; //�β�

	//���� ����
	rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 0, 0), thickness);
	line(src, Point(INPUT_WINDOW - 1, 0), Point(INPUT_WINDOW - 1, src.rows - 1), Scalar(0, 0, 0), thickness);
	for (int y = src.rows / 5; y < src.rows; y += src.rows / 5) //��� ���� �и�
		line(src, Point(INPUT_WINDOW, y), Point(src.cols - 1, y), Scalar(0, 0, 0), thickness);

	//��ɿ� ���� ���ڿ� �Է�â�� ����
	String function_text[] = {"Save", "Load", "Clear", "Run", "Exit"};
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1.0; //��Ʈ ũ�� Ȯ��/��� ����
	int old_height = 0;
	int current_height = 0;
	for (int i = 0; i < 5; i++) {
		Size sizeText = getTextSize(function_text[i], fontFace, fontScale, thickness, 0);
		Mat dst = src(Rect(INPUT_WINDOW, 0, src.cols - INPUT_WINDOW, src.rows)); //��� ����� ��(��� ��ü ����)
		old_height = dst.rows * i / 5;
		current_height = dst.rows * (i + 1) / 5 + old_height;
		Point org((dst.cols - sizeText.width) / 2, (current_height + sizeText.height) / 2);
		putText(dst, function_text[i], org, fontFace, fontScale, Scalar(0, 0, 0), thickness);
	}
	namedWindow("src");
	setMouseCallback("src", onMouse, &src);

	//jgw::ox; //static ������� ���� ��
	while (ox) {
		imshow("src", src);
		waitKey(1);
	}
	cout << "���α׷� ����" << endl;
	return 0;
}


void onMouse(int event, int x, int y, int flags, void* userdata) {
	Mat src = *(Mat*)userdata;
	
	Rect num_input_area = Rect(0, 0, INPUT_WINDOW, INPUT_WINDOW); //���� �Է�â ����
	Mat dst = src(Rect(INPUT_WINDOW, 0, src.cols - INPUT_WINDOW, src.rows));

	//Rect�� �ص� ������ ������? (Mat���� �����͸� �����ؾ��� ���� ���縦 ���� ������ ������ �� �ִ� �� �ƴ���) 
	//vector<Mat> function_area; //���(1)
	vector<Rect> function_area; //���(2) - �� ��ɵ��� ����
	//0: "Save", 1: "Load", 2: "Clear", 3: "Run", 4: "Exit"
	for (int i = 0; i < 5; i++) {
		//Mat x = dst(Rect(0, dst.rows * i / 5, dst.cols, dst.rows / 5)); //���(1)
		Rect x = Rect(INPUT_WINDOW, src.rows * i / 5, src.cols - INPUT_WINDOW, src.rows / 5); //���(2)
		function_area.push_back(x);
	}

	static Point old_pixel;
	switch (event) {
	case EVENT_LBUTTONDOWN:
		//line�� �׸������� pixel value
		old_pixel = Point(x, y);
		break;
	case EVENT_LBUTTONUP:
		if (Point(x, y) == old_pixel) {
			//Clear
			if (function_area[2].contains(old_pixel))
				clear_function(src, num_input_area);
			//Save
			else if (function_area[0].contains(old_pixel))
				save_function(src, num_input_area);
			//Load
			else if (function_area[1].contains(old_pixel))
				load_function(src, num_input_area);
			//Exit
			else if (function_area[4].contains(old_pixel))
				ox = false;
				//jgw::ox = false; //static ������� ���� ��
		}
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) { //���� ���콺�� ���� ���¿��� �����̴���
			//&& num_input_area.contains(old_pixel)
			if (num_input_area.contains(Point(x, y)) ) { //500x500 ���� �ȿ� �����̴���
				line(src, old_pixel, Point(x, y), Scalar::all(0), 5);
				old_pixel = Point(x, y);
			}
		}
		break;

	default:
		break;
	}
}