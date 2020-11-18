#!/bin/bash
exec 2>/dev/null
cd /home/pwn
export LD_PRELOAD=/home/pwn/libc.so.6
timeout 60 /home/pwn/KNOTE
