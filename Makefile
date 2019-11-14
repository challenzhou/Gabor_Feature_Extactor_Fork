CXX = g++

CXXFLAGS += -c -g -Wall
LDFLAGS += $(shell pkg-config --libs --static opencv)

SRCS = main.cpp gaborfeature.cpp gaborwavelet.cpp
OBJS = $(subst .cpp,.o,$(SRCS))
OBJDIR = objects
OBJECTS = $(addprefix $(OBJDIR)/,$(OBJS))

EXECUTABLE = gabor_wavelet 

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -lstdc++

$(OBJECTS): $(OBJDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) -o $@ $< 

clean :
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
