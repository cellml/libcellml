.. _tutorial0_py:

==========================================================
Tutorial 0: Python-based installation
==========================================================

**TODO* Update this with pip installation instructions??

-----------------------------------------------------
1: Create the libCellML library
-----------------------------------------------------

.. container:: dothis

    **1.a** Create an empty folder and navigate into it, then create a further empty
    folder called :code:`libcellml`, and navigate into that one.

.. code-block:: console

    mkdir MyLibCellMLDirectory
    cd MyLibCellMLDirectory
    mkdir libcellml
    cd libcellml

.. container:: dothis

    **1.b** Clone the branch from the libCellML library github repository.  This will
    create and populate a folder called :code:`libcellml`.

.. code-block:: console

    git clone -b develop --single-branch https://github.com/cellml/libcellml.git

Your folder structure is now:

.. code-block:: text

    -- MyLibCellMLDirectory
        +--libcellml
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
        +--libcellml
            +--build
                +-- ( ... empty )
            +--install
                +-- ( ... empty )
            +--source
                +-- ( ... contains the files you cloned )

-------------------------------------------
2: Build and install the library
-------------------------------------------

.. container:: dothis

    **2.a** Navigate into the :code:`MyLibCellMLDirectory/libcellml/build` directory
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
    -- Build files have been written to: /Users/YourName/MyLibCellMLDirectory/libcellml/build

.. container:: dothis

    **2.b** From the same location, install the library:

.. code-block:: console

    make -j install

You should see output which finishes with a list of library and include files
like this:

.. code-block:: console

    Install the project...
    -- Install configuration: "Debug"
    -- Installing: /Users/YourName/MyLibCellMLDirectory/libcellml/build/../install/lib/libcellmld.0.2.0.dylib
    -- Installing: /Users/kmoy001/MyLibCellMLDirectory/libcellml/build/../install/lib/libcellmld.dylib
        ...

Your directory structure should now look like:

.. code-block:: text

    -- MyLibCellMLDirectory
            +--libcellml
                +--build
                    +-- ( ... lots of files from the build )
                +--install
                    +--include
                    +--lib
                +--source
                    +-- ( ... the files you cloned in step 1.b )

------------------------------
3: Create the tutorials
------------------------------

.. container:: dothis

    **3.a** Change back into the top directory (:code:`MyLibCellMLDirectory`),
    and create a directory for the tutorials.

.. code-block:: console

    cd ../../
    mkdir tutorials

Your directory structure should now look like:

.. code-block:: text

    -- MyLibCellMLDirectory
        +--libcellml
            ( ... all the files created in steps 1 and 2 )
        +--tutorials
            ( ... empty )

.. container:: dothis

    **3.b** Change into the new :code:`tutorials` directory and clone the
    flavour of tutorials that you're interested in.

For C++:

.. code-block:: console

    cd tutorials
    git clone https://github.com/kerimoyle/libcellml-tutorials-cpp.git

For Python:

.. code-block:: console

    cd tutorials
    git clone https://github.com/kerimoyle/libcellml-tutorials-python.git

Your folder structure should now look like what's shown below.  Note that
whichever flavour of tutorial you have cloned does not alter the structure,
only the folder name inside your :code:`tutorials` folder:

.. code-block:: text

    -- MyLibCellMLDirectory
        +--libcellml
            +--build
                +-- ( ... lots of files from your earlier make command )
            +--install
                +-- include
                +-- lib
            +--source
                +-- ( ... lots of files from your first git clone )
     +--tutorials
        +--libcellml-tutorials-yourCodeFlavour
            +--documentation
            +--resources
            +--tutorials
            +--tutorials_complete
            +--utilities

-------------------------------------------------------
4: Test the installation by running your first tutorial
-------------------------------------------------------
If all has gone well so far you should see four folders:

- The :code:`documentation` folder contains an offline copy of the tutorials'
  documentation.  This is also available online at **TODO**.  To use your
  offline copy, simply open the :code:`index.html` file in your favourite
  web browser.
- The :code:`resources` folder contains files and code snippets that will
  help you out as you go through the tutorials.  They have been designed
  so that they will build from one to another, but if you've missed an
  earlier tutorial you can always copy the required files from this folder
  instead.
- The :code:`tutorials` folder contains skeleton code for each of the
  tutorials.  This code has comments which mimic the instructions so will
  take you through it all one step at a time.
- The :code:`tutorials_complete` folder contains a working version of each
  of the tutorials.  If you're short on time, or struggling with any of the
  steps you can just check the code provided here.
- The :code:`utilities` folder has files with a few simple routines which
  will help you with the tutorials.

Finally, let's test that the installation has worked by building and running
Tutorial 0.

.. container:: dothis

    **4.a** Navigate into the :code:`tutorials/tutorial0` directory to run CMake to
    create the Makefile.

.. code-block:: console

    cd tutorials/tutorial0
    cmake .

.. container:: dothis

    **4.b**  If this is correct you should see an output ending similar to this:

.. code-block:: console

    -- Configuring done
    -- Generating done
    -- Build files have been written to: /Users/YourName/MyLibCellMLDirectory/tutorials/libcellml-tutorials-cpp/tutorials/tutorial0

If this isn't what you see then please see the Troubleshooting section TODO

.. container:: dothis

    **4.c** Now build the :code:`tutorial0` example

.. code-block:: console

    make -j

.. container:: dothis

    **4.d** Finally, run the program to give the following output:

.. code-block:: console

    ./tutorial0

.. code-block:: console

    -----------------------------------------------
        Welcome to libCellML!
        This version number is 0.2.0
    -----------------------------------------------

.. container:: dothis

    **4.e** Go and have a cuppa, you're done!
