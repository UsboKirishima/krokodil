SRC := $(foreach x, ./src, $(wildcard $(addprefix $(x)/*,.c*)))
DIRS := $(foreach x, ./src/**, $(wildcard $(addprefix $(x)/*,.c*)))
INCLUDES:=$(shell pkg-config --cflags libavformat libavcodec libswresample libswscale libavutil gtk4)
LIBS=$(shell pkg-config --libs gtk4 )
out.o: 
	gcc ${SRC} -I include ${INCLUDES} ${DIRS} -o build/krokodil -pthread -ldiscord -lcurl ${LIBS} && ./build/krokodil