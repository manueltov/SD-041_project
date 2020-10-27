# SD-041
# João Figueiredo, nº 53524
# Manuel Tovar, nº 49522
# Mariana Bento, nº 53676

OBJECTS = data.o entry.o tree.o serialization.o test_data.o test_entry.o test_serialization.o test_tree.o
OBJ_dir = object/
BIN_dir = binary/
INC_dir = include/
SRC_dir = source/

CC = gcc
CFLAGS = -Wall -I $(INC_dir) -c
cmd = $(CC) $(CFLAGS) $(SRC_dir)

out: $(OBJECTS)
	$(CC) $(addprefix $(OBJ_dir),$(OBJECTS)) -o out

data.o: $(INC_dir)data.h
		$(cmd)data.c -o $(OBJ_dir)data.o

entry.o: $(INC_dir)entry.h $(INC_dir)data.h
		$(cmd)entry.c -o $(OBJ_dir)entry.o

tree.o: $(INC_dir)tree.h $(INC_dir)tree-private.h $(INC_dir)data.h
		$(cmd)tree.c -o $(OBJ_dir)tree.o

serialization.o: $(INC_dir)serialization.h $(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)tree.h
				$(cmd)serialization.c -o $(OBJ_dir)serialization.o

test_data.o: $(INC_dir)data.h
			$(cmd)test_data.c -o $(OBJ_dir)test_data.o

test_entry.o: $(INC_dir)data.h $(INC_dir)entry.h
			$(cmd)test_entry.c -o $(OBJ_dir)test_entry.o

test_serialization.o: $(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)serialization.h
			$(cmd)test_serialization.c -o $(OBJ_dir)test_serialization.o

test_tree.o: $(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)tree.h
			$(cmd)test_tree.c -o $(OBJ_dir)test_tree.o

test_data: test_data.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_data $(SRC_dir)data.c $(SRC_dir)test_data.c
	$(BIN_dir)test_data

test_data_debug: test_data.o
	$(CC) -g -Wall -I include/ -o $(BIN_dir)test_data_debug $(SRC_dir)data.c $(SRC_dir)test_data.c
	$(BIN_dir)test_data_debug

test_entry: test_entry.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_entry $(SRC_dir)entry.c $(SRC_dir)data.c $(SRC_dir)test_entry.c
	$(BIN_dir)test_entry

test_serialization: test_serialization.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_serialization $(SRC_dir)serialization.c $(SRC_dir)test_serialization.c
	$(BIN_dir)test_serialization

test_tree: test_tree.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_tree $(SRC_dir)tree.c $(SRC_dir)test_tree.c
	$(BIN_dir)test_tree

test_all: test_data test_entry test_serialization test_tree

clean:
		rm -f $(OBJ_dir)*.o
		rm -f $(BIN_dir)*
