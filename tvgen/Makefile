CPP = g++
CFLAGS = -std=c++11
IPATH = ${XILINX_VIVADO}/include/
OBJ = tvgen.o ../common/APxLinkData.o

all: check-env tvgen

check-env:
ifndef XILINX_VIVADO
	$(error XILINX_VIVADO is not set)
endif

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I $(IPATH)

tvgen: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS)

clean:
	rm -f tvgen *.o ../common/*.o
