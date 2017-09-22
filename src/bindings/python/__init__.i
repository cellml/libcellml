%module(package="libcellml") __init__

//TODO: http://www.swig.org/Doc1.3/Python.html#Python_nn65

%pythoncode %{
from libcellml.entity import Entity
from libcellml.namedentity import NamedEntity
from libcellml.importedentity import ImportedEntity
from libcellml.componententity import ComponentEntity
from libcellml.model import Model
from libcellml.component import Component
from libcellml.variable import Variable
from libcellml.units import Units
from libcellml.importsource import Import as ImportSource #TODO
from libcellml.entity import Entity
from libcellml.entity import Entity
from libcellml.entity import Entity





%}
