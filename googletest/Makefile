
PLATFORM_DIR ?= $(abspath ..)
INCLUDE_DIR := $(PLATFORM_DIR)/include/make

include $(INCLUDE_DIR)/defaults.mk

PKG_NAME:=fusekit
PKG_VERSION:=release-1.8.0
PKG_GITHUB_PROJECT:=google/googletest

include $(INCLUDE_DIR)/utils.mk
# include $(INCLUDE_DIR)/packageDeps.mk   No package dependencies
include $(INCLUDE_DIR)/github.mk
include $(INCLUDE_DIR)/package/cmake.mk
