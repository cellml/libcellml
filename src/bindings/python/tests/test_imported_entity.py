#
# Tests the ImportedEntity class, which is the base class for all entities that
# can be imported.
#
import unittest
class TestNamedEntity(unittest.TestCase):

    def test_named_entity(self):
    
        from libcellml.importedentity import ImportedEntity
        
        # Test create/copy/destroy
        x = ImportedEntity()
        del(x)
        y = ImportedEntity()
        z = ImportedEntity(y)
        del(y,z)
        
        # Test access to inherited methods
        x = ImportedEntity()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        
        # Test own methods
        x = ImportedEntity()
        self.assertFalse(x.isImport())
        self.assertEqual(x.getImportReference(), '')
        self.assertIsNone(x.getImport()) #TODO: Need class import!
        
