CC=gcc
CFLAGS=-Wall -g

TARGET ?=
OBJ_FILES=$(TARGET).o comp_calc.o double_mat_calc.o file_rw.o fourier_trans.o

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET) -lm
	@del $(OBJ_FILES)

$(TARGET).o: $(TARGET).c lib/file_rw.h lib/fourier_trans.h lib/comp_calc.h lib/setting.h
	$(CC) $(CFLAGS) -c $(TARGET).c

file_rw.o: lib/file_rw.c lib/file_rw.h lib/setting.h
	$(CC) $(CFLAGS) -c lib/file_rw.c

fourier_trans.o: lib/fourier_trans.c lib/fourier_trans.h lib/comp_calc.h lib/setting.h lib/file_rw.c lib/file_rw.h
	$(CC) $(CFLAGS) -c lib/fourier_trans.c

comp_calc.o: lib/comp_calc.c lib/comp_calc.h lib/setting.h
	$(CC) $(CFLAGS) -c lib/comp_calc.c

double_mat_calc.o: lib/double_mat_calc.c lib/double_mat_calc.h lib/setting.h
	$(CC) $(CFLAGS) -c lib/double_mat_calc.c

clean:
	del $(TARGET).exe
