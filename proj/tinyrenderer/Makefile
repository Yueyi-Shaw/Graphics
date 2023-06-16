SYSCONF_LINK = g++
CPPFLAGS     =
LDFLAGS      =
LIBS         = -lm

DESTDIR = build/
TARGET  = main

OBJECTS := $(patsubst src%.cpp,$(DESTDIR)%.o,$(wildcard src/*.cpp))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(DESTDIR)%.o: src/%.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga

