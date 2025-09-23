CXX = g++
CXXFLAGS = -std=c++20

all: _input.exe _output.exe _input_validator.exe gen

_input.exe: input.cpp
	$(CXX) $(CXXFLAGS) input.cpp -o _input.exe

_output.exe: output.cpp
	$(CXX) $(CXXFLAGS) output.cpp -o _output.exe

_input_validator.exe: input_validator.cpp
	$(CXX) $(CXXFLAGS) input_validator.cpp -o _input_validator.exe

gen_input: _input.exe
	./_input.exe

gen_output: _output.exe
	./_output.exe

check: _input_validator.exe
	./_input_validator.exe

gen: gen_input check gen_output

clean:
	rm -f _input.exe _output.exe _input_validator.exe
	rm -f ../data/secret/*.in

.PHONY: all gen_input gen_output check gen clean