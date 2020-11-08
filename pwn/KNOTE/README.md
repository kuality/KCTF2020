### Vulnerability

취약점은 4번 Edit 메뉴에서 발생한다.

```c
void *sub_C2F()
{
  void *result; // rax
  size_t nbytes; // [rsp+Ch] [rbp-4h]

  result = buf;
  if ( buf )
  {
    printf("size : ");
    LODWORD(nbytes) = sub_A5F();
    printf("? ");
    result = (void *)read(0, buf, (unsigned int)nbytes);
    buf = 0LL;
  }
  return result;
}
```

전역 포인터변수인 buf에 값을 입력하는데 사용자가 입력하고 싶은 크기만큼 입력하게 된다.

또한 buf변수에 역할은 1번 Add 메뉴에서 힙 영역 메모리를 할당받고 마지막으로 할당 받은 주소를 저장하고 있다.

그리고 이를 2번 메뉴를 통해서 free해도 buf의 전역변수는 초기화 하지 않기 때문에 해제된 힙 영역에 값을 쓸 수 있다.

또한 문제에서 사용되는 라이브러리는 glibc 2.27를 사용하여 tcache가 적용되어 있는점을 생각하여 공격해야 한다.

### MEMORY LEAK

아쉽게도 3번메뉴인 View 메뉴가 구현되어 있지 않는다.

또한 지정된 문자열 이외에는 뭔가 출력되지 않으며 보호기법이 전부 걸려있는 것을 확인할 수 있다.

unsorted bin을 해제하면 fd, bk에 main arena 값이 남게된다.

바로 이 값을 이용해서 우리는 libc의 베이스를 구할 것이다.

main arena값이 남게될 때 하위 2바이트만 수정하여 stdout의 file structure flag의 주소를 만들 수 있다.

또한 하위 12bit는 고정이기 때문에 나머지  4bit 값만 brute force을 통해서 충분히 구할 수 있다.

fd를 수정하여 stdout의 file structure flag 부분으로 힙 메모리 영역을 할당받고 flag부분을 0xfbad1800 바꾼다.

그리고 NULL 값을 25개 정도 써주면 libc 주소가 출력되는것을 확인할 수 있다.

### ATTACK

구한 라이브러리 베이스를 이용해서 one shot 가젯의 주소와 free_hook을 덮어 RCE를 획득할 수 있다.