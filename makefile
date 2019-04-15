CXX=g++
LIBFLAGS=-lglut -lGLU -lGL
DEPS = camera.h cube.h
OBJ = rjex_project4.o camera.o cube.o

all: rjex_project4

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(LIBFLAGS)

rjex_project3: $(OBJ)
	$(CXX) -o $@ $^ $(LIBFLAGS)

clean:
	rm -f $(OBJ)
