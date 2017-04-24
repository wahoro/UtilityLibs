#-----created by cai jingnan ----2012-06-08 #model single-target of libs
CC:=g++
AR:=ar -crs

#----------target sets
CURRENT_DIR=$(shell pwd)
SRC_DIR = $(CURRENT_DIR)
DEPS_DIR = $(CURRENT_DIR)
OBJS_DIR = $(CURRENT_DIR)
BIN_DIR = $(CURRENT_DIR)
LIB_DIR = $(CURRENT_DIR)
PRONAME=fileagent
DYNAMICS = $(PRONAME:%=lib%.so)
STATICS = $(PRONAME:%=lib%.a)

##############Objs file path
EXTENSION=cpp
OBJS=$(patsubst $(SRC_DIR)/%.$(EXTENSION), $(OBJS_DIR)/%.o, $(wildcard $(SRC_DIR)/*.$(EXTENSION)))
DEPS=$(patsubst $(OBJS_DIR)/%.o, $(DEPS_DIR)/%.d, $(OBJS))

#---------search path
INCDIR:=-I. -I.. -I../../../../Library/Include
LIBDIR:=-L. -L.. -L./ChangeDat -L./IniFile
LIBS:=-lInifile -lChangeDat -lcurl -lrt -lpthread

#---------default flags
CPPFLAGS:=-D__LINUX__ -Wall -Wno-non-virtual-dtor -g -funsigned-char -D_unix_ -DLINUX  $(INCDIR)
LDFLAGS:=$(LIBDIR) $(LIBS)

.PHONY: all rebuild clean

#---------make action
all:$(PRONAME)

$(PRONAME):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DYNAMICS):$(OBJS)
	$(CC) -shared -fPIC $(LDFLAGS) $^ $(LIBS) -o $@

$(STATICS):$(OBJS)
	$(AR) -o $@ $^

$(DEPS_DIR)/%.d: $(SRC_DIR)/%.$(EXTENSION)
	$(CC) -MM $(INCDIR) $(CPPFLAGS) $< | sed -e 1's,^,$(OBJS_DIR)/,' > $@

sinclude $(DEPS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.$(EXTENSION)
	$(CC) $< -o $@ -c $(CPPFLAGS) $(INCDIR)

rebuild: clean all

clean:
	rm -rf $(OBJS) $(DEPS) $(PRONAME) $(DYNAMICS) $(STATICS)

