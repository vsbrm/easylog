CXX = clang++
CXXFLAGS = -I. -std=c++17
DEPS = easylog.h
OBJ = easylog.o
W100OBJ = write_100times_test.o $(OBJ)
WRONGFNOBJ = wrong_filename_test.o $(OBJ)

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

all: w100test wrongfilenametest

w100test: $(W100OBJ)
	$(CXX) -o $@.out $^ $(CXXFLAGS)

wrongfilenametest: $(WRONGFNOBJ)
	$(CXX) -o $@.out $^ $(CXXFLAGS)
