#------------------------------------------------------------------------------
# Package dependency helper include file
#
# When included from within a project makefile, add clean and configure
# dependencies for all packages specified with PACKAGE_DEPS in the including
# Makefile
#
# To use:
# 1. Define PACKAGE_DEPS in your makefile and include this file
# 2. Use the exposed cleanall make target
#
#------------------------------------------------------------------------------

INSTALLED_DIR ?= $(STAGING_DIR)/.installed

PACKAGE_DEPS_INSTALLED := $(foreach p,$(PACKAGE_DEPS),$(p).installed)
PKG_DEPS_EXECUTE_UNITTESTS ?= 0

define install_done
	@mkdir -p $(INSTALLED_DIR)
	@touch $(INSTALLED_DIR)/$(notdir $@)
endef

vpath %.installed $(INSTALLED_DIR)

.SECONDEXPANSION:
%.installed: $(BUILD_IF_FORCED) $$(call git_watched_in,$$*)
	$(call stepinfo)
	@mkdir -p $(STAGING_DIR)
	@$(MAKE) -C $(TOP_DIR)/$(notdir $*) install STAGING_DIR=$(STAGING_DIR) EXECUTE_UNITTESTS=$(PKG_DEPS_EXECUTE_UNITTESTS)
	$(call install_done)

configure.done: $(PACKAGE_DEPS_INSTALLED)

.PHONY : %.clean
%.clean:
	$(call stepinfo)
	-$(MAKE) -C $(TOP_DIR)/$* clean

.PHONY : cleanall
cleanall: $(foreach p,$(PACKAGE_DEPS),$(p).clean) clean
	-rm -rf $(STAGING_DIR)
	-rm -rf $(DEPLOYMENT_DIR)

