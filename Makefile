CC = gcc
CFLAGS = -g
CXX = g++
CXXFLAGS = -g -std=c++2a -fconcepts -I"json/include"
OPTIONS_DIR = options
OPTIONSH_NAME = optionsh
OPTIONSH_CXX_SOURCES = optionsh.cpp options/options++.cpp
OPTIONSH_C_SOURCES = options/options.c options/formatting.c
OPTIONSH_OBJECTS = optionsh.o options/options++.o options/options.o options/formatting.o
OPTIONSH_SCRIPT = optionsh.sh
DESTDIR = /usr/local

MAKEFILE_TARGETS_WITHOUT_INCLUDE := clean distclean

$(OPTIONSH_NAME): $(OPTIONSH_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OPTIONSH_OBJECTS)

clean: 
	rm -f $(OPTIONSH_OBJECTS) optionsh

distclean: clean
	rm -f .optionsh_c_depend
	rm -f .optionsh_cxx_depend

options/options++.o: options/options++.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

options/options.o: options/options.c
	$(CC) $(CFLAGS) -c -o $@ $^

options/formatting.o: options/formatting.c
	$(CC) $(CFLAGS) -c -o $@ $^

optionsh_cxx_depend: .optionsh_cxx_depend

.optionsh_cxx_depend: $(OPTIONSH_CXX_SOURCES)
	rm -f ./.optionsh_cxx_depend
	$(CXX) $(CXXFLAGS) -MM $^ > ./.optionsh_cxx_depend

optionsh_c_depend: .optionsh_c_depend

.optionsh_c_depend: $(OPTIONSH_C_SOURCES)
	rm -f ./.optionsh_c_depend
	$(CC) $(CFLAGS) -MM $^ > ./.optionsh_c_depend

# Include only if the goal needs it
ifeq ($(filter $(MAKECMDGOALS),$(MAKEFILE_TARGETS_WITHOUT_INCLUDE)),)
include .optionsh_cxx_depend
include .optionsh_c_depend
endif

install: $(OPTIONSH_NAME) $(OPTIONSH_SCRIPT)
	mkdir -p $(DESTDIR)/bin
	cp $(OPTIONSH_NAME) $(DESTDIR)/bin/$(OPTIONSH_NAME)
	cp $(OPTIONSH_SCRIPT) $(DESTDIR)/bin/$(OPTIONSH_SCRIPT)
