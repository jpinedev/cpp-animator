CXXTEST_HOME?=../cxxtest-4.4
CXXTEST_GEN=$(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE=$(CXXTEST_HOME)

PROGRAMS=runner

CXXFLAGS=-std=c++11 -O0 -fno-inline -g -Wall -Wextra -Wpedantic -Werror -Wno-ignored-qualifiers -pedantic-errors
LDFLAGS=-std=c++11

all: $(PROGRAMS)

runner: runner.o ../animation_builder/animation_builder.o ../animation_builder/errors.o ../model/frames.o ../model/shapes.o ../util/util.o animation_builder.cxxtest.o
	g++ $(LDFLAGS) $^ -o $@

%.o: %.cpp *.hpp Makefile
	g++ -I$(CXXTEST_INCLUDE) $(CXXFLAGS) -c $< -o $@

%.cxxtest.cpp: %.cxxtest.hpp
	$(CXXTEST_GEN) --part --error-printer $< -o $@

runner.cpp:
	$(CXXTEST_GEN) --root --error-printer -o $@


clean:
	rm -rf test.log *~ *.o *.dSYM $(PROGRAMS) *.gcda *.gcno *.gcov callgrind.out.* runner.cpp *.cxxtest.cpp
