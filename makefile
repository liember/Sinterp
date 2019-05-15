.PHONY: clean
CC = gcc
CFLAGS = -Wall -g -Wextra -Werror -Wshadow -MMD -MP 
DEPFLAGS = -MMD -MP
DEPDIR = dep/
OBJDIR = obj/
BINDIR = bin/
SRCDIR = src/
SRC_FILES := $(wildcard $(SRCDIR)*.c)
OBJ_FILES := $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC_FILES))
DEP_FILES := $(wildcard $(DEPDIR)*.d)
EXECUTABLE = $(BINDIR)main
 
 
.PHONY: all
all: dirs $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
 
$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CCFLAGS) $(DEPFLAGS) -c -o $@ $<
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d
 
dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR)
 
clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d
   
include $(DEP_FILES)
