CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++11
LDFLAGS=
LDLIBS=-lm -lpthread

SRCS=MQTTSim.cpp Message.cpp SimClient.cpp SimPublisher.cpp Broker.cpp Client.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: MQTTSim

MQTTSim: $(OBJS)
	$(CXX) $(LDFLAGS) -o MQTTSim $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) MQTTSim

distclean: clean
	$(RM) *~ .depend

include .depend
