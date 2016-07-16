CC = g++
CFLAGS = -std=c++11 -fno-stack-protector -g -rdynamic

_OBJ = pen-lang.o \
	   pen-interfaces.o \
	   pen-keyword.o \
	main.o 
	
_DEPS = pen-interfaces.hpp \
		pen-lang.hpp \
		pen-utility.hpp

ODIR = bin
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

IDIR = includes
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o : %.cpp  $(DEPS)
	 @mkdir $(ODIR) -p
	 $(CC) -c -o $@ $< $(CFLAGS)

pen : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	cp ./pen ./bin/pen

.PHONY : clean rebuild

all : 
	pen

clean : 
	rm -rf $(ODIR)

rebuild : 
	clean pen
