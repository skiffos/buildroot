################################################################################
#
# python-pylru
#
################################################################################

PYTHON_PYLRU_VERSION = 1.3.1
PYTHON_PYLRU_SOURCE = pylru-$(PYTHON_PYLRU_VERSION).tar.gz
PYTHON_PYLRU_SITE = https://files.pythonhosted.org/packages/76/5f/1c22971415233fa6132453fa8b5a7464b7b7af004a2f236717de403a42c6
PYTHON_PYLRU_SETUP_TYPE = setuptools
PYTHON_PYLRU_LICENSE = MIT
PYTHON_PYLRU_LICENSE_FILES = LICENSE.txt

$(eval $(python-package))
