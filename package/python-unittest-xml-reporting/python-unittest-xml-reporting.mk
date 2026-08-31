################################################################################
#
# python-unittest-xml-reporting
#
################################################################################

PYTHON_UNITTEST_XML_REPORTING_VERSION = 4.0.0
PYTHON_UNITTEST_XML_REPORTING_SOURCE = unittest_xml_reporting-$(PYTHON_UNITTEST_XML_REPORTING_VERSION).tar.gz
PYTHON_UNITTEST_XML_REPORTING_SITE = https://files.pythonhosted.org/packages/42/6b/5847d0e6e95d08e056f23b3f8cd95bede2d3ade10a1c1a9d5b50916454e1
PYTHON_UNITTEST_XML_REPORTING_DEPENDENCIES = host-python-setuptools-scm
PYTHON_UNITTEST_XML_REPORTING_SETUP_TYPE = setuptools
PYTHON_UNITTEST_XML_REPORTING_LICENSE = BSD-2-Clause
PYTHON_UNITTEST_XML_REPORTING_LICENSE_FILES = LICENSE

$(eval $(python-package))
