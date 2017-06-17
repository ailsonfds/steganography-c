BINDIR = bin
SRCDIR = src
INCLUDEDIR = include
APPDIR = application
OBJDIR = build
TESTDIR = test

CC = gcc
CFLAGS = -O3 -Wall -ansi -pedantic -I $(INCLUDEDIR)
LDFLAGS =

BIN = ${BINDIR}/steg
APP = ${APPDIR}/main.c

SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
APPOBJ = $(patsubst $(APPDIR)/%.c,$(OBJDIR)/%.o,$(APP))

_TESTS = $(wildcard $(TESTDIR)/*.c)
TESTS = $(patsubst %.c,%,$(_TESTS))

$(BIN): $(OBJS) $(APPOBJ)
	$(CC) -o $(BIN) $(APPOBJ) $(OBJS) $(CFLAGS) $(LDFLAGS)

$(APPOBJ): $(APP)
	$(CC) -c -o $@ $< $(CFLAGS)

${OBJDIR}/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TESTS) 
	$(info ************  Testes concluídos com sucesso! ************)

$(TESTDIR)/t_%: $(TESTDIR)/t_%.c $(OBJS)
	$(CC) -o $@ $< $(OBJS) $(CFLAGS) $(LDFLAGS)
	$@

execute:
	./$(BIN)

clean:
	rm -f $(BIN) $(OBJS) $(APPOBJ)
	rm -f $(TESTS) $(LDFLAGS)
