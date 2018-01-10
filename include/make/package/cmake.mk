#------------------------------------------------------------------------------
# CMake package generator Make include file
#
# When included from within a project makefile, will generate all the necessary
# targets and dependencies to build an autoconf package.
#
# To use:
# 1. Define the following in your Makefile
#      PKG_NAME :=          The package name
#      PKG_SOURCE_SUBDIR := The sub-directory in the BUILD_DIR where the package
#                             source (or makefiles if building out-of-tree) are
#                             located
#      CMAKE_OPTIONS :=     Additional specialized CMake command-line arguments
# 2. Include the following make include files in your Makefile
#      make/defaults.mk
#      make/utils.mk
# 3. Consider the following should you need the functionality
#      make/buildReqs.mk
#      make/packageDeps.mk
#      make/extract.mk
# 4. Include this file in your Makefile
#
#------------------------------------------------------------------------------

MAKE_PAKGAGE_INCLUDE_DIR ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

include $(MAKE_PAKGAGE_INCLUDE_DIR)/common.mk

configure.done:
	$(call stepinfo)
	@mkdir -p $(PKG_BUILD_DIR) 
	@cd $(PKG_BUILD_DIR) && cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=$(BUILD) -D CMAKE_PREFIX_PATH="$(PREFIX_PATH)" $(CMAKE_OPTIONS) $(PKG_SOURCE_DIR)
	$(done)
