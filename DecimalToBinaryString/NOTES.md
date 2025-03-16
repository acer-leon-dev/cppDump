compiling with gcc
```
g++ -c -Iinclude src/binary.cpp -o bin/binary.o
ar rcs lib/libbinary.a bin/binary.o
```

compiling test
```
g++ -Iinclude -Llib -lbinary src/binary.cpp -o bin/app.exe
```