CXX = g++
CXXFLAGS = -std=c++20 -O2

all: _gen.exe _val.exe _run.exe

_gen.exe: gen.cpp
	$(CXX) $(CXXFLAGS) gen.cpp -o _gen.exe

_val.exe: val.cpp
	$(CXX) $(CXXFLAGS) val.cpp -o _val.exe

_run.exe: run.cpp
	$(CXX) $(CXXFLAGS) run.cpp -o _run.exe

gen_input: _gen.exe
	./_gen.exe

check: _val.exe
	./_val.exe

gen_output: _run.exe
	./_run.exe

gen: gen_input check gen_output

clean:
	rm -f _gen.exe _val.exe _run.exe
	rm -f ../data/secret/*.in ../data/secret/*.ans

.PHONY: all gen_input gen_output check gen clean