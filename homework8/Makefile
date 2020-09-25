CFLAGS = -std=c99 -Wall -pedantic -Wextra -Werror -O2 -Wstrict-prototypes -Wold-style-definition -g 
OBJECTS = todo.o todo_helpers.o todo_data.o
todo: $(OBJECTS) 
	gcc $(CFLAGS) -o todo $(OBJECTS) 
$(OBJECTS): todo.h