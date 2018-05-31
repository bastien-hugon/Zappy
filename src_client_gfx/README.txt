To compile the library launch:
    gcc -fpic --shared $(python3-config --includes) module.c -o sockets.abi3.so
and then python3:
    ./hello.py ip:port