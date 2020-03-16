# On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
# Signed: Kim Woo Bin   Student Number: 21600124

CC = g++
SRCS = bubble.cpp insertion.cpp quicksort.cpp selection.cpp
OBJS = $(SRCSL.cpp=.o)
TARGET = libsort.a

$(TARGET): $(OBJS)
	ar cru $@ $^
	ranlib $@

$(OBJS): %.o: %.cpp
	$(CC) -c $< -o $@
	$(CC) -MM -MF $*.d $<
-include $(SRCS:.cpp=.d)
