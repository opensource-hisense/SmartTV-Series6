#########################################################
#
# XSD2C Examles Makefile
#
#########################################################

SHELL	= bash
CC	= gcc


VPATH	= . ../

EXECNAME= ex3.exe
XSDFILE = ex3.xsd
EXSRC	= ex3.c utils.c
GENSRC	= Person_xsd.c Customer_xsd.c

EXOBJ	= $(addsuffix .o, $(basename $(EXSRC)))
GENOBJ	= $(addsuffix .o, $(basename $(GENSRC)))
OBJECTS =  $(EXOBJ) $(GENOBJ) 
XSD2C	= ../../xsd2c

$(EXECNAME): stubs  $(GENSRC) $(OBJECTS) 
	$(CC) -g $(CFLAGS) -o $@ $(OBJECTS) $(CLIBS)

CFLAGS	= `xml2-config --cflags`
CLIBS	= `xml2-config --libs`


stubs:
	$(XSD2C)  -S $(XSDFILE) 

clean:
	-@rm -f *.o
	-@rm -f *_xsd.h
	-@rm -f *_xsd.c
	-@rm -f *~
	-@rm -f $(EXECNAME)
