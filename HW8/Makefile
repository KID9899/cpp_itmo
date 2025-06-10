CXXFLAGS+=-std=c++17 -Wall -O2
CXX=g++

all: out out/hw8

run: out out/hw8
	./out/hw8

out/hw8: src/*.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/hw8
out:
	mkdir -p out

clean:
	rm -rf out
