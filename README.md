# number_recognize
[객체 인식 작동 영상](https://youtu.be/-IGvKEwKx3o)
[객체 인식 작동 영상](https://youtu.be/sDc75Gjcx60)

#### void src_resize(Mat& src, int array_size)
https://github.com/jogeonuuuu/number_recognize/blob/8bcbea02443aa641ed58dca3bf970cf817b7b027/mylib.cpp#L4-L9
- 기능 계수에 따라 원본 Mat객체 사이즈 자동 조정하는 함수


#### void draw_line(Mat& src, int array_size)
https://github.com/jogeonuuuu/number_recognize/blob/8bcbea02443aa641ed58dca3bf970cf817b7b027/mylib.cpp#L12-L20
- 기능 계수에 따라 라인을 자동으로 그려주는 함수


#### putText_function 수정 (전)
https://github.com/jogeonuuuu/number_recognize/blob/814a6c753d13d0756d10d265ef8471b2d33edb42/main.cpp#L16-L17
https://github.com/jogeonuuuu/number_recognize/blob/814a6c753d13d0756d10d265ef8471b2d33edb42/mylib.cpp#L6-L20
- void putText_function(Mat& src, String* text)는 String 객체를 전달받아 각 기능에 대한 문자열을 중앙에 그려주는 함수
- (main.cpp)line 12, (mylib.cpp)line 15, 16은 기능이 현재 5개라고 가정

> [!CAUTION]
> 외부 함수에서 배열의 크기를 사용할 때 매개변수에 'array_size'를 전달하여 사용하는 이유
```
void src_resize(Mat& src, int array_size)
void draw_line(Mat& src, int array_size)
void putText_function(Mat& src, String* text, int array_size)
```
- 매개변수에 'String* text'와 같이 배열을 함수에 전달하고, 함수 내에서 'int array_size = sizeof(text) / sizeof(text[0])'처럼 사용 -> ${\textsf{\color{red}Error}}$
- 배열을 함수에 전달하면, 배열은 ${\textsf{\color{red}포인터로 변환되어 크기 정보를 잃게되고}}$, 배열의 크기가 아닌 포인터의 크기를 계산하게 됨.
- 이를 해결하기 위해 배열의 크기를 인수로 전달하는 방법을 사용

#### void putText_function(Mat& src, String* text, int array_size) 수정 (후)
https://github.com/jogeonuuuu/number_recognize/blob/8bcbea02443aa641ed58dca3bf970cf817b7b027/mylib.cpp#L23-L43
- String function_text[] = { "Save", "Load", "Clear", "Run", "Exit", "Feature1", "Feature2" };과 같이 String을 전달하면 각 text가 중앙에 오도록 자동으로 그려주는 함수


#### void feature1(Mat& src, Rect& area)
https://github.com/jogeonuuuu/number_recognize/blob/8bcbea02443aa641ed58dca3bf970cf817b7b027/mylib.cpp#L87-L108
- 외곽선 개수를 판단하여 분류를 크게 잡음
- 외곽선 개수 1개: 1, 2, 3, 4, 5, 7
- 외곽선 개수 2개: 0, 4, 6, 9
- 외곽선 개수 2개: 8


#### void feature2(Mat& src, Rect& area)
https://github.com/jogeonuuuu/number_recognize/blob/8bcbea02443aa641ed58dca3bf970cf817b7b027/mylib.cpp#L111-L124
- 위 함수에서 크게 분류한 값들 중 0, 6, 9를 분류하기 위해 'dst2.rows / 2 - 1'과 같이 mat객체 중앙을 나누어 비율을 판단하여 분류하는 함수
