savedcmd_syscalls/built-in.a := rm -f syscalls/built-in.a;  printf "syscalls/%s " syscalls.o | xargs ar cDPrST syscalls/built-in.a
