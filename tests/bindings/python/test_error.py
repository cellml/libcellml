#
# Tests the Error class bindings
#
import sys
import unittest

class ErrorTestCase(unittest.TestCase):

    def test_error(self):
        import libcellml
        from libcellml import Error
        
        # Test create/copy/destroy
        x = Error()
        del(x)
        y = Error()
        z = Error(y)
        del(y, z)
        
        # Test Kind enum
        self.assertIsInstance(Error.Kind.COMPONENT, int)
        self.assertIsInstance(Error.Kind.CONNECTION, int)
        self.assertIsInstance(Error.Kind.ENCAPSULATION, int)
        self.assertIsInstance(Error.Kind.IMPORT, int)
        self.assertIsInstance(Error.Kind.MATHML, int)
        self.assertIsInstance(Error.Kind.MODEL, int)
        self.assertIsInstance(Error.Kind.UNDEFINED, int)
        self.assertIsInstance(Error.Kind.UNITS, int)
        self.assertIsInstance(Error.Kind.VARIABLE, int)
        self.assertIsInstance(Error.Kind.XML, int)
        
        # Test SpecificationRule enum
        from libcellml import SpecificationRule
        self.assertIsInstance(SpecificationRule.UNDEFINED, int)
        self.assertIsInstance(SpecificationRule.MODEL_ELEMENT, int)
        self.assertIsInstance(SpecificationRule.MODEL_NAME, int)
        self.assertIsInstance(SpecificationRule.MODEL_CHILD, int)
        self.assertIsInstance(SpecificationRule.IMPORT_HREF, int)
        self.assertIsInstance(SpecificationRule.IMPORT_CHILD, int)
        self.assertIsInstance(SpecificationRule.IMPORT_CIRCULAR, int)
        self.assertIsInstance(SpecificationRule.IMPORT_UNITS_NAME, int)
        self.assertIsInstance(SpecificationRule.IMPORT_UNITS_REF, int)
        self.assertIsInstance(SpecificationRule.IMPORT_COMPONENT_NAME, int)
        self.assertIsInstance(SpecificationRule.IMPORT_COMPONENT_REF, int)
        self.assertIsInstance(SpecificationRule.UNITS_NAME, int)
        self.assertIsInstance(SpecificationRule.UNITS_MODEL_UNIQUE, int)
        self.assertIsInstance(SpecificationRule.UNITS_COMPONENT_UNIQUE, int)
        self.assertIsInstance(SpecificationRule.UNITS_STANDARD, int)
        self.assertIsInstance(SpecificationRule.UNITS_BASE, int)
        self.assertIsInstance(SpecificationRule.UNITS_CHILD, int)
        self.assertIsInstance(SpecificationRule.UNIT_UNITS_REF, int)
        self.assertIsInstance(SpecificationRule.UNIT_DIGRAPH, int)
        self.assertIsInstance(SpecificationRule.UNIT_CIRCULAR_REF, int)
        self.assertIsInstance(SpecificationRule.UNIT_ATTRIBUTE, int)
        self.assertIsInstance(SpecificationRule.UNIT_PREFIX, int)
        self.assertIsInstance(SpecificationRule.UNIT_MULTIPLIER, int)
        self.assertIsInstance(SpecificationRule.UNIT_EXPONENT, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_NAME, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_CHILD, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_ATTRIBUTE, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_NAME, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_UNITS, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_INTERFACE, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_INITIAL_VALUE, int)
        self.assertIsInstance(SpecificationRule.ENCAPSULATION_COMPONENT_REF,
            int)
        self.assertIsInstance(SpecificationRule.COMPONENT_REF_COMPONENT, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_REF_CHILD, int)
        self.assertIsInstance(
            SpecificationRule.ENCAPSULATION_COMPONENT_REF_CHILD, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_CHILD, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_MAP_COMPONENTS, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_MAP_VARIABLES, int)
        self.assertIsInstance(SpecificationRule.MAP_COMPONENTS_COMPONENT1, int)
        self.assertIsInstance(SpecificationRule.MAP_COMPONENTS_COMPONENT2, int)
        self.assertIsInstance(SpecificationRule.MAP_VARIABLES_VARIABLE1, int)
        self.assertIsInstance(SpecificationRule.MAP_VARIABLES_VARIABLE2, int)
        
        # Test methods
        
        # void setDescription(const std::string& description)
        e = Error()
        e.setDescription('hello')
        e.setDescription('')
        del(e)

        # std::string getDescription()
        d = 'hi'
        e = Error()
        self.assertEqual(e.getDescription(), '')
        e.setDescription(d)
        self.assertEqual(e.getDescription(), d)
        del(d, e)

        # void setKind(Kind kind)
        e = Error()
        e.setKind(Error.Kind.CONNECTION)
        del(e)

        # Kind getKind()
        e = Error()
        self.assertEqual(e.getKind(), Error.Kind.UNDEFINED)
        e.setKind(Error.Kind.MATHML)
        self.assertEqual(e.getKind(), Error.Kind.MATHML)
        del(e)

        # bool isKind(const Kind &kind)
        e = Error()
        self.assertTrue(e.isKind(Error.Kind.UNDEFINED))
        self.assertFalse(e.isKind(Error.Kind.MODEL))
        del(e)

        # void setRule(SpecificationRule rule)
        e = Error()
        e.setRule(SpecificationRule.MAP_VARIABLES_VARIABLE2)
        del(e)

        # SpecificationRule getRule()
        e = Error()
        self.assertEqual(e.getRule(), SpecificationRule.UNDEFINED)
        del(e)

        # std::string getSpecificationHeading()
        e = Error()
        self.assertEqual('', e.getSpecificationHeading())
        del(e)

        # void setComponent(const ComponentPtr &component)
        from libcellml import Component
        e = Error()
        e.setComponent(Component())
        del(e)

        # ComponentPtr getComponent()
        e = Error()
        self.assertIsNone(e.getComponent())
        name = 'cellml'
        c = Component()
        c.setName(name)
        e.setComponent(c)
        self.assertIsInstance(e.getComponent(), Component)
        self.assertEqual(e.getComponent().getName(), name)
        del(e, c, name)

        # void setImportSource(const ImportSourcePtr &import)
        from libcellml import ImportSource
        e = Error()
        e.setImportSource(ImportSource())
        del(e)

        # ImportSourcePtr getImportSource()
        e = Error()
        self.assertIsNone(e.getComponent())
        name = 'uri'
        i = ImportSource()
        i.setId(name)
        e.setImportSource(i)
        self.assertIsInstance(e.getImportSource(), ImportSource)
        self.assertEqual(e.getImportSource().getId(), name)
        del(e, i, name)

        # void setModel(const ModelPtr &model)
        from libcellml import Model
        e = Error()
        e.setModel(Model())
        del(e)

        # ModelPtr getModel()
        e = Error()
        self.assertIsNone(e.getModel())
        name = 'moodle'
        m = Model()
        m.setName(name)
        e.setModel(m)
        self.assertIsInstance(e.getModel(), Model)
        self.assertEqual(e.getModel().getName(), name)
        del(e, m, name)
        
        # void setUnits(const UnitsPtr &units)
        from libcellml import Units
        e = Error()
        e.setUnits(Units())
        del(e)
        
        # UnitsPtr getUnits()
        e = Error()
        self.assertIsNone(e.getUnits())
        name = 'furlong'
        u = Units()
        u.setName(name)
        e.setUnits(u)
        self.assertIsInstance(e.getUnits(), Units)
        self.assertEqual(e.getUnits().getName(), name)
        del(e, u, name)

        # void setVariable(const VariablePtr &variable)
        from libcellml import Variable
        e = Error()
        e.setVariable(Variable())
        del(e)

        # VariablePtr getVariable()
        e = Error()
        self.assertIsNone(e.getVariable())
        name = 'var'
        v = Variable()
        v.setName(name)
        e.setVariable(v)
        self.assertIsInstance(e.getVariable(), Variable)
        self.assertEqual(e.getVariable().getName(), name)
        del(e, v, name)

if __name__ == '__main__':
    unittest.main()
