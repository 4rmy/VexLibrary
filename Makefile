CEXTS:=c
ASMEXTS:=s S
CXXEXTS:=cpp c++ cc

ROOT=.
FWDIR:=$(ROOT)/firmware
BINDIR=$(ROOT)/bin
SRCDIR=$(ROOT)/src
INCDIR=$(ROOT)/include

WARNFLAGS+=
EXTRA_CFLAGS=
EXTRA_CXXFLAGS=

USE_PACKAGE:=1

EXCLUDE_COLD_LIBRARIES:= 

IS_LIBRARY:=1
-include ./library.mk

EXCLUDE_SRC_FROM_LIB+=$(foreach file, $(SRCDIR)/main,$(foreach cext,$(CEXTS),$(file).$(cext)) $(foreach cxxext,$(CXXEXTS),$(file).$(cxxext)))

TEMPLATE_FILES=$(INCDIR)/$(LIBNAME)/*.hpp $(INCDIR)/$(LIBNAME)/subs/*.hpp $(INCDIR)/$(LIBNAME)/utils/*.hpp

.DEFAULT_GOAL=quick

-include ./common.mk
