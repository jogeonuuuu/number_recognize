#include "mylib.h"
namespace jgw {
	//기능에 대한 문자열 입력창에 삽입
	void putText_function(Mat& src, String* text) {
		int thickness = 2; //두께
		int fontFace = FONT_HERSHEY_SIMPLEX;
		double fontScale = 1.0; //폰트 크기 확대/축소 비율
		int old_height = 0;
		int current_height = 0;
		for (int i = 0; i <= text->size(); i++) {
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
		String file_name;
		cout << "<Save> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		Mat dst;
		resize(src(area), dst, Size(INPUT_WINDOW, INPUT_WINDOW));
		bool tf = imwrite(file_name, dst);
		if (tf) cout << file_name << "파일이 저장됨" << endl;
	}
	//Load
	void load_function(Mat& src, Rect& area) {
		String file_name;
		cout << "<Load> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		Mat mRead = imread(file_name);
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
