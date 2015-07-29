appname := aise

CXX := g++
CXXFLAGS := -std=c++11 -iquote src/ -iquote src/values/ -iquote src/runtime/ -iquote src/interpreter -iquote src/tests/

srcfiles := $(shell find . -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
		rm -f ./.depend
		$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
		rm -f $(objects)

dist-clean: clean
		rm -f *~ .depend

test: all
	./aise

include .depend
