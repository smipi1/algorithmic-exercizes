#------------------------------------------------------------------------------
# Common package recipes and dependencies
#
# Do not include directly. Use package/cmake.mk or package/automake.mk
#
#------------------------------------------------------------------------------

.DEFAULT_GOAL := all

PKG_SOURCE_SUBDIR ?= $(PKG_NAME)
PKG_BUILD_DIR := $(abspath $(BUILD_DIR)/$(PKG_SOURCE_SUBDIR))
PKG_SOURCE_DIR ?= $(PKG_BUILD_DIR)
SET_STAGING_ENV := $(STAGING_TOOLS_DIR)/set-env

.SECONDEXPANSION:
.PHONY: compile configure extract
compile configure extract: $$@.done

.PHONY: all
all: compile.done

.PHONY : deploy
deploy: install
	mkdir -p $(DEPLOYMENT_DIR)
	rsync --archive --verbose \
	    $(foreach exclude,$(DEPLOYMENT_EXCLUDES),--exclude=$(exclude)) \
	    $(STAGING_DIR)/* \
	    $(DEPLOYMENT_DIR)/

.PHONY : install
install: compile.done
	@mkdir -p $(STAGING_DIR)
	@cp -a $(SET_STAGING_ENV) $(STAGING_DIR)
	@$(MAKE) -C $(PKG_BUILD_DIR) DESTDIR=$(STAGING_DIR) install

compile.done: configure.done
	$(call stepinfo)
	@$(MAKE) -C $(PKG_BUILD_DIR)
	$(git_prune_missing_files)
	$(done)

.PHONY : clean
clean:
	$(call stepinfo)
	-rm -rf $(BUILD_DIR)
