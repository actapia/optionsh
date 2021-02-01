CC = gcc
CFLAGS = -g
CXX = g++
CXXFLAGS = -g -std=c++2a -fconcepts -I"json/include"
OPTIONS_DIR = options
OPTIONSH_NAME = optionsh
OPTIONSH_CXX_SOURCES = optionsh.cpp options/options++.cpp
OPTIONSH_C_SOURCES = options/options.c options/formatting.c
OPTIONSH_OBJECTS = optionsh.o options/options++.o options/options.o options/formatting.o

optionsh: $(OPTIONSH_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OPTIONSH_OBJECTS)

clean: 
	rm -f $(OPTIONSH_OBJECTS) optionsh

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

include .optionsh_cxx_depend
include .optionsh_c_depend
