all:test test1
LDFLAGS=-ljsoncpp

test:test.cc
	g++ -o $@ $^ $(LDFLAGS) -std=c++11
test1:test1.cc
	g++ -o $@ $^ $(LDFLAGS) -std=c++11

.PHONY:clean
clean:
	rm -f test test1 
