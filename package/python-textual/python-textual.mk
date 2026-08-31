################################################################################
#
# python-textual
#
################################################################################

PYTHON_TEXTUAL_VERSION = 8.2.5
PYTHON_TEXTUAL_SOURCE = textual-$(PYTHON_TEXTUAL_VERSION).tar.gz
PYTHON_TEXTUAL_SITE = https://files.pythonhosted.org/packages/62/1e/1eedc5bac184d00aaa5f9a99095f7e266af3ec46fa926c1051be5d358da1
PYTHON_TEXTUAL_SETUP_TYPE = poetry
PYTHON_TEXTUAL_LICENSE = MIT
PYTHON_TEXTUAL_LICENSE_FILES = LICENSE

$(eval $(python-package))
