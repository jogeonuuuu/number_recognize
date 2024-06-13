#include "mylib.h"
namespace jgw {
	//기능 개수에 따른 src 사이즈 조정 함수
	void src_resize(Mat& src, int array_size) {
		int count = 1;
		while (array_size > count * 5)
			count++;
		resize(src, src, Size(INPUT_WINDOW + FUNCT_WINDOW_W * count, 500));
	}

	//라인 그리기 함수
	void draw_line(Mat& src, int array_size) { //함수 내에서 array_size값을 변경하기 때문에 참조로 선언하지 않음(실수로라도 값이 변경되지 않게 하기위해
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
		int fontFace = FONT_HERSHEY_SIMPLEX; //폰트 
		double fontScale = 0.8; //폰트 크기 확대/축소 비율

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

			if (++count == 5)
				count = 0;
		}
	}

	//Save
	void save_function(Mat& src, Rect& area) { //line 47, 56
		//String file_route = "C:\\Users\\jogeo\\source\\repos\\Open_cv\\Project_기말\\num_data\\"; //작성자 파일 경로
		String file_name;
		cout << "<Save> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		Mat dst;
		resize(src(area), dst, Size(INPUT_WINDOW, INPUT_WINDOW));
		//bool tf = imwrite(file_route + file_name, dst);  //작성자 파일 경로
		bool tf = imwrite(file_name, dst);
		if (tf) cout << file_name << "파일이 저장됨" << endl << endl;
	}

	//Load
	void load_function(Mat& src, Rect& area) { //line 63, 70
		//String file_route = "C:\\Users\\jogeo\\source\\repos\\Open_cv\\Project_기말\\num_data\\"; //작성자 파일 경로
		String file_name;
		cout << "<Load> 파일명 입력 : "; //학번_00_00
		cin >> file_name;
		if (file_name == "exit") return;

		file_name += ".jpg";
		//Mat mRead = imread(file_route + file_name); //작성자 파일 경로
		Mat mRead = imread(file_name);
		if (mRead.empty()) {
			cout << "파일 불러오기 실패" << endl << endl;
			return;
		}
		cout << file_name << "파일을 불러옴" << endl << endl;
		mRead(area).copyTo(src(area));
	}

	//Clear
	void clear_function(Mat& src, Rect& area) {
		src(area) = Scalar(255, 255, 255);
		cout << "입력창 삭제됨" << endl << endl;
	}

	//객체(number) 인식 후 숫자의 전체적인 크기를 300x300 변경(morpholgy연산 전에 수행)
	double num_resize(Mat& src, Mat& dst, Rect& area, Rect& outside) {
		cvtColor(src(area), dst, COLOR_BGR2GRAY);
		threshold(dst, dst, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

		vector<vector<Point>> contours;
		findContours(dst, contours, RETR_LIST, CHAIN_APPROX_NONE); //외곽선 개수
		//외부 외곽선 정보
		if (contours.size() == 0)
			cerr << "탐색할 객체가 없음." << endl;
		int max_index = contours.size() - 1; //외부 외곽선 index
		outside = boundingRect(contours[max_index]); //외부 외곽선

		//모폴로지 연산에 사용되는 반복횟수(iterations) 계산
		//그림의 비율을 이용하여 반복횟수 설정
		double iterations = 1;
		int i = 1;
		while (true) {
			if (outside.width < (dst.cols * i / 10) || outside.height < (dst.rows * i / 10))
				break;
			iterations += 0.2;
			i++;
		}
		resize(dst(outside), dst, Size(300, 300));

		//morphologyEx(dst, dst, MORPH_CLOSE, Mat(), Point(-1, -1), 10 * iterations); //닫기 연산을 통해 조금 떨어진 선을 연결

		return iterations;
	}

	//외곽선(Contours)
	int get_contours(Mat& src, Mat& dst, Rect& area) {
		//Mat dst;
		Rect outside;
		double iterations = num_resize(src, dst, area, outside);
		//imshow("dst", dst);

		//cout << "morphology 연산 횟수 : " << iterations << endl;
		morphologyEx(dst, dst, MORPH_CLOSE, Mat(), Point(-1, -1), 10 * iterations); //닫기 연산을 통해 조금 떨어진 선을 연결

		vector<vector<Point>> contours;
		findContours(dst, contours, RETR_LIST, CHAIN_APPROX_NONE);
		if (contours.size() == 0)
			cerr << "탐색할 객체가 없음." << endl;
		int max_index = contours.size() - 1;
		outside = boundingRect(contours[max_index]);

		cvtColor(dst, dst, COLOR_GRAY2BGR);
		for (int i = 0; i < contours.size(); i++) {
			Scalar c(rand() & 255, rand() & 255, rand() & 255);
			drawContours(dst, contours, i, c, LINE_THICKNESS);
		}
		//imshow("dst", dst);

		return contours.size();
	}

	//무게 중심 (1) - (직접 구현)
	Point center_of_gravity(Mat& src, Mat& dst, Rect& area) {
		Rect outside;
		double iterations = num_resize(src, dst, area, outside);

		morphologyEx(dst, dst, MORPH_CLOSE, Mat(), Point(-1, -1), 10 * iterations); //닫기 연산을 통해 조금 떨어진 선을 연결

		vector<vector<Point>> contours;
		findContours(dst, contours, RETR_LIST, CHAIN_APPROX_NONE);
		if (contours.size() == 0)
			cerr << "탐색할 객체가 없음." << endl;
		int max_index = contours.size() - 1;
		outside = boundingRect(contours[max_index]);

		int x_count = 0, y_count = 0;
		Point x_value, y_value;
		for (int x = 0; x < outside.width; x++) {
			for (int y = 0; y < outside.height; y++) {
				//dst(outside).at<Vec3b>(y, x) == dst.at<Vec3b>(outside.y + y, outside.x + x)( = Vec3b pixel)
				if (dst(outside).at<uchar>(y, x) == 255) {
					x_count++; y_count++;
					x_value += Point(x, 0);
					y_value += Point(0, y);
				}
			}
		}
		Point2f w = x_value / x_count;
		Point2f h = y_value / y_count;
		Point cog = w + h;
		cvtColor(dst, dst, COLOR_GRAY2BGR);
		circle(dst, cog, 3, Scalar(0, 255, 0), -1);

		return cog;
	}

	//무게 중심 (2)-(connectedComponentsWithStats 함수 사용)
	/*Point center_of_gravity(Mat& src, Rect& area) {
		Mat dst;
		cvtColor(src(area), dst, COLOR_BGR2GRAY);
		threshold(dst, dst, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); //객체 인식을 하기위해 객체를 흰색으로 변환

		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 3));
		morphologyEx(dst, dst, MORPH_CLOSE, kernel, Point(-1, -1), 5); //닫기 연산을 통해 조금 떨어진 선을 연결

		vector<vector<Point>> contours;
		findContours(dst, contours, RETR_LIST, CHAIN_APPROX_NONE); //외곽선 개수

		//외부 외곽선에 대한 정보
		if (contours.size() == 0)
			return Point(0, 0);
		int max_index = contours.size() - 1; //외부 외곽선 index
		Rect outside = boundingRect(contours[max_index]); //외부 외곽선


		Mat labels, stats, centroids;
		int count = connectedComponentsWithStats(dst, labels, stats, centroids); //배경 index : '0' , 반환값 : (배경+객체) 개수
		if (count > 1)
		{
			Point cog(centroids.at<double>(count - 1, 0), centroids.at<double>(count - 1, 1));
			cvtColor(dst, dst, COLOR_GRAY2BGR);
			circle(dst(outside), cog, 3, Scalar(0, 255, 0), -1);
			cout << cog << endl;
			cout << "dst(outside): " << dst(outside).cols << ", " << dst(outside).rows << endl; //
		}
		else {
			cerr << "객체 없음" << endl;
			return;
		}

		imshow("num", dst(outside));

		return cog;
	}*/


	void center(Mat& src, Rect& area) {
		Mat dst;
		Rect outside, inside;
		double iterations = num_resize(src, dst, area, outside);
		imshow("dst", dst);

		//cout << "morphology 연산 횟수 : " << iterations << endl;
		morphologyEx(dst, dst, MORPH_CLOSE, Mat(), Point(-1, -1), 10 * iterations); //닫기 연산을 통해 조금 떨어진 선을 연결

		vector<vector<Point>> contours;
		findContours(dst, contours, RETR_LIST, CHAIN_APPROX_NONE);
		if (contours.size() == 0)
			cerr << "탐색할 객체가 없음." << endl;
		int max_index = contours.size() - 1;
		outside = boundingRect(contours[max_index]); //외부 외곽선
		inside = boundingRect(contours[0]); //내부 외곽선

		cvtColor(dst, dst, COLOR_GRAY2BGR);
		drawContours(dst, contours, 0, Scalar(0, 0, 255), LINE_THICKNESS);


		//내부 외곽선 중심 좌표에 원 그리기(빨)
		Point inside_center(inside.width / 2, inside.height / 2);
		circle(dst(inside), inside_center, 3, Scalar(0, 0, 255), -1);
		//외부 외곽선 중심 좌표에 원 그리기(파)
		Point outside_center(outside.width / 2, outside.height / 2);
		circle(dst(outside), outside_center, 3, Scalar(255, 0, 0), -1);
		imshow("center", dst(outside));
	}

	//Run
	void run_function(Mat& src, Mat& dst, Rect& area) {
		cout << "결과 값: ";
		Rect outside;
		double iterations = num_resize(src, dst, area, outside);

		morphologyEx(dst, dst, MORPH_CLOSE, Mat(), Point(-1, -1), 10 * iterations); //닫기 연산을 통해 조금 떨어진 선을 연결

		vector<vector<Point>> contour;
		findContours(dst, contour, RETR_LIST, CHAIN_APPROX_NONE);
		if (contour.size() == 0)
			cerr << "탐색할 객체가 없음." << endl;
		int max_index = contour.size() - 1;
		outside = boundingRect(contour[max_index]);

		Point cog = center_of_gravity(src, dst, area);

		if (get_contours(src, dst, area) == 1) {
			Mat num1;
			dst.copyTo(num1);
			line(num1, Point(0, 0), Point(dst.cols - 1, dst.rows - 1), Scalar(255, 255, 255), LINE_THICKNESS);

			cvtColor(num1, num1, COLOR_BGR2GRAY);
			threshold(dst, dst, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

			findContours(dst, contour, RETR_LIST, CHAIN_APPROX_NONE); //외곽선 개수

			imshow("num1", num1);

			if (contour.size() == 4)
				cout << "1" << endl;
			//if ((130 <= cog.y && 170 >= cog.y) && (130 <= cog.x && 170 >= cog.x)) //dst == dst(outside) , dst.rows * 2 /5 == 120

			else
				cout << endl;
		}
		else if (get_contours(src, dst, area) == 2) {
			if ((130 <= cog.y && 170 >= cog.y) && (130 <= cog.x && 170 >= cog.x)) //dst == dst(outside) , dst.rows * 2 /5 == 120
				cout << "0" << endl;
			else if (dst.rows / 2 < cog.y)
				cout << "6" << endl;
			else if (dst.rows / 2 > cog.y)
				cout << "9" << endl;
			else
				cout << "4" << endl;
		}
		else if (get_contours(src, dst, area) == 3)
			cout << "8" << endl;
	}
}
