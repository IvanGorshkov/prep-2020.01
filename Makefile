TARGET = main.out
TEST_TARGET = test.out
HDRS_DIR = project/include/
SRCS = \
	project/src/main.c\
	project/src/filemodule.c\
	project/src/menu.c
TEST_SRC = \
	project/src/test.c\
	project/src/filemodule.c\
	project/src/menu.c\
	project/src/test_func.c

.PHONY: all clean

all: main test
	
main: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)
test: $(TEST_SRC)
	$(CC) -I$(HDRS_DIR) -Wall -Wextra -Werror -o $(TEST_TARGET) $(CFLAGS) $(TEST_SRC)

clean:
	rm -rf $(TARGET)
	rm -rf $(TEST_TARGET) 