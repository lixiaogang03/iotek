CC:=gcc
CFLAGS:=-Include
CFLAGS+=-c
TARGET:=bin/client
DEPEND:=obj/main.o
DEPEND+=obj/fun.o


$(TARGET):$(DEPEND)
	$(CC) -o $@ $^ -lpthread
obj/main.o:src/main.c
	$(CC) -o $@ $(CFLAGS) $^	
obj/fun.o:src/fun.c
	$(CC) -o $@ $(CFLAGS) $^

.PHONY:clean
clean:
	rm -fr $(DEPEND)
	rm -fr $(TARGET)

