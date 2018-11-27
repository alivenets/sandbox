
PROG = messagequeue

SOURCES = messagequeue.o main.o

CXXFLAGS = -std=c++14

LDFLAGS = -lboost_system -lboost_thread -lpthread

%.o: %.c
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all: $(PROG)

$(PROG): $(SOURCES)
	$(CXX) $^ -o $@ $(LDFLAGS)

clean: 
	rm $(PROG) *.o


.PHONY: clean