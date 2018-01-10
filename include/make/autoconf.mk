#------------------------------------------------------------------------------
# Autoconf package helper include file
#
# When included from within a project makefile, will generate all the necessary
# targets and dependencies to generate an autoconf config.site file.
#
#------------------------------------------------------------------------------

export CONFIG_SITE := $(PREFIX_PATH)/share/config.site
export PKG_CONFIG_PATH := $(PREFIX_PATH)/lib/pkgconfig

configure.done: $(CONFIG_SITE)

$(CONFIG_SITE):
	@mkdir -p $(dir $@)
	@rm -f $@
	@echo 'CXXFLAGS="-I$(PREFIX_PATH)/include $(CXXFLAGS)"' >>$@
	@echo 'CFLAGS="-I$(PREFIX_PATH)/include $(CFLAGS)"' >>$@
	@echo 'LDFLAGS=-L$(PREFIX_PATH)/lib' >>$@
