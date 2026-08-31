################################################################################
#
# python-boto3
#
################################################################################

PYTHON_BOTO3_VERSION = 1.43.1
PYTHON_BOTO3_SOURCE = boto3-$(PYTHON_BOTO3_VERSION).tar.gz
PYTHON_BOTO3_SITE = https://files.pythonhosted.org/packages/98/36/028c12ed6ed85009a21b5472eb76c27f9b0341c6986f06f83475b40aaf51
PYTHON_BOTO3_SETUP_TYPE = setuptools
PYTHON_BOTO3_LICENSE = Apache-2.0
PYTHON_BOTO3_LICENSE_FILES = LICENSE

$(eval $(python-package))
