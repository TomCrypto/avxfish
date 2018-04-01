#CC = clang
NASM = nasm

CFLAGS = -O3 -fPIC -g -Wall -Wextra -std=gnu99 -pedantic -mavx512f -mavx512vl
LDFLAGS = -static
INCLUDES = include
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

HEADERS = $(shell find $(INCLUDES) -name '*.h')

.PHONY: all
all: $(BINDIR)/bench $(BINDIR)/test

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

$(OBJDIR) $(BINDIR):
	mkdir $@

$(OBJDIR)/%.asm.o: $(SRCDIR)/%.asm | $(OBJDIR)
	$(NASM) -o $@ -f elf64 $<

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) -o $@  -I$(INCLUDES) $(CFLAGS) -c $<

$(BINDIR)/bench: $(OBJDIR)/avxfish.asm.o $(OBJDIR)/bench.c.o | $(BINDIR)
	$(CC) -o $@ $(LDFLAGS) $^

$(BINDIR)/test: $(OBJDIR)/avxfish.asm.o $(OBJDIR)/test.c.o | $(BINDIR)
	$(CC) -o $@ $(LDFLAGS) $^
