################################################################################
#
# python-regex
#
################################################################################

PYTHON_REGEX_VERSION = 2026.4.4
PYTHON_REGEX_SOURCE = regex-$(PYTHON_REGEX_VERSION).tar.gz
PYTHON_REGEX_SITE = https://files.pythonhosted.org/packages/cb/0e/3a246dbf05666918bd3664d9d787f84a9108f6f43cc953a077e4a7dfdb7e
PYTHON_REGEX_SETUP_TYPE = setuptools
PYTHON_REGEX_LICENSE = Apache-2.0
PYTHON_REGEX_LICENSE_FILES = LICENSE.txt

$(eval $(python-package))
$(eval $(host-python-package))
