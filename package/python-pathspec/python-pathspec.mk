################################################################################
#
# python-pathspec
#
################################################################################

PYTHON_PATHSPEC_VERSION = 1.1.1
PYTHON_PATHSPEC_SOURCE = pathspec-$(PYTHON_PATHSPEC_VERSION).tar.gz
PYTHON_PATHSPEC_SITE = https://files.pythonhosted.org/packages/5a/82/42f767fc1c1143d6fd36efb827202a2d997a375e160a71eb2888a925aac1
PYTHON_PATHSPEC_LICENSE = MPL-2.0
PYTHON_PATHSPEC_LICENSE_FILES = LICENSE
PYTHON_PATHSPEC_SETUP_TYPE = flit

$(eval $(python-package))
$(eval $(host-python-package))
