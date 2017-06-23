CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi majio.cgi updatestuinfo.cgi deletestu.cgi doupdatestu.cgi addc.cgi doaddc.cgi selC.cgi updateC.cgi deleteC.cgi doupdateC.cgi selsch.cgi doaddsch.cgi updateSch.cgi deleteSch.cgi doupdateSch.cgi addSC.cgi doaddSC.cgi updateSC.cgi deleteSC.cgi SC.cgi doupdateSC.cgi
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
	cp -r public /var/www/html/
	sudo cp header.html /var/www/html/header.html
	sudo cp stu.html /var/www/html/stu.html
	sudo cp admin.html /var/www/html/admin.html
	sudo cp addstu.html /var/www/html/addstu.html
	sudo cp editstu.html /var/www/html/editstu.html
	sudo cp editC.html /var/www/html/editC.html
	sudo cp editSC.html /var/www/html/editSC.html
	sudo cp addsch.html /var/www/html/addsch.html
	sudo cp editsch.html /var/www/html/editsch.html
	sudo cp addc.html /usr/lib/cgi-bin/sx/addc.html
	sudo cp addstu.html /usr/lib/cgi-bin/sx/addstu.html
