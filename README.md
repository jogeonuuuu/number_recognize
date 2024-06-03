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
