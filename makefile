OBJS = weather_main.cpp
CC = g++
MINGW = x86_64-w64-mingw32-g++
MIN_FLAGS = -I ~/mingw/include -L ~/mingw/lib -DCURL_STATICLIB -static-libgcc -static-libstdc++
MIN_LIBS = -lcurl -lws2_32
DEBUG = -g
CFLAGS = -Wall -std=gnu++0x -lcurl -c $(DEBUG)
LFLAGS = -Wall -std=gnu++0x -lcurl $(DEBUG)

linux: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o weather

windows: $(OBJS)
	$(MINGW) $(LFLAGS) $(MIN_FLAGS) $(OBJS) $(MIN_LIBS) -o weather.exe

clean:
	@rm -f weather
	@rm -f weather.exe
