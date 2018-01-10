#########################################################
#
# XSD2C Examles Makefile
#
#########################################################

SHELL	= bash
CC	= gcc


VPATH	= . ../

EXECNAME= ex1.exe
XSDFILE = ex1.xsd
EXSRC	= ex1.c utils.c
GENSRC	= Person_xsd.c

EXOBJ	= $(addsuffix .o, $(basename $(EXSRC)))
GENOBJ	= $(addsuffix .o, $(basename $(GENSRC)))
OBJECTS =  $(EXOBJ) $(GENOBJ) 
XSD2C	= ../../xsd2c

CFLAGS	= `xml2-config --cflags`
CLIBS	= `xml2-config --libs`

$(EXECNAME): stubs  $(GENSRC) $(OBJECTS) 
	$(CC) -g $(CFLAGS) -o $@ $(OBJECTS) $(CLIBS)


stubs:
	$(XSD2C) -S $(XSDFILE) 

clean:
	-@rm -f *.o
	-@rm -f *_xsd.h
	-@rm -f *_xsd.c
	-@rm -f *~
	-@rm -f $(EXECNAME)
