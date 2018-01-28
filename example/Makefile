export EXECUTE_UNITTESTS ?= 1

TOP_DIR:=\
  $(abspath ..)

INCLUDE_DIR:=\
  $(TOP_DIR)/include/make

include $(INCLUDE_DIR)/defaults.mk

PKG_SOURCE_DIR:=\
  $(abspath .)

PKG_NAME:=\
  $(notdir $(abspath .))

PACKAGE_DEPS:=\
  googletest \

include $(INCLUDE_DIR)/utils.mk
include $(INCLUDE_DIR)/packageDeps.mk
include $(INCLUDE_DIR)/package/cmake.mk
include $(INCLUDE_DIR)/coverage.mk

.PHONY: compile.done

.PHONY: check-stimulus
check-stimulus: all
	@$(STAGING_DIR)/set-env $(BUILD_DIR)/$(PKG_NAME)/example < stimulus.txt
