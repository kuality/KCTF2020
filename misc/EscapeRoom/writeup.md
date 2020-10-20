총 3개의 스테이지로 나뉘어져 있어서 3개를 각각 풀어줘야합니다.



room1 : 단순히 이미지를 투명도 100%로 만들어 놓은거라 다시 투명도를 0%로 만들면 됩니다.



room2 : png속 png입니다. hxD로 열어보면 마지막에 IEND®B`로 마무리되고, 바로 위에 또다시 IEND®B`가 반복되는걸 보아 또다른 png파일이 있음을 유추할 수 있습니다.

단순히 png를 검색하여 따로 추출하면 key2가 나오게 됩니다.



room3 : 사진은 바로 주어지는데, 사진 안에 steganography를 통해 비밀번호 형식을 알아낼 수 있습니다

hidden message : The password format is "1t is _____". Find what has to go in _____ using all key1, key2, key3. Good luck!



총 얻어진 3개의 key를 가지고 세 장을 겹치면 04:58이라는 시간을 얻을 수 있습니다.

비밀번호 : 1t is 04:58

Flag : KCTF{TM1:_th1$\_w@z_m4d3_aT_O4:58_AM}
