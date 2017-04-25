#created by wang hongrong
CC:=g++
AR:=ar -crs
        
#----------target sets
CURRENT_DIR=$(shell pwd)
SRC_DIR = $(CURRENT_DIR)
DEPS_DIR = $(CURRENT_DIR)/deps
OBJS_DIR = $(CURRENT_DIR)/objs
BIN_DIR = $(CURRENT_DIR)
LIB_DIR = $(CURRENT_DIR)
PRONAME=test                                                                                                                                                                                                
DYNAMICS = $(PRONAME:%=lib%.so)
STATICS = $(PRONAME:%=lib%.a)

EXTENSION=cpp

#-------去除重复，并源文件的查找路径
ALL_SRC_DIR=$(sort $(dir $(shell find $(SRC_DIR) -name *.$(EXTENSION))))
vpath %.cpp $(ALL_SRC_DIR)
        
#------------Objs file path
#------------利用shell命令查找所有源文件
ALL_SRCS=$(notdir $(shell find $(SRC_DIR) -name *.$(EXTENSION)))
OBJS=$(ALL_SRCS:%.cpp=$(OBJS_DIR)/%.o) 
DEPS=$(ALL_SRCS:%.cpp=$(DEPS_DIR)/%.d) 
        
#---------search path
INCDIR:=-I. -I..
LIBDIR:=-L. -L.. 
LIBS:=
        
#---------default flags
CPPFLAGS:=-D__LINUX__ -Wall -Wno-non-virtual-dtor -g -funsigned-char -D_unix_ -DLINUX  $(INCDIR)
LDFLAGS:=$(LIBDIR) $(LIBS)
        
.PHONY: all rebuild clean
        
#---------make action
all:$(PRONAME)
        
$(PRONAME):$(OBJS)
    @echo $(ALL_SRC_DIR)
    $(CC) -o $@ $^ $(LDFLAGS)
        
$(DYNAMICS):$(OBJS)
    $(CC) -shared -fPIC $(LDFLAGS) $^ $(LIBS) -o $@
        
$(STATICS):$(OBJS)
    $(AR) -o $@ $^
        
$(DEPS_DIR)/%.d:%.$(EXTENSION)
    $(CC) -MM $(INCDIR) $(CPPFLAGS) $< | sed -e 1's,^,$(OBJS_DIR)/,' > $@
        
sinclude $(DEPS)

$(OBJS_DIR)/%.o: %.$(EXTENSION)
        $(CC) $< -o $@ -c $(CPPFLAGS) $(INCDIR)

rebuild: clean all

clean:
        rm -rf $(OBJS) $(DEPS) $(PRONAME) $(DYNAMICS) $(STATICS)
