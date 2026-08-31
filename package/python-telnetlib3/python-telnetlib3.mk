################################################################################
#
# python-telnetlib3
#
################################################################################

PYTHON_TELNETLIB3_VERSION = 4.0.2
PYTHON_TELNETLIB3_SOURCE = telnetlib3-$(PYTHON_TELNETLIB3_VERSION).tar.gz
PYTHON_TELNETLIB3_SITE = https://files.pythonhosted.org/packages/2c/1f/a5de9f0f86976d299a439619417019a9674fa8662377659734dd6e067235
PYTHON_TELNETLIB3_SETUP_TYPE = hatch
PYTHON_TELNETLIB3_LICENSE = ISC
PYTHON_TELNETLIB3_LICENSE_FILES = LICENSE.txt

$(eval $(python-package))
