.. _libCellMLUseCases:

=======================
Use-cases for libCellML
=======================

1. **Create:** Create a model from scratch and serialise it to XML (in each case the test is that the serialised model matches manually validated XML documents)

   i. an empty model
   #. a model with a valid name
   #. a model with an invalid name
   #. a model with a single component

      a. a component with a valid name
      #. a component with an invalid name

   #. a model with two or more components
   #. a model with three components and an encapsulation hierarchy

      a. one component encapsulating two children
      #. one component encapsulating a single child which in turn encapsulates a single child
      #. an invalid cyclical encapsulation hierarchy

   #. manipulation of a model with multi-level component encapsulation hierarchy

      a. remove a top-level component
      #. remove an encapsulated child component
      #. change the name of a top-level component
      #. change the name of an encapsulated child component
      #. replace one component with a new component
      #. take a component (remove the component and return it to the user)
      #. determine if a component with a given name exists in a model or component
      #. determine the number of components encapsulated by a model or component

   #. a model with imported components

      a. import a component from a model
      #. import two components from the same model as separate components
      #. import a component into a hierarchy
      #. import a component from a non-existent URL

   #. a model with units

      a. a single base units with valid name
      #. a single base units with an invalid name
      #. a units which defines micro-Ampere * Kelvin / milli-siemens
      #. the units from *1.ix.a* and *1.ix.c* and multiplies them
      #. create a new base units e.g. 'pH'

   #. a model with imported units

      a. import a units from a model

         #. with a valid name
         #. with an invalid name

      #. import a units from a non-existent URL
      #. import a units from a model and scale it, prefix it, offset it, exponentise it

   #. a model with variables

      a. model from *1.iv.a* and define a variable with a valid name and units dimensionless

         #. with a valid variable initial value of 0.0
         #. with a private interface

      #. model from *1.iv.a* and define a variable with an invalid name and units dimensionless
      #. model from *1.iv.a* and define a variable with a valid name and invalid units name.
      #. a model with a single component containing two variables.

         #. with valid variable initial values of 1.0 and -1.0, respectively.
         #. one with an initial value of 1.0 and the other with an initial value of the first variable.
         #. with one public and one public_and_private interface, respectively.

   #. a model with connections

      a. model from *1.vi.a*, each child containing a single variable

         #. with a private interface in the parent and public interface in the child components and connect the variable in both children to the parent.
         #. with a public interface in all components and connect the variables in the children to the parent

   #. a model with maths and variables

      a. model from *1.xi.d.1* and define valid maths

   #. a model with maths, variables and connections

      a. model with two components, each containing two variables, maths, and one connection

#. **Modify:** Modify models from 1.

   i. add {components, units, maths, variables, connections}
   #. remove {components, units, maths, variables, connections}
   #. update {components, units, maths, model attributes, variables, connections}

#. **Load:** Load each of the models from 1 and 2 (new models can be added for this part if required).

   #. a model with imported components

      a. a single component
      #. a component with a hierarchy
      #. a component from a non-existent URL

#. **Validate:**  Create, load, and modify models and then validate them (the test is that the models are correctly identified as valid or invalid, and for the case when they are invalid the correct reason is given, covering each rule in the specification).

#. Import CellML 1.0/1.1 models

#. Export CellML 1.1 (and by extension CellML 1.0)

