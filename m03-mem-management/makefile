TARGETS = shallow-copy stack-vs-heap ref-vs-pointer object-array show_memo pointer rule-of-3 rule-of-5
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
