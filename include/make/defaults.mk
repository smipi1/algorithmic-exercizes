SUPPORTED_BUILDS=debug release
export BUILD ?= $(firstword $(SUPPORTED_BUILDS))
BUILD_DIR ?= $(abspath build_dir/$(BUILD))
export STAGING_DIR ?= $(abspath staging_dir/$(BUILD))
export PREFIX_PATH := $(STAGING_DIR)/usr/local
export PATH := $(PREFIX_PATH)/bin:$(PATH)

export DEPLOYMENT_DIR ?= $(abspath output/$(BUILD))
export DEPLOYMENT_EXCLUDES ?= \
  cmake \
  *.cmake \
  *.a \
  *.h \
  *.hpp \
  *.o \
  *.pump

ifneq ($(findstring $(BUILD),$(SUPPORTED_BUILDS)), $(BUILD))
$(error error: BUILD=$(BUILD) not supported. Valid values are: $(SUPPORTED_BUILDS))
endif

CFLAGS += -ggdb
CXXFLAGS += -ggdb

ifeq ($(BUILD),debug)
  CFLAGS += -O0
  CXXFLAGS += -O0
else
  CFLAGS += -O2
  CXXFLAGS += -O2
endif

export CFLAGS
export CXXFLAGS
export LDFLAGS += -L$(PREFIX_PATH)/lib
export LD_LIBRARY_PATH := $(PREFIX_PATH)/lib:$(LD_LIBRARY_PATH)

MAKE_INCLUDE_DIR ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
STAGING_TOOLS_DIR := $(MAKE_INCLUDE_DIR)/../tools/staging
