TARGETS = shallow-copy stack-vs-heap ref-vs-pointer object-array show_memo pointer
CXXFLAGS = -Wall -std=c++14
RM = rm -rf

.PHONY: all clean

all : $(TARGETS)

$(TARGETS) : % : %.o
	g++ -o $@ $<

%.o : %.cpp
	g++ -c -o $@ $< $(CXXFLAGS)

clean :
	$(RM) $(TARGETS) *.o
