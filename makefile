#SD-041
#João Figueiredo, nº 53524
#Manuel Tovar, nº 49522
#Mariana Bento, nº 53676

OBJECTS = data.o entry.o tree.o message.o network_client.o network_server.o client_stub.o tree_client.o tree_server.o tree_skel.o sdmessage.pb-c.o test_data.o test_entry.o test_tree.o
OBJ_dir = object/
BIN_dir = binary/
INC_dir = include/
SRC_dir = source/
LIB_dir = lib/
PROTOC_dir = /usr/local/

CC = gcc
CFLAGS = -Wall -I $(INC_dir) -c
LDFLAGS = ${PROTOC_dir}lib/libprotobuf-c.a
cmd = $(CC) $(CFLAGS) $(SRC_dir)
protoc= protoc --c_out=.

out: $(OBJECTS) client-lib.o server-lib.o tree-client tree-server

protoc:
	$(protoc) sdmessage.proto
	mv sdmessage.pb-c.h $(INC_dir)
	mv sdmessage.pb-c.c $(SRC_dir)

sdmessage.pb-c.o: $(INC_dir)sdmessage.pb-c.h
									$(cmd)sdmessage.pb-c.c -o $(OBJ_dir)sdmessage.pb-c.o

data.o: $(INC_dir)data.h
		$(cmd)data.c -o $(OBJ_dir)data.o

entry.o: $(INC_dir)entry.h $(INC_dir)data.h
		$(cmd)entry.c -o $(OBJ_dir)entry.o

tree.o: $(INC_dir)tree.h $(INC_dir)tree-private.h $(INC_dir)data.h
		$(cmd)tree.c -o $(OBJ_dir)tree.o

test_data.o: $(INC_dir)data.h
			$(cmd)test_data.c -o $(OBJ_dir)test_data.o

test_entry.o: $(INC_dir)data.h $(INC_dir)entry.h
			$(cmd)test_entry.c -o $(OBJ_dir)test_entry.o

test_tree.o: $(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)tree.h
			$(cmd)test_tree.c -o $(OBJ_dir)test_tree.o

test_data: test_data.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_data $(SRC_dir)data.c $(SRC_dir)test_data.c
	$(BIN_dir)test_data

test_entry: test_entry.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_entry $(SRC_dir)entry.c $(SRC_dir)data.c $(SRC_dir)test_entry.c
	$(BIN_dir)test_entry

test_tree: test_tree.o
	$(CC) -Wall -I include/ -o $(BIN_dir)test_tree $(SRC_dir)tree.c  $(SRC_dir)entry.c  $(SRC_dir)data.c $(SRC_dir)test_tree.c
	$(BIN_dir)test_tree

message.o:$(INC_dir)message_private.h
		$(cmd)message.c -o $(OBJ_dir)message.o

network_client.o:$(INC_dir)client_stub_private.h $(INC_dir)sdmessage.pb-c.h $(INC_dir)client_stub.h
									$(cmd)network_client.c -o $(OBJ_dir)network_client.o

network_server.o:$(INC_dir)tree_skel.h
									$(cmd)network_server.c -o $(OBJ_dir)network_server.o

client_stub.o:$(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)client_stub_private.h
								$(cmd)client_stub.c -o $(OBJ_dir)client_stub.o

tree_client.o:$(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)tree.h $(INC_dir)sdmessage.pb-c.h $(INC_dir)client_stub.h $(INC_dir)network_client.h
									$(cmd)tree_client.c -o $(OBJ_dir)tree_client.o

tree_skel.o: $(INC_dir)tree.h $(INC_dir)sdmessage.pb-c.h
									$(cmd)tree_skel.c -o $(OBJ_dir)tree_skel.o

tree_server.o:$(INC_dir)data.h $(INC_dir)entry.h $(INC_dir)tree.h	$(INC_dir)tree_skel.h $(INC_dir)sdmessage.pb-c.h $(INC_dir)network_client.h $(INC_dir)client_stub.h
							 	 	$(cmd)tree_server.c -o $(OBJ_dir)tree_server.o

client-lib.o:
						ld -r $(OBJ_dir)data.o $(OBJ_dir)entry.o $(OBJ_dir)tree.o $(OBJ_dir)client_stub.o $(OBJ_dir)network_client.o $(OBJ_dir)message.o $(OBJ_dir)sdmessage.pb-c.o -o $(LIB_dir)client-lib.o

server-lib.o:
						ld -r $(OBJ_dir)data.o $(OBJ_dir)entry.o $(OBJ_dir)tree.o $(OBJ_dir)tree_skel.o $(OBJ_dir)network_server.o $(OBJ_dir)message.o $(OBJ_dir)sdmessage.pb-c.o -o $(LIB_dir)server-lib.o

tree-client:$(OBJ_dir)tree_client.o $(LIB_dir)client-lib.o
						$(CC) $(OBJ_dir)tree_client.o $(LIB_dir)client-lib.o -I $(INC_dir) -L $(LDFLAGS) -o $(BIN_dir)tree-client

tree-server:$(OBJ_dir)tree_server.o
						$(CC) $(OBJ_dir)tree_server.o $(LIB_dir)server-lib.o -I $(INC_dir) -L $(LDFLAGS) -o $(BIN_dir)tree-server
clean:
	    rm -f $(OBJ_dir)*.o
			rm -f $(BIN_dir)*
			rm -f $(LIB_dir)*
