PROG = ungreek 
OBJECTS = 

#CC = cc
CFLAGS += -g -Wall -std=c99 
LDFLAGS +=
LDLIBS += 

$(PROG): $(OBJECTS)

clean:
	rm -f *.o $(PROG)
	rm -rf $(PROG).dSYM
