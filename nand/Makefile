
MODEL_FILE = nand.cpp
TESTBENCH_FILE = tb.cpp
TOP_FILE = main.cpp

SRC_FILES = nand.cpp tb.cpp main.cpp
OBJ_FILES = nand.o tb.o main.o
EXE_FILE = nand.exe

CPP = g++
SC_LIB = /home/user/workspace/systemc-2.2.0/lib-linux64
SC_INC = /home/user/workspace/systemc-2.2.0/include
SR_INC = .

ifdef DEBUG
DEBUG_OPT = -O0
else
DEBUG_OPT = -O3
endif

WARNING_SHOW = -Wall

DEFINE_SC_INCLUDE_FX = -DSC_INCLUDE_FX

IFLAGS = -I$(SR_INC) -I$(SC_INC)
CFLAGS = $(WARNING_SHOW) $(DEFINE_SC_INCLUDE_FX) $(DEBUG_OPT)
LFLAGS = -L$(SC_LIB) -lsystemc -lm

$(OBJ_FILES) : %.o : %.cpp
	$(CPP) $(IFLAGS) $(CFLAGS) -c $< -o $@

build: $(SRC_FILES) $(OBJ_FILES)
	$(CPP)   $(CFLAGS)   -o $(EXE_FILE)   $(OBJ_FILES)   $(LFLAGS) 

run: $(OBJ_FILES)
	./$(EXE_FILE)

clean: 
	rm -rf $(OBJ_FILES) $(EXE_FILE)

