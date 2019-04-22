CXX = g++
LIBFLAGS = -lglut -lGLU -lGL
DEPS = camera.h polygon.h
OBJ = rjex_project5.o camera.o polygon.o

all: rjex_project5

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(LIBFLAGS)

rjex_project3: $(OBJ)
	$(CXX) -o $@ $^ $(LIBFLAGS)

clean:
	rm -f $(OBJ)
