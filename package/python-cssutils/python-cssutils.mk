################################################################################
#
# python-cssutils
#
################################################################################

PYTHON_CSSUTILS_VERSION = 2.15.0
PYTHON_CSSUTILS_SOURCE = cssutils-$(PYTHON_CSSUTILS_VERSION).tar.gz
PYTHON_CSSUTILS_SITE = https://files.pythonhosted.org/packages/01/00/7e89107ea389e952eea73b1b90ac6633e15a519c4a518ee90bb93a2f83dc
PYTHON_CSSUTILS_LICENSE = LGPL-3.0+
PYTHON_CSSUTILS_LICENSE_FILES = LICENSE
PYTHON_CSSUTILS_SETUP_TYPE = setuptools
PYTHON_CSSUTILS_DEPENDENCIES = \
	host-python-coherent-licensed \
	host-python-setuptools-scm

$(eval $(python-package))
