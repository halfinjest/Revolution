ifeq ($(strip $(DEVKITPPC)),)
$(error "Set the DEVKITPPC path: export DEVKITPPC=<path to devkitPPC>")

endif

.SUFFIXES:

include $(DEVKITPPC)/wii_rules
TARGET		=	$(notdir $(CURDIR))
BUILD		=	build
SOURCES		=	source
DATA		=	data
INCLUDES	=	include
CFLAGS		=	-g -O2 -Wall $(MACHDEP) $(INCLUDE)
LDFLAGS		=	-g $(MACHDEP) -Wl,-Map,$(notdir $@).map
LIBS		=	-lwiiuse -lbte -logc -lm
LIBDIRS		=

ifneq ($(BUILD),$(notdir $(CURDIR)))
export OUTPUT	=	$(CURDIR)/$(TARGET)
export VPATH	=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
	$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR	=	$(CURDIR)/$(BUILD)
CFILES		=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
export LD = $(CC)
export OFILES	=	$(CFILES:.c=.o)
export INCLUDE	=	$(foreach dir,$(INCLUDES), -iquote $(CURDIR)/$(dir)) \
	$(foreach dir,$(LIBDIRS),-I$(dir)/include) -I$(CURDIR)/$(BUILD) \
	-I$(LIBOGC_INC)
export LIBPATHS	=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) -L$(LIBOGC_LIB)
export OUTPUT	=	$(CURDIR)/$(TARGET)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean: @rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

run: wiiload $(TARGET).dol

else
DEPENDS = $(OFILES:.o=.d)

$(OUTPUT).dol: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES)

-include $(DEPENDS)

endif
