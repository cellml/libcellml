""" libCellML Library: A library for the parsing, printing, and manipulation
of CellML 2.0 compliant models.

"""

classifiers = """\
Development Status :: 5 - Production/Stable
Intended Audience :: Developers
Intended Audience :: Education
Intended Audience :: Science/Research
License :: OSI Approved :: Apache Software License
Programming Language :: Python
Operating System :: Microsoft :: Windows
Operating System :: Unix
Operating System :: MacOS :: MacOS X
Topic :: Software Development :: Libraries :: Python Modules
"""

import os
from setuptools import setup
from setuptools.dist import Distribution
from setuptools.command.install import install

doclines = __doc__.split("\n")


class BinaryDistribution(Distribution):
    def is_pure(self):
        return False

    def has_ext_modules(self):
        return True


class InstallCommand(install):
    def initialize_options(self):
        super().initialize_options()
        if os.name != 'nt':
            self.install_lib = ""


setup(
    name='@PYPI_PACKAGE_NAME@',
    version='@PYPI_PACKAGE_VERSION@@PYPI_PACKAGE_DEVELOPER_VERSION@',
    author='libCellML developers',
    author_email='libcellml@googlegroups.com',
    packages=['libcellml'],
    package_data={'libcellml': [@SETUP_PY_PACKAGE_FILES_STR@]},
    url='@PYPI_PACKAGE_URL@',
    license='Apache Software License',
    description=doclines[0],
    classifiers=classifiers.split("\n"),
    long_description=open('README.rst').read(),
    long_description_content_type='text/x-rst',
    distclass=BinaryDistribution,
    cmdclass={
        'install': InstallCommand,
    },
    include_package_data=True,
    zip_safe=False,
)
