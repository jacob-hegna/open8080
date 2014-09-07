BUILDDIR    = ./bin/
SOURCEDIR   = ./src/

DEFINES     =

SDIRS       = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(SDIRS):$(foreach dir, $(SDIRS), $(wildcard $(dir)*/))

IFILES      = $(shell find $(SOURCEDIR) -name '*.c')

OFILES      = $(subst $(SOURCEDIR),  $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR)  -name '*.c'))))

CC          = gcc
LINKER      = $(CC)
ARCH        = 64

CCFLAGS     = -c -g -w -O3 -m$(ARCH)
LINKFLAGS   = -m$(ARCH)


TARGET = open8080

all: $(TARGET)

$(TARGET): $(foreach file, $(OFILES), $(BUILDDIR)$(file))
	$(LINKER) $^ $(LINKFLAGS) -o $(BUILDDIR)$@

$(BUILDDIR)%.c.o: %.c
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $@


.PHONY: clean
clean:
	rm $(BUILDDIR)*
	rm $(TARGET)
