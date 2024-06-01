#include "mylib.h"
namespace jgw {
	extern bool ox = true;

	//Clear
	void clear_function(Mat& src, Rect& area) {
		src(area) = Scalar(255, 255, 255);
		rectangle(src, area, Scalar(0, 0, 0), 2);
		cout << "입력창 삭제됨" << endl;
	}
	//Save
	void save_function(Mat& src, Rect& area) {
		String file_name;
		cout << "<Save> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		bool tf = imwrite(file_name, src(area));
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
		mRead.copyTo(src(area));
	}
}