################################################################################
#
# ripgrep
#
################################################################################

RIPGREP_VERSION = 0.8.1
RIPGREP_SITE = $(call github,burntsushi,ripgrep,$(RIPGREP_VERSION))
RIPGREP_LICENSE = MIT
RIPGREP_LICENSE_FILES = LICENSE-MIT

$(eval $(cargo-package))
