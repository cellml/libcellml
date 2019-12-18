.. _simplesolver_cpp:

=================================
A simple solver for the C profile
=================================
In C++ you can use the code provided in the :code:`tutorials/solver` directory
to build your generated code into a runable simulation.  To use the package
just follow the instructions below.

.. container:: dothis

  **1.a** Assuming you've already generated code using the C profile, open a
  terminal window and navigate into the :code:`tutorials/solver` directory.

.. code-block:: terminal

  cd your_base_path/tutorials/solver

Because the code you've generated needs to be built at the same time as the
solver code is built, each different model requires rebuilding the solver
to include the generated code.

.. container:: dothis

  **1.b** The next step is to build your generated code into the solver code.
  From inside the :code:`tutorials/solver` directory, use the CMake command
  line to point to your generated files.  **NB** It's assumed that both of the
  header and source files have the same base filename (eg: baseFileName.c
  and baseFileName.h).  The general CMake command is below.

.. code-block:: terminal

  cmake -DINPUT=/path/to/your/files/baseFileName .

.. container:: nb

  Note that the fullstop in the cmake command sets both the source and binary
  directories to the solver directory.  This is because even though your
  generated files are elsewhere, the solver code and CMakeLists.txt file are
  in *this* directory.

If all has gone well you should see the output similar to:

.. code-block:: terminal

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

    1) First use 'make -j' to build the file for running
    2) Then solve by running: ./solve_baseFileName with the arguments:
      -n  step_total
      -dt step_size

    -- Configuring done
    -- Generating done
    -- Build files have been written to: /path/to/your/stuff/tutorials/solver

.. container:: dothis

  **1.c** Following the instructions in the output, next you need to build the
  executable by entering:

  .. code-block:: terminal

    make -j

.. container:: dothis

  **1.d** Finally you're ready to solve your model.  The executable will have
  been given the prefix :code:`solve_` and then your :code:`baseFileName`, and
  can be run using the command line flags :code:`-n` to indicate the number of
  steps to run, and :code:`-dt` to indicate the step size, for example:

  .. code-block:: terminal

    ./solve_baseFileName -n 20000 -dt 0.001

The parameters read from the file, along with your command line arguments are
printed to the terminal for checking, and the results of the simulation
written to a tab-delimited file with the extension :code:`_solution.txt` after
your baseFileName.
