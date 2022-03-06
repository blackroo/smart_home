TARGET = server


INCLUDE += -I./header
#CCFLAGS += -O3 -g -Wall $(INCLUDE) -DUCLIB -D_GNU_SOURCE -DROUTER
CCFLAGS += $(INCLUDE)


SRCS = $(shell find -type f -name "*.c" -print)
OBJS = $(SRCS:%.c=%.o)

.c.o:
	gcc $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS)

all:$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET).gdb $(TARGET)

