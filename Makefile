# =================== SETTINGS ===================
EXENAME := finalProject
TEST_NAME := run_tests
ANIMATION_NAME := run_animation

CXX			:=	clang++
CXXFLAGS	:=	$(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic -Iheaders
LD			:=	clang++
LDFLAGS		:=	-std=c++1y -stdlib=libc++ -lc++abi -lm -Iheaders
ALL_HEADERS	:=	graph/flightGraph.h graph/node.h  graph/edge.h 
#----------------------------------------------

define make-build-dir
	@mkdir -p build
endef 

.PHONY: all-data all clean

# $^ = all dependencies
# $< = first dependency
# $@ = target

all : $(EXENAME) $(TEST_NAME) $(ANIMATION_NAME)

####################### executables #########################

$(EXENAME): build/main.o build/graph.o build/node.o build/edge.o
	$(LD) $^ $(LDFLAGS) -o $@

$(TEST_NAME): build/tests.o build/catch.o build/graph.o build/node.o build/edge.o
	$(LD) $^ $(LDFLAGS) -o $@

$(ANIMATION_NAME): drawandalgorithms.cpp build/graph.o build/node.o build/edge.o build/algorithms.o build/lab_inheritance/PNG.o build/lab_inheritance/circle.o build/lab_inheritance/vector2.o build/lab_inheritance/HSLAPixel.o build/lab_inheritance/shape.o build/lab_inheritance/line.o build/lab_inheritance/lodepng.o
	$(LD) $^ $(LDFLAGS) -o $@

####################### cs225 files #########################

build/lab_inheritance/circle.o: lab_inheritance/circle.cpp build/lab_inheritance/HSLAPixel.o build/lab_inheritance/PNG.o build/lab_inheritance/shape.o
	$(CXX) $(CXXFLAGS) $< -o $@

build/lab_inheritance/shape.o: lab_inheritance/shape.cpp build/lab_inheritance/HSLAPixel.o build/lab_inheritance/vector2.o
	$(CXX) $(CXXFLAGS) $< -o $@

build/lab_inheritance/line.o: lab_inheritance/line.cpp build/lab_inheritance/HSLAPixel.o build/lab_inheritance/vector2.o build/lab_inheritance/PNG.o
	$(CXX) $(CXXFLAGS) $< -o $@
	
build/lab_inheritance/PNG.o: lab_inheritance/PNG.cpp build/lab_inheritance/HSLAPixel.o build/lab_inheritance/lodepng.o
	$(CXX) $(CXXFLAGS) $< -o $@

build/lab_inheritance/lodepng.o: lab_inheritance/lodepng.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

build/lab_inheritance/vector2.o: lab_inheritance/vector2.cpp build/lab_inheritance/HSLAPixel.o
	$(CXX) $(CXXFLAGS) $< -o $@

build/lab_inheritance/HSLAPixel.o: lab_inheritance/HSLAPixel.cpp build/lab_inheritance
	$(CXX) $(CXXFLAGS) $< -o $@

build/lab_inheritance: build
	mkdir build/lab_inheritance

####################### Our files #########################

build/algorithms.o: algorithms.cpp build/graph.o build/node.o build/edge.o build
	$(CXX) $(CXXFLAGS) $< -o $@

build/tests.o: test/tests.cpp build/catch.o graph/flightGraph.h graph/node.h graph/edge.o build
	$(CXX) $(CXXFLAGS) $< -o $@

build/catch.o: catch/catchmain.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

build/main.o: graph/main.cpp graph/flightGraph.h graph/node.h graph/edge.h build
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@
	
build/graph.o: graph/flightGraph.cpp $(ALL_HEADERS) build
	$(CXX) $(CXXFLAGS) $< -o $@

build/node.o: graph/node.cpp $(ALL_HEADERS) build
	$(CXX) $(CXXFLAGS) $< -o $@

build/edge.o: graph/edge.cpp $(ALL_HEADERS) build
	$(CXX) $(CXXFLAGS) $< -o $@

build:
	mkdir build

clean:
	rm -rf build/ $(EXENAME) $(ANIMATION_NAME) $(TEST_NAME)
