#include "mylib.h"
namespace jgw {
	extern bool ox = true;

	//Clear
	void clear_function(Mat& src, Rect& area) {
		src(area) = Scalar(255, 255, 255);
		rectangle(src, area, Scalar(0, 0, 0), 2);
		cout << "�Է�â ������" << endl;
	}
	//Save
	void save_function(Mat& src, Rect& area) {
		String file_name;
		cout << "<Save> ���ϸ� �Է� : "; //�й�_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		bool tf = imwrite(file_name, src(area));
		if (tf) cout << file_name << "������ �����" << endl;
	}
	//Load
	void load_function(Mat& src, Rect& area) {
		String file_name;
		cout << "<Load> ���ϸ� �Է� : "; //�й�_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		Mat mRead = imread(file_name);
		if (mRead.empty()) {
			cout << "���� �ҷ����� ����" << endl;
			return;
		}
		cout << file_name << "������ �ҷ���" << endl;
		mRead.copyTo(src(area));
	}
}