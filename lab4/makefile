#Raymond Rolston, Joe Kim, Cameron Parlman
SRC_FILES = lab4.c makefile

lab4 :lab4.c
	gcc -Wall -g -o lab4 lab4.c

clean :
	-rm lab4

submit : $(SRC_FILES)
	mkdir Lab4Rolston_rrolsto1
	cp $(SRC_FILES) Lab4Rolston_rrolsto1
	tar -cvzf Lab4Rolston_rrolsto1.tar.gz Lab4Rolston_rrolsto1
	mv Lab4Rolston_rrolsto1.tar.gz Lab4Rolston_rrolsto1.tgz
	rm -r Lab4Rolston_rrolsto1
