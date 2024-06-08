#include "mylib.h"
namespace jgw {
	//기능 개수에 따른 src 사이즈 조정 함수
	void src_resize(Mat& src, int array_size) {
		int count = 1;
		while (true) {
			if (array_size <= count * 5) {
				resize(src, src, Size(INPUT_WINDOW + FUNCT_WINDOW_W * count, 500));
				break;
			}
			count++;
		}
	}

	//각 기능들 영역 라인 그리기 함수
	void draw_line(Mat& src, int array_size) {
		rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 0, 0), LINE_THICKNESS);
		for (int x = INPUT_WINDOW - 1; x < src.cols; x += FUNCT_WINDOW_W) {
			line(src, Point(x, 0), Point(x, src.rows - 1), Scalar(0, 0, 0), LINE_THICKNESS);            //세로줄
			for (int y = FUNCT_WINDOW_H - 1; y < FUNCT_WINDOW_H * array_size; y += FUNCT_WINDOW_H)      //기능 영역 분리(세로로 5개씩 자르기)
				line(src, Point(x, y), Point(x + FUNCT_WINDOW_W, y), Scalar(0, 0, 0), LINE_THICKNESS);  //가로줄
			array_size -= 5;
		}
	}

	//기능에 대한 문자열 입력창에 삽입 함수
	void putText_function(Mat& src, String* text, int array_size) {
		int thickness = 2; //두께
		int fontFace = FONT_HERSHEY_SIMPLEX;
		double fontScale = 1.0; //폰트 크기 확대/축소 비율

		int old_height = 0;
		int current_height = 0;
		int count = 0;
		for (int i = 0; i < array_size; i++) {
			Size sizeText = getTextSize(text[i], fontFace, fontScale, thickness, 0); 
			old_height = FUNCT_WINDOW_H * count;
			current_height = (FUNCT_WINDOW_H * (count + 1)) + old_height;
			Mat dst = src(Rect(INPUT_WINDOW + (FUNCT_WINDOW_W * (i / 5)), 0, FUNCT_WINDOW_W, src.rows));

			Point org((dst.cols - sizeText.width) / 2, (current_height + sizeText.height) / 2);
			putText(dst, text[i], org, fontFace, fontScale, Scalar(0, 0, 0), thickness);

			if (++count == 5) {
				count = 0;
				cout << endl;
			}
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
