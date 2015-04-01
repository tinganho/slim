
OPTIONS = \
	-std=c++11 \
	-stdlib=libc++ \

LIBS = \
	compiler/scanner.cpp \
	compiler/parser.cpp \
	compiler/utils.cpp \

TEST = \
	test/program.cpp \
	test/test.utils.cpp \
	compiler/*.test.cpp \

INCLUDES = \
	-I./compiler/ \
	-I./test/ \
	-I./includes/gtest-1.7.0/include \

OUTPUT = \
  ./bin/slim


.PHONY: all test clean


GTEST_DIR = ./includes/gtest-1.7.0

CPPFLAGS += -isystem $(GTEST_DIR)/include -std=c++11 -stdlib=libc++

CXXFLAGS += -g -Wall -pthread

GTEST_HEADERS = \
	$(GTEST_DIR)/include/gtest/*.h \
	$(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


all:
	clang++ -O3 $(OPTIONS) $(INCLUDES) $(LIBS) ./compiler/program.cpp -o $(OUTPUT)


test: gtest.a
	clang++ -g -Wall $(OPTIONS) $(INCLUDES) $(TEST) $(LIBS) -L./bin -lgtest -o ./bin/test


runtest: test
	./bin/test


gtest-all.o: $(GTEST_SRCS_)
	clang++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc


gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) ./bin/libgtest.a $^
