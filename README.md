# 1. cvui 사용법
정말 쉽다. 그냥 cvui 관련 전역 변수 설정해 주고 파일 중에 cvui.h를 헤더파일로 추가시키면 된다.<br>
```c
  #define CVUI_IMPLEMENTATION
  #include "cvui.h"
'''
당연히 opencv는 지원이 되어야 한다.<br>
단, 파일에 보면 **Enhanced** 가 붙은 파일이 있는데 얘는 EnhancedWindows.h라는 파일을 더 추가시키면 된다.<br>
한글 설명을 추가 시켜놔서 
