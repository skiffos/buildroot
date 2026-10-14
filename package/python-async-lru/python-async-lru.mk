################################################################################
#
# python-async-lru
#
################################################################################

PYTHON_ASYNC_LRU_VERSION = 2.3.0
PYTHON_ASYNC_LRU_SOURCE = async_lru-$(PYTHON_ASYNC_LRU_VERSION).tar.gz
PYTHON_ASYNC_LRU_SITE = https://files.pythonhosted.org/packages/e8/1f/989ecfef8e64109a489fff357450cb73fa73a865a92bd8c272170a6922c2
PYTHON_ASYNC_LRU_SETUP_TYPE = setuptools
PYTHON_ASYNC_LRU_LICENSE = MIT
PYTHON_ASYNC_LRU_LICENSE_FILES = LICENSE

$(eval $(python-package))
