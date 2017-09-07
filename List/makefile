CXX = g++

IBOOST_DIR=C:/boost/boost_1_64_0
ICPPLIBS=C:/_cpplibs/include

LDIR=C:/boost/lib_64gcc/lib
LIBS=
IDIR=incl

CFLAGS=-O2 -Wall -Wextra -pedantic -std=c++14 -I$(IBOOST_DIR) -I$(ICPPLIBS) \
-I$(IDIR) -L$(LDIR) $(LIBS) -static


_DEPS = List.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

SDIR=src
_SRC = 
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

ODIR=obj
_OBJ = 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

TDIR=bin
_TARGET = 
TARGET = $(patsubst %,$(TDIR)/%,$(_TARGET)) 


TESTS_DIR=tests
_TESTS_DEPS =  
TESTS_DEPS = $(patsubst %,$(TESTS_DIR)/%,$(_TESTS_DEPS))
_TESTSO = List_tests.o
TESTSO = $(patsubst %,$(TESTS_DIR)/%,$(_TESTSO))

_TESTS = List_tests.exe
TESTS = $(patsubst %,$(TESTS_DIR)/%,$(_TESTS))

# if you want to compile libraries
LIBTARGET=build/libmain.lib
LIBSOTARGET=build/libmain.dll


all: $(TARGET) $(TESTS) # $(LIBTARGET) $(LIBSOTARGET)


# Compile the project
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)


# Compile tests
$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp $(DEPS) $(TESTS_DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(TESTS): $(TESTSO)
	$(CXX) -o $@ $^ $(CFLAGS)

# makes the target, first the .a file (ar) and then the library via ranlib
$(LIBTARGET): $(OBJ)
	ar rcs $@ $(OBJ)
	ranlib $@

$(LIBSOTARGET): $(LIBTARGET) $(OBJ)
	$(CXX) -shared -o $@ $(OBJ)


clean:
	rm -f $(ODIR)/*.* $(TDIR)/*.*
	rm -f $(TESTS_DIR)/*.o $(TESTS_DIR)/*.exe
	rm -f build/*.lib build/*.dll


.PHONY: all, clean
