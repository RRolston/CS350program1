#Raymond Rolston, Joe Kim, Cameron Parlman
SRC_FILES = lab5.c makefile

lab5 :lab5.c
	gcc -Wall -g -o lab5 lab5.c

clean :
	-rm lab5

submit : $(SRC_FILES)
	mkdir Lab5Rolston_rrolsto1
	cp $(SRC_FILES) Lab5Rolston_rrolsto1
	tar -cvzf Lab5Rolston_rrolsto1.tar.gz Lab5Rolston_rrolsto1
	mv Lab5Rolston_rrolsto1.tar.gz Lab5Rolston_rrolsto1.tgz
	rm -r Lab5Rolston_rrolsto1
