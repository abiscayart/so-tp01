export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

export PATH := $(shell pwd):$(PATH)

.DEFAULT_GOAL := all

include ej1/tasks.mk
include ej2/tasks.mk
include ej3/batch.mk
include ej5/rr.mk
include ej6/fcfs.mk
include ej7/mist.mk
include ej8/rr2.mk
OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

ejercicios: ejercicio1  ejercicio2 ejercicio3 ejercicio5 ejercicio6 ejercicio7 ejercicio8

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all

