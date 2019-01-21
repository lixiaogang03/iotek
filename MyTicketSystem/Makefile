CC:=gcc
CFLAGS:=-Include
CFLAGS+=-c
TARGET:=bin/ticket
DEPEND:=obj/main.o
DEPEND+=obj/menu.o
DEPEND+=obj/fun.o
DEPEND+=obj/file_deal.o
DEPEND+=obj/link_user.o
DEPEND+=obj/link_ticket.o
DEPEND+=obj/link_winner.o

$(TARGET):$(DEPEND)
	$(CC) -o $@ $^
obj/main.o:src/main.c
	$(CC) -o $@ $(CFLAGS) $^
obj/menu.o:src/menu.c
	$(CC) -o $@ $(CFLAGS) $^	
obj/fun.o:src/fun.c
	$(CC) -o $@ $(CFLAGS) $^
obj/file_deal.o:src/file_deal.c
	$(CC) -o $@ $(CFLAGS) $^
obj/link_user.o:src/link_user.c
	$(CC) -o $@ $(CFLAGS) $^
obj/link_ticket.o:src/link_ticket.c
	$(CC) -o $@ $(CFLAGS) $^
obj/link_winner.o:src/link_winner.c
	$(CC) -o $@ $(CFLAGS) $^

.PHONY:clean
clean:
	rm -fr $(DEPEND)


