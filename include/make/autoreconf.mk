#------------------------------------------------------------------------------
# Autoconf package helper include file
#
# When included from within a project makefile, will generate all the necessary
# targets and dependencies to run autogen before the package is configured.
#
#------------------------------------------------------------------------------

autoreconf.done: extract.done
	$(call stepinfo)
	@mkdir -p $(PKG_BUILD_DIR)
	@cd $(PKG_BUILD_DIR) && autoupdate
	@cd $(PKG_BUILD_DIR) && autoreconf -f -i -Wall
	$(done)

configure.done: autoreconf.done
