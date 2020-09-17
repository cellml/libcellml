#
# Tests the GeneratorProfile class bindings
#
import unittest


class GeneratorProfileTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import GeneratorProfile

        x = GeneratorProfile()
        del x

    def test_generator_profile(self):
        from libcellml import GeneratorProfile

        # Create a default, i.e. C, profile.
        p = GeneratorProfile()
        self.assertEqual(GeneratorProfile.Profile.C, p.profile())

        # Make the profile a Python profile.
        p.setProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, p.profile())

        # Create a Python profile.
        pp = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
        self.assertEqual(GeneratorProfile.Profile.PYTHON, pp.profile())

    @unittest.skip("Create tests script")
    def test_create_tests(self):
        import re
        from libcellml import GeneratorProfile

        p = GeneratorProfile()

        seen = {}

        def working_name(entry):
            name = re.sub('([A-Z]{1})', r'_\1', entry).lower()
            if name.startswith("set"):
                name = name[4:]

            return name

        def ignore(entry):
            if entry.startswith("_") or entry in ["Profile", "profile", "this", "thisown"]:
                return True

            return False

        def visited(entry):
            result = entry in seen

            return entry in seen
            if entry not in seen:
                seen[entry] = True
                return False

            return True

        def getSetNames(entry):
            if entry.startswith("set"):
                getter = entry[3:]
                getter = getter[0].lower() + getter[1:]
                return [getter, entry]
            else:
                setter = entry
                setter = "set" + setter[0].upper() + setter[1:]
                return [entry, setter]

        def printStringMethod(entry):

            [getter, setter] = getSetNames(entry)
            content = getattr(p, getter)()
            content = content.replace("\n", "\\n")
            print("        from libcellml import GeneratorProfile")
            print("        ")
            print("        g = GeneratorProfile()")
            print("        ")
            print(f"        self.assertEqual(\"{content}\", g.{getter}())")
            print(f"        g.{setter}(\"Some text content.\")")
            print(f"        self.assertEqual(\"Some text content.\", g.{getter}())")
            print("        ")

        def printHasMethod(entry):
            print("        from libcellml import GeneratorProfile")
            print("        ")
            print("        g = GeneratorProfile()")
            print("        ")
            print("        self.assertFalse(g.{0}())".format(entry))
            print("        ")

        def isStringMethod(name):
            return name.endswith("string")

        def isHasMethod(name):
            return name.startswith("has")

        for entry in dir(p):
            name = working_name(entry)
            if not ignore(entry) and not name in seen:
                seen[name] = True
                print("    def test_{0}(self):".format(name))
                if isStringMethod(name):
                    printStringMethod(entry)
                elif isHasMethod(name):
                    printHasMethod(entry)
                else:
                    print("        # Yikes missing this method: " + entry)

    def test_absolute_value_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("fabs", g.absoluteValueString())
        g.setAbsoluteValueString("Some text content.")
        self.assertEqual("Some text content.", g.absoluteValueString())

    def test_acos_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acos", g.acosString())
        g.setAcosString("Some text content.")
        self.assertEqual("Some text content.", g.acosString())

    def test_acosh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acosh", g.acoshString())
        g.setAcoshString("Some text content.")
        self.assertEqual("Some text content.", g.acoshString())

    def test_acot_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double acot(double x)\n{\n    return atan(1.0/x);\n}\n", g.acotFunctionString())
        g.setAcotFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.acotFunctionString())

    def test_acot_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acot", g.acotString())
        g.setAcotString("Some text content.")
        self.assertEqual("Some text content.", g.acotString())

    def test_acoth_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double acoth(double x)\n{\n    double oneOverX = 1.0/x;\n\n    return 0.5*log((1.0+oneOverX)/(1.0-oneOverX));\n}\n",
            g.acothFunctionString())
        g.setAcothFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.acothFunctionString())

    def test_acoth_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acoth", g.acothString())
        g.setAcothString("Some text content.")
        self.assertEqual("Some text content.", g.acothString())

    def test_acsc_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double acsc(double x)\n{\n    return asin(1.0/x);\n}\n", g.acscFunctionString())
        g.setAcscFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.acscFunctionString())

    def test_acsc_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acsc", g.acscString())
        g.setAcscString("Some text content.")
        self.assertEqual("Some text content.", g.acscString())

    def test_acsch_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double acsch(double x)\n{\n    double oneOverX = 1.0/x;\n\n    return log(oneOverX+sqrt(oneOverX*oneOverX+1.0));\n}\n",
            g.acschFunctionString())
        g.setAcschFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.acschFunctionString())

    def test_acsch_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("acsch", g.acschString())
        g.setAcschString("Some text content.")
        self.assertEqual("Some text content.", g.acschString())

    def test_algebraic_variable_type_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("ALGEBRAIC", g.algebraicVariableTypeString())
        g.setAlgebraicVariableTypeString("Some text content.")
        self.assertEqual("Some text content.", g.algebraicVariableTypeString())

    def test_and_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.andFunctionString())
        g.setAndFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.andFunctionString())

    def test_and_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" && ", g.andString())
        g.setAndString("Some text content.")
        self.assertEqual("Some text content.", g.andString())

    def test_array_element_separator_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(",", g.arrayElementSeparatorString())
        g.setArrayElementSeparatorString("Some text content.")
        self.assertEqual("Some text content.", g.arrayElementSeparatorString())

    def test_asec_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double asec(double x)\n{\n    return acos(1.0/x);\n}\n", g.asecFunctionString())
        g.setAsecFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.asecFunctionString())

    def test_asec_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asec", g.asecString())
        g.setAsecString("Some text content.")
        self.assertEqual("Some text content.", g.asecString())

    def test_asech_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double asech(double x)\n{\n    double oneOverX = 1.0/x;\n\n    return log(oneOverX+sqrt(oneOverX*oneOverX-1.0));\n}\n",
            g.asechFunctionString())
        g.setAsechFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.asechFunctionString())

    def test_asech_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asech", g.asechString())
        g.setAsechString("Some text content.")
        self.assertEqual("Some text content.", g.asechString())

    def test_asin_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asin", g.asinString())
        g.setAsinString("Some text content.")
        self.assertEqual("Some text content.", g.asinString())

    def test_asinh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("asinh", g.asinhString())
        g.setAsinhString("Some text content.")
        self.assertEqual("Some text content.", g.asinhString())

    def test_assignment_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" = ", g.assignmentString())
        g.setAssignmentString("Some text content.")
        self.assertEqual("Some text content.", g.assignmentString())

    def test_atan_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("atan", g.atanString())
        g.setAtanString("Some text content.")
        self.assertEqual("Some text content.", g.atanString())

    def test_atanh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("atanh", g.atanhString())
        g.setAtanhString("Some text content.")
        self.assertEqual("Some text content.", g.atanhString())

    def test_ceiling_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("ceil", g.ceilingString())
        g.setCeilingString("Some text content.")
        self.assertEqual("Some text content.", g.ceilingString())

    def test_close_array_initializer_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("}", g.closeArrayInitializerString())
        g.setCloseArrayInitializerString("Some text content.")
        self.assertEqual("Some text content.", g.closeArrayInitializerString())

    def test_close_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("]", g.closeArrayString())
        g.setCloseArrayString("Some text content.")
        self.assertEqual("Some text content.", g.closeArrayString())

    def test_command_separator_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(";", g.commandSeparatorString())
        g.setCommandSeparatorString("Some text content.")
        self.assertEqual("Some text content.", g.commandSeparatorString())

    def test_comment_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("/* <CODE> */\n", g.commentString())
        g.setCommentString("Some text content.")
        self.assertEqual("Some text content.", g.commentString())

    def test_common_logarithm_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("log10", g.commonLogarithmString())
        g.setCommonLogarithmString("Some text content.")
        self.assertEqual("Some text content.", g.commonLogarithmString())

    def test_computed_constant_variable_type_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("COMPUTED_CONSTANT", g.computedConstantVariableTypeString())
        g.setComputedConstantVariableTypeString("Some text content.")
        self.assertEqual("Some text content.", g.computedConstantVariableTypeString())

    def test_conditional_operator_else_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(":<ELSE_STATEMENT>", g.conditionalOperatorElseString())
        g.setConditionalOperatorElseString("Some text content.")
        self.assertEqual("Some text content.", g.conditionalOperatorElseString())

    def test_conditional_operator_if_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("(<CONDITION>)?<IF_STATEMENT>", g.conditionalOperatorIfString())
        g.setConditionalOperatorIfString("Some text content.")
        self.assertEqual("Some text content.", g.conditionalOperatorIfString())

    def test_constant_variable_type_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("CONSTANT", g.constantVariableTypeString())
        g.setConstantVariableTypeString("Some text content.")
        self.assertEqual("Some text content.", g.constantVariableTypeString())

    def test_cos_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("cos", g.cosString())
        g.setCosString("Some text content.")
        self.assertEqual("Some text content.", g.cosString())

    def test_cosh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("cosh", g.coshString())
        g.setCoshString("Some text content.")
        self.assertEqual("Some text content.", g.coshString())

    def test_cot_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double cot(double x)\n{\n    return 1.0/tan(x);\n}\n", g.cotFunctionString())
        g.setCotFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.cotFunctionString())

    def test_cot_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("cot", g.cotString())
        g.setCotString("Some text content.")
        self.assertEqual("Some text content.", g.cotString())

    def test_coth_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double coth(double x)\n{\n    return 1.0/tanh(x);\n}\n", g.cothFunctionString())
        g.setCothFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.cothFunctionString())

    def test_coth_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("coth", g.cothString())
        g.setCothString("Some text content.")
        self.assertEqual("Some text content.", g.cothString())

    def test_csc_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double csc(double x)\n{\n    return 1.0/sin(x);\n}\n", g.cscFunctionString())
        g.setCscFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.cscFunctionString())

    def test_csc_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("csc", g.cscString())
        g.setCscString("Some text content.")
        self.assertEqual("Some text content.", g.cscString())

    def test_csch_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double csch(double x)\n{\n    return 1.0/sinh(x);\n}\n", g.cschFunctionString())
        g.setCschFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.cschFunctionString())

    def test_csch_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("csch", g.cschString())
        g.setCschString("Some text content.")
        self.assertEqual("Some text content.", g.cschString())

    def test_divide_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("/", g.divideString())
        g.setDivideString("Some text content.")
        self.assertEqual("Some text content.", g.divideString())

    def test_e_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("2.71828182845905", g.eString())
        g.setEString("Some text content.")
        self.assertEqual("Some text content.", g.eString())

    def test_empty_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.emptyMethodString())
        g.setEmptyMethodString("Some text content.")
        self.assertEqual("Some text content.", g.emptyMethodString())

    def test_eq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.eqFunctionString())
        g.setEqFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.eqFunctionString())

    def test_eq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" == ", g.eqString())
        g.setEqString("Some text content.")
        self.assertEqual("Some text content.", g.eqString())

    def test_exponential_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("exp", g.exponentialString())
        g.setExponentialString("Some text content.")
        self.assertEqual("Some text content.", g.exponentialString())

    def test_false_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("0.0", g.falseString())
        g.setFalseString("Some text content.")
        self.assertEqual("Some text content.", g.falseString())

    def test_floor_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("floor", g.floorString())
        g.setFloorString("Some text content.")
        self.assertEqual("Some text content.", g.floorString())

    def test_geq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.geqFunctionString())
        g.setGeqFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.geqFunctionString())

    def test_geq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" >= ", g.geqString())
        g.setGeqString("Some text content.")
        self.assertEqual("Some text content.", g.geqString())

    def test_gt_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.gtFunctionString())
        g.setGtFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.gtFunctionString())

    def test_gt_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" > ", g.gtString())
        g.setGtString("Some text content.")
        self.assertEqual("Some text content.", g.gtString())

    def test_has_and_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasAndOperator())
        g.setHasAndOperator(False)
        self.assertFalse(g.hasAndOperator())

    def test_has_conditional_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasConditionalOperator())
        g.setHasConditionalOperator(False)
        self.assertFalse(g.hasConditionalOperator())

    def test_has_eq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasEqOperator())
        g.setHasEqOperator(False)
        self.assertFalse(g.hasEqOperator())

    def test_has_geq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasGeqOperator())
        g.setHasGeqOperator(False)
        self.assertFalse(g.hasGeqOperator())

    def test_has_gt_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasGtOperator())
        g.setHasGtOperator(False)
        self.assertFalse(g.hasGtOperator())

    def test_has_leq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasLeqOperator())
        g.setHasLeqOperator(False)
        self.assertFalse(g.hasLeqOperator())

    def test_has_lt_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasLtOperator())
        g.setHasLtOperator(False)
        self.assertFalse(g.hasLtOperator())

    def test_has_neq_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasNeqOperator())
        g.setHasNeqOperator(False)
        self.assertFalse(g.hasNeqOperator())

    def test_has_not_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasNotOperator())
        g.setHasNotOperator(False)
        self.assertFalse(g.hasNotOperator())

    def test_has_or_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertTrue(g.hasOrOperator())
        g.setHasOrOperator(False)
        self.assertFalse(g.hasOrOperator())

    def test_has_power_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertFalse(g.hasPowerOperator())
        g.setHasPowerOperator(True)
        self.assertTrue(g.hasPowerOperator())

    def test_has_xor_operator(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertFalse(g.hasXorOperator())
        g.setHasXorOperator(True)
        self.assertTrue(g.hasXorOperator())

    def test_implementation_compute_computed_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeComputedConstants(double *variables)\n{\n<CODE>}\n",
                         g.implementationComputeComputedConstantsMethodString())
        g.setImplementationComputeComputedConstantsMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationComputeComputedConstantsMethodString())

    def test_implementation_compute_rates_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "void computeRates(double voi, double *states, double *rates, double *variables)\n{\n<CODE>}\n",
            g.implementationComputeRatesMethodString())
        g.setImplementationComputeRatesMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationComputeRatesMethodString())

    def test_implementation_compute_variables_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "void computeVariables(double voi, double *states, double *rates, double *variables)\n{\n<CODE>}\n",
            g.implementationComputeVariablesMethodString())
        g.setImplementationComputeVariablesMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationComputeVariablesMethodString())

    def test_implementation_create_states_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double * createStatesArray()\n{\n    return (double *) malloc(STATE_COUNT*sizeof(double));\n}\n",
            g.implementationCreateStatesArrayMethodString())
        g.setImplementationCreateStatesArrayMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationCreateStatesArrayMethodString())

    def test_implementation_create_variables_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "double * createVariablesArray()\n{\n    return (double *) malloc(VARIABLE_COUNT*sizeof(double));\n}\n",
            g.implementationCreateVariablesArrayMethodString())
        g.setImplementationCreateVariablesArrayMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationCreateVariablesArrayMethodString())

    def test_implementation_delete_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void deleteArray(double *array)\n{\n    free(array);\n}\n",
                         g.implementationDeleteArrayMethodString())
        g.setImplementationDeleteArrayMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationDeleteArrayMethodString())

    def test_implementation_header_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("#include \"<INTERFACE_FILE_NAME>\"\n\n#include <math.h>\n#include <stdlib.h>\n",
                         g.implementationHeaderString())
        g.setImplementationHeaderString("Some text content.")
        self.assertEqual("Some text content.", g.implementationHeaderString())

    def test_implementation_initialize_states_and_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void initializeStatesAndConstants(double *states, double *variables)\n{\n<CODE>}\n",
                         g.implementationInitializeStatesAndConstantsMethodString())
        g.setImplementationInitializeStatesAndConstantsMethodString("Some text content.")
        self.assertEqual("Some text content.", g.implementationInitializeStatesAndConstantsMethodString())

    def test_implementation_libcellml_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const char LIBCELLML_VERSION[] = \"<LIBCELLML_VERSION>\";\n",
                         g.implementationLibcellmlVersionString())
        g.setImplementationLibcellmlVersionString("Some text content.")
        self.assertEqual("Some text content.", g.implementationLibcellmlVersionString())

    def test_implementation_state_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const size_t STATE_COUNT = <STATE_COUNT>;\n", g.implementationStateCountString())
        g.setImplementationStateCountString("Some text content.")
        self.assertEqual("Some text content.", g.implementationStateCountString())

    def test_implementation_state_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const VariableInfo STATE_INFO[] = {\n<CODE>};\n", g.implementationStateInfoString())
        g.setImplementationStateInfoString("Some text content.")
        self.assertEqual("Some text content.", g.implementationStateInfoString())

    def test_implementation_variable_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const size_t VARIABLE_COUNT = <VARIABLE_COUNT>;\n", g.implementationVariableCountString())
        g.setImplementationVariableCountString("Some text content.")
        self.assertEqual("Some text content.", g.implementationVariableCountString())

    def test_implementation_variable_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const VariableInfoWithType VARIABLE_INFO[] = {\n<CODE>};\n",
                         g.implementationVariableInfoString())
        g.setImplementationVariableInfoString("Some text content.")
        self.assertEqual("Some text content.", g.implementationVariableInfoString())

    def test_implementation_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const char VERSION[] = \"0.1.0\";\n", g.implementationVersionString())
        g.setImplementationVersionString("Some text content.")
        self.assertEqual("Some text content.", g.implementationVersionString())

    def test_implementation_voi_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("const VariableInfo VOI_INFO = <CODE>;\n", g.implementationVoiInfoString())
        g.setImplementationVoiInfoString("Some text content.")
        self.assertEqual("Some text content.", g.implementationVoiInfoString())

    def test_indent_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("    ", g.indentString())
        g.setIndentString("Some text content.")
        self.assertEqual("Some text content.", g.indentString())

    def test_inf_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("INFINITY", g.infString())
        g.setInfString("Some text content.")
        self.assertEqual("Some text content.", g.infString())

    def test_interface_compute_computed_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeComputedConstants(double *variables);\n",
                         g.interfaceComputeComputedConstantsMethodString())
        g.setInterfaceComputeComputedConstantsMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceComputeComputedConstantsMethodString())

    def test_interface_compute_rates_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeRates(double voi, double *states, double *rates, double *variables);\n",
                         g.interfaceComputeRatesMethodString())
        g.setInterfaceComputeRatesMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceComputeRatesMethodString())

    def test_interface_compute_variables_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void computeVariables(double voi, double *states, double *rates, double *variables);\n",
                         g.interfaceComputeVariablesMethodString())
        g.setInterfaceComputeVariablesMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceComputeVariablesMethodString())

    def test_interface_create_states_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double * createStatesArray();\n", g.interfaceCreateStatesArrayMethodString())
        g.setInterfaceCreateStatesArrayMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceCreateStatesArrayMethodString())

    def test_interface_create_variables_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double * createVariablesArray();\n", g.interfaceCreateVariablesArrayMethodString())
        g.setInterfaceCreateVariablesArrayMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceCreateVariablesArrayMethodString())

    def test_interface_delete_array_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void deleteArray(double *array);\n", g.interfaceDeleteArrayMethodString())
        g.setInterfaceDeleteArrayMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceDeleteArrayMethodString())

    def test_interface_file_name_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("model.h", g.interfaceFileNameString())
        g.setInterfaceFileNameString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceFileNameString())

    def test_interface_header_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("#pragma once\n\n#include <stddef.h>\n", g.interfaceHeaderString())
        g.setInterfaceHeaderString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceHeaderString())

    def test_interface_initialize_states_and_constants_method_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("void initializeStatesAndConstants(double *states, double *variables);\n",
                         g.interfaceInitializeStatesAndConstantsMethodString())
        g.setInterfaceInitializeStatesAndConstantsMethodString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceInitializeStatesAndConstantsMethodString())

    def test_interface_libcellml_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const char LIBCELLML_VERSION[];\n", g.interfaceLibcellmlVersionString())
        g.setInterfaceLibcellmlVersionString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceLibcellmlVersionString())

    def test_interface_state_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const size_t STATE_COUNT;\n", g.interfaceStateCountString())
        g.setInterfaceStateCountString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceStateCountString())

    def test_interface_state_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const VariableInfo STATE_INFO[];\n", g.interfaceStateInfoString())
        g.setInterfaceStateInfoString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceStateInfoString())

    def test_interface_variable_count_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const size_t VARIABLE_COUNT;\n", g.interfaceVariableCountString())
        g.setInterfaceVariableCountString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceVariableCountString())

    def test_interface_variable_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const VariableInfoWithType VARIABLE_INFO[];\n", g.interfaceVariableInfoString())
        g.setInterfaceVariableInfoString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceVariableInfoString())

    def test_interface_version_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const char VERSION[];\n", g.interfaceVersionString())
        g.setInterfaceVersionString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceVersionString())

    def test_interface_voi_info_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("extern const VariableInfo VOI_INFO;\n", g.interfaceVoiInfoString())
        g.setInterfaceVoiInfoString("Some text content.")
        self.assertEqual("Some text content.", g.interfaceVoiInfoString())

    def test_leq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.leqFunctionString())
        g.setLeqFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.leqFunctionString())

    def test_leq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" <= ", g.leqString())
        g.setLeqString("Some text content.")
        self.assertEqual("Some text content.", g.leqString())

    def test_lt_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.ltFunctionString())
        g.setLtFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.ltFunctionString())

    def test_lt_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" < ", g.ltString())
        g.setLtString("Some text content.")
        self.assertEqual("Some text content.", g.ltString())

    def test_max_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double max(double x, double y)\n{\n    return (x > y)?x:y;\n}\n", g.maxFunctionString())
        g.setMaxFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.maxFunctionString())

    def test_max_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("max", g.maxString())
        g.setMaxString("Some text content.")
        self.assertEqual("Some text content.", g.maxString())

    def test_min_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double min(double x, double y)\n{\n    return (x < y)?x:y;\n}\n", g.minFunctionString())
        g.setMinFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.minFunctionString())

    def test_min_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("min", g.minString())
        g.setMinString("Some text content.")
        self.assertEqual("Some text content.", g.minString())

    def test_minus_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("-", g.minusString())
        g.setMinusString("Some text content.")
        self.assertEqual("Some text content.", g.minusString())

    def test_nan_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("NAN", g.nanString())
        g.setNanString("Some text content.")
        self.assertEqual("Some text content.", g.nanString())

    def test_napierian_logarithm_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("log", g.napierianLogarithmString())
        g.setNapierianLogarithmString("Some text content.")
        self.assertEqual("Some text content.", g.napierianLogarithmString())

    def test_neq_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.neqFunctionString())
        g.setNeqFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.neqFunctionString())

    def test_neq_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" != ", g.neqString())
        g.setNeqString("Some text content.")
        self.assertEqual("Some text content.", g.neqString())

    def test_not_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.notFunctionString())
        g.setNotFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.notFunctionString())

    def test_not_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("!", g.notString())
        g.setNotString("Some text content.")
        self.assertEqual("Some text content.", g.notString())

    def test_open_array_initializer_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("{", g.openArrayInitializerString())
        g.setOpenArrayInitializerString("Some text content.")
        self.assertEqual("Some text content.", g.openArrayInitializerString())

    def test_open_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("[", g.openArrayString())
        g.setOpenArrayString("Some text content.")
        self.assertEqual("Some text content.", g.openArrayString())

    def test_or_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.orFunctionString())
        g.setOrFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.orFunctionString())

    def test_or_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(" || ", g.orString())
        g.setOrString("Some text content.")
        self.assertEqual("Some text content.", g.orString())

    def test_origin_comment_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "The content of this file was generated using <PROFILE_INFORMATION> libCellML <LIBCELLML_VERSION>.",
            g.originCommentString())
        g.setOriginCommentString("Some text content.")
        self.assertEqual("Some text content.", g.originCommentString())

    def test_pi_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("3.14159265358979", g.piString())
        g.setPiString("Some text content.")
        self.assertEqual("Some text content.", g.piString())

    def test_piecewise_else_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.piecewiseElseString())
        g.setPiecewiseElseString("Some text content.")
        self.assertEqual("Some text content.", g.piecewiseElseString())

    def test_piecewise_if_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.piecewiseIfString())
        g.setPiecewiseIfString("Some text content.")
        self.assertEqual("Some text content.", g.piecewiseIfString())

    def test_plus_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("+", g.plusString())
        g.setPlusString("Some text content.")
        self.assertEqual("Some text content.", g.plusString())

    def test_power_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("pow", g.powerString())
        g.setPowerString("Some text content.")
        self.assertEqual("Some text content.", g.powerString())

    def test_rates_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("rates", g.ratesArrayString())
        g.setRatesArrayString("Some text content.")
        self.assertEqual("Some text content.", g.ratesArrayString())

    def test_rem_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("fmod", g.remString())
        g.setRemString("Some text content.")
        self.assertEqual("Some text content.", g.remString())

    def test_sec_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double sec(double x)\n{\n    return 1.0/cos(x);\n}\n", g.secFunctionString())
        g.setSecFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.secFunctionString())

    def test_sec_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sec", g.secString())
        g.setSecString("Some text content.")
        self.assertEqual("Some text content.", g.secString())

    def test_sech_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double sech(double x)\n{\n    return 1.0/cosh(x);\n}\n", g.sechFunctionString())
        g.setSechFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.sechFunctionString())

    def test_sech_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sech", g.sechString())
        g.setSechString("Some text content.")
        self.assertEqual("Some text content.", g.sechString())

    def test_sin_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sin", g.sinString())
        g.setSinString("Some text content.")
        self.assertEqual("Some text content.", g.sinString())

    def test_sinh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sinh", g.sinhString())
        g.setSinhString("Some text content.")
        self.assertEqual("Some text content.", g.sinhString())

    def test_square_root_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("sqrt", g.squareRootString())
        g.setSquareRootString("Some text content.")
        self.assertEqual("Some text content.", g.squareRootString())

    def test_square_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("", g.squareString())
        g.setSquareString("Some text content.")
        self.assertEqual("Some text content.", g.squareString())

    def test_states_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("states", g.statesArrayString())
        g.setStatesArrayString("Some text content.")
        self.assertEqual("Some text content.", g.statesArrayString())

    def test_string_delimiter_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("\"", g.stringDelimiterString())
        g.setStringDelimiterString("Some text content.")
        self.assertEqual("Some text content.", g.stringDelimiterString())

    def test_tan_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("tan", g.tanString())
        g.setTanString("Some text content.")
        self.assertEqual("Some text content.", g.tanString())

    def test_tanh_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("tanh", g.tanhString())
        g.setTanhString("Some text content.")
        self.assertEqual("Some text content.", g.tanhString())

    def test_times_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("*", g.timesString())
        g.setTimesString("Some text content.")
        self.assertEqual("Some text content.", g.timesString())

    def test_true_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("1.0", g.trueString())
        g.setTrueString("Some text content.")
        self.assertEqual("Some text content.", g.trueString())

    def test_variable_info_entry_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\"}", g.variableInfoEntryString())
        g.setVariableInfoEntryString("Some text content.")
        self.assertEqual("Some text content.", g.variableInfoEntryString())

    def test_variable_info_object_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "typedef struct {\n    char name[<NAME_SIZE>];\n    char units[<UNITS_SIZE>];\n    char component[<COMPONENT_SIZE>];\n} VariableInfo;\n",
            g.variableInfoObjectString())
        g.setVariableInfoObjectString("Some text content.")
        self.assertEqual("Some text content.", g.variableInfoObjectString())

    def test_variable_info_with_type_entry_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("{\"<NAME>\", \"<UNITS>\", \"<COMPONENT>\", <TYPE>}", g.variableInfoWithTypeEntryString())
        g.setVariableInfoWithTypeEntryString("Some text content.")
        self.assertEqual("Some text content.", g.variableInfoWithTypeEntryString())

    def test_variable_info_with_type_object_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual(
            "typedef struct {\n    char name[<NAME_SIZE>];\n    char units[<UNITS_SIZE>];\n    char component[<COMPONENT_SIZE>];\n    VariableType type;\n} VariableInfoWithType;\n",
            g.variableInfoWithTypeObjectString())
        g.setVariableInfoWithTypeObjectString("Some text content.")
        self.assertEqual("Some text content.", g.variableInfoWithTypeObjectString())

    def test_variable_type_object_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("typedef enum {\n    CONSTANT,\n    COMPUTED_CONSTANT,\n    ALGEBRAIC\n} VariableType;\n",
                         g.variableTypeObjectString())
        g.setVariableTypeObjectString("Some text content.")
        self.assertEqual("Some text content.", g.variableTypeObjectString())

    def test_variables_array_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("variables", g.variablesArrayString())
        g.setVariablesArrayString("Some text content.")
        self.assertEqual("Some text content.", g.variablesArrayString())

    def test_voi_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("voi", g.voiString())
        g.setVoiString("Some text content.")
        self.assertEqual("Some text content.", g.voiString())

    def test_xor_function_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("double xor(double x, double y)\n{\n    return (x != 0.0) ^ (y != 0.0);\n}\n",
                         g.xorFunctionString())
        g.setXorFunctionString("Some text content.")
        self.assertEqual("Some text content.", g.xorFunctionString())

    def test_xor_string(self):
        from libcellml import GeneratorProfile

        g = GeneratorProfile()

        self.assertEqual("xor", g.xorString())
        g.setXorString("Some text content.")
        self.assertEqual("Some text content.", g.xorString())


if __name__ == '__main__':
    unittest.main()
