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

    **1.b** Clone the branch from the libCellML library github repository.  This will
    create and populate a folder called :code:`libcellml`.

.. code-block:: console

    git clone -b develop --single-branch https://github.com/cellml/libcellml.git

Your folder structure is now:

.. code-block:: text

    -- MyLibCellMLDirectory
        +--libcellml
            +-- ( ... contains the files you cloned )

.. container:: dothis

    **1.c** Rename the cloned :code:`libcellml` folder to be :code:`source`, and create
    two sibling folders called :code:`build` and :code:`install`:

.. code-block:: console

    mv libcellml source
    mkdir build
    mkdir install

Your folder structure should now look like this:

.. code-block:: text

    -- MyLibCellMLDirectory
        +--build
            +-- ( ... empty )
        +--install
            +-- ( ... empty )
        +--source
            +-- ( ... contains the files you cloned )


2: Build and install the library
================================

.. container:: dothis

    **2.a** Navigate into the :code:`MyLibCellMLDirectory/build` directory
    to make the library:

.. code-block:: console

    cd build
    cmake -DINSTALL_PREFIX=../install ../source
    make -j

You should see output which runs through some checks (make sure they all pass),
and finishes with a message like this:

.. code-block:: console

       ( ... lots of checks ... )
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /Users/YourName/MyLibCellMLDirectory/build

.. container:: dothis

    **2.b** From the same location, install the library:

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

    -- MyLibCellMLDirectory
        +--build
            +-- ( ... lots of files from the build )
        +--install
            +--include
            +--lib
        +--source
            +-- ( ... the files you cloned in step 1.b )

3: Test the installation by running your first tutorial
=======================================================
All the documentation and tutorials are inside the :code:`docs` folder within
the initial cloned directory.

.. container:: dothis

    **3.a** Navigate into the :code:`MyLibCellMLDirectory/source/docs/tutorials` directory
    to see the documentation and tutorials:

.. code-block:: console

    cd source/docs/tutorials

You should see a list of directories like this:

- images (ignore this one)
- quickstart (ignore this one too)
- resources
    - This directory contains input files for tutorials which you'll need later
      on.  These tutorials have been designed
      so that they will build from one to another, but if you've missed an
      earlier tutorial you can always copy the required files from this folder
      instead.
- solver
    - The solver directory has simple scripts to run a numerical integration on
      your model.
- tutorial0 (- tutorial8)
    - The tutorial directories contain the bulk of what you'll need, including
      skeleton code to get you started, as well as instructions for both C++
      and Python, and completed code in case you get stuck.
- utilities
    - The utilities directory contains some commonly used scripts and functions
      which make life easier.

Finally, let's test that the installation has worked by building and running
Tutorial 0.

.. container:: dothis

    **3.b** Navigate into the :code:`tutorial0` directory to run CMake to
    create the Makefile.

.. code-block:: console

    cd tutorial0
    cmake .

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
    -- Build files have been written to: /Users/YourName/MyLibCellMLDirectory/source/docs/tutorials/tutorial0

If this isn't what you see then please see the Troubleshooting section TODO

.. container:: dothis

    **3.c** Now build the :code:`tutorial0` example

.. code-block:: console

    make -j

.. container:: dothis

    **3.d** Finally, run the program to output the welcome and version number
    of the linked libCellML installation:


.. code-block:: console

    ./tutorial0

    -----------------------------------------------
        Welcome to libCellML!
        This version number is 0.2.0
    -----------------------------------------------


.. container:: dothis

    **3.e** Go and have a cuppa, you're done!
