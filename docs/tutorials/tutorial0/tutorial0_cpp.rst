..  _tutorial0_cpp:

===========================================
Tutorial 0: Installation and testing in C++
===========================================

**TODO** Update this with binary/Docker/something else installation instructions

.. contents:: Contents
    :local:

1: Create the libCellML library
===============================

.. container:: dothis

  **1.a** Create an empty folder and navigate into it.

  .. code-block:: console

    mkdir MyLibCellMLDirectory
    cd MyLibCellMLDirectory

.. container:: dothis

  **1.b** Clone the branch from the libCellML library github repository.
  This will create and populate a folder called :code:`libcellml`.

  .. code-block:: console

    git clone -b master --single-branch https://github.com/cellml/libcellml.git

Your folder structure is now:

.. code-block:: text

  ── MyLibCellMLDirectory
      └─ libcellml
          └─ ( ... contains the files you cloned )

.. container:: dothis

  **1.c** Rename the cloned :code:`libcellml` folder to be :code:`source`, and create sibling folders called :code:`build`, :code:`install`, and :code:`tutorials`:

  .. code-block:: console

    mv libcellml source
    mkdir build
    mkdir install
    mkdir tutorials

Your folder structure should now look like this:

.. code-block:: text

  ── MyLibCellMLDirectory
      ├─ build
      │   └─ ( ... empty )
      ├─ install
      │   └─ ( ... empty )
      ├─ source
      │   └─ ( ... contains the files you cloned )
      └─ tutorials
          └─ ( ... empty )


2: Build and instal the library
===============================

.. container:: dothis

  **2.a** Navigate into the :code:`MyLibCellMLDirectory/build` directory to make the library:

  .. code-block:: console

    cd build
    cmake -DINSTALL_PREFIX=../install -DTUT_PREFIX=../tutorials ../source
    make -j

You should see output which runs through some checks (make sure they all pass), and finishes with a message like this:

.. code-block:: console

     ( ... lots of checks ... )
  -- Configuring done
  -- Generating done
  -- Build files have been written to: /Users/YourName/MyLibCellMLDirectory/build

.. container:: dothis

  **2.b** From the same location, instal the library:

  .. code-block:: console

      make -j install

You should see output which finishes with a list of library and include files
like this:

.. code-block:: console

  Install the project...
  -- Install configuration: "Debug"
  -- Installing: /Users/YourName/MyLibCellMLDirectory/build/../install/lib/libcellmld.0.2.0.dylib
  -- Installing: /Users/kmoy001/MyLibCellMLDirectory/build/../install/lib/libcellmld.dylib
      ...

Your directory structure should now look like:

.. code-block:: text

  ── MyLibCellMLDirectory
      ├─ build
      │   └─ ( ... lots of files from the build )
      ├─ install
      │   ├─ include
      │   └─ lib
      ├─ source
      │   └─ ( ... the files you cloned in step 1.b )
      └─ tutorials
          └─ ( ... a collection of folders explained below )

3: Test the installation by running your first tutorial
=======================================================
All the documentation and tutorials are inside the :code:`docs` folder within
the initial cloned directory, but in order to keep your source tree clean,
the :code:`tutorials` directory has been copied into the directory given by the
:code:`-DTUT_PREFIX` argument when you built the library.  If you've used the
same structure as outlined here, this will be the
:code:`MyLibCellMLDirectory/tutorials` directory.

.. container:: dothis

  **3.a** Navigate into the :code:`MyLibCellMLDirectory/tutorials` directory to see its contents:

  .. code-block:: console

    cd tutorials

You should see a list of directories like this:

  - images (ignore this one)
  - examples (ignore this one too)
  - resources
    - This directory contains input files for tutorials which you'll need later on.
      These tutorials have been designed so that they will build from one to another, but if you've missed an earlier tutorial you can always copy the required files from this folder instead.
  - solver
    - The solver directory has simple scripts to run a numerical integration on your model.
  - tutorial0 ( ... to tutorial8)
    - The tutorial directories contain the bulk of what you'll need, including skeleton code to get you started, as well as instructions for both C++ and Python, and completed code in case you get stuck.
  - utilities
    - The utilities directory contains some commonly used scripts and functions which make life easier.

.. container:: dothis

  **3.b** Navigate into the :code:`tutorial0` directory to run CMake to create the Makefile.
  Note that you will need to specify the path to the :code:`install` directory using the :code:`-DINSTALL_PREFIX` flag.

  .. code-block:: console

    cd tutorial0
    cmake -DINSTALL_PREFIX=../../install .

If this is correct you should see an output ending similar to this:

.. code-block:: console

    -- The C compiler identification is AppleClang 10.0.1.10010046
    -- The CXX compiler identification is AppleClang 10.0.1.10010046
    -- Check for working C compiler: /Library/Developer/CommandLineTools/usr/bin/cc
    -- Check for working C compiler: /Library/Developer/CommandLineTools/usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++
    -- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /Users/YourName/MyLibCellMLDirectory/tutorials/tutorial0

If this isn't what you see then please see the Troubleshooting section **TODO**

.. container:: dothis

  **3.c** Now build the :code:`tutorial0` example

  .. code-block:: console

    make -j

You should see an output similar to this:

.. code-block:: console

    Scanning dependencies of target tutorial1
    [ 50%] Building CXX object CMakeFiles/tutorial1.dir/tutorial1.cpp.o
    [100%] Linking CXX executable tutorial1
    [100%] Built target tutorial1

.. container:: dothis

    **3.d** Finally, run the program to output the welcome and version number of the linked libCellML instalation:

  .. code-block:: console

    ./tutorial0

You should see the output of:

.. code-block:: console

  -----------------------------------------------
      Welcome to libCellML!
      This version number is 0.2.0
  -----------------------------------------------

.. container:: dothis

  **3.e** Go and have a cuppa, you're done!
