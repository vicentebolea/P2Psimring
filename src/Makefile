# Local makefile

SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

$(OBJECTS) : $(SOURCES)

all: packet lru $(OBJECTS)

packet:
	$(MAKE) -C $(SRCDIR)/packet

lru:
	$(MAKE) -C $(SRCDIR)/lru
