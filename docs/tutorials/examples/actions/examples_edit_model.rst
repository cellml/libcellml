.. _examples_edit_model:

Edit aspects of a ``Model``
+++++++++++++++++++++++++++

Every aspect of a model can be edited and changed through the libCellML API.
The most complicated part is editing the MathML, which is discussed separately in **TODO**.
For entities in the list below the simple functions are available:

Where the item can contain only one of the attributes (name, id, maths for a component, units for a variable) then the standard get and set idiom is available:
- Get the attribute :code:`xyz` using the camelCase function :code:`xyx()` without arguments;
- Set its attribute using the camelCase function :code:`setXyz(arg)` with an appropriate argument.

For example:

- :code:`name()` and :code:`setName("myNewName")` to retrieve and set the item's name to :code:`"myNewName"`;
- :code:`id()` and :code:`setId("myNewID")` to retrieve and set the item's ID to :code:`"myNewID"`;

Specific to different items:

- :code:`Variable` items please see the :api:`full API Variable reference<Variable>`.

  - :code:`Units`

    - :code:`variable->units()` retrieve a pointer to the :code:`Units` associated with this :code:`Variable`;
    - :code:`variable->setUnits("newUnitName")` set the name of the :code:`Units` to attach to this :code:`Variable`; and
    - :code:`variable->setUnits(myUnit)` to set the :code:`Units` item for this :code:`Variable` directly.

  - :code:`interfaceType()` to return the enum for the interface of the :code:`Variable`;
  - :code:`setInterfaceType(libcellml::Variable::InterfaceType::PUBLIC)` to set the :code:`public` interface type;
  - :code:`initialValue()` returns a string corresponding to the initial value for the :code:`variable`.
    Note that this could be either:

    - the name of another :code:`Variable` from which to take value; or
    - a string containing the real number for the initial value.

- :code:`Component` items please see the :api:`full API Component reference<Component>`.

  - MathML string:

    - :code:`math()` to return the MathML string for this :code:`Component`;
    - :code:`setMath(newMathMLString)` to over-write the current MathML string with :code:`newMathMLString`; and
    - :code:`appendMath(extraMathMLString)` to append to the current MathML string with :code:`extraMathMLString`.

- :code:`Reset` items please see the :api:`full API Reset reference<Reset>`.

  - :code:`variable()` and :code:`testVariable()` to return pointers to the reset variable and test variable respectively;
  - :code:`setVariable(myVariable)` and :code:`setTestVariable(myTestVariable)` to set the reset and test variables to :code:`myVariable` and :code:`myTestVariable` respectively;
  - :code:`testValue()` and :code:`resetValue()` to return the MathML string fragment used for the test value and reset values;
  - :code:`setTestValue(testMathMLString)` and :code:`setResetValue(resetMathMLString)` to set the test value and reset value MathML string fragments respectively;
  - :code:`order()` to return the order of the reset; and
  - :code:`setOrder(1)` to set the order to :code:`1`.


Where an item can contain multiple child items, a different set of functions
