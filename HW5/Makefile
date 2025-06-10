CXXFLAGS+=-std=c++17 -Wall -O2
CXX=g++

all: out out/hw5

run: out out/hw5
	./out/hw5

out/hw5: src/hw5.cpp src/SplayTree.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/hw5
out:
	mkdir -p out

clean:
	rm -rf out
