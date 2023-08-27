SRC := $(foreach x, ./src, $(wildcard $(addprefix $(x)/*,.c*)))
LIB := $(foreach x, ./lib, $(wildcard $(addprefix $(x)/*,.c*)))
DIRS := $(foreach x, ./src/**, $(wildcard $(addprefix $(x)/*,.c*)))
INCLUDES:=$(shell pkg-config --cflags libavformat libavcodec libswresample libswscale libavutil gtk+-3.0 )
LIBS=$(shell pkg-config --libs gtk+-3.0  )
out.o: 
	gcc ${SRC} -I include ${INCLUDES} ${DIRS} -o build/krokodil -pthread -ldiscord -lcurl ${LIBS} 2> /dev/null && ./build/krokodil

test: 
	gcc ${SRC} -I include ${INCLUDES} ${DIRS} -o build/krokodil -pthread -ldiscord -lcurl ${LIBS} && ./build/krokodil

install: 
	chmod +x INSTALL && sh INSTALL

win: 
	gcc ${SRC} -I include ${INCLUDES} ${DIRS} -o build/krokodil.exe -pthread -ldiscord -lcurl ${LIBS} 2> /dev/null && wine ./build/krokodil.exe

w: 
	mcs rpc/prog.cs && mono rpc/prog.exe

dist: 
	gcc ${SRC} -I include ${INCLUDES} ${DIRS} -o build/krokodil -pthread -ldiscord -lcurl ${LIBS}

desktop:
	desktop-file-validate krokodil.desktop && desktop-file-install --dir=$HOME/.local/share/applications ~/krokodil.desktop && update-desktop-database ~/.local/share/applications