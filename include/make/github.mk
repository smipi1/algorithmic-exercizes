#------------------------------------------------------------------------------
# Package source download/extraction make include file
#
# When included from within a project, will generate all the necessary targets
# and dependencies to download and extract a package.
#
#------------------------------------------------------------------------------

ifndef PKG_GITHUB_PROJECT
$(error PKG_GITHUB_PROJECT not defined)
endif

ifndef PKG_VERSION
$(error PKG_VERSION not defined)
endif

configure.done: extract.done

extract.done:
	$(call stepinfo)
	@rm -rf $(PKG_BUILD_DIR)
	@mkdir -p $(PKG_BUILD_DIR)
	curl -L https://github.com/$(PKG_GITHUB_PROJECT)/tarball/$(PKG_VERSION) | tar -xzv -C $(PKG_BUILD_DIR) --strip 1
	$(done)
