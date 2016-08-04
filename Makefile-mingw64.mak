CC = g++
CFLAGS = -std=c++11 -fno-stack-protector -O2 -Wl,--stack=2147483648

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
	 $(CC) -c -o $@ $< $(CFLAGS)

pen : $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	cp ./pen.exe ./bin/pen.exe

.PHONY : clean rebuild

all : pen

clean : 
	@rm -rf $(ODIR)

install : pen
	copy pen.exe C:\Windows\pen.exe

rebuild : clean pen
