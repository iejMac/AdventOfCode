CXX = g++
CPPFLAGS = -Wall -g -std=c++11

all: output
	-@echo "--= All targets built! =--"

output: day8.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	-@rm -f output
	-@echo "--= Clean =--"
