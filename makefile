OBJECTS = data.o entry.o tree.o serialization.o test_data.o test_entry.o test_tree.o test_serialization.o
OBJ_dir = object/
BIN_dir = binary/
INC_dir = include/
SRC_dir = source/

CC = gcc
CFLAGS = -Wall -I $(INC_dir) -c
cmd = $(CC) $(CFLAGS) $(SRC_dir)

#out: $(OBJECTS)
#	gcc -Wall -I include/ -o data source/data.c source/test_data.c
# out: $(OBJETOS)
# 	$(CC) $(OBJETOS) -o $(BIN_dir)out
out: $(OBJECTS) test_data test_entry test_tree test_serialization

data.o: $(INC_dir)data.h
	      $(cmd)data.c -o $(OBJ_dir)data.o

entry.o: $(INC_dir)entry.h $(INC_dir)data.h
	       $(cmd)entry.c -o $(OBJ_dir)entry.o

tree.o: $(INC_dir)tree.h $(INC_dir)data.h
	      $(cmd)tree.c -o $(OBJ_dir)tree.o

tree-private.o: $(INC_dir)tree-private.h $(INC_dir)tree.h
	              $(cmd)tree-private.c -o $(OBJ_dir)tree-private.o

serialization.o: $(INC_dir)serialization.h $(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)tree.h
	               $(cmd)serialization.c -o $(OBJ_dir)serialization.o

clean:
	    rm -f $(OBJ_dir)*.o
			rm -f $(BIN_dir)*
