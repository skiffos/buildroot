################################################################################
#
# tinifier
#
################################################################################

TINIFIER_VERSION = 2.1.0
TINIFIER_SITE = $(call github,tarampampam,tinifier,v$(TINIFIER_VERSION))
TINIFIER_LICENSE = MIT
TINIFIER_LICENSE_FILES = LICENSE
TINIFIER_GOMOD = tinifier

$(eval $(golang-package))
