CXXFLAGS+=-std=c++17 -Wall -O2
CXX=g++

all: out out/hw6

run: out out/hw6
	./out/hw6

out/hw6: src/hw6.cpp src/BigIntegerAlgorithms.cpp src/BigIntegerReload.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/hw6
out:
	mkdir -p out

clean:
	rm -rf out
