################################################################################
#
# python-poetry-core
#
################################################################################

PYTHON_POETRY_CORE_VERSION = 2.3.2
PYTHON_POETRY_CORE_SOURCE = poetry_core-$(PYTHON_POETRY_CORE_VERSION).tar.gz
PYTHON_POETRY_CORE_SITE = https://files.pythonhosted.org/packages/10/48/5b4f344c252ee2f75051b6bf7dfb68ab53aa00a107f5f8e5cbf795701dad
PYTHON_POETRY_CORE_SETUP_TYPE = pep517
PYTHON_POETRY_CORE_LICENSE = MIT
PYTHON_POETRY_CORE_LICENSE_FILES = LICENSE

$(eval $(host-python-package))
