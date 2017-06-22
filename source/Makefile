CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi majio.cgi updatestuinfo.cgi deletestu.cgi doupdatestu.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
	cp *.cgi /usr/lib/cgi-bin/sx/
init:
	sudo cp index.html /var/www/html/index.html
	#cp -r public /usr/lib/cgi-bin/sx
	cp -r public /var/www/html/
	sudo cp header.html /var/www/html/header.html
	sudo cp stu.html /var/www/html/stu.html
	sudo cp admin.html /var/www/html/admin.html
	sudo cp addstu.html /var/www/html/addstu.html
	sudo cp editstu.html /var/www/html/editstu.html
