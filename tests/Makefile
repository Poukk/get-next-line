CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I.. -I$(MUNIT_DIR)
LIBS = -lm

# Directories
ROOT_DIR = ..
MUNIT_DIR = .

# Source files
GNL_SRCS = $(ROOT_DIR)/get_next_line.c $(ROOT_DIR)/get_next_line_utils.c
MUNIT_SRCS = $(MUNIT_DIR)/munit.c $(MUNIT_DIR)/main.c
SRCS = $(GNL_SRCS) $(MUNIT_SRCS)

# Object files
OBJS = $(notdir $(SRCS:.c=.o))

# Target executable
TARGET = test.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: $(ROOT_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f *~ $(ROOT_DIR)/*~

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
