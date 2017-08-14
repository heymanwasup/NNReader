PROGNAME      = main
SRCDIR		  = $(PWD)/src
INCDIR        = $(PWD)/include
LIBDIR		  = $(PWD)/lib
rwildcard	  = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS 		  = $(call rwildcard,$(SRCDIR)/,*.cxx)
INCLUDES	  = $(call rwildcard,$(INCDIR)/,*.h)
LDFLAGS		= 	

OBJS		  = $(patsubst %.cxx, %.o, $(SRCS))
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --nonew --libs)
CFLAGS        = -O2 -Wall -fPIC -I$(INCDIR) -g $(ROOTCFLAGS)
LIBS          = -L$(LIBDIR) $(ROOTLIBS) -lMinuit -lTMVA -llwtnn
$(PROGNAME):    $(OBJS)
#g++ -static $^ $(LDFLAGS) $(LIBS) -o $@
	g++ -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
%.o : %.cxx $(INCLUDES)
	g++ ${CFLAGS} -c  -g -o $@ $<
clean:	
	-rm -f ${PROGNAME} ${OBJS}
