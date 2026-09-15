################################################################################
#
# python-redis
#
################################################################################

PYTHON_REDIS_VERSION = 7.4.0
PYTHON_REDIS_SOURCE = redis-$(PYTHON_REDIS_VERSION).tar.gz
PYTHON_REDIS_SITE = https://files.pythonhosted.org/packages/7b/7f/3759b1d0d72b7c92f0d70ffd9dc962b7b7b5ee74e135f9d7d8ab06b8a318
PYTHON_REDIS_SETUP_TYPE = hatch
PYTHON_REDIS_LICENSE = MIT
PYTHON_REDIS_LICENSE_FILES = LICENSE

$(eval $(python-package))
