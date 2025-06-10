CXXFLAGS+=-std=c++17 -Wall -O2
CXX=g++

all: out out/hw7

run: out out/hw7
	./out/hw7

out/hw7: src/*.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/hw7
out:
	mkdir -p out

clean:
	rm -rf out
