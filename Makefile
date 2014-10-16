CC = g++
LIBFILE = libhgRegex
OBJECTS = Dfa.o Ebuf.o linked_list.o
LIBS = -lhgRegex
VERSION = 0.8.1
TARGET = all

all : Target Dfa.o Ebuf.o linked_list.o main.cpp
	$(CC) -shared -Wl,-soname,$(LIBFILE).so.0 -o $(LIBFILE).so.$(VERSION) $(OBJECTS)
	ln -s $(LIBFILE).so.$(VERSION) $(LIBFILE).so
	ln -s $(LIBFILE).so.$(VERSION) $(LIBFILE).so.0
	$(CC) -o Target/bin/main main.cpp -L./ $(LIBS)
	mv $(LIBFILE)* Target/lib 
	
	
Target : 
	mkdir Target; mkdir Target/bin; mkdir Target/lib 

Dfa.o : Dfa.cpp
	$(CC) -fPIC -c Dfa.cpp
	
Ebuf.o : Ebuf.cpp
	$(CC) -fPIC -c Ebuf.cpp
	
linked_list.o : linked_list.cpp
	$(CC) -fPIC -c linked_list.cpp
	
test : all
	@echo [TEST] :
	@Target/bin/main
	
clean : 
	rm -rf *.o Target *.so.* *.so
