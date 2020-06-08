.. _solver:

==================================
Simple solver for generated models
==================================

The theory behind how a numerical solver or integration program works is outlined in the :ref:`Theory of ODE solvers<theory_ode_solutions>` page.
This section describes how to use the simple solvers provided to run models generated with either the C or Python profiles.

.. contents:: Contents
    :local:


C profile solver
================
In C++ you can use the code provided in the :code:`tutorials/solver` directory to build your generated code into a runable simulation.
To use the package just follow the instructions below.
You will need to download:

  - :download:`CMakeLists.txt <CMakeLists.txt>` The CMake file which controls the building of the solver.
    Note that this is a little different from usual, as outlined below.
  - :download:`simpleSolver.cpp<simpleSolver.cpp>` The source file.

.. container:: dothis

  **1.a** Assuming you've already generated code using the C profile, open a terminal window and navigate into the :code:`tutorials/solver` directory.

.. code-block:: console

  cd your_base_path/tutorials/solver

Because the code you've generated needs to be built at the same time as the solver code is built, each different model requires rebuilding the solver to include the generated code.

.. container:: dothis

  **1.b** The next step is to build your generated code into the solver code.
  From inside the :code:`tutorials/solver` directory, use the CMake command line to point to your generated files.
  **NB** It's assumed that both of the header and source files have the same base filename (eg: baseFileName.c and baseFileName.h).
  The general CMake command is below.

.. code-block:: console

  cmake -DINPUT=/path/to/your/files/baseFileName .

.. container:: NB

  Note that the fullstop in the cmake command sets both the source and binary directories to the solver directory.
  This is because even though your generated files are elsewhere, the solver code and CMakeLists.txt file are in *this* directory.

If all has gone well you should see the output similar to:

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

  .. code-block:: console

    make -j

.. container:: dothis

  **1.d** Finally you're ready to solve your model.
  The executable will have been given the prefix :code:`solve_` and then your :code:`baseFileName`, and can be run using the command line flags :code:`-n` to indicate the number of steps to run, and :code:`-dt` to indicate the step size.
  For example:

  .. code-block:: console

    ./solve_baseFileName -n 20000 -dt 0.001

The parameters read from the file, along with your command line arguments are printed to the terminal for checking, and the results of the simulation written to a tab-delimited file with the extension :code:`_solution.txt` after your base file name.


Python profile solver
=====================

The solver script is a very simple implementation of the Euler stepping method in Python.
The theory on which it's based can be found on the :ref:`Theory of ODE solver<theory_ode_solutions>` page.
You will need to download:

  - :download:`simplesolver.py<simplesolver.py>` The solver script.

Once you've used the :code:`Generator` to write a CellML model into Python format, you need to run it to produce the solution.
The script can be run from the command line as below:

.. container:: dothis

    **1.**  Navigate into the "solver" directory

.. code-block:: console

    cd your_base_path/tutorials/solver

.. container:: dothis

    **2.**  Run the solver.  To do this you'll need to enter:

        - :code:`-m` the path to the generated file to run, relative to the solver directory;
        - :code:`-dt` the step size for the integration variable to take; and
        - :code:`-n` the total number of steps to take.

.. code-block:: console

    python3 simplesolver.py -m path_to_your_file -n number_of_steps -dt step_size

You should see output to the terminal which echoes the settings and initial conditions, as below.
An example file for running is provided for you in the :code:`resources/tutorial3_PredatorPrey_generated.py` file, which can be run for 2000 steps and a step size of 0.01.
Running this will give you the terminal output:

.. code-block:: console

    python3 simplesolver.py -m ../resources/tutorial3_PredatorPrey_generated.py -dt 0.01 -n 2000

    ====================================================================
       SIMPLE SOLVER: ../resources/tutorial3_PredatorPrey_generated
    --------------------------------------------------------------------

       VARIABLE OF INTEGRATION (units, stepsize)
    --------------------------------------------------------------------
          time (day, 0.01)
          2000 steps

       STATE VARIABLES (units, initial value)
    --------------------------------------------------------------------
          y_s (number_of_sharks, 1.0)
          y_f (thousands_of_fish, 2.0)

       VARIABLES (units, initial value)
    --------------------------------------------------------------------
          a (per_day, -0.8)
          b (per_shark_day, 0.3)
          d (per_fish_day, -0.6)
          c (per_day, -2.8)

       SOLUTION written to ../resources/tutorial3_PredatorPrey_generated_solution.txt
    ====================================================================

The output is a tab delimited file with the ending :code:`_solution.txt` after the input file name (note that it's in the same directory as the running file too), which can be opened by the plotting program of your choice.
