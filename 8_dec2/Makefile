T1 = counter_fetch_and_add
T2 = counter_ttas
T3 = counter_non_lock
T4 = counter_pthread_lock
T5 = counter_imaginary_cas_lock
T6 = counter_tas
T7 = counter_hoshino
T8 = general_lock_list

CC = g++
CFLAGS = -g -c -Wall -O0 -std=c++11
LDFLAGS = -lm -pthread 

OBJ_T1 = counter_fetch_and_add.o
OBJ_T2 = counter_ttas.o
OBJ_T3 = counter_non_lock.o
OBJ_T4 = counter_pthread_lock.o
OBJ_T5 = counter_imaginary_cas_lock.o
OBJ_T6 = counter_tas.o
OBJ_T7 = counter_hoshino.o
OBJ_T8 = general_lock_list.o

all: $(T1) $(T2) $(T3) $(T4) $(T6) 

$(T1): $(OBJ_T1)
	$(CC) $(LDFLAGS) -o $@ $^
$(T2): $(OBJ_T2)
	$(CC) $(LDFLAGS) -o $@ $^
$(T3): $(OBJ_T3)
	$(CC) $(LDFLAGS) -o $@ $^
$(T4): $(OBJ_T4)
	$(CC) $(LDFLAGS) -o $@ $^
$(T5): $(OBJ_T5)
	$(CC) $(LDFLAGS) -o $@ $^
$(T6): $(OBJ_T6)
	$(CC) $(LDFLAGS) -o $@ $^
$(T7): $(OBJ_T7)
	$(CC) $(LDFLAGS) -o $@ $^
$(T8): $(OBJ_T8)
	$(CC) $(LDFLAGS) -o $@ $^

.cc.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *~ *.o $(T1) $(T2) $(T3) $(T4) $(T5) $(T6) $(T7) $(T8) 
