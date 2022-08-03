import os
import platform

from skbuild import setup

cmake_args = ["-DUNIT_TESTS=OFF", "-DCOVERAGE=OFF", "-DMEMCHECK=OFF", "-DLLVM_COVERAGE=OFF"]

if platform.system() == "Windows":
  cmake_args.append("-DLibXml2_DIR=C:/Program Files (x86)/libxml2/libxml2-2.9.10/CMake/")


tag = os.environ.get("LIBCELLML_VERSION_TAG", "v0.0.0")

setup(
    name="libcellml",
    version=tag[1:],
    description="libCellML is a library for manipulating CellML models.",
    author="libCellML contributors",
    url="https://libcellml.org",
    license="Apache 2.0",
    packages=["libcellml"],
    include_package_data=True,
    #package_data={'libcellml': ['libcellml.0.2.0-dev.24.dylib', '_analyser.so', '_analyserequation.so', '_analyserequationast.so', '_analyserexternalvariable.so', '_analysermodel.so', '_analyservariable.so', '_annotator.so', '_component.so', '_componententity.so', '_entity.so', '_enums.so', '_generator.so', '_generatorprofile.so', '_importer.so', '_importsource.so', '_importedentity.so', '_issue.so', '_logger.so', '_model.so', '_namedentity.so', '_parentedentity.so', '_parser.so', '_printer.so', '_reset.so', '_types.so', '_units.so', '_validator.so', '_variable.so', '_version.so']},
    cmake_source_dir="../../../",
    cmake_install_target="install-wheel",
    cmake_args=cmake_args,
    #cmake_install_dir="libcellmlXXXXXX",
    exclude_package_data={"": ["bin/*", "cmake/*", "include/*", "lib/*"]},
)
