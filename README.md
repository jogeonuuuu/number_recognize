# number_recognize
[객체 인식 작동 영상](https://youtu.be/-IGvKEwKx3o)

### Line 9-13 (line함수를 통해 영역을 나누는 코드)
```
rectangle(src, Rect(0, 0, src.cols, src.rows), Scalar(0, 0, 0), thickness);
line(src, Point(INPUT_WINDOW - 1, 0), Point(INPUT_WINDOW - 1, src.rows - 1), Scalar(0, 0, 0), thickness);
for (int y = src.rows / 5; y < src.rows; y += src.rows / 5) //기능 영역 분리
  line(src, Point(INPUT_WINDOW, y), Point(src.cols - 1, y), Scalar(0, 0, 0), thickness);
```
- line 10 : 출력화면의 전체적인 테두리
- line 11 : 숫자 입력창과 기능창 분할
- line 12-13 : 각 기능창들의 영역 분리(5개라고 가정)

### Line 16-17 (기능에 대한 문자열 입력창에 삽입)
```
String function_text[] = { "Save", "Load", "Clear", "Run", "Exit" };
  putText_function(src, function_text);
```
```
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
```
- 
