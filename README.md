# number_recognize
[객체 인식 작동 영상](https://youtu.be/-IGvKEwKx3o)

### Line 9-13 (line함수를 통해 영역을 나누는 코드)
https://github.com/jogeonuuuu/number_recognize/blob/814a6c753d13d0756d10d265ef8471b2d33edb42/main.cpp#L9-L13
- line 10 : 출력화면의 전체적인 테두리
- line 11 : 숫자 입력창과 기능창 분할
- line 12-13 : 각 기능창들의 영역 분리(기능이 5개라고 가정)

### Line 16-17 (기능에 대한 문자열 입력창에 삽입)
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
