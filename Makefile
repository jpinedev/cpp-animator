PROGRAMS=main

CC=g++
CXXFLAGS=-std=c++14 -O0 -fno-inline -g -Wall -Wextra -Wpedantic -Werror -pedantic-errors
LDFLAGS=-std=c++14

## for gcov
#CXXFLAGS:=$(CXXFLAGS) -fprofile-arcs -ftest-coverage
#LDFLAGS:=$(LDFLAGS) -fprofile-arcs

all: util model animation_builder views $(PROGRAMS)

main: main.o animation_builder/animation_builder.o animation_builder/errors.o model/frames.o model/shapes.o util/util.o views/svg_view/svg_util.o views/svg_view/svg_view.o views/text_view/text_view.o
	$(CC) $(LDFLAGS) $^ -o $@

animation_builder: animation_builder/animation_builder.o animation_builder/errors.o

model: model/frames.o model/shapes.o

util: util/util.o

views: views/svg_view/svg_util.o views/svg_view/svg_view.o views/text_view/text_view.o

%.o: %.cpp *.hpp Makefile
	$(CC) $(CXXFLAGS) -c $< -o $@
	

clean:
	rm -rf .vscode/*~ *.o */*.o */*/*.o *.dSYM $(PROGRAMS) *.gcda *.gcno *.gcov callgrind.out.*