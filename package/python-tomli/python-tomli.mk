################################################################################
#
# python-tomli
#
################################################################################

PYTHON_TOMLI_VERSION = 2.4.1
PYTHON_TOMLI_SOURCE = tomli-$(PYTHON_TOMLI_VERSION).tar.gz
PYTHON_TOMLI_SITE = https://files.pythonhosted.org/packages/22/de/48c59722572767841493b26183a0d1cc411d54fd759c5607c4590b6563a6
PYTHON_TOMLI_LICENSE = MIT
PYTHON_TOMLI_LICENSE_FILES = LICENSE
PYTHON_TOMLI_SETUP_TYPE = flit

$(eval $(python-package))
$(eval $(host-python-package))
