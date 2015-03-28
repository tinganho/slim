
OPTIONS = \
	-std=c++11 \
	-stdlib=libc++ \

LIBS = \
	compiler/scanner.cpp \

TEST = \
	test/program.cpp \
	test/test.utils.cpp \

INCLUDES = \
	-I./compiler/ \
	-I./includes/gtest-1.7.0/include \

OUTPUT = \
  ./bin/slim

.PHONY: all test clean

all:
	clang++ -O3 $(OPTIONS) $(INCLUDES) $(LIBS) ./compiler/program.cpp -o $(OUTPUT)

test:
	clang++ -g -Wall $(OPTIONS) $(INCLUDES) $(TEST) $(LIBS) -L/usr/local/lib -lgtest_clang   -o ./bin/test
	./bin/test