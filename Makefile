SRC=src/
OBJ=obj/
NAME=example.out
CC=g++

OPTIONS=-Wall -Wextra -std=c++11 -pedantic

DEVLIBS=
OBJECTS=$(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(wildcard $(SRC)*.cpp))


all: dir $(NAME)
$(NAME): $(OBJECTS)
	$(CC) $^ $(OPTIONS) $(DEVLIBS) -o $(NAME)

$(OBJ)main.o: $(SRC)file_io.hpp
$(OBJ)file_io.o: $(SRC)file_io.hpp

$(OBJ)%.o: $(SRC)%.cpp
	$(CC) -o $@ -c $< $(OPTIONS)

clean:
	rm $(OBJ)*.o $(NAME)

dir:
	mkdir -p obj
