CC=g++
CFLAGS=-g -std=c++17 -Iinclude

SRCDIR = src
INCDIR = include
BUILDDIR = build

SRCEXT = cc
HEADEREXT = h

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
HEADERS := $(shell find $(INCDIR) -type f -name *.$(HEADEREXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

EXECUTABLE = BinaryTree

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(CFLAGS) -lm

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

DEPS := $(OBJECTS:.o=.d)
-include $(DEPS)

$(BUILDDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@$(CC) -MM -MT '$(BUILDDIR)/$*.o' $< $(CFLAGS) > $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean

clean:
	@rm -rf $(BUILDDIR) $(EXECUTABLE)
	@echo "Make clean: ¡Limpieza realizada con éxito!"
