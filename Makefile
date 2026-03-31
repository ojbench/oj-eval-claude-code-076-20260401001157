CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

# Since src.hpp is header-only, we create a dummy target
# The OJ will provide its own main.cpp that includes src.hpp
code:
	@echo "Header-only library - OJ will compile with its own main.cpp"
	@touch code

.PHONY: clean
clean:
	rm -f code
