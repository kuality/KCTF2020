# KCTF2020

- Flag format : `KCTF{ ... }`

- 각 카테고리 내에 문제 별 디렉토리 생성 후(문제 이름은 마음대로), 다음과 같이 `share` 디렉토리 내에 문제 파일 및 플래그 구성

- << 친 곳만 채워주세요.
- https://github.com/kuality-cysc/KCTFJr_2020 참고.

```
 ── KCTF2020
    ├── README.md
    ├── pwn
    │     ├── pwn1
    │     │     ├── share
    │     │     │     ├── binary (elf/exe) << 문제 파일
    │     │     │     ├── flag             << 플래그
    │     │     │     └── run.sh
    │     │     │── Dockerfile 
    │     │     ├── binary.c               << 문제 코드
    │     │     ├── binary_exploit.py      << 익스 코드
    │     │     ├── README.md              << 문제 설명
    │     │     └── xinetd
    │     ├── pwn2
    ...   ...
    │     │
    │     └──  docker-compose.yml
    ├── ...
    └── web
```

