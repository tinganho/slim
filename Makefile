
OPTIONS = \
	-std=c++11 \
	-stdlib=libc++ \

MAINSRCS = \
  compiler/program.cpp \
  compiler/scanner.cpp \

INCLUDES = \
  -I./includes/\
  -I./compiler/\

OUTPUT = \
  ./bin/slim

all:
	clang++ -O3 $(OPTIONS) $(INCLUDES) $(MAINSRCS) -o $(OUTPUT)
