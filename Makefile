CXX = g++
TARGET = hello

CXXFLAGS = -std=c++20
LDFLAGS = -lGLEW -lGL -lglfw

ODIR = bin

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=$(ODIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJS): $(ODIR)/%.o: %.cpp | $(ODIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR):
	mkdir -p $(ODIR)

clean:
	$(RM) -r $(ODIR)
	$(RM) $(TARGET)