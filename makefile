#target:  dependency1 dependency2 ... dependencyn
#      <tab> command
CC = g++
INC_LIBS = "C:\MinGW\lib\gcc\mingw32\6.3.0\include\c++"

avz.obj : avz.cpp
	$(CC) -o avz.obj -c -I $(INC_LIBS) avz.cpp
	
alienvszombie.obj : main.cpp
	$(CC) -o alienvszombie.obj -c -I $(INC_LIBS) main.cpp
	
alienvszombie.exe : alienvszombie.obj avz.obj
	$(CC) -o alienvszombie.exe alienvszombie.obj avz.obj
	
all : alienvszombie.exe
	