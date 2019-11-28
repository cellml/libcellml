.. _generator_notes:

============================
Code generation in libCellML
============================

Some exciting new functionality of libCellML is its ability to generate a
runable file from a model description.  This means that you don't need to
link your model to a solver of any kind, you can simply generate a script
which contains all the required behind-the-scenes mechanics required to
run your simulation.  Let's give it a go.

The generator is instantiated in the same way as the other items:

.. code-block:: cpp

    // Instantiate the generator and submit a model to it for processing
    libcellml::Generator generator;
    generator.processModel(model);

.. code-block:: python

    from libcellml import Generator
    # Instantiate the generator and submit a model to it for processing
    generator = Generator()
    generator.processModel(model)

The Generator functionality allows you to export your CellML model in
different languages, called *profiles*.  The default setting is for :code:`C`,
but you can change this using the :code:`setProfile` function if you need to.

.. code-block:: cpp

    libcellml::GeneratorProfilePtr profile = std::make_shared<libcellml::GeneratorProfile>(libcellml::GeneratorProfile::Profile::PYTHON);
    generator.setProfile(profile);

.. code-block:: python

    profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
    generator.setProfile(profile)

Of course, your choice of generator profile (language) will affect
what you need to export.  If you're using the C profile, then you will need
both the interface code (the header file) as well as the implementation code
(the source file).  If you're using Python
profile, you will only need the source code.

For the C profile:

.. code-block:: cpp

    // Retrieve the interface or header code:
    std::string headerCode = generator.interfaceCode();
    // Retrieve the main source code:
    std::string sourceCode = generator.implementationCode();

.. code-block:: python

    # Retrieve the interface or header code:
    header_code = generator.interfaceCode()
    # Retrieve the main source code:
    source_code = generator.implementationCode()

For the Python profile:

.. code-block:: cpp

    // Retrieve the main script code only:
    std::string sourceCode = generator.implementationCode();
