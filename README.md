# 1. cvui 사용법
정말 쉽다. 그냥 cvui 관련 전역 변수 설정해 주고 파일 중에 cvui.h를 헤더파일로 추가시키면 된다.<br>
```c
  #define CVUI_IMPLEMENTATION
  #include "cvui.h"
```

# 2. 사용하기 위한 조건
- 당연히 opencv는 지원이 되어야 한다. 다만 2.X, 3.X 버전이어야 한다. 4.X버전은 오류가 발생한다. <br>
- 폴더나 파일들을 보면 **Enhanced** 가 붙은 파일이 있는데 얘는 EnhancedWindows.h라는 파일을 더 추가시키면 된다. 해당 function이 추가 헤더 파일을 요구함.<br>
- 한글 설명도 추가시킴.


# 3. 참고사이트.
스샷 : https://dovyski.github.io/cvui/ <br>
github : https://github.com/Dovyski/cvui <br>
