CPP = g++
CFLAGS = -std=c++11
IPATH = ${XILINX_VIVADO}/include/
IROOT = -g -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore
OBJ = tvgen.o ../common/APxLinkData.o

all: check-env tvgen

check-env:
ifndef XILINX_VIVADO
	$(error XILINX_VIVADO is not set)
endif

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I $(IPATH) ${IROOT}

tvgen: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS) ${IROOT}

clean:
	rm -f tvgen *.o ../common/*.o
