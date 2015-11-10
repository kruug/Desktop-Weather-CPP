OBJS = weather_main.cpp
CC = g++
DEBUG = -g
CFLAGS = -Wall -std=gnu++0x -lcurl -c $(DEBUG)
LFLAGS = -Wall -std=gnu++0x -lcurl $(DEBUG)

weather: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o weather
clean:
	\rm weather
