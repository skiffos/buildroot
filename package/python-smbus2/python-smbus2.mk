################################################################################
#
# python-smbus2
#
################################################################################

PYTHON_SMBUS2_VERSION = 0.6.1
PYTHON_SMBUS2_SOURCE = smbus2-$(PYTHON_SMBUS2_VERSION).tar.gz
PYTHON_SMBUS2_SITE = https://files.pythonhosted.org/packages/87/37/b3f7b501502c4915ba3819d1dc277bf3f5fae4a9d067caa4f502aaddd889
PYTHON_SMBUS2_SETUP_TYPE = setuptools
PYTHON_SMBUS2_LICENSE = MIT
PYTHON_SMBUS2_LICENSE_FILES = LICENSE

$(eval $(python-package))
