# =================== SETTINGS ===================
EXENAME := finalProject
TEST_NAME := run_tests

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

all : $(EXENAME) $(TEST_NAME)

$(EXENAME): build/main.o build/graph.o build/node.o build/edge.o
	$(LD) $^ $(LDFLAGS) -o $@

$(TEST_NAME): build/tests.o build/graph.o build/node.o build/edge.o
	$(LD) $^ $(LDFLAGS) -o $@

build/tests.o: catch/catchmain.cpp test/tests.cpp graph/flightGraph.h graph/node.h graph/edge.o 
	$(CXX) $(CXXFLAGS) $< -o $@

build/main.o: graph/main.cpp graph/flightGraph.h graph/node.h graph/edge.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@
	
build/graph.o: graph/flightGraph.cpp $(ALL_HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@

build/node.o: graph/node.cpp $(ALL_HEADERS) 
	$(CXX) $(CXXFLAGS) $< -o $@

build/edge.o: graph/edge.cpp $(ALL_HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build/ $(EXENAME)
