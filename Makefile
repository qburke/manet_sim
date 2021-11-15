CXX := g++
CXX_FLAGS := -Wall

BIN := bin
SRC := src
INCLUDE := include
LIBRARIES := -lSDL2
EXECUTABLE := sim

run: clean all
	./$(BIN)/$(EXECUTABLE)

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE) : $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*