CC=g++
CXXFLAGS=-Wall -std=c++11

TARGET	:= ChessboardTour

IDIR	:= include
SDIR	:= source
BDIR	:= .build

INC		:= $(wildcard $(IDIR)/engine/*.h)
ENGINE_OBJ	:= $(patsubst $(SDIR)/engine/%.cpp, $(BDIR)/%.o, $(wildcard $(SDIR)/engine/*.cpp))
MAIN_OBJ	:= $(patsubst $(SDIR)/%.cpp, $(BDIR)/%.o, $(wildcard $(SDIR)/*.cpp))

.PHONY: all clean

all: bdir $(TARGET)

bdir:
	mkdir -p $(BDIR)

$(BDIR)/%.o: $(SDIR)/engine/%.cpp $(INC)
	$(CC) -o $@ $< -c $(CXXFLAGS) -I$(IDIR)

$(BDIR)/%.o: $(SDIR)/%.cpp $(INC)
	$(CC) -o $@ $< -c $(CXXFLAGS) -I$(IDIR)

$(TARGET): $(ENGINE_OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ -lncurses

clean:
	rm -f $(BDIR)/*.o $(TARGET)
	rm -rf $(BDIR)
