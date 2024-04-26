# Compiler and linker configurations
CC = g++
CFLAGS = -Wall -std=c++11
LDFLAGS = -lm
GTEST_DIR = ./googletest
GTEST_INC = -isystem $(GTEST_DIR)/googletest/include
GTEST_LIB = $(GTEST_DIR)/build/lib/libgtest.a

# Build targets
all: WavelengthCalculator ShannonsCapacityCalculator test

WavelengthCalculator: main_wavelength.o utilities.o
	$(CC) -o WavelengthCalculator main_wavelength.o utilities.o $(LDFLAGS)

ShannonsCapacityCalculator: main_shannons_capacity.o utilities.o
	$(CC) -o ShannonsCapacityCalculator main_shannons_capacity.o utilities.o $(LDFLAGS)

main_wavelength.o: main_wavelength.cpp utilities.h
	$(CC) -c main_wavelength.cpp $(CFLAGS)

main_shannons_capacity.o: main_shannons_capacity.cpp utilities.h
	$(CC) -c main_shannons_capacity.cpp $(CFLAGS)

utilities.o: utilities.cpp utilities.h
	$(CC) -c utilities.cpp $(CFLAGS)

test: utilities_test
	./utilities_test

utilities_test: utilities_test.cpp utilities.o
	$(CC) $(GTEST_INC) -pthread utilities_test.cpp utilities.o $(GTEST_LIB) -o utilities_test $(LDFLAGS)

clean:
	rm -f *.o WavelengthCalculator ShannonsCapacityCalculator utilities_test

.PHONY: all clean test