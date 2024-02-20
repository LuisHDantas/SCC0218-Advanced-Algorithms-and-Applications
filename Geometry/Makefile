CXX = g++
SRCS = problem.cpp  # Add your source files here
OBJS = $(SRCS:.cpp=.o)
EXEC = convex_hull

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)
