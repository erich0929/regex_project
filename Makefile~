CC = g++
LIBFILE = libhgRegex
OBJECTS = Dfa.o Ebuf.o linked_list.o
LIBS = -lhgRegex
TARGET = all

all : Target Dfa.o Ebuf.o linked_list.o main.cpp
	$(CC) -shared -Wl,-soname,$(LIBFILE).so.0 -o $(LIBFILE).so.0.0.0 $(OBJECTS)
	ln -s $(LIBFILE).so.0.0.0 $(LIBFILE).so
	ln -s $(LIBFILE).so.0.0.0 $(LIBFILE).so.0
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
