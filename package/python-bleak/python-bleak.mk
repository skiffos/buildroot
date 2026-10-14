################################################################################
#
# python-bleak
#
################################################################################

PYTHON_BLEAK_VERSION = 3.0.1
PYTHON_BLEAK_SOURCE = bleak-$(PYTHON_BLEAK_VERSION).tar.gz
PYTHON_BLEAK_SITE = https://files.pythonhosted.org/packages/87/9f/dd19d92309e4a37823210827f0f42460e69603254309b99499622b511294
PYTHON_BLEAK_SETUP_TYPE = poetry
PYTHON_BLEAK_LICENSE = MIT
PYTHON_BLEAK_LICENSE_FILES = LICENSE

$(eval $(python-package))
