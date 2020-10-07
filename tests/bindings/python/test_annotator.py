#
# Tests the Component class bindings
#
import unittest

from test_resources import file_contents


class AnnotatorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Annotator

        x = Annotator()
        self.assertIsNotNone(x)
        del x

    def test_item(self):
        from libcellml import Annotator, CellMLElement, Model, Parser

        annotator = Annotator()
        model = Model()
        parser = Parser()

        model_string = file_contents("annotator/unique_ids.cellml")

        model = parser.parseModel(model_string)
        annotator.setModel(model)

        self.assertEqual(CellMLElement.UNDEFINED, annotator.item("not_an_id")[0])
        self.assertEqual(CellMLElement.UNDEFINED, annotator.item("not_an_id", 3)[0])
        self.assertEqual(CellMLElement.MAP_VARIABLES, annotator.item("map_variables_2")[0])

        # For coverage purposes only.
        annotator._itemCellmlElement("not_an_id", 0)

    def test_type_based_retrieval(self):
        from libcellml import Annotator, Model, Parser

        annotator = Annotator()
        model = Model()
        parser = Parser()

        model_string = file_contents("annotator/unique_ids.cellml")

        model = parser.parseModel(model_string)
        annotator.setModel(model)

        v1v1 = (model.component("component2").variable("variable1"), model.component(
            "component2").component("component3").variable("variable1"))
        v2v2 = (model.component("component2").variable("variable2"), model.component(
            "component2").component("component3").variable("variable2"))

        self.assertEqual(model.name(), annotator.model("model_1").name())
        self.assertEqual(model.name(), annotator.encapsulation("encapsulation_1").name())
        self.assertEqual(model.component("component1").name(),
                         annotator.component("component_1").name())
        self.assertEqual(model.component("component2").name(),
                         annotator.component("component_2").name())
        self.assertEqual(model.component("component2").name(),
                         annotator.component("component_ref_1").name())
        self.assertEqual(model.component("component2").component("component3").name(),
                         annotator.component("component_3").name())
        self.assertEqual(model.component("component2").component("component3").name(),
                         annotator.componentRef("component_ref_2").name())
        self.assertEqual(model.component("component1").importSource().url(),
                         annotator.importSource("import_1").url())
        self.assertEqual(model.units("units1").name(),
                         annotator.units("units_1").name())
        self.assertEqual(model.units("units1").importSource().url(),
                         annotator.importSource("import_2").url())
        self.assertEqual(model.units("units2").name(),
                         annotator.units("units_2").name())
        self.assertEqual(model.units("units2").name(),
                         annotator.unit("unit_1")[0].name())
        self.assertEqual(0, annotator.unit("unit_1")[1])

        self.assertEqual(model.component("component2").variable("variable1").name(),
                         annotator.variable("variable_1").name())

        self.assertEqual(model.component("component2").variable("variable2").name(),
                         annotator.variable("variable_2").name())
        self.assertEqual(model.component("component2").reset(0).variable().name(),
                         annotator.reset("reset_1").variable().name())
        self.assertEqual(model.component("component2").reset(0).testVariable().name(),
                         annotator.reset("reset_1").testVariable().name())
        self.assertEqual(model.component("component2").reset(0).testValue(),
                         annotator.testValue("test_value_1").testValue())
        self.assertEqual(model.component("component2").reset(0).resetValue(),
                         annotator.resetValue("reset_value_1").resetValue())

        self.assertEqual(model.component("component2").component("component3").variable("variable1").name(),
                         annotator.variable("variable_3").name())
        self.assertEqual(model.component("component2").component("component3").variable("variable2").name(),
                         annotator.variable("variable_4").name())
        self.assertEqual(v1v1[0].name(),
                         annotator.connection("connection_1")[0].name())

        self.assertEqual(v1v1[1].name(),
                         annotator.connection("connection_1")[1].name())
        self.assertEqual(v1v1[0].name(),
                         annotator.mapVariables("map_variables_1")[0].name())
        self.assertEqual(v1v1[1].name(),
                         annotator.mapVariables("map_variables_1")[1].name())
        self.assertEqual(v2v2[0].name(),
                         annotator.mapVariables("map_variables_2")[0].name())
        self.assertEqual(v2v2[1].name(),
                         annotator.mapVariables("map_variables_2")[1].name())

        self.assertIsNone(annotator.model("i_dont_exist"))
        self.assertIsNone(annotator.component("i_dont_exist"))
        self.assertIsNone(annotator.variable("i_dont_exist"))
        self.assertIsNone(annotator.units("i_dont_exist"))
        non_existent_unit = annotator.unit("i_dont_exist")
        self.assertIsNone(non_existent_unit.first)
        self.assertEqual(0, non_existent_unit.second)
        self.assertIsNone(annotator.reset("i_dont_exist"))
        self.assertIsNone(annotator.resetValue("i_dont_exist"))
        self.assertIsNone(annotator.testValue("i_dont_exist"))
        self.assertIsNone(annotator.componentRef("i_dont_exist"))
        non_existent_connection = annotator.connection("i_dont_exist")
        self.assertIsNone(non_existent_connection.first)
        self.assertIsNone(non_existent_connection.second)
        self.assertIsNone(annotator.importSource("i_dont_exist"))

    def test_ids(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()

        model = parser.parseModel(file_contents("annotator/unique_ids.cellml"))
        annotator.setModel(model)

        self.assertEqual(24, len(annotator.ids()))

    def test_duplicate_count(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()

        model = parser.parseModel(file_contents("annotator/lots_of_duplicate_ids.cellml"))
        annotator.setModel(model)

        self.assertEqual(8, annotator.duplicateCount("duplicateId1"))
        self.assertEqual(7, annotator.duplicateCount("duplicateId3"))

    def test_has_model(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()

        self.assertFalse(annotator.hasModel())

        model = parser.parseModel(file_contents("annotator/unique_ids.cellml"))
        annotator.setModel(model)

        self.assertTrue(annotator.hasModel())

    def test_is_unique(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()

        model = parser.parseModel(file_contents("annotator/unique_ids.cellml"))
        annotator.setModel(model)

        self.assertTrue(annotator.isUnique("variable_3"))

        model = parser.parseModel(file_contents("annotator/lots_of_duplicate_ids.cellml"))
        annotator.setModel(model)

        self.assertFalse(annotator.isUnique("duplicateId2"))

    def test_assign_by_type(self):
        from libcellml import Annotator, Parser, Variable
        from libcellml.annotator import UnitItem, VariablePair

        annotator = Annotator()
        parser = Parser()
        model_string = file_contents("annotator/no_ids.cellml")

        model = parser.parseModel(model_string)
        annotator.setModel(model)

        c = model.component(0)

        self.assertEqual("", model.id())
        annotator.assignModelId(model)
        self.assertEqual("b4da55", model.id())

        self.assertEqual("", model.encapsulationId())
        annotator.assignEncapsulationId(model)
        self.assertEqual("b4da56", model.encapsulationId())

        self.assertEqual("", c.id())
        annotator.assignComponentId(c)
        self.assertEqual("b4da57", c.id())

        self.assertEqual("", c.encapsulationId())
        annotator.assignComponentRefId(c)
        self.assertEqual("b4da58", c.encapsulationId())

        c2v1 = model.component("component2").variable("variable1")
        c3v1 = model.component("component3").variable("variable1")

        self.assertEqual("", Variable.equivalenceConnectionId(c2v1, c3v1))
        annotator.assignConnectionId(VariablePair(c2v1, c3v1))
        self.assertEqual("b4da59", Variable.equivalenceConnectionId(c2v1, c3v1))

        self.assertEqual("", Variable.equivalenceMappingId(c2v1, c3v1))
        annotator.assignMapVariablesId(VariablePair(c2v1, c3v1))
        self.assertEqual("b4da5a", Variable.equivalenceMappingId(c2v1, c3v1))

        c3v2 = model.component("component3").variable("variable2")

        self.assertEqual("", c3v2.id())
        annotator.assignVariableId(c3v2)
        self.assertEqual("b4da5b", c3v2.id())

        u = model.units(1)

        self.assertEqual("", u.id())
        annotator.assignUnitsId(u)
        self.assertEqual("b4da5c", u.id())

        r = model.component("component2").reset(0)

        self.assertEqual("", r.id())
        annotator.assignResetId(r)
        self.assertEqual("b4da5d", r.id())

        self.assertEqual("", r.testValueId())
        annotator.assignTestValueId(r)
        self.assertEqual("b4da5e", r.testValueId())

        self.assertEqual("", r.resetValueId())
        annotator.assignResetValueId(r)
        self.assertEqual("b4da5f", r.resetValueId())

        i = model.importSource(0)

        self.assertEqual("", i.id())
        annotator.assignImportSourceId(i)
        self.assertEqual("b4da60", i.id())

        self.assertEqual("", u.unitId(0))
        annotator.assignUnitId(UnitItem(u, 0))
        self.assertEqual("b4da61", u.unitId(0))

    def test_auto_ids(self):
        from libcellml import Annotator, Parser, Variable
        annotator = Annotator()
        parser = Parser()
        model_string = file_contents("annotator/unique_ids.cellml")

        model = parser.parseModel(model_string)
        annotator.setModel(model)

        annotator.clearAllIds()
        annotator.assignAllIds()

        self.assertEqual("b4da55", model.id())
        self.assertEqual("b4da56", model.importSource(0).id())
        self.assertEqual("b4da57", model.importSource(1).id())
        self.assertEqual("b4da58", model.units(0).id())
        self.assertEqual("b4da59", model.units(1).id())
        self.assertEqual("b4da5a", model.units(2).id())
        self.assertEqual("b4da5b", model.units(3).id())
        self.assertEqual("b4da5c", model.units(1).unitId(0))
        self.assertEqual("b4da5d", model.component(0).id())
        self.assertEqual("b4da5e", model.component(1).id())
        self.assertEqual("b4da5f", model.component(1).component(0).id())
        self.assertEqual("b4da60", model.component(1).variable(0).id())
        self.assertEqual("b4da61", model.component(1).variable(1).id())
        self.assertEqual("b4da62", model.component(
            1).component(0).variable(0).id())
        self.assertEqual("b4da63", model.component(
            1).component(0).variable(1).id())

        self.assertEqual("b4da64", model.component(1).reset(0).id())
        self.assertEqual("b4da65", model.component(1).reset(0).resetValueId())
        self.assertEqual("b4da66", model.component(1).reset(0).testValueId())

        c2v1 = model.component("component2").variable("variable1")
        c2v2 = model.component("component2").variable("variable2")
        c3v1 = model.component("component3").variable("variable1")
        c3v2 = model.component("component3").variable("variable2")

        self.assertEqual(
            "b4da67", Variable.equivalenceConnectionId(c2v1, c3v1))
        self.assertEqual(
            "b4da67", Variable.equivalenceConnectionId(c2v2, c3v2))
        self.assertEqual("b4da68", Variable.equivalenceMappingId(c2v1, c3v1))
        self.assertEqual("b4da69", Variable.equivalenceMappingId(c2v2, c3v2))
        self.assertEqual("b4da6a", model.component(
            "component2").encapsulationId())
        self.assertEqual("b4da6b", model.component(
            "component3").encapsulationId())
        self.assertEqual("b4da6c", model.encapsulationId())

    def test_assign_id(self):
        from libcellml import Annotator, Component, Model, Units
        from libcellml.annotator import UnitItem
        from libcellml.enums import CellMLElement_UNDEFINED

        annotator = Annotator()
        model = Model()
        component1 = Component("c1")
        component2 = Component("c2")
        component3 = Component("c3")
        component3.setId("id3")

        units = Units("u1")
        units.addUnit("volt")

        model.addComponent(component1)
        model.addComponent(component2)
        component2.addComponent(component3)
        model.addUnits(units)

        annotator.setModel(model)

        self.assertEqual("", component1.id())
        self.assertEqual("", component2.id())
        self.assertEqual("", units.unitId(0))

        annotator.assignId(component1)

        self.assertEqual("b4da55", component1.id())
        self.assertEqual("", component2.id())
        self.assertEqual("", units.unitId(0))

        annotator.assignId(UnitItem(units, 0))

        self.assertEqual("b4da55", component1.id())
        self.assertEqual("", component2.id())
        self.assertEqual("b4da56", units.unitId(0))

        self.assertEqual("", annotator.assignId(None, CellMLElement_UNDEFINED))

        item = annotator.item("id3")
        annotator.assignId(item)
        self.assertEqual("b4da57", component3.id())

        # For coverage only.
        annotator._assignId(component2)

    def test_auto_ids_group(self):
        from libcellml import Annotator, Component, Model
        from libcellml.enums import CellMLElement_COMPONENT
        annotator = Annotator()
        model = Model()
        component1 = Component("c1")
        component2 = Component("c2")
        component3 = Component("c3")

        model.addComponent(component1)
        model.addComponent(component2)
        component2.addComponent(component3)

        annotator.setModel(model)

        self.assertEqual("", model.id())
        self.assertEqual("", component1.id())
        self.assertEqual("", component2.id())
        self.assertEqual("", component3.id())

        annotator.assignIds(CellMLElement_COMPONENT)

        self.assertEqual("", model.id())
        self.assertEqual("b4da55", component1.id())
        self.assertEqual("b4da56", component2.id())
        self.assertEqual("b4da57", component3.id())

    def test_auto_id_individual(self):
        from libcellml import Annotator, CellMLElement, Parser, Variable
        from libcellml.annotator import UnitItem, VariablePair

        annotator = Annotator()
        parser = Parser()
        model_string = file_contents("annotator/no_ids.cellml")
        model = parser.parseModel(model_string)

        annotator.setModel(model)

        self.assertEqual("b4da55", annotator.assignId(model.component(0), CellMLElement.COMPONENT))
        self.assertEqual("b4da55", model.component(0).id())

        self.assertEqual("b4da56", annotator.assignId(model.component("component2"), CellMLElement.COMPONENT_REF))
        self.assertEqual("b4da56", model.component("component2").encapsulationId())

        self.assertEqual("b4da57", annotator.assignId(VariablePair(model.component("component2").variable("variable1"),
                                                                   model.component("component2").variable(
                                                                       "variable1").equivalentVariable(0)),
                                                      CellMLElement.CONNECTION))

        self.assertEqual("b4da57", Variable.equivalenceConnectionId(
            model.component("component2").variable("variable1"),
            model.component("component2").variable("variable1").equivalentVariable(0)))

        self.assertEqual("b4da58", annotator.assignId(model.importSource(0)))
        self.assertEqual("b4da58", model.importSource(0).id())

        self.assertEqual("b4da59", annotator.assignId(VariablePair(model.component("component2").variable("variable2"),
                                                                   model.component("component2").variable(
                                                                       "variable2").equivalentVariable(0)),
                                                      CellMLElement.MAP_VARIABLES))
        self.assertEqual("b4da59", Variable.equivalenceMappingId(model.component("component2").variable("variable2"),
                                                                 model.component("component2").variable(
                                                                     "variable2").equivalentVariable(0)))
        self.assertEqual("b4da5a", annotator.assignId(model, CellMLElement.MODEL))
        self.assertEqual("b4da5a", model.id())

        self.assertEqual("b4da5b", annotator.assignId(model.component("component2").reset(0), CellMLElement.RESET))
        self.assertEqual("b4da5b", model.component("component2").reset(0).id())

        self.assertEqual("b4da5c",
                         annotator.assignId(model.component("component2").reset(0), CellMLElement.RESET_VALUE))
        self.assertEqual("b4da5c", model.component("component2").reset(0).resetValueId())

        self.assertEqual("b4da5d", annotator.assignId(model.component("component2").reset(0), CellMLElement.TEST_VALUE))
        self.assertEqual("b4da5d", model.component("component2").reset(0).testValueId())

        self.assertEqual("b4da5e", annotator.assignId(UnitItem(model.units(1), 0)))
        self.assertEqual("b4da5e", model.units(1).unitId(0))

        self.assertEqual("b4da5f", annotator.assignId(model.units(1)))
        self.assertEqual("b4da5f", model.units(1).id())

        self.assertEqual("b4da60", annotator.assignId(model.component(1).variable(0)))
        self.assertEqual("b4da60", model.component(1).variable(0).id())

        self.assertEqual("b4da61", annotator.assignId(model, CellMLElement.ENCAPSULATION))
        self.assertEqual("b4da61", model.encapsulationId())

    def test_list_duplicate_ids(self):
        from libcellml import Annotator, CellMLElement, Parser

        model_string = file_contents("annotator/lots_of_duplicate_ids.cellml")

        parser = Parser()
        annotator = Annotator()
        model = parser.parseModel(model_string)
        annotator.setModel(model)
        id_list = annotator.duplicateIds()
        expected_ids = ('duplicateId1', 'duplicateId2', 'duplicateId3', 'duplicateId4')
        self.assertEqual(expected_ids, id_list)

        # Get the collections by duplicated id.
        c2v1 = model.component("component2").variable("variable1")
        c2v2 = model.component("component2").variable("variable2")
        c3v1 = model.component("component2").component("component3").variable("variable1")
        c3v2 = model.component("component2").component("component3").variable("variable2")
        c4v1 = model.component("component4").variable("variable1")
        c4v2 = model.component("component4").variable("variable2")

        expected_items = {
            "duplicateId1": (
                (CellMLElement.UNITS, model.units("units2")),
                (CellMLElement.IMPORT, model.importSource(0)),
                (CellMLElement.MAP_VARIABLES, (c4v1, c2v1)),
                (CellMLElement.COMPONENT, model.component("component2")),
                (CellMLElement.CONNECTION, (c2v1, c3v1)),
                (CellMLElement.TEST_VALUE, model.component("component2").reset(0)),
                (CellMLElement.COMPONENT_REF, model.component("component2").component("component3")),
                (CellMLElement.VARIABLE, model.component("component2").component("component3").variable("variable2")),
            ),
            "duplicateId2": (
                (CellMLElement.MODEL, model),
                (CellMLElement.UNITS, model.units("units1")),
                (CellMLElement.UNITS, model.units("blob")),
                (CellMLElement.CONNECTION, (c4v2, c2v2)),
                (CellMLElement.VARIABLE, c4v2),
                (CellMLElement.COMPONENT_REF, model.component("component2")),
                (CellMLElement.RESET, model.component("component2").reset(0)),
                (CellMLElement.VARIABLE, c3v1),
            ),
            "duplicateId3": (
                (CellMLElement.IMPORT, model.importSource(1)),
                (CellMLElement.UNITS, model.units("units3")),
                (CellMLElement.VARIABLE, c4v1),
                (CellMLElement.VARIABLE, c2v2),
                (CellMLElement.MAP_VARIABLES, (c2v2, c4v2)),
                (CellMLElement.COMPONENT, model.component("component2").component("component3")),
                (CellMLElement.ENCAPSULATION, model),
            ),
            "duplicateId4": (
                (CellMLElement.UNIT, ((model.units("units2"), 0))),
                (CellMLElement.COMPONENT, model.component("component1")),
                (CellMLElement.COMPONENT, model.component("component4")),
                (CellMLElement.MAP_VARIABLES, (c2v1, c3v1)),
                (CellMLElement.VARIABLE, c2v1),
                (CellMLElement.MAP_VARIABLES, (c2v2, c4v2)),
                (CellMLElement.RESET_VALUE, model.component("component2").reset(0)),
            )}

        for id in expected_ids:
            items_with_id = annotator.items(id)
            count = 0
            for item in items_with_id:
                self.assertEqual(item[0], expected_items[id][count][0])
                # SWIG copies the pointers so can't expect a comparison to be true. Not sure how to
                # compare these ...
                # self.assertEqual(item[1], expected_items[id][count][1])
                count = count + 1

    def test_unit_item_coverage(self):
        from libcellml import Units
        from libcellml.annotator import UnitItem

        u = Units("bob")
        u_i = UnitItem()
        self.assertEqual(2, len(u_i))
        self.assertEqual("(None, 0)", str(u_i))
        u_i[0] = u
        u_i[1] = 4
        self.assertEqual("bob", u_i.first.name())
        self.assertEqual(4, u_i.second)

    def test_variable_pair_coverage(self):
        from libcellml import Variable
        from libcellml.annotator import VariablePair
        
        v1 = Variable("ray")
        v2 = Variable("charles")
        v_p = VariablePair()
        self.assertEqual(2, len(v_p))
        self.assertEqual("(None, None)", str(v_p))
        v_p[0] = v1
        v_p[1] = v2
        self.assertEqual("ray", v_p.first.name())
        self.assertEqual("charles", v_p.second.name())

    def test_assign_ids_to_duplicates(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()
        model_string = file_contents("annotator/lots_of_duplicate_ids.cellml")
        model = parser.parseModel(model_string)
        annotator.setModel(model)

        for id in annotator.duplicateIds():
            item_list = annotator.items(id)
            for item in item_list:
                annotator.assignId(item)
            self.assertEqual(0, annotator.duplicateCount(id))

    def test_raise_not_found_issue(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()

        message = 'Could not find an item with an id of \'i_dont_exist\' in the model.'

        model = parser.parseModel(file_contents('annotator/unique_ids.cellml'))
        annotator.setModel(model)
        annotator.item('i_dont_exist')

        self.assertEqual(1, annotator.issueCount())
        self.assertEqual(message, annotator.issue(0).description())

    def test_raise_non_unique_issue(self):
        from libcellml import Annotator, Parser

        annotator = Annotator()
        parser = Parser()

        non_unique_message = 'The id \'duplicateId\' occurs 29 times in the model so a unique item cannot be located.'

        model = parser.parseModel(file_contents('annotator/duplicate_ids.cellml'))
        annotator.setModel(model)

        annotator.item('duplicateId')
        self.assertEqual(1, annotator.issueCount())
        self.assertEqual(non_unique_message, annotator.issue(0).description())


if __name__ == '__main__':
    unittest.main()
