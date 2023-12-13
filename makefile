
PROJECT =  duplicates
HEADERS =  $(PROJECT).h
OBJ     =  duplicates.o scandir.o strSHA2.o  find.o  hashtable.o listdupes.o

C11     =  cc -std=c11
CFLAGS  =  -Wall -Werror -pedantic


$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<
clean:
	rm -f $(PROJECT) $(OBJ)
