OBJS = weather_main.cpp
CC = g++
MIN32 = i686-w64-mingw32-g++
MIN64 = x86_64-w64-mingw32-g++
MIN32_FLAGS = -I deps/32/include -L deps/32/lib -DCURL_STATICLIB -static-libgcc -static-libstdc++
MIN64_FLAGS = -I deps/64/include -L deps/64/lib -DCURL_STATICLIB -static-libgcc -static-libstdc++
MIN_LIBS = -lcurl -lws2_32
DEBUG = -g
CFLAGS = -Wall -std=gnu++0x -lcurl -c $(DEBUG)
LFLAGS = -Wall -std=gnu++0x -lcurl $(DEBUG)

all: $(OBJS)
	make clean
	make depends
	make linux
	make win32
	make win64

linux: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o weather

win32: $(OBJS)
	$(MIN32) $(LFLAGS) $(MIN32_FLAGS) $(OBJS) $(MIN_LIBS) -o weather32.exe

win64: $(OBJS)
	$(MIN64) $(LFLAGS) $(MIN64_FLAGS) $(OBJS) $(MIN_LIBS) -o weather64.exe

clean:
	@rm -rf deps/32/*
	@rm -rf deps/64/*
	@rm -f deps/master.tar.gz*
	@rm -rf deps/curl-master
	@rm -f weather
	@rm -f weather32.exe
	@rm -f weather64.exe

depends:
	@deps/build.sh
