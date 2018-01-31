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

INPUT_FILES:= \
  data.in \
  B-small-practice.in \
  B-large-practice.in

OUTPUT_FILES:=\
  $(patsubst %.in,%.out,$(INPUT_FILES))

.PHONY: check-stimulus
check-stimulus: $(OUTPUT_FILES)

.SECONDEXPANSION:
.PHONY: %.out
%.out: $$*.in all
	$(STAGING_DIR)/set-env $(BUILD_DIR)/$(PKG_NAME)/ratatouille <$< | tee $@
