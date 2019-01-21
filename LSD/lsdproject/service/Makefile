CC:=gcc
CFLAGS:=-Include
CFLAGS+=-c
TARGET:=bin/server
DEPEND:=obj/main.o
DEPEND+=obj/control.o
DEPEND+=obj/view.o
DEPEND+=obj/link_user.o
DEPEND+=obj/link_online.o
DEPEND+=obj/link_daily.o

$(TARGET):$(DEPEND)
	$(CC) -o $@ $^ -lpthread
obj/main.o:src/main.c
	$(CC) -o $@ $(CFLAGS) $^	
obj/control.o:src/control.c
	$(CC) -o $@ $(CFLAGS) $^
obj/view.o:src/view.c
	$(CC) -o $@ $(CFLAGS) $^
obj/link_user.o:src/link_user.c
	$(CC) -o $@ $(CFLAGS) $^
obj/link_online.o:src/link_online.c
	$(CC) -o $@ $(CFLAGS) $^
obj/link_daily.o:src/link_daily.c
	$(CC) -o $@ $(CFLAGS) $^

.PHONY:clean
clean:
	rm -fr $(DEPEND)
	rm -fr $(TARGET)
