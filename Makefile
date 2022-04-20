CXX=g++
CXXFLAGS= -Wall -Wextra -Werror -pedantic -std=c++2a -lpthread -g

OBJS= $(wildcard src/*.cc)
MAIN_OBJ= src/main/main.cc
TEST_OBJS= $(wildcard tests/*.cc) 

main: ${OBJS} ${MAIN_OBJ}
	${CXX} -o $@ $^

test: ${TEST_OBJS} ${OBJS}
	${CXX} -o $@ $^ -lgtest -lpthread

check: test
	./test

clean:
	${RM} test main
.PHONY: main check test clean