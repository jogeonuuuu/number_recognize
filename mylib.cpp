#include "mylib.h"
namespace jgw {
	//각 기능들 영역 라인 그리기 함수
	void draw_line(Mat& src, int array_size) {
		int quotient = array_size / 5; //몫
		int remainder = array_size % 5; //나머지
		Size function_window(200, src.rows / 5);

		//기능의 계수에 따라 src 사이즈 조정
		if (array_size <= 5)
			resize(src, src, Size(700, 500));
		else if(array_size <=10)
			resize(src, src, Size(900, 500));

		rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 0, 0), LINE_THICKNESS);
		for (int x = INPUT_WINDOW; x < src.cols; x += 200) {
			line(src, Point(x - 1, 0), Point(x - 1, src.rows - 1), Scalar(0, 0, 0), LINE_THICKNESS);
			for (int y = function_window.height - 1; y < function_window.height * remainder; y += function_window.height) //기능 영역 분리(세로로 5개씩 자르기)
				line(src, Point(x - 1, y), Point(x + 199, y), Scalar(0, 0, 0), LINE_THICKNESS);
		}
	}

	//기능에 대한 문자열 입력창에 삽입
	void putText_function(Mat& src, String* text) {
		int thickness = 2; //두께
		int fontFace = FONT_HERSHEY_SIMPLEX;
		double fontScale = 1.0; //폰트 크기 확대/축소 비율
		int old_height = 0;
		int current_height = 0;
		int array_size = sizeof(text) / sizeof(text[0]);
		cout << array_size << endl;
		for (int i = 0; i < array_size; i++) {
			Size sizeText = getTextSize(text[i], fontFace, fontScale, thickness, 0);
			Mat dst = src(Rect(INPUT_WINDOW, 0, src.cols - INPUT_WINDOW, src.rows)); //계속 변경될 값(기능 전체 영역)
			old_height = dst.rows * i / 5;
			current_height = dst.rows * (i + 1) / 5 + old_height;
			Point org((dst.cols - sizeText.width) / 2, (current_height + sizeText.height) / 2);
			putText(dst, text[i], org, fontFace, fontScale, Scalar(0, 0, 0), thickness);
		}
	}

	//Save
	void save_function(Mat& src, Rect& area) {
		String file_route = "C:\\Users\\jogeo\\source\\repos\\Open_cv\\Project_기말\\num_data\\";
		String file_name;
		cout << "<Save> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		Mat dst;
		resize(src(area), dst, Size(INPUT_WINDOW, INPUT_WINDOW));
		bool tf = imwrite(file_route + file_name, dst);
		if (tf) cout << file_name << "파일이 저장됨" << endl;
	}
	//Load
	void load_function(Mat& src, Rect& area) {
		String file_route = "C:\\Users\\jogeo\\source\\repos\\Open_cv\\Project_기말\\num_data\\";
		String file_name;
		cout << "<Load> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		Mat mRead = imread(file_route + file_name);
		if (mRead.empty()) {
			cout << "파일 불러오기 실패" << endl;
			return;
		}
		cout << file_name << "파일을 불러옴" << endl;
		mRead(area).copyTo(src(area));
	}
	//Clear
	void clear_function(Mat& src, Rect& area) {
		src(area) = Scalar(255, 255, 255);
		cout << "입력창 삭제됨" << endl;
	}
	//Run
	void run_function(Mat& src, Rect& area) {

	}
}
