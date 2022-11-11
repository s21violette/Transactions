FLAGS = g++ -g #-std=c++17 -Wall -Wextra -Werror
MAIN = ConsoleEngine/main.cpp
CONSOLE_ENGINE = ConsoleEngine/ConsoleEngine.cpp
HASH_TABLE = Databases/HashTable/HashTable.cpp
HASH_TABLE_BINARY = hash_table.out

all: hash_table_compile

hash_table: hash_table_compile
	./$(HASH_TABLE_BINARY)

hash_table_compile:
	$(FLAGS) -DHASHTABLE $(MAIN) $(CONSOLE_ENGINE) $(HASH_TABLE) -o $(HASH_TABLE_BINARY)