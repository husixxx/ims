CXX = g++
CXXFLAGS = -std=gnu++11 -Wall -Wextra -pedantic
LDFLAGS = -lsimlib -lm
SRCS = main.cpp Vehicle.cpp PackageGenerator.cpp LoaderWorker.cpp Package.cpp
OBJS = $(SRCS:.cpp=.o)

ims.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) ims.out
all:
	clean ims.out
