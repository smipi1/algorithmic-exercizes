#------------------------------------------------------------------------------
# Unittest coverage make include file
#
# When included from within a project, will generate all the necessary targets
# and dependencies to generate unittest coverage data.
#
#------------------------------------------------------------------------------

GCOVR_OPTIONS := \
  --exclude-unreachable-branches

.PHONY: unittest-coverage
unittest-coverage: $(BUILD_DIR)/unittest-coverage.html

$(BUILD_DIR)/unittest-coverage.html: all
	@$(call printInColor,$(YELLOW),Collecting coverage information:)
	@$(call printInColor,$(RED),	Refer to: $@)
	@gcovr -r $(abspath .) $(GCOVR_OPTIONS) --html --html-details --exclude='staging_dir/.*' -o $@
