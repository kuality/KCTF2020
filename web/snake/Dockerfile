FROM ubuntu:18.04

RUN sed -i 's/archive.ubuntu.com/mirror.kakao.com/g' /etc/apt/sources.list
RUN groupadd -g 1000 pwn
RUN useradd -g 1000 -u 1000 -m pwn
RUN apt-get update
RUN apt-get install -y xinetd gcc-multilib
RUN chmod 774 /tmp
RUN chmod -R 774 /var/tmp
RUN chmod -R 774 /dev
RUN chmod -R 774 /run
RUN chmod 1733 /tmp /var/tmp /dev/shm
RUN chown pwn:pwn /home/pwn
RUN chmod 550 /home/pwn
WORKDIR /home/pwn
