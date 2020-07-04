
MODEL_FILE = sram8x256.h wb_slave_if.h wb_sram.h
TESTBENCH_FILE = tb.h
TOP_FILE = main.cpp

INC_FILES = $(TESTBENCH_FILE) $(MODULE_FILE) 
SRC_FILES = $(TOP_FILE)
OBJ_FILES = main.o
EXE_FILE = main.exe

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

##$(OBJ_FILES) : %.o : %.cpp
##	$(CPP) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_FILES) : $(INC_FILES) $(SRC_FILES)
	$(CPP) $(IFLAGS) $(CFLAGS) -c $(SRC_FILES) -o $@
	
test: build run

build: $(SRC_FILES) $(OBJ_FILES)
	$(CPP)   $(CFLAGS)   -o $(EXE_FILE)   $(OBJ_FILES)   $(LFLAGS) 

run: $(OBJ_FILES)
	./$(EXE_FILE)

clean: 
	rm -rf $(OBJ_FILES) $(EXE_FILE) log

