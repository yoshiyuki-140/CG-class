# For linux replace the next line with
# CC =  gcc
# and you may have to add -L/usr/X11R6/lib to LDLIBS

CC = c++
#CXX = g++ 

LDLIBS = -DWIN32 -lglut32 -lglut32 -lopengl32 -lglu32 

p8-finger:	p8-finger.o mylib.o CFinger.o

p8-hand:	p8-hand.o mylib.o CFinger.o CHand.o

tmp:	tmp.o mylib.o

#p8-hand.o:	p8-hand.cpp CFinger.h CHand.h
#	$(CXX) -c p8-hand.cpp


#.c:
#	$(CC)  $@.c $(LIBS) -o $@

#.cpp:
#	$(CXX)  $@.cpp $(LIBS) -o $@



