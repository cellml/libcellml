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
        del(y,z)
        
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

        # SpecificationRule getRule()

        # std::string getSpecificationHeading()

        # void setComponent(const ComponentPtr &component)

        # ComponentPtr getComponent()

        # void setImport(const ImportPtr &import)

        # ImportPtr getImport()

        # void setModel(const ModelPtr &model)

        # ModelPtr getModel()

        # void setUnits(const UnitsPtr &units)
        
        # UnitsPtr getUnits()

        # void setVariable(const VariablePtr &variable)

        # VariablePtr getVariable()

if __name__ == '__main__':
    unittest.main()
