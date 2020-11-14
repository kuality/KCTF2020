# Eye_Of_Agamotto

1. Check 함수에서 1byte씩 leak 가능 (canary, rbp)
2. help 함수에서 p1 포인터에 입력 가능 -> p포인터 값 조작
3. input 함수에서 rand값을 맞추면 배열 p포인터 초기화를 안함 -> 2번에서 넣어준 주소부터 입력 -> BOF 발생
4. libc_base 구해준뒤 binsh을 인자로 system 함수 호출.
