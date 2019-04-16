/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "test_utils.h"

#include "gtest/gtest.h"

#include <libcellml>

/*
 * The tests in this file are here to catch any branches of code that
 * are not picked up by the main tests testing the API of the library
 */

 /**
 These are the definitions from the current CellML 2.0 draft standard.  The lines below feed a
 set of doxygen files which will be used to compare the current validation tests against the
 standard.  Use the alias codes "at"cellml2_[2-19] to leave a note in the documentation where a
 test is performed.  NB: Single line comments need to start with three slashes instead of two.

 The following lines will need to be manually added to the Doxyfile in order to generate the
 documentation correctly.

 ALIASES                = "cellml2_2=\xrefitem CellML2_2 \"CellML2_2\" \"CellML 2.0: 2. General Matters \""
 ALIASES				   += "cellml2_3=\xrefitem CellML2_3 \"CellML2_3\" \"CellML 2.0: 3. Data representation \""
 ALIASES				   += "cellml2_4=\xrefitem CellML2_4 \"CellML2_4\" \"CellML 2.0: 4. Model elements \""
 ALIASES				   += "cellml2_5=\xrefitem CellML2_5 \"CellML2_5\" \"CellML 2.0: 5. Import elements \""
 ALIASES				   += "cellml2_6=\xrefitem CellML2_6 \"CellML2_6\" \"CellML 2.0: 6. Import-units elements \""
 ALIASES				   += "cellml2_7=\xrefitem CellML2_7 \"CellML2_7\" \"CellML 2.0: 7. Import-component elements \""
 ALIASES				   += "cellml2_8=\xrefitem CellML2_8 \"CellML2_8\" \"CellML 2.0: 8. Units elements \""
 ALIASES				   += "cellml2_9=\xrefitem CellML2_9 \"CellML2_9\" \"CellML 2.0: 9. Unit elements \""
 ALIASES				   += "cellml2_10=\xrefitem CellML2_10 \"CellML2_10\" \"CellML 2.0: 10. Component elements \""
 ALIASES				   += "cellml2_11=\xrefitem CellML2_11 \"CellML2_11\" \"CellML 2.0: 11. Variable elements \""
 ALIASES				   += "cellml2_12=\xrefitem CellML2_12 \"CellML2_12\" \"CellML 2.0: 12. Reset elements \""
 ALIASES				   += "cellml2_13=\xrefitem CellML2_13 \"CellML2_13\" \"CellML 2.0: 13. When elements \""
 ALIASES				   += "cellml2_14=\xrefitem CellML2_14 \"CellML2_14\" \"CellML 2.0: 14. Math elements \""
 ALIASES				   += "cellml2_15=\xrefitem CellML2_15 \"CellML2_15\" \"CellML 2.0: 15. Encapsulation elements \""
 ALIASES				   += "cellml2_16=\xrefitem CellML2_16 \"CellML2_16\" \"CellML 2.0: 16. Component-ref elements \""
 ALIASES				   += "cellml2_17=\xrefitem CellML2_17 \"CellML2_17\" \"CellML 2.0: 17. Connection elements \""
 ALIASES				   += "cellml2_18=\xrefitem CellML2_18 \"CellML2_18\" \"CellML 2.0: 18. Map-variables elements \""
 ALIASES				   += "cellml2_19=\xrefitem CellML2_19 \"CellML2_19\" \"CellML 2.0: 19. Interpretation of CellML models \""


 @cellml2_3 {
 __3. Data representation formats in CellML__\n
 The following data representation formats are defined for use in this specification:\n
 3.1. A CellML identifier:\n
 3.1.1. SHALL be a sequence of Unicode characters.\n
 3.1.2. SHALL NOT contain any characters except basic Latin alphanumeric
 characters and basic Latin underscores.\n
 3.1.3. SHALL contain one or more basic Latin alphabetic characters.\n
 3.1.4. SHALL NOT begin with a European numeric character.\n
 3.1.5. SHALL, when comparing two identifiers, be considered identical to another
 identifier if and only if both identifiers have identical sequences of Unicode
 characters.\n
 3.2. A non-negative integer string:\n
 3.2.1. SHALL be a base 10 representation of a non-negative integer.\n
 3.2.2. SHALL consist entirely of European numeric characters.\n
 3.3. An integer string:\n
 3.3.1. SHALL be a base 10 representation of an integer.\n
 3.3.2. SHALL, when the integer being represented is negative, consist of the basic
 Latin hyphen-minus character U+002D , followed by the non-negative integer
 string representation of the absolute value of the integer.\n
 3.3.3. SHALL, when the integer being represented is non-negative, consist of the
 non-negative integer string representation of the integer.\n
 3.4. A basic real number string:\n
 3.4.1. SHALL be a base 10 representation of a real number.\n
 3.4.2. SHALL, when the basic real number being represented is negative, begin with
 the basic Latin hyphen-minus character U+002D as the sign indicator.\n
 3.4.3. MAY contain a single decimal point separator, which SHALL be the basic
 Latin full stop character U+002E .\n
 3.4.4. SHALL, other than the sign indicator and the decimal point separator, consist
 only of European numeric characters.\n
 3.5. A real number string:\n
 3.5.1. SHALL be a base 10 representation of a real number r = s ⋅ 10 e , where s is the
 significand, a real number, and e is the exponent, an integer.\n
 3.5.2. The representation of the number SHALL be the representation of the
 significand followed immediately by the representation of the exponent.\n
 3.5.3. The significand SHALL be represented as a basic real number string.\n
 3.5.4. A non-zero exponent SHALL be represented by an exponent separator
 character, followed by the integer string representation of the value of the
 exponent. The exponent separator character SHALL be either the basic Latin
 ‘E’ character U+0045 or the basic Latin ‘e’ character U+0065 .\n
 3.5.5. If the exponent is zero, the exponent MAY be represented by an empty string,
 or MAY be represented according to the rule for non-zero exponent.\n
 }


 @cellml2_4 {
 __4. The model element information item__\n
 _4.1. Top-level of CellML infosets_\n
 The top-level element information item in a CellML infoset MUST be an element
 information item in the CellML namespace with a local name equal to model . In this
 specification, the top-level element information item is referred to as the model element.\n
 _4.2. Specific information items_\n
 4.2.1. Every model element MUST contain an unprefixed name attribute. The value of the
 name attribute MUST be a valid CellML identifier.\n
 4.2.2. A model element MAY contain zero or more additional specific information item
 children, each of which MUST be of one of the following types:\n
 4.2.2.1. A component element; or\n
 4.2.2.2. A connection element; or\n
 4.2.2.3. An encapsulation element; or\n
 4.2.2.4. An import element; or\n
 4.2.2.5. A units element;\n
 4.2.3. A model element MUST NOT contain more than one encapsulation element.\n
 }

 @cellml2_5 {
 __5. The import element information item__\n
 An import element information item (referred to in this specification as an import element)
 is an element information item in the CellML namespace with a local name equal to import .\n
 _5.1. Specific information items_\n
 5.1.1. Every import element MUST contain an attribute information item in the namespace
 http://www.w3.org/1999/xlink , and with a local name equal to href . The value of
 this attribute SHALL be a valid locator href , as defined in section 5.4 of the XLink
 specification . The href attribute SHALL be treated according to the XLink
 specification, by applying the rules for simple-type elements. When describing an
 import element or one of its children, the phrase “imported CellML infoset” SHALL
 refer to the CellML infoset obtained by parsing the document referenced by the href
 attribute.\n
 5.2. Every import element MAY contain zero or more specific information item children,
 each of which MUST be of one of the following types:\n
 5.2.1. An import units element; or\n
 5.2.2. An import component element.\n
 5.3. The imported CellML infoset MUST NOT be semantically equivalent (see
 Semantically equivalent CellML infosets ) to the importing CellML infoset. Any
 CellML infoset imported, directly or indirectly, by the imported CellML infoset
 MUST NOT be semantically equivalent to the importing CellML infoset.\n
 }

 @cellml2_6 {
 __6. The import units element information item__\n
 An import units element information item (referred to in this specification as an import
 units element) is an element information item in the CellML namespace with a local name
 equal to units , which appears as a child of an import element.\n
 6.1. Specific information items\n
 6.1.1. Every import units element MUST contain an unprefixed name attribute. The value
 of the name attribute MUST be a valid CellML identifier. The value of the name
 attribute MUST NOT be identical to the name attribute of any other units element
 that appears as the direct child of a model element or import units element in the
 CellML infoset.\n
 6.1.2. Every import units element MUST contain an unprefixed units_ref attribute. The
 value of the units_ref attribute MUST be a valid CellML identifier. The value of the
 units_ref attribute MUST match the value of the name attribute on a units element
 or import units element in the imported CellML infoset. The value of the
 units_ref attribute MUST NOT match the value of the units_ref attribute on any
 sibling import units element.
 }

 @cellml2_7 {
 __7. The import component element information item__\n
 An import component element information item (referred to in this specification as an
 import component element) is an element information item in the CellML namespace with a
 local name equal to component , which appears as a child of an import element.\n
 _7.1. Specific information items_\n
 7.1.1. Every import component element MUST contain an unprefixed name attribute. The
 value of the name attribute MUST be a valid CellML identifier. The value of the name
 attribute MUST NOT be identical to the name attribute of any other component
 element or import component element in the CellML infoset.\n
 7.1.2. Every import component element MUST contain an unprefixed component_ref
 attribute. The value of the component_ref attribute MUST be a valid CellML
 identifier. The value of the component_ref attribute MUST match the value of the
 name attribute on a component element or import component element in the imported
 CellML infoset. See also the Component reference section.\n
 }

 @cellml2_8 {
 __8. The units element information item__\n
 A units element information item (referred to in this specification as a units element) is an
 element information item in the CellML namespace with a local name equal to units , and
 with a model element as its parent.\n
 _8.1. Specific information items_\n
 8.1.1. Every units element MUST contain an unprefixed name attribute. The value of the
 name attribute MUST be a valid CellML identifier.\n
 8.1.2. The value of the name attribute MUST NOT be identical to the name attribute of any
 other units element or import units element in the CellML infoset.\n
 8.1.3. The value of the name attribute MUST NOT be equal to the name of any of the units
 listed in the Built-in units table.\n
 8.1.4. A units element MAY contain one or more unit element children.\n
 }

 @cellml2_9 {
 __9. The unit element information item__\n
 A unit element information item (referred to in this specification as a unit element) is an
 element information item in the CellML namespace with a local name equal to unit , and
 with a units element as its parent.\n
 _9.1. Specific information items_\n
 9.1.1. Every unit element MUST contain an unprefixed units attribute information item.
 The value of the units attribute MUST be a valid units reference, as defined in the
 Units reference section.\n
 9.1.1.1. For the purpose of the constraint in the next paragraph, the units element
 inclusion digraph SHALL be defined as a conceptual digraph which SHALL
 contain one node for every units element in the CellML model. The units
 element inclusion digraph SHALL contain an arc from units element A to
 units element B if and only if units element A contains a unit element with
 units attribute value that is a units reference to units element B .\n
 9.1.1.2. The value of the units attribute MUST NOT be such that the units element
 inclusion digraph contains one or more cycles (in other words, units
 definitions must not be circular).\n
 9.1.2. A unit element MAY contain any of the following unprefixed attribute information
 items:\n
 9.1.2.1. The prefix attribute. If present, the value of the attribute MUST meet the
 constraints specified in the Interpretation of units section.\n
 9.1.2.2. The multiplier attribute. If present, the value of the attribute MUST be a real
 number string.\n
 9.1.2.3. The exponent attribute. If present, the value of the attribute MUST be a real
 number string.\n
 }

 @cellml2_10 {
 __10. The component element information item__ \n
 A component element information item (referred to in this specification as a component
 element) is an element information item in the CellML namespace with a local name equal to
 component , and which appears as a child of a model element.\n
 _10.1. Specific information items_ \n
 10.1.1. Every component element MUST contain an unprefixed name attribute. The value of
 the name attribute MUST be a valid CellML identifier. The value of the name attribute
 MUST NOT be identical to the name attribute on any other component element or
 import component element in the CellML infoset. \n
 10.1.2. A component element MAY contain one or more specific information item children,
 each of which MUST be of one of the following types: \n
 10.1.2.1. A variable element; or\n
 10.1.2.2. A reset element; or\n
 10.1.2.3. A math element\n
 }

 @cellml2_11 {
 __11. The variable element information item__\n
 A variable element information item (referred to in this specification as a variable
 element) is an element information item in the CellML namespace with a local name equal to
 variable , and which appears as a child of a component element.\n
 _11.1. Specific information items_\n
 11.1.1. Every variable element MUST have each of the following unprefixed attribute
 information items:\n
 11.1.1.1. The name attribute. The value of the name attribute MUST be a valid CellML
 identifier. The value of the name attribute MUST NOT be identical to the name
 attribute on any sibling variable element.\n
 11.1.1.2. The units attribute. The value of the units attribute MUST be a valid
 CellML identifier, and MUST meet the constraints described in the Effect of
 units on variables section.\n
 11.1.2. Every variable element MAY contain one or more of the following unprefixed
 attribute information items:\n
 11.1.2.1. The interface attribute. If the attribute is present, it MUST have one of the
 values public , private , public_and_private , or none .\n
 11.1.2.2. The initial_value attribute. If the attribute is present, it MUST meet the
 requirements described by the Interpretation of initial values section.\n
 }

 @cellml2_12 {
 __12. The reset element information item__\n
 A reset element information item (referred to in this specification as a reset element) is an
 element information item in the CellML namespace with a local name equal to reset , and
 which appears as a child of a component element.\n
 _12.1. Specific information items_\n
 12.1.1. Every reset element MUST have each of the following unprefixed attribute
 information items:\n
 12.1.1.1. The variable attribute. The value of the variable attribute MUST be a
 variable reference to a variable defined within the component element parent
 of the reset element.\n
 12.1.1.2. The order attribute. The value of the order attribute MUST be an integer
 string. The value of the order attribute MUST be unique for all reset
 elements for variables that are in the same connected variable set (see
 Interpretation of map_variables ).\n
 12.1.1.3. A reset element MUST contain one or more specific information item
 children, each of which MUST be a when element.\n
 }

 @cellml2_13 {
 __13. The when element information item__\n
 A when element information item (referred to in this specification as a when element) is an
 element information item in the CellML namespace with a local name equal to when , and
 which appears as a child of a reset element.\n
 _13.1. Specific information items_\n
 13.1.1. Every when element MUST contain an unprefixed order attribute. The value of the
 order attribute MUST be an integer string. All sibling when elements MUST have a
 unique value for order .\n
 13.1.2. A when element MUST contain two specific information item children, each of which
 MUST be math elements.\n
 }

 @cellml2_14 {
 __14. The math element information item__\n
 A math element information item (referred to in this specification as a math element) is an
 element information item in the MathML namespace that appears as a direct child of a
 component element, or as a direct child of a when element.
 _14.1. Specific information items_\n
 14.1.1. A math element MUST be the top-level of a content MathML tree, as described in
 MathML 2.0 .\n
 14.1.2. Each element information item child of a math element MUST have an element-type
 name that is listed in the Supported MathML Elements table, and where allowable
 types are listed in that table the element MUST exhibit one of those types.\n
 14.1.3. Every variable name given using the MathML ci element MUST be a variable
 reference to a variable within the component element that the math element is
 contained within.\n
 14.1.4. Any MathML cn elements MUST each have an attribute information item in the
 CellML namespace, with a local name equal to units . The value of this attribute
 information item MUST be a valid units reference.\n
 }

 @cellml2_15 {
 __15. The encapsulation element information item__\n
 An encapsulation element information item (referred to in this specification as an
 encapsulation element) is an element information item in the CellML namespace with a
 local name equal to encapsulation , and which appears as a child of a model element.\n
 _15.1. Specific information items_\n
 15.1.1. Every encapsulation element MUST contain one or more component_ref elements.\n
 }

 @cellml2_16 {
 __16. The component_ref element information item__\n
 A component_ref element information item (referred to in this specification as a
 component_ref element) is an element information item in the CellML namespace with a
 local name equal to component_ref , and which appears as a child of an encapsulation
 element.
 _16.1. Specific information items_\n
 16.1.1. Every component_ref element MUST contain an unprefixed component attribute
 information item. The value of this attribute MUST be a valid CellML identifier, and
 MUST match the name attribute on a component element or an import component
 element in the CellML infoset.\n
 16.1.2. Every component_ref element MAY in turn contain zero or more component_ref
 element children.\n
 16.1.3. component_ref elements which are immediate children of encapsulation elements
 MUST each contain at least one component_ref element child.\n
 }

 @cellml2_17 {
 __17. The connection element information item__\n
 A connection element information item (referred to in this specification as a connection
 element) is an element information item in the CellML namespace with a local name equal to
 connection , and which appears as a child of a model element.
 _17.1. Specific information items_\n
 17.1.1. Each connection element MUST contain an unprefixed component_1 attribute. The
 value of the component_1 attribute MUST be a valid CellML identifier. The value of
 this attribute MUST be equal to the name attribute on a component or import
 component element in the CellML infoset (see Component reference ).\n
 17.1.2. Each connection element MUST contain an unprefixed component_2 attribute. The
 value of the component_2 attribute MUST be a valid CellML identifier. The value of
 this attribute MUST be equal to the name attribute on a component or import
 component element in the CellML infoset (see Component reference ). It MUST NOT
 be equal to the value of the component_1 attribute.\n
 17.1.3. A CellML infoset MUST NOT contain more than one connection element with a
 given pair of component s referenced by the component_1 and component_2 attribute
 values, in any order.\n
 17.1.4. Every connection element MUST contain one or more map_variables elements.\n
 }

 @cellml2_18 {
 __18. The map_variables element information item__\n
 A map_variables element information item (referred to in this specification as a
 map_variables element) is an element information item in the CellML namespace with a
 local name equal to map_variables , and which appears as a child of a connection element.\n
 _18.1. Specific information items_\n
 18.1.1. Each map_variables element MUST contain an unprefixed variable_1 attribute.
 The value of the variable_1 attribute MUST be a valid CellML identifier. The value
 of this attribute MUST be equal to the name attribute on a variable element child of
 the component element or import component element referenced by the
 component_1 attribute on the connection element which is the parent of this element.\n
 18.1.2. Each map_variables element MUST contain an unprefixed variable_2 attribute.
 The value of the variable_2 attribute MUST be a valid CellML identifier. The value
 of this attribute MUST be equal to the name attribute on a variable element child of
 the component element or import component element referenced by the
 component_2 attribute on the connection element which is the parent of this element.\n
 18.1.3. A connection element MUST NOT contain more than one map_variables element
 with a given variable_1 attribute value and variable_2 attribute value pair.\n
 }

 @cellml2_19 {
 __19. Interpretation of CellML models__\n
 _19.1. Interpretation of imports_\n
 19.1.1. Each import element present in a CellML infoset (the importing infoset) SHALL
 define a new and separate instance of the CellML infoset referenced by the href
 attribute (the imported infoset). See Units reference and Component reference for the
 specifics of importing units and components.\n
 }
 @cellml2_19 {
 _19.2. Units reference_\n
 19.2.1. A units reference SHALL be a CellML identifier, and in terms of the semantics of the
 model content SHALL be interpreted dependent on the context of the CellML model
 in which it occurs, according to the units referencing rules defined later in this section.\n
 19.2.2. A CellML infoset MUST NOT contain a units reference for which no referencing rule
 can be held to have been followed.\n
 19.2.3. The units referencing rules are:\n
 19.2.3.1. Where there is a units element with a name attribute identical to the units
 reference, then the units reference SHALL refer to that units element.\n
 19.2.3.2. Where there is an import units element in the CellML infoset, such that the
 import units element has a name attribute identical to the units reference,
 then the units reference SHALL be treated with respect to referencing rules as
 if the units reference appeared in the imported infoset, in an information item
 descended from the imported infoset’s model element, and referred to the name
 specified in the units_ref attribute of the import units element.\n
 19.2.3.3. Where the units reference is equal to the value in the ‘Name’ column of the
 Built-in units table, then the units reference SHALL be a reference to the
 built-in unit corresponding to that row of the table.\n
 }
 @cellml2_19 {
 _19.3. Interpretation of units_\n
 19.3.1. The units element SHALL be interpreted as the product of its unit element children,
 according to the following rules:\n
 19.3.1.1. The prefix term is a conceptual property of unit elements. If the unit element
 does not have a prefix attribute information item, the prefix term SHALL
 have value 0.0 . If the prefix attribute information item has a value which is an
 integer string, then the value of the prefix term SHALL be the numerical value
 of that string. Otherwise, the prefix attribute information item MUST have a
 value taken from the ‘Name’ column of the Prefix values table, and the prefix
 term SHALL have the value taken from the ‘Value’ column of the same row.\n
 19.3.1.2. The exponent term is a conceptual property of unit elements. If a unit
 element has no exponent attribute information item, the exponent term
 SHALL have value 1.0 . Otherwise, the value of the exponent attribute
 information item MUST be a real number string, and the value of the exponent
 term SHALL be the numerical value of that string.\n
 19.3.1.3. The multiplier term is a conceptual property of unit elements. If a unit
 element has no multiplier attribute information item, the multiplier term
 SHALL have value 1.0 . Otherwise, the value of the multiplier attribute
 information item MUST be a real number string, and the value of the
 multiplier term SHALL be the numerical value of that string.\n
 19.3.1.4. The relationship between the product, P, of numerical values given in each
 and every child unit element units, to a numerical value, x, with units given
 by the encompassing units element, SHALL be <see equation in original document>
 where: u x denotes the units of the units element; p i , e i , m i , and u i refer to the
 prefix, exponent and multiplier terms and units of the i th unit child element,
 respectively. Square brackets encompass the units of numerical values.\n
 19.3.2. For the purposes of this specification, the “irreducible units” of a model SHALL
 consist of 1) the units defined in a model that are not defined in terms of other units
 (i.e. the set of units elements in the CellML model which have no unit child
 elements), and 2) built-in irreducible units (those built-in units with ‘-’ in the ‘Unit
 Reduction...’ column of the Built-in units Table) referenced by variables or other units
 in the model.\n
 19.3.3. The “unit reduction” is a conceptual property of units elements. It consists of a set of
 tuples where each tuple is composed of a) a unit name and b) a real-valued exponent.
 Tuples SHALL be determined as follows:\n
 19.3.3.1. If the units element has no unit child elements, then the set of tuples
 SHALL have a single member, which SHALL consist of the name of the
 units element and the exponent 1.0.\n
 19.3.3.2. If the units element has one or more unit child elements, then the set of
 tuples SHALL consist of the entire collection of tuples given by all unit child
 elements. Tuples for each unit child element SHALL be determined as
 follows:\n
 19.3.3.2.1. Where the units reference of the unit child element is to a single unit
 which is an irreducible unit, then the set of tuples SHALL have a
 single member, which SHALL consist of the name of the irreducible
 unit being referenced and the exponent 1.0 .\n
 19.3.3.2.2. Where the units reference of the unit child element is to built-in units
 other than an irreducible unit, then the tuples SHALL be derived
 directly from the Built-in units table. Specifically, the set of tuples
 SHALL consist of the tuples given in the ‘Unit reduction tuple ... set’
 column of the row for which the value in the ‘Name’ column matches
 the name of the units reference.\n
 19.3.3.2.3. Where the units reference of the unit child element is to a unit which
 is neither built-in, nor an irreducible unit, the set of tuples SHALL be
 defined recursively as the set of tuples for the units element so
 referenced.\n
 19.3.3.2.4. The exponents of each tuple in the set for the current unit element, as
 derived by following rule 3.2.1, 3.2.2 or 3.2.3 above, SHALL be
 multiplied by the exponent term of the current, referencing, unit
 element.\n
 19.3.3.3. Tuples which have the name element of ‘dimensionless’ SHALL be removed
 from the set of tuples. Note that this can result in the set of tuples being empty.\n
 19.3.3.4. Where the set of tuples consists of tuples which have the same name element,
 those tuples SHALL be combined into a single tuple with that name element
 and an exponent being the sum of the combined tuples’ exponents. If the
 resulting tuple’s exponent term is zero, the tuple SHALL be removed from the
 set of tuples. Note that this can result in the set of tuples being empty.\n
 }
 @cellml2_19 {
 _19.4. Component reference_\n
 19.4.1. A component reference SHALL be the name of a component, and SHALL be
 interpreted based on the context within the CellML model in which it occurs.\n
 19.4.2. A component reference present in an information item which is a descendant of a
 model element SHALL be identical to either the name attribute on a component
 element or to the name attribute on an import component element.\n
 19.4.3. A component reference which is identical to the name attribute on a component
 element SHALL be treated as a reference to that component element.\n
 19.4.4. A component reference which is identical to the name attribute on an import
 component element SHALL be treated for the purposes of referencing as if the
 component reference appeared in the imported model, and referred to element with
 the name specified in the component_ref attribute of the import component element.\n
 19.4.5. It is noted, for the avoidance of doubt, that CellML models MAY apply the previous
 rule recursively, to reference an import component element which in turn references
 another import component element.\n
 }
 @cellml2_19 {
 _19.5. Variable reference_\n
 19.5.1. When present in an information item which is a descendant of a component element, a
 variable reference SHALL be the name of a variable, and SHALL refer to the
 variable element in that component with a name attribute identical to the variable
 reference.\n
 19.5.2. In all other cases, a variable reference SHALL consist of a component reference and a
 variable name. In this case, the variable reference SHALL be treated as if it was just
 the variable name present in the component element referenced by the component
 reference.\n
 }
 @cellml2_19 {
 _19.6. Interpretation of initial values_\n
 19.6.1. The initial_value attribute of a variable element MUST either be a real number
 string, or a variable reference.\n
 19.6.2. The conditions when initial values hold are (by design) not defined in a CellML
 model document. It is intended that those conditions be supplied by CellML
 processing software where appropriate.\n
 19.6.3. Where the initial_value attribute has a real number value, it SHALL be interpreted
 as a statement that the variable on which the attribute appears is equal to that real
 number value, under the conditions when the initial value holds.\n
 19.6.4. Where the initial_value attribute is a variable reference, it SHALL be interpreted
 as a statement that the variable on which the attribute appears is equal to the
 referenced variable under the conditions when the initial value holds.\n
 }
 @cellml2_19 {
 _19.7. Effect of units on variables_\n
 19.7.1. The value of the units attribute on every variable element MUST be a valid units
 reference. The target of this units reference is referred to as the variable units, and the
 corresponding unit reduction (see Interpretation of units ) is referred to as the variable
 unit reduction.\n
 }
 @cellml2_19 {
 _19.8. Interpretation of mathematics_\n
 19.8.1. The following component elements SHALL, for the purposes of this specification, be
 “pertinent component elements”:\n
 19.8.1.1. All component elements in the top-level CellML infoset for the CellML
 model;\n
 19.8.1.2. All component elements referenced by import component elements (see The
 import component element information item ) in the top-level CellML infoset;
 and \n
 19.8.1.3. All component elements which are descendants in the encapsulation digraph
 (see Interpretation of encapsulation ) of a pertinent component element. \n
 19.8.2. Every MathML element in the CellML model which appears as a direct child
 information item of a MathML math element information item, which in turn appears
 as a child information item of a pertinent component element, SHALL be treated, in
 terms of the semantics of the mathematical model, as a statement which holds true
 unconditionally.\n
 19.8.3. Units referenced by a units attribute information item SHALL NOT affect the
 mathematical interpretation of the CellML model. However, CellML processing
 software MAY use this information to assist the user in the detection and correction of
 units errors in the CellML model.\n
 }
 @cellml2_19 {
 _19.9. Interpretation of encapsulation_\n
 19.9.1. For the purposes of this specification, there SHALL be a “conceptual encapsulation
 digraph” in which there is one node for every component in the CellML model.\n
 19.9.2. Where a component_ref element appears as a child of another component_ref
 element, there SHALL be an arc in the encapsulation digraph, and that arc SHALL be
 from the node corresponding to the component referenced by the parent
 component_ref element, and to the node corresponding to the component referenced
 by the child component_ref element.\n
 19.9.3. The encapsulation digraph MUST NOT contain any loops, and MUST NOT contain
 any directed cycles.\n
 19.9.4. The encapsulated set for a component A SHALL be the set of all components B such
 that there exists an arc in the encapsulation digraph from the node corresponding to A
 to the node corresponding to B .\n
 19.9.5. The encapsulation parent for a component A SHALL be the component corresponding
 to the node which is the parent node in the encapsulation digraph of the node
 corresponding to A .\n
 19.9.6. The sibling set for a component A SHALL be the set of all components which have
 the same encapsulation parent as A , or in the case that A has no encapsulation parent,
 SHALL be the set of all components which do not have an encapsulation parent.\n
 19.9.7. The hidden set for a component A SHALL be the set of all components B where
 component B is not in the encapsulated set for component A , and component B is not
 the encapsulation parent of component A , and component B is not in the sibling set for
 component A .\n
 19.9.8. There MUST NOT be a connection element such that the component referenced by
 the component_1 attribute is in the hidden set of the component referenced by the
 component_2 attribute, nor vice versa.\n
 }
 @cellml2_19 {
 _19.10. Interpretation of map_variables_\n
 19.10.1. For the purposes of this specification, a variable equivalence (conceptual) network
 SHALL be a graph with one node for every variable element in the CellML model.\n
 19.10.2. For each map_variables element present in the CellML model, we define variables A
 and B for use in the rules in this section as follows.\n
 19.10.2.1. Variable A SHALL be the variable referenced by the encompassing
 connection element’s component_1 and this map_variables element’s
 variable_1 attributes.\n
 19.10.2.2. Variable B SHALL be the variable referenced by the encompassing
 connection element’s component_2 and this map_variables element’s
 variable_2 attributes.\n
 19.10.3. For every map_variables element present in the CellML model, there SHALL be an
 arc in the variable equivalence network.\n
 19.10.3.1. One endpoint of the arc in the variable equivalence network SHALL be the
 node corresponding to variable A .\n
 19.10.3.2. One endpoint of the arc in the variable equivalence network SHALL be the
 node corresponding to variable B .\n
 19.10.4. CellML models MUST NOT contain any pair of map_variables elements which
 define the same arc in the variable equivalence network (according to the previous
 paragraph).\n
 19.10.5. The variable equivalence network MUST NOT contain any cycles (that is, it must be
 a tree).\n
 19.10.6. For each map_variables element present in the CellML model, the variable unit
 reduction (see Effect of units on variables ) of variable A MUST have an identical set
 of tuples to the variable unit reduction of variable B . Two sets of tuples SHALL be
 considered identical if all of the tuples from each set are present in the other, or if both
 sets are empty. Two tuples are considered identical if and only if both the name and
 exponent value of each tuple are equivalent.\n
 19.10.7. Processing software concerned with providing numerical solutions to the
 mathematical model MAY provide automatic numerical conversion between variables
 which have the same variable unit reduction but different multipliers (see
 Interpretation of units ) by employment of conversion factors.\n
 19.10.8. For a given variable, the available interfaces SHALL be determined by the interface
 attribute information item on the corresponding variable element as follows.\n
 19.10.8.1. A value of public specifies that the variable has a public interface.\n
 19.10.8.2. A value of private specifies that the variable has a private interface.\n
 19.10.8.3. A value of public_and_private specifies that the variable has both a public
 and a private interface.\n
 19.10.8.4. A value of none specifies that the variable has no interface.\n
 19.10.8.5. If the interface attribute information item is absent, then the variable has no
 interface.\n
 19.10.9. The applicable interfaces for variables A and B SHALL be defined as follows.\n
 19.10.9.1. When the parent component element of variable A is in the sibling set of the
 parent component element of variable B , the applicable interface for both
 variables A and B SHALL be the public interface.\n
 19.10.9.2. When the parent component element of variable A is in the encapsulated set of
 the parent component element of variable B , the applicable interface for
 variable A SHALL be the public interface, and the applicable interface for
 variable B SHALL be the private interface.\n
 19.10.9.3. When the parent component element of variable B is in the encapsulated set of
 the parent component element of variable A , the applicable interface for
 variable A SHALL be the private interface, and the applicable interface for
 variable B SHALL be the public interface.\n
 19.10.10. CellML models MUST NOT contain a map_variables element where the applicable
 interface of variable A or B is not defined or is not an available interface.\n
 19.10.11. For the purposes of this specification, the variable elements in a CellML model
 SHALL be treated as belonging to one of one or more disjoint “connected variable
 sets”. Each set of “connected variables” is the set of all variable elements for which
 the corresponding nodes in the variable equivalence network form a weakly
 connected subgraph. Each set of connected variables represents one variable in the
 underlying mathematical model.\n
 }
 @cellml2_19 {
 _19.11. Interpretation of variable resets_\n
 19.11.1. Each reset element describes a change to be applied to the variable referenced by the
 variable attribute when specified conditions are met during the simulation of the
 model.\n
 19.11.2. All reset elements SHALL be considered sequentially for the connected variable set
 (see Interpretation of map_variables ) to which the referenced variable belongs. The
 sequence SHALL be determined by the value of the reset element’s order attribute,
 lowest (least positive) having priority.\n
 19.11.3. The change, and conditions for the change, to a variable for a given reset element
 SHALL be defined by the evaluation of that element’s when child elements.\n
 19.11.3.1. A when element SHALL be deemed to be true when the evaluation of the
 MathML expression encoded in first child element of the when element
 changes from the boolean expression false to true.\n
 19.11.3.2. If a when element is deemed to be true, then false, then true again during the
 same ‘instant’ or interval of integration, it SHALL nevertheless be held to be
 false.\n
 19.11.3.3. The second child element of a when element SHALL define the MathML
 expression to be evaluated and assigned to the parent reset element’s
 referenced variable when the when element is deemed to be true.\n
 19.11.3.4. Consideration of the set of when child elements of a given reset element
 SHALL stop at the first occurrence of a when deemed to be true.\n
 19.11.3.5. The order of consideration of the set of when child elements SHALL be based
 on the value of the when element’s order attribute, lowest having priority.\n
 }
 */

TEST(Validator, namedModel) {
    /// @cellml2_4 4.2.1 Validate TEST model name format
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    model->setName("awesomeName");
    validator.validateModel(model);
    EXPECT_EQ(0u, validator.errorCount());
}

TEST(Validator, unnamedModel) {
    /// @cellml2_4 4.2.1 Validate TEST mode name format
    std::string expectedError = "Model does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    validator.validateModel(model);
    EXPECT_EQ(2u, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(1)->getDescription());
    EXPECT_EQ("4.2.1", validator.getError(1)->getSpecificationHeading());
}

TEST(Validator, invalidCellMLIdentifiersWithSpecificationHeading) {
    /// @cellml2_10 10.1.1 Validate TEST component name format
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must not begin with a European numeric character [0-9].",
        "Model does not have a valid name attribute.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
    };
    std::vector<std::string> expectedSpecificationHeadings = {
        "3.1.4",
        "4.2.1",
        "3.1.2",
        "10.1.1",
        "3.1.3",
        "10.1.1",
        "3.1.2",
        "10.1.1",
        "3.1.3",
        "10.1.1",
    };

    libcellml::Validator v;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c5 = std::make_shared<libcellml::Component>();

    model->setName("9numbernine");
    c1->setName("try.this");
    c2->setName("");
    c3->setName("or this");
    c4->setName("nice_name");

    model->addComponent(c1);
    model->addComponent(c2);
    model->addComponent(c3);
    model->addComponent(c4);
    model->addComponent(c5);

    v.validateModel(model);

    EXPECT_EQ(10u, v.errorCount());
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
        EXPECT_EQ(expectedSpecificationHeadings.at(i), v.getError(i)->getSpecificationHeading());
    }
}

TEST(Validator, moveCopyValidatorWithUnnamedModel) {
    libcellml::Validator v, vm;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    v.validateModel(model);

    // Move
    vm = std::move(v);
    // Copy
    libcellml::Validator vc(vm);

    // Check that the model error is in the copy.
    EXPECT_EQ(libcellml::Error::Kind::MODEL, vc.getError(1)->getKind());
}

TEST(Validator, namedModelWithUnnamedComponent) {
    /// @cellml2_10 10.1.1 Validate TEST component name is not empty
    std::string expectedError = "Component does not have a valid name attribute.";
    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    model->setName("awesomeName");
    model->addComponent(component);
    validator.validateModel(model);
    EXPECT_EQ(2u, validator.errorCount());
    EXPECT_EQ(expectedError, validator.getError(1)->getDescription());
}

TEST(Validator, unnamedModelWithUnnamedComponentWithUnnamedUnits) {
    /// @cellml2_4 4.2.1 Validate TEST unnamed model with unnamed units
    /// @cellml2_8 8.1.1 Validate TEST unnamed units in model
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Model does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Component does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Units does not have a valid name attribute."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr component = std::make_shared<libcellml::Component>();
    libcellml::UnitsPtr units = std::make_shared<libcellml::Units>();
    model->addComponent(component);
    model->addUnits(units);
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, modelWithDuplicateComponentsAndUnits) {
    /// @cellml2_8 8.1.2 Validate TEST Valid units names must be unique to the model
    /// @cellml2_10 10.1.1 Validate TEST Valid names must be unique to the model
    std::vector<std::string> expectedErrors = {
        "Model 'multiplicity' contains multiple components with the name 'michael'. Valid component names must be unique to their model.",
        "Model 'multiplicity' contains multiple units with the name 'keaton'. Valid units names must be unique to their model."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    model->addComponent(c1);
    model->addComponent(c2);
    model->addUnits(u1);
    model->addUnits(u2);

    model->setName("multiplicity");
    c1->setName("michael");
    c2->setName("michael");
    u1->setName("keaton");
    u2->setName("keaton");
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, unitsWithPrefixOutOfRange) {
    // int limit is 18,446,744,073,709,551,615

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("myModel");
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    c->setName("myComponent");
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    v->setName("myVariable");
    libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

    u->setName("myUnits");
    u->addUnit("second", "18446744073709551616");

    v->setUnits(u);
    c->addVariable(v);
    m->addComponent(c);
    m->addUnits(u);

    validator.validateModel(m);
    // This does not throw any errors as they're caught in the stoi function.  Only here to give complete
    // test coverage. 
    EXPECT_EQ(0u, validator.errorCount());
}

TEST(Validator, unnamedAndDuplicateNamedVariablesWithAndWithoutValidUnits) {
    /// @cellml2_11 11.1.1.1 Validate TEST variable names must be unique to their component
    /// @cellml2_11 11.1.1.1 Validate TEST variable name must be valid
    /// @cellml2_8 8.1.1 Validate TEST units name must be valid
    /// @cellml2_11 11.1.1.2 Validate TEST variable units name is a valid reference  
    /// @cellml2_19 19.7.1 Validate TEST variable units name is a valid reference

    std::vector<std::string> expectedErrors = {
        "Component 'fargo' contains multiple variables with the name 'margie'. Valid variable names must be unique to their component.",
        "CellML identifiers must not begin with a European numeric character [0-9].",
        "Variable does not have a valid name attribute.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Variable 'margie' does not have a valid units attribute.",
        "Variable 'ransom' has an invalid units reference 'dollars' that does not correspond with a standard unit or units in the variable's parent component or model."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    model->addComponent(c1);
    c1->addVariable(v1);
    c1->addVariable(v2);
    c1->addVariable(v3);
    c1->addVariable(v4);

    model->setName("minnesota");
    c1->setName("fargo");
    v1->setName("2cold");
    v1->setUnits("ampere");
    v2->setName("margie");
    v2->setUnits("ampere");
    v3->setName("margie");
    v4->setName("ransom");
    v4->setUnits("dollars");
    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, invalidVariableInitialValuesAndInterfaces) {
    /// @cellml2_11 11.1.2.1 Validate TEST variable interface value is valid
    /// @cellml2_11 11.1.2.2 Validate TEST initial_value attrbute is real number string or variable reference
    std::vector<std::string> expectedErrors = {
        "Variable 'candidate' has an invalid interface attribute value 'orange'.",
        "Variable 'candidate' has an invalid initial value 'trump'. Initial values must be a real number string or a variable reference."
    };

    libcellml::Validator validator;
    libcellml::ModelPtr model = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    model->addComponent(c1);
    c1->addVariable(v1);

    model->setName("election");
    c1->setName("republican");
    v1->setName("candidate");
    v1->setUnits("ampere");
    v1->setInterfaceType("orange");
    v1->setInitialValue("trump");

    validator.validateModel(model);

    EXPECT_EQ(expectedErrors.size(), validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, importUnits) {
    /// @cellml2_6 6.1.2 Validate TEST import units has valid units_ref attribute
    /// @cellml2_6 6.1.1 Validate TEST import units have a valid name
    /// @cellml2_6 6.1.2 Validate TEST import units have a units_ref unique to this model
    /// @cellml2_6 6.1.1 Validate TEST import units has a name unique in this model
    /// @cellml2_5 5.1.1 Validate TEST import element has a valid href formatted attribute TODO This is very restrictive at present, check ...
    
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units 'invalid_imported_units_in_this_model' does not have a valid units_ref attribute.",
        "Import of units 'invalid_imported_units_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported units from 'some-other-model.xml' with the same units_ref attribute 'units_in_that_model'.",
        "Import of units 'name_for_invalid_import' has an invalid URI in the href attribute, 'not @ valid url'. ",
        "Model 'model_name' contains multiple units with the name 'units_to_be_duplicated'. Valid units names must be unique to their model.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported units does not have a valid name attribute."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid units import
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits = std::make_shared<libcellml::Units>();
    importedUnits->setName("valid_imported_units_in_this_model");
    importedUnits->setSourceUnits(imp, "units_in_that_model");
    m->addUnits(importedUnits);
    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());

    // Invalid units import- missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::UnitsPtr importedUnits2 = std::make_shared<libcellml::Units>();
    importedUnits2->setName("invalid_imported_units_in_this_model");
    importedUnits2->setSourceUnits(imp2, "");
    m->addUnits(importedUnits2);
    v.validateModel(m);
    EXPECT_EQ(3u, v.errorCount());

    // Invalid units import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setUrl("some-other-model.xml");
    libcellml::UnitsPtr importedUnits3 = std::make_shared<libcellml::Units>();
    importedUnits3->setName("duplicate_imported_units_in_this_model");
    importedUnits3->setSourceUnits(imp3, "units_in_that_model");
    m->addUnits(importedUnits3);
    v.validateModel(m);
    EXPECT_EQ(4u, v.errorCount());

    // Invalid units import - unnamed units
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::UnitsPtr importedUnits4 = std::make_shared<libcellml::Units>();
    importedUnits4->setSourceUnits(imp4, "units_in_that_model");
    m->addUnits(importedUnits4);
    v.validateModel(m);
    EXPECT_EQ(6u, v.errorCount());

    // Invalid html ref
    libcellml::ImportSourcePtr imp5 = std::make_shared<libcellml::ImportSource>();
    imp5->setUrl("not @ valid url");
    libcellml::UnitsPtr importedUnits5 = std::make_shared<libcellml::Units>();
    importedUnits5->setName("name_for_invalid_import");
    importedUnits5->setSourceUnits(imp5, "units_in_that_model");
    m->addUnits(importedUnits5);
    v.validateModel(m);
    EXPECT_EQ(7u, v.errorCount());

    // Duplicated units name
    libcellml::UnitsPtr manualUnits1 = std::make_shared<libcellml::Units>();
    manualUnits1->setName("units_to_be_duplicated");
    manualUnits1->addUnit("dimensionless");

    libcellml::UnitsPtr manualUnits2 = std::make_shared<libcellml::Units>();
    manualUnits2->setName("units_to_be_duplicated");
    manualUnits1->addUnit("dimensionless");

    m->addUnits(manualUnits1);
    m->addUnits(manualUnits2);

    v.validateModel(m);
    EXPECT_EQ(8u, v.errorCount());
    
    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, importComponents) {
    /// @cellml2_7 7.1.1 Validate TEST import component must have valid name format
    /// @cellml2_7 7.1.2 Validate TEST import component must have unique component_ref
    /// @cellml2_7 7.1.1 Validate TEST import component must have unique name
    /// @cellml2_5 5.1.1 Validate TEST import has valid href attribute
    
    std::vector<std::string> expectedErrors = {
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component 'invalid_imported_component_in_this_model' does not have a valid component_ref attribute.",
        "Import of component 'invalid_imported_component_in_this_model' does not have a valid locator xlink:href attribute.",
        "Model 'model_name' contains multiple imported components from 'some-other-model.xml' with the same component_ref attribute 'component_in_that_model'.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Imported component does not have a valid name attribute.",
        "Model 'model_name' contains multiple imported components from 'yet-another-other-model.xml' with the same component_ref attribute 'new_shiny_component_ref'.",
        "Import of component 'a_bad_imported_component' has an invalid URI in the href attribute, 'not @ valid url'. ",
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    m->setName("model_name");

    // Valid component import
    libcellml::ImportSourcePtr imp = std::make_shared<libcellml::ImportSource>();
    imp->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent = std::make_shared<libcellml::Component>();
    importedComponent->setName("valid_imported_component_in_this_model");
    importedComponent->setSourceComponent(imp, "component_in_that_model");
    m->addComponent(importedComponent);
    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());

    // Another valid component import 
    libcellml::ImportSourcePtr imp5 = std::make_shared<libcellml::ImportSource>();
    imp5->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent5 = std::make_shared<libcellml::Component>();
    importedComponent5->setName("another_valid_imported_component_in_this_model");
    importedComponent5->setSourceComponent(imp5, "new_shiny_component_ref");
    m->addComponent(importedComponent5);
    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());

    // Invalid component import - missing refs
    libcellml::ImportSourcePtr imp2 = std::make_shared<libcellml::ImportSource>();
    libcellml::ComponentPtr importedComponent2 = std::make_shared<libcellml::Component>();
    importedComponent2->setName("invalid_imported_component_in_this_model");
    importedComponent2->setSourceComponent(imp2, "");
    m->addComponent(importedComponent2);
    v.validateModel(m);
    EXPECT_EQ(3u, v.errorCount());

    // Invalid component import - duplicate refs
    libcellml::ImportSourcePtr imp3 = std::make_shared<libcellml::ImportSource>();
    imp3->setUrl("some-other-model.xml");
    libcellml::ComponentPtr importedComponent3 = std::make_shared<libcellml::Component>();
    importedComponent3->setName("duplicate_imported_component_in_this_model");
    importedComponent3->setSourceComponent(imp3, "component_in_that_model");
    m->addComponent(importedComponent3);
    v.validateModel(m);
    EXPECT_EQ(4u, v.errorCount());

    // Invalid component import - unnamed component
    libcellml::ImportSourcePtr imp4 = std::make_shared<libcellml::ImportSource>();
    imp4->setUrl("some-other-different-model.xml");
    libcellml::ComponentPtr importedComponent4 = std::make_shared<libcellml::Component>();
    importedComponent4->setSourceComponent(imp4, "component_in_that_model");
    m->addComponent(importedComponent4);
    v.validateModel(m);
    EXPECT_EQ(6u, v.errorCount());

    // Invalid: duplicating component_ref and source
    libcellml::ImportSourcePtr imp6 = std::make_shared<libcellml::ImportSource>();
    imp6->setUrl("yet-another-other-model.xml");
    libcellml::ComponentPtr importedComponent6 = std::make_shared<libcellml::Component>();
    importedComponent6->setName("another_duplicate_imported_component");
    importedComponent6->setSourceComponent(imp6, "new_shiny_component_ref");
    m->addComponent(importedComponent6);
    v.validateModel(m);
    EXPECT_EQ(7u, v.errorCount());

    // Valid: duplicate component_ref from a different source
    libcellml::ImportSourcePtr imp7 = std::make_shared<libcellml::ImportSource>();
    imp7->setUrl("yet-another-other-model.xml"); // source used before
    libcellml::ComponentPtr importedComponent7 = std::make_shared<libcellml::Component>();
    importedComponent7->setName("a_good_imported_component");
    importedComponent7->setSourceComponent(imp7, "component_in_that_model");
    m->addComponent(importedComponent7);
    v.validateModel(m);
    EXPECT_EQ(7u, v.errorCount());

    // Iinvalid: component_ref is not valid html
    libcellml::ImportSourcePtr imp8 = std::make_shared<libcellml::ImportSource>();
    imp8->setUrl("not @ valid url"); // source used before
    libcellml::ComponentPtr importedComponent8 = std::make_shared<libcellml::Component>();
    importedComponent8->setName("a_bad_imported_component");
    importedComponent8->setSourceComponent(imp8, "component_in_some_model");
    m->addComponent(importedComponent8);
    v.validateModel(m);
    EXPECT_EQ(8u, v.errorCount());
 
    // Check for expected error messages
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMath) {
    /// @cellml2_14 14.1 Validate TEST valid maths input works
    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci> C </ci>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A</ci>"
                        "<ci>B</ci>"
                    "</apply>"
                "</apply>"
            "</math>";

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());

}

TEST(Validator, invalidMath) {
    /// @cellml2_14 14.1.2 Validate TEST mismatch opening and closing tags
    /// @cellml2_14 14.1.1 Validate TEST valid XML root node for math on a component
    /// @cellml2_14 14.1.1 Validate TEST root node type is of type math
    std::string math1 =
            "<math>"
                "<invalid_xml></not_valid>"
            "</math>";

    std::string math2 = "<invalid_math/>";

    std::vector<std::string> expectedErrors = {
        "Opening and ending tag mismatch: invalid_xml line 1 and not_valid.",
        "Could not get a valid XML root node from the math on component 'componentName1'.",
        "Math root node is of invalid type 'invalid_math' on component 'componentName2'. A valid math root node should be of type 'math'."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();

    m->setName("modelName");
    c1->setName("componentName1");
    c2->setName("componentName2");

    c1->setMath(math1);
    c2->setMath(math2);
    m->addComponent(c1);
    m->addComponent(c2);

    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLElements) {
    /// @cellml2_14 14.1.2 Validate TEST maths elements are supported MathML elements
    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<equals/>"
                    "<ci>C</ci>"
                    "<apply>"
                        "<addition/>"
                        "<ci>A</ci>"
                        "<ci>B</ci>"
                    "</apply>"
                "</apply>"
            "</math>";

    std::vector<std::string> expectedErrors = {
        "Math has a 'equals' element that is not a supported MathML element.",
        "Math has a 'addition' element that is not a supported MathML element.",
        "No declaration for element equals.",
        "No declaration for element addition."
    };
    // NOTE: The MathML DTD also gives errors that list every possible operator when an
    //       invalid option is given. We'll just explicitly check the less verbose errors here.

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(6u, v.errorCount());

    // Check for two expected error messages (see note above).
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLVariables) {
    /// @cellml2_14 14.1.2 Validate TEST math elements are supported MathML elements
    /// @cellml2_14 14.1.3 Validate TEST ci children point to valid variables in this component
    /// @cellml2_14 14.1.3 Validate TEST check for duplicate names between bound variables and variables in this component
    /// @cellml2_14 14.1.3 Validate TEST check for empty ci element or whitespace only 
    /// @cellml2_14 14.1.3 Validate TEST check that ci variables have been declared

    std::string math =
            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>answer</ci>"
                    "<partialdiff/>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A</ci>"
                        "<apply>"
                            "<plus/>"
                            "<bvar>"
                            "<ci>new_bvar</ci>"
                            "</bvar>"
                            "<apply>"
                                "<plus/>"
                                "<ci>   </ci>"
                                "<apply>"
                                    "<plus/>"
                                    "<ci><nonsense/></ci>"
                                    "<apply>"
                                        "<plus/>"
                                        "<ci/>"
                                        "<bvar>"
                                        "<ci>B</ci>"
                                        "</bvar>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                    "</apply>"
                "</apply>"
            "</math>";

    std::vector<std::string> expectedErrors = {
        "Component 'componentName' contains multiple variables with the name 'C'. Valid variable names must be unique to their component.",
        "Math has a 'partialdiff' element that is not a supported MathML element.",
        "Math has a 'nonsense' element that is not a supported MathML element.",
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "MathML ci element has the child text 'answer', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has no child.",
        "No declaration for element nonsense.",
        "Element nonsense is not declared in ci list of possible children."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    // Check for expected error messages.
    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, invalidMathMLCiAndCnElementsWithCellMLUnits) {
    std::string math =
            "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<cn cellml:units=\"invalid\">oops</cn>"
                    "<apply>"
                        "<plus/>"
                        "<ci>A</ci>"
                        "<apply>"
                            "<plus/>"
                            "<bvar>"
                            "<ci cellml:units=\"dimensionless\" cellml:value=\"zero\">new_bvar</ci>"
                            "</bvar>"
                            "<apply>"
                                "<plus/>"
                                "<ci>   </ci>"
                                "<apply>"
                                    "<plus/>"
                                    "<ci>undefined_variable</ci>"
                                    "<apply>"
                                        "<plus/>"
                                        "<ci/>"
                                        "<bvar>"
                                        "<ci cellml:units=\"9wayswrong\">B</ci>"
                                        "</bvar>"
                                        "<apply>"
                                            "<plus/>"
                                            "<cn>2.0</cn>"
                                        "</apply>"
                                    "</apply>"
                                "</apply>"
                            "</apply>"
                        "</apply>"
                    "</apply>"
                "</apply>"
            "</math>";

    /// @cellml2_14 14.1.3 Validate TEST check for duplication between bound variable name and variable name in the same component
    /// @cellml2_14 14.1.4 Validate TEST check for valid units reference inside cn
    /// @cellml2_14 14.1.2 Validate TEST check for valid type specification (ie: real, e-notation)
    /// @cellml2_14 14.1.3 Validate TEST check for whitespace only ci element
    /// @cellml2_14 14.1.3 Validate TEST ci has valid variable reference in ths component
    /// @cellml2_14 14.1.3 Validate TEST ci is not empty
    /// @cellml2_14 14.1.3 Validate TEST ci units has valid name
    /// @cellml2_14 14.1.4 Validate TEST cn units are specified
    /// @cellml2_14 "Namespace prefix cellml for value on ci is not defined."
    /// @cellml2_14 "No declaration for attribute cellml:value of element ci."

    std::vector<std::string> expectedErrors = {
        "Math in component 'componentName' contains 'B' as a bvar ci element but it is already a variable name.",
        "Math has a cn element with a cellml:units attribute 'invalid' that is not a valid reference to units in component 'componentName' or a standard unit.",
        "Math ci element has an invalid attribute type 'value' in the cellml namespace.",
        "MathML ci element has a whitespace-only child element.",
        "MathML ci element has the child text 'undefined_variable', which does not correspond with any variable names present in component 'componentName' and is not a variable defined within a bvar element.",
        "MathML ci element has no child.",
        "CellML identifiers must contain one or more basic Latin alphabetic characters.",
        "Math cn element with the value '2.0' does not have a valid cellml:units attribute.",
        "Namespace prefix cellml for value on ci is not defined.",
        "No declaration for attribute cellml:value of element ci."
    };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("A");
    v2->setName("B");
    v3->setName("C");
    v1->setInitialValue("1.0");
    v2->setInitialValue("-1.0");
    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");

    c->addVariable(v1);
    c->addVariable(v2);
    c->addVariable(v3);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    // NOTE: We're not checking the exact message of the last error as older versions of
    //       libxml may not include the namespace in the error message.
    for (size_t i = 0; i < v.errorCount() - 1; ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, parseAndValidateInvalidUnitErrors) {
    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">"
                "<units name=\"ampere\"/>"
                "<units name=\"north\"/>"
                "<units name=\"stark\">"
                    "<unit units=\"volt\" prefix=\"mega\" multiplier=\"1000.0\"/>"
                    "<unit units=\"north\"/>"
                    "<unit units=\"ned\"/>"
                    "<unit units=\"king in the north\"/>"
                    "<unit prefix=\"wolf\" units=\"celsius\"/>"
                "</units>"
            "</model>";

    /// @cellml2_8 8.1.3 Validate TEST Units name does not overload a built-in units name
    /// @cellml2_9 9.1.1 Validate TEST Unit units attribute is valid reference to local or built-in units
    /// @cellml2_9 9.1.1 Validate TEST Unit units attribute must be valid cellml identifier format
    /// @cellml2_9 9.2.1 Validate TEST Unit prefix must be valid real number or SI prefix

    std::vector<std::string> expectedErrors = {
        "Units is named 'ampere', which is a protected standard unit name.",
        "Units reference 'ned' in units 'stark' is not a valid reference to a local units or a standard unit type.",
        "CellML identifiers must not contain any characters other than [a-zA-Z0-9_].",
        "Unit in units 'stark' does not have a valid units reference.",
        "Prefix 'wolf' of a unit referencing 'celsius' in units 'stark' is not a valid integer or a SI prefix.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(0u, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

    for (size_t i = 0; i < v.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validateInvalidConnections) {
    /// @cellml2_18 18.1.1 Validate TEST check parent component for variable
    /// @cellml2_18 Validate TEST reciprocity check of equivalent variables.  See 19.10.3
    /// @cellml2_19 19.10.3 Validate TEST reciprocity check that equivalence goes both ways

    std::vector<std::string> expectedErrors = {
        "Variable 'variable4' is an equivalent variable to 'variable1_1' but has no parent component.",
        "Variable 'variable2' has an equivalent variable 'variable1_2'  which does not reciprocally have 'variable2' set as an equivalent variable.",
        };

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp5 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp6 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp7 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1_1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    comp5->setName("component5");
    comp6->setName("component6");
    comp7->setName("component7");

    v1_1->setName("variable1_1");
    v1_2->setName("variable1_2");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");
    v5->setName("variable5");
    v6->setName("variable6");
    v7->setName("variable7");

    v1_1->setUnits("dimensionless");
    v1_2->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
    v4->setUnits("dimensionless");
    v5->setUnits("dimensionless");
    v6->setUnits("dimensionless");
    v7->setUnits("dimensionless");

    comp1->addVariable(v1_1);
    comp1->addVariable(v1_2);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    comp5->addVariable(v5);
    comp6->addVariable(v6);
    comp7->addVariable(v7);
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
    m->addComponent(comp4);
    m->addComponent(comp5); 
    m->addComponent(comp6);
    m->addComponent(comp7);

    // Valid connections.
    libcellml::Variable::addEquivalence(v1_1, v2);  
    libcellml::Variable::addEquivalence(v1_2, v2);
    // Removed the line below to prevent the cycles from appearing here.  Cycles are tested separately in validateNoCycles
    // libcellml::Variable::addEquivalence(v1_1, v3);  // !! creates cycle with v1_1, v2, v3
    libcellml::Variable::addEquivalence(v1_1, v4);
    libcellml::Variable::addEquivalence(v2, v3);    
    libcellml::Variable::addEquivalence(v5, v6);	// valid here but duplicated below

    // Not valid connections
    libcellml::Variable::addEquivalence(v6, v5);    // duplicated above, does not overwrite, skips silently
    
    // Make v4 a variable without a parent component.
    comp4->removeVariable(v4);
    // Remove all connections on v1_2, leaving dangling reciprocal connections.
    v1_2->removeAllEquivalences();

    v.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < v.errorCount(); ++i) {
       EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validateConnectionComponent1NotEqualComponent2) {

    std::vector<std::string> expectedErrors = {
        "Variable 'doppelganger' has an equivalent variable 'doppelganger' equal to itself. ",
    };
    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v = std::make_shared<libcellml::Variable>();
    m->setName("modelName");
    v->setName("doppelganger");
    v->setUnits("dimensionless");
    c->setName("bucket");
    c->addVariable(v);
    m->addComponent(c);
    libcellml::Variable::addEquivalence(v, v);          
    validator.validateModel(m);

    EXPECT_EQ(1u, validator.errorCount());
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(validator.getError(i)->getDescription(), expectedErrors[i]);
    }
}

TEST(Validator, validateNoCyclesSimple) {
    /// @cellml2_19 19.10.5 Validate that no variable equivalence network has cycles - simple test
    /// @cellml2_19 19.10.5 TODO Can two sibling variables in the same component be equivalent to one variable in another?

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    
    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    
    v1->setName("variable1");
    v2->setName("variable2");
    v3->setName("variable3");

    v1->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
  
    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp3->addVariable(v3);
    
    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
   
    libcellml::Variable::addEquivalence(v1, v2); 
    libcellml::Variable::addEquivalence(v2, v3);
    libcellml::Variable::addEquivalence(v3, v1); 
   
    v.validateModel(m);
    EXPECT_EQ(1u, v.errorCount());

    if (v.errorCount() == 1) {
        size_t pos = 0;
        std::string split = "Loop: ";
        std::string msg = v.getError(0)->getDescription();
        std::vector<std::string> split_msg;

        while ((pos = msg.find(split)) != std::string::npos) {
            split_msg.push_back(msg.substr(0, pos));
            msg.erase(0, pos + split.length());
        }
        split_msg.push_back(msg);

        EXPECT_EQ(2u, split_msg.size());

        if (split_msg.size() == 2) {
            bool found = false;
            if (split_msg[1].find("variable1") &&
                split_msg[1].find("variable2") &&
                split_msg[1].find("variable3")) {
                found = true;
            }
            EXPECT_TRUE(found);
        }
    }   
}

TEST(Validator, validateNoCyclesComplicated) {
    /// @cellml2_19 19.10.5 Validate that no variable equivalence network has cycles, complicated example
    /// @cellml2_19 19.10.5 TODO Can two sibling variables in the same component be equivalent to one variable in another?
 
    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp4 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp5 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp6 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp7 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp8 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp9 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp10 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp11 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp12 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp13 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp14 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp15 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp16 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp17 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1_1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v1_4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v8 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v9 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v10 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v13 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v14 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v15 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v16 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v17 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    comp1->setName("component1");
    comp2->setName("component2");
    comp3->setName("component3");
    comp4->setName("component4");
    comp5->setName("component5");
    comp6->setName("component6");
    comp7->setName("component7");
    comp8->setName("component8");
    comp9->setName("component9");
    comp10->setName("component10");
    comp11->setName("component11");
    comp12->setName("component12");
    comp13->setName("component13");
    comp14->setName("component14");
    comp15->setName("component15");
    comp16->setName("component16");
    comp17->setName("component17");

    v1_1->setName("variable1_1");
    v1_2->setName("variable1_2");
    v1_3->setName("variable1_3");
    v1_4->setName("variable1_4");
    v2->setName("variable2");
    v3->setName("variable3");
    v4->setName("variable4");
    v5->setName("variable5");
    v6->setName("variable6");
    v7->setName("variable7");
    v8->setName("variable8");
    v9->setName("variable9");
    v10->setName("variable10");
    v11->setName("variable11");
    v12->setName("variable12");
    v13->setName("variable13");
    v14->setName("variable14");
    v15->setName("variable15");
    v16->setName("variable16");
    v17->setName("variable17");

    v1_1->setUnits("dimensionless");
    v1_2->setUnits("dimensionless");
    v1_3->setUnits("dimensionless");
    v1_4->setUnits("dimensionless");
    v2->setUnits("dimensionless");
    v3->setUnits("dimensionless");
    v4->setUnits("dimensionless");
    v5->setUnits("dimensionless");
    v6->setUnits("dimensionless");
    v7->setUnits("dimensionless");
    v8->setUnits("dimensionless");
    v9->setUnits("dimensionless");
    v10->setUnits("dimensionless");
    v11->setUnits("dimensionless");
    v12->setUnits("dimensionless");
    v13->setUnits("dimensionless");
    v14->setUnits("dimensionless");
    v15->setUnits("dimensionless");
    v16->setUnits("dimensionless");
    v17->setUnits("dimensionless");

    comp1->addVariable(v1_1);
    comp1->addVariable(v1_2);
    comp1->addVariable(v1_3);
    comp1->addVariable(v1_4);

    comp2->addVariable(v2);
    comp3->addVariable(v3);
    comp4->addVariable(v4);
    comp5->addVariable(v5);
    comp6->addVariable(v6);
    comp7->addVariable(v7);
    comp8->addVariable(v8);
    comp9->addVariable(v9);
    comp10->addVariable(v10);
    comp11->addVariable(v11);
    comp12->addVariable(v12);
    comp13->addVariable(v13);
    comp14->addVariable(v14);
    comp15->addVariable(v15);
    comp16->addVariable(v16);
    comp17->addVariable(v17);

    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);
    m->addComponent(comp4);
    m->addComponent(comp5); 
    m->addComponent(comp6);
    m->addComponent(comp7);
    m->addComponent(comp8);
    m->addComponent(comp9); 
    m->addComponent(comp10);
    m->addComponent(comp11);
    m->addComponent(comp12);
    m->addComponent(comp13);
    m->addComponent(comp14);
    m->addComponent(comp15);
    m->addComponent(comp16);
    m->addComponent(comp17);

    libcellml::Variable::addEquivalence(v2, v4); 
    libcellml::Variable::addEquivalence(v3, v4);
    libcellml::Variable::addEquivalence(v8, v6); 
    libcellml::Variable::addEquivalence(v2, v8);    
    libcellml::Variable::addEquivalence(v3, v6);    // Loop formed: 2, 4, 3, 6, 8, 2 

    libcellml::Variable::addEquivalence(v6, v7);    
    
    // NB Attached loops (ie: a-b-c-a and b-c-d-b) *are* detected and handled but return too many variations of the loop 
    // (eg a-b-c-d, a-b-c, b-c-d, etc) to be viable as a hard-coded test, so have broken the attachment here.
    // libcellml::Variable::addEquivalence(v3, v7);    // Second attached loop: 3, 6, 7 

    libcellml::Variable::addEquivalence(v9, v5); 
    libcellml::Variable::addEquivalence(v5, v1_2);
    libcellml::Variable::addEquivalence(v1_2, v9);  // Unattached loop: 5, 9, 1_2

    libcellml::Variable::addEquivalence(v11, v4); 
    libcellml::Variable::addEquivalence(v11, v14);
    libcellml::Variable::addEquivalence(v11, v13);
    libcellml::Variable::addEquivalence(v11, v12);
    libcellml::Variable::addEquivalence(v12, v15);
    libcellml::Variable::addEquivalence(v12, v17);
    libcellml::Variable::addEquivalence(v17, v16);   // Complicated tree, no loops 

    libcellml::Variable::addEquivalence(v1_1, v8);  
    libcellml::Variable::addEquivalence(v1_3, v2);  
    // libcellml::Variable::addEquivalence(v1_4, v2);  // TODO Can two sibling variables in the same component be equivalent to one in another?

    v.validateModel(m);
    EXPECT_EQ(1u, v.errorCount());

    // Two loops are present, split error message at "Loop":
    // Check that one loop contains 'variable6' <-> 'variable8' <-> 'variable2' <-> 'variable4' <-> 'variable3' <-> 'variable6',
    // Check that the other contains 'variable1_2' <-> 'variable9' <-> 'variable5' <-> 'variable1_2',
    // "Cyclic variables exist, 2 loops found (Variable(Component)). Loop: 'variable4'(in 'component4') <-> 'variable3'(in 'component3') <-> 'variable6'(in 'component6') <-> 'variable8'(in 'component8') <-> '...
    if (v.errorCount() == 1) {
        size_t pos = 0;
        std::string split = "Loop: ";
        std::string msg = v.getError(0)->getDescription();
        std::vector<std::string> split_msg;

        while ((pos = msg.find(split)) != std::string::npos) {
            split_msg.push_back(msg.substr(0, pos));
            msg.erase(0, pos + split.length());
        }
        split_msg.push_back(msg);

        EXPECT_EQ(3u, split_msg.size());

        if (split_msg.size() == 3) {
        // Check that we have each of the variables present in the two loops
            int found = 0;
            if (((split_msg[1].find("variable6")) &&
                (split_msg[1].find("variable8")) &&
                 (split_msg[1].find("variable2")) &&
                 (split_msg[1].find("variable4")) &&
                 (split_msg[1].find("variable3")))
                || ((split_msg[2].find("variable6")) &&
                (split_msg[2].find("variable8")) &&
                    (split_msg[2].find("variable2")) &&
                    (split_msg[2].find("variable4")) &&
                    (split_msg[2].find("variable3")))) {
                found++;
            }
            if (((split_msg[1].find("variable9")) && (split_msg[1].find("variable5")) && (split_msg[1].find("variable1_2")))
                || ((split_msg[2].find("variable9")) && (split_msg[2].find("variable5")) && (split_msg[2].find("variable1_2")))) {
                found++;
            }
            EXPECT_EQ(2, found);
        }
    }
}

TEST(Validator, integerStrings) {

    /// @cellml2_12 12.1.1.2 Validate TEST order is an integer string (ok: 1, -1; not ok: +1, '', -, string)

    const std::string input =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<model xmlns=\"http://www.cellml.org/cellml/2.0#\" name=\"asoiaf\">"
                "<component name=\"component\">"
                    "<variable name=\"variable\" units=\"dimensionless\"/>"
                    "<reset variable=\"variable\" order=\"1\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"-1\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"+1\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"-\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                    "<reset variable=\"variable\" order=\"odd\">"
                        "<when order=\"200\">"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                            "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                            "</math>"
                        "</when>"
                    "</reset>"
                "</component>"
            "</model>";

    std::vector<std::string> expectedErrors = {
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
        "Component 'component' contains a reset referencing variable 'variable' which does not have an order set.",
    };

    libcellml::Parser p;
    libcellml::ModelPtr m = p.parseModel(input);
    EXPECT_EQ(4u, p.errorCount());

    libcellml::Validator v;
    v.validateModel(m);
    EXPECT_EQ(expectedErrors.size(), v.errorCount());

}

TEST(Validator, resets) {
    /// @cellml2_12 12.1.1.2 Validate TEST Resets in a component have duplicated order values
    /// @cellml2_12 12.1.1.1 Validate TEST Reset does not reference a variable
    /// @cellml2_12 12.1.1.1-2 Validate TEST Reset does not have an order or reference a variable
    /// @cellml2_12 12.1.2 Validate TEST Reset does not contain when item
    /// @cellml2_12 12.1.1.1 and 12.1.2 Validate TEST Reset without order also missing child when
    /// @cellml2_12 12.1.1.1-2 Validate TEST Reset without order does not reference a variable
    /// @cellml2_12 12.1.1.1-2 and 12.1.2 Validate TEST Reset without order, variable and any child whens

    std::vector<std::string> expectedErrors1 = {
        "Component 'comp' contains multiple resets with order '300'.",
        "Reset in component 'comp' with order '300' does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' with order '500' referencing variable 'var' does not have at least one child When.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var'.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var' does not have at least one child When.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable.",
        "Reset in component 'comp' does not have an order set, does not reference a variable, does not have at least one child When.",
    };

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr var = std::make_shared<libcellml::Variable>();

    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r4 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r5 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r6 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r7 = std::make_shared<libcellml::Reset>();

    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();


    w1->setOrder(776);
    w1->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w1->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w2->setOrder(345);
    w2->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w2->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");

    r1->setOrder(300);
    r1->addWhen(w1);

    r6->addWhen(w1);

    r2->setOrder(300);
    r2->addWhen(w1);
    r2->addWhen(w2);
    r2->setVariable(var);

    r3->setOrder(400);
    r3->addWhen(w2);
    r3->setVariable(var);

    r4->setVariable(var);
    r4->setOrder(500);

    r5->setVariable(var);

    c->setName("comp");
    var->setName("var");
    var->setUnits("second");

    c->addVariable(var);
    c->addReset(r1);
    c->addReset(r6);
    c->addReset(r2);
    c->addReset(r3);
    c->addReset(r4);
    c->addReset(r5);
    c->addReset(r7);

    m->setName("main");
    m->addComponent(c);

    // adding reset to second component which does not contain the variable needed
    /// @cellml2_12 12.1.1.1 TODO Validate TEST that variable attribute in a reset must be defined within the component parent
    /// of that reset
    libcellml::ModelPtr m2 = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var2 = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r8 = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();

    w3->setOrder(20);
    w3->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w3->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");

    var2->setName("var2");
    var2->setUnits("metre");

    libcellml::Validator v1;

    v1.validateModel(m);
    EXPECT_EQ(expectedErrors1.size(), v1.errorCount());
    for (size_t i = 0; i < expectedErrors1.size(); ++i) {
        EXPECT_EQ(expectedErrors1.at(i), v1.getError(i)->getDescription());
    }
    /* TODO This should fail but doesn't because we're not checking resets properly ...*/
    /// @cellml2_12 12.1.1 TODO Validate that reset variable exists in component.  Code to check commented out here
    /*r8->setOrder(20);
    r8->addWhen(w3);
    r8->setVariable(var); // not inside this component ...

    c2->addVariable(var2);
    c2->addReset(r8); 
    c2->setName("comp2");

    m2->setName("main2");
    m2->addComponent(c2);

    libcellml::Validator v2;
    v2.validateModel(m2);
    EXPECT_EQ(1u, v2.errorCount());*/

}

TEST(Validator, whens) {
    std::vector<std::string> expectedErrors {
        "Reset in component 'comp' with order '300' does not reference a variable.",
        "When in reset with order '300' which does not reference a variable, does not have an order set.",
        "When in reset with order '300' which does not reference a variable, does not have an order set, does not have a MathML condition set.",
        "When in reset with order '300' which does not reference a variable, does not have an order set, does not have a MathML value set.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var'.",
        "Reset in component 'comp' does not have an order set, referencing variable 'var' has multiple whens with order '250'.",
        "When in reset which does not have an order set, referencing variable 'var' with order '250' does not have a MathML value set.",
        "When in reset which does not have an order set, referencing variable 'var' with order '250' does not have a MathML condition set.",
    };

    /// @cellml2_13 13.1.1 Validate TEST When item has an order
    /// @cellml2_12 12.1.1 Validate TEST When item has a reset which references a variable
    /// @cellml2_13 13.1.2 Validate TEST When item has a reset which references a variable, contains a MathML condition
    /// @cellml2_13 13.1.2 Validate TEST When item has a reset which references a variable, contains a MathML value
    /// @cellml2_12 12.1.2 Validate TEST Reset item has an order
    /// @cellml2_12 12.1.2 Validate TEST Reset item has duplicated order values
    /// @cellml2_13 13.1.2 Validate TEST Reset item references a when which does not have a MathML value 
    /// @cellml2_13 13.1.2 Validate TEST Reset item references a when which does not have a MathML condition
    /// @cellml2_13 13.1.1 Validate TEST When item has unique order amongst siblings

    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr var = std::make_shared<libcellml::Variable>();
    libcellml::ResetPtr r1 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r2 = std::make_shared<libcellml::Reset>();
    libcellml::ResetPtr r3 = std::make_shared<libcellml::Reset>();
    libcellml::WhenPtr w1 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w2 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w3 = std::make_shared<libcellml::When>();
    libcellml::WhenPtr w4 = std::make_shared<libcellml::When>();

    r1->setOrder(300);
    r1->addWhen(w1);
    //r2->setOrder(400);
    r2->addWhen(w2);
    r2->addWhen(w3);
    r3->setOrder(500);
    r3->addWhen(w4);
    // r1->setVariable(var);
    r2->setVariable(var);
    r3->setVariable(var);

    c->setName("comp");
    var->setName("var");
    var->setUnits("second");

    w2->setOrder(250);
    w2->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w3->setOrder(250);
    w3->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w4->setOrder(365);
    w4->setCondition("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");
    w4->setValue("<math xmlns=\"http://www.w3.org/1998/Math/MathML\"></math>");

    c->addVariable(var);
    c->addReset(r1);
    c->addReset(r2);
    c->addReset(r3);

    m->setName("main");
    m->addComponent(c);

    libcellml::Validator v;
    v.validateModel(m);

    EXPECT_EQ(expectedErrors.size(), v.errorCount());
    for (size_t i = 0; i < expectedErrors.size(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), v.getError(i)->getDescription());
    }
}

TEST(Validator, validMathCnElements) {
    std::string math =
            "<math xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns=\"http://www.w3.org/1998/Math/MathML\">"
                "<apply>"
                    "<eq/>"
                    "<ci>C</ci>"
                    "<apply>"
                        "<plus/>"
                        "<cn cellml:units=\"dimensionless\">3.44<sep/>2</cn>"
                        "<cn cellml:units=\"dimensionless\">-9.612</cn>"
                    "</apply>"
                "</apply>"
            "</math>";

    /// @cellml2_14 14.1.4 Validate TEST Tests that valid ci entries pass the tests

    libcellml::Validator v;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr c = std::make_shared<libcellml::Component>();
    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();

    m->setName("modelName");
    c->setName("componentName");
    v1->setName("C");
    v1->setInitialValue("3.5");
    v1->setUnits("dimensionless");

    c->addVariable(v1);
    c->setMath(math);
    m->addComponent(c);

    v.validateModel(m);
    EXPECT_EQ(0u, v.errorCount());
}

TEST(Validator, importDuplicateInfoset) {
    /// @cellml2_5 5.1.3 __TODO?__ Validate TEST Check for semantic equivalence between parent and child infoset: you cannot import yourself
}

TEST(Validator, setUnitsWithNoChildUnit) {

    std::vector<std::string> expectedErrors = {
        "Variable 'v1' has units of 'bushell_of_apples' and an equivalent variable 'v2' with non-matching units of 'bunch_of_bananas'. The mismatch is: apple^10.000000, banana^-5.000000, ",
        "Variable 'v4' has units of 'gram' and an equivalent variable 'v3' with non-matching units of 'litre'. The mismatch is: kilogram^1.000000, metre^-3.000000, ",
        "Variable 'v7' has units of 'apple' and an equivalent variable 'v8' with non-matching units of 'banana'. The mismatch is: apple^1.000000, banana^-1.000000, ",
        "Variable 'v2' has units of 'bunch_of_bananas' and an equivalent variable 'v1' with non-matching units of 'bushell_of_apples'. The mismatch is: apple^-10.000000, banana^5.000000, ",
        "Variable 'v5' has units of 'metre' and an equivalent variable 'v6' with non-matching units of 'second'. The mismatch is: metre^1.000000, second^-1.000000, ",
        "Variable 'v8' has units of 'banana' and an equivalent variable 'v7' with non-matching units of 'apple'. The mismatch is: apple^-1.000000, banana^1.000000, ",
        "Variable 'v3' has units of 'litre' and an equivalent variable 'v4' with non-matching units of 'gram'. The mismatch is: kilogram^-1.000000, metre^3.000000, ",
        "Variable 'v6' has units of 'second' and an equivalent variable 'v5' with non-matching units of 'metre'. The mismatch is: metre^-1.000000, second^1.000000, ",
    };

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();

    libcellml::ComponentPtr c1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr c3 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v8 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v9 = std::make_shared<libcellml::Variable>();

    m->setName("m");
    c1->setName("c1");
    c2->setName("c2");
    c3->setName("c3");
    
    v1->setName("v1");
    v2->setName("v2");
    v3->setName("v3");
    v4->setName("v4");
    v5->setName("v5");
    v6->setName("v6");
    v7->setName("v7");
    v8->setName("v8");
    v9->setName("v9");

    libcellml::UnitsPtr uApple = std::make_shared<libcellml::Units>();
    uApple->setName("apple");

    libcellml::UnitsPtr uBanana = std::make_shared<libcellml::Units>();
    uBanana->setName("banana");

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("bushell_of_apples"); 
    u1->addUnit("apple", 0, 10.0, 1.0);

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("bunch_of_bananas");
    u2->addUnit("banana", 0, 5.0, 1.0);

    libcellml::UnitsPtr u9 = std::make_shared<libcellml::Units>();
    u9->setName("big_barrel"); 
    u9->addUnit("metre", 0, 3.0, 1.0);

    v1->setUnits(u1); // bushell of apples - testing user-defined base units
    v2->setUnits(u2); // bunch of bananas - testing user-defined base units
    
    v3->setUnits("litre"); // testing standard units which are not base units
    v4->setUnits("gram");

    v5->setUnits("metre"); // testing built-in base units
    v6->setUnits("second");

    v7->setUnits("apple");
    v8->setUnits("banana");

    v9->setUnits(u9);

    c1->addVariable(v1);
    c2->addVariable(v2);
    c3->addVariable(v3);

    c1->addVariable(v4);
    c2->addVariable(v5);
    c3->addVariable(v6);

    c1->addVariable(v7);
    c2->addVariable(v8);
    c3->addVariable(v9);

    m->addComponent(c1);
    m->addComponent(c2);
    m->addComponent(c3);

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u9);
    m->addUnits(uApple);
    m->addUnits(uBanana);
       
    libcellml::Variable::addEquivalence(v1, v2); // bushell of apples != bunch of bananas
    libcellml::Variable::addEquivalence(v3, v4); // litre != gram
    libcellml::Variable::addEquivalence(v5, v6); // metre != second
    libcellml::Variable::addEquivalence(v7, v8); // apple != banana
    libcellml::Variable::addEquivalence(v3, v9); // litre = big_barrel (excluding multipliers)

    validator.validateModel(m);

    EXPECT_EQ(8u, validator.errorCount());

    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}

TEST(Validator, variableEquivalentUnits) {
    /// @cellml2_19 19.10.6 Validate TEST Check unit reduction is the same for equivalent variables
    
    std::vector<std::string> expectedErrors = {
        "Variable 'potayto' has units of 'testunit3' and an equivalent variable 'tomahto' with non-matching units of 'testunit2'. The mismatch is: kilogram^1.000000, metre^-2.000000, second^-2.000000, ",
        "Variable 'tomahto' has units of 'testunit2' and an equivalent variable 'potayto' with non-matching units of 'testunit3'. The mismatch is: kilogram^-1.000000, metre^2.000000, second^2.000000, ",
        "Variable 'pjs' has units of 'testunit13' and an equivalent variable 'pajamas' with non-matching units of 'testunit14'. The mismatch is: metre^1.000000, ",
        "Variable 'pajamas' has units of 'testunit14' and an equivalent variable 'pjs' with non-matching units of 'testunit13'. The mismatch is: metre^-1.000000, "
    };

    libcellml::Validator validator;
    libcellml::ModelPtr m = std::make_shared<libcellml::Model>();
    libcellml::ComponentPtr comp1 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp2 = std::make_shared<libcellml::Component>();
    libcellml::ComponentPtr comp3 = std::make_shared<libcellml::Component>();

    libcellml::VariablePtr v1 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v2 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v3 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v4 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v5 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v6 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v7 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v8 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v9 = std::make_shared<libcellml::Variable>();

    libcellml::VariablePtr v10 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v11 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v12 = std::make_shared<libcellml::Variable>();

    libcellml::VariablePtr v13 = std::make_shared<libcellml::Variable>();
    libcellml::VariablePtr v14 = std::make_shared<libcellml::Variable>();

    v1->setName("tomayto");
    v2->setName("tomahto");
    v3->setName("potayto");
    v4->setName("potahto");
    v5->setName("aunty");
    v6->setName("tante");
    v7->setName("auntie");

    v8->setName("neether");
    v9->setName("nyther");

    v10->setName("oom");
    v11->setName("uncle");
    v12->setName("oncle");

    v13->setName("pjs");
    v14->setName("pajamas");

    comp1->setName("isay");
    comp2->setName("yousay");
    comp3->setName("wesay");

    m->setName("callthewholethingoff");

    comp1->addVariable(v1);
    comp2->addVariable(v2);
    comp1->addVariable(v3);
    comp2->addVariable(v4);

    comp1->addVariable(v5);
    comp2->addVariable(v6);
    comp3->addVariable(v7);

    comp2->addVariable(v8);
    comp3->addVariable(v9);

    comp2->addVariable(v10);
    comp3->addVariable(v11);

    comp1->addVariable(v12);
    comp2->addVariable(v13);
    comp3->addVariable(v14);

    m->addComponent(comp1);
    m->addComponent(comp2);
    m->addComponent(comp3);

    libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
    u1->setName("testunit1");
    u1->addUnit("metre");

    libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
    u2->setName("testunit2");
    u2->addUnit("meter");

    libcellml::UnitsPtr u3 = std::make_shared<libcellml::Units>();
    u3->setName("testunit3");
    u3->addUnit("pascal");

    libcellml::UnitsPtr u4 = std::make_shared<libcellml::Units>();
    u4->setName("testunit4");
    u4->addUnit("metre", 0, -1.0, 1.0); // prefix, exp, mult
    u4->addUnit("kilogram", 0, 1.0, 1.0);
    u4->addUnit("second", 0, -2.0, 1.0);

    libcellml::UnitsPtr u5 = std::make_shared<libcellml::Units>();
    u5->setName("testunit5");
    u5->addUnit("metre", 0, -2.0, 1.0);
    u5->addUnit("meter", 0, 2.0, 1.0);

    libcellml::UnitsPtr u6 = std::make_shared<libcellml::Units>();
    u6->setName("testunit6");
    u6->addUnit("dimensionless");

    libcellml::UnitsPtr u7 = std::make_shared<libcellml::Units>();
    u7->setName("testunit7");
    u7->addUnit("steradian");

    libcellml::UnitsPtr u8 = std::make_shared<libcellml::Units>();
    u8->setName("testunit8");
    u8->addUnit("newton", 0, 1, 1);
    u8->addUnit("pascal", 0, -1, 1);
    u8->addUnit("sievert", 0, -1, 1);

    libcellml::UnitsPtr u9 = std::make_shared<libcellml::Units>();
    u9->setName("testunit9");
    u9->addUnit("second", 0, 2, 1);
    u9->addUnit("radian", 0, -4, 1);
    u9->addUnit("steradian", 0, 2, 1);

    libcellml::UnitsPtr u10 = std::make_shared<libcellml::Units>();
    u10->setName("testunit10");
    u10->addUnit("gram", 0, 1, 1000.0);

    libcellml::UnitsPtr u11 = std::make_shared<libcellml::Units>();
    u11->setName("testunit11");
    u11->addUnit("kilogram");

    libcellml::UnitsPtr u12 = std::make_shared<libcellml::Units>();
    u12->setName("testunit12");
    u12->addUnit("gram", "kilo", 1.0, 1.0);

    libcellml::UnitsPtr u13 = std::make_shared<libcellml::Units>();
    u13->setName("testunit13");
    u13->addUnit("testunit2", 0, 2.0, 1.0);
    u13->addUnit("testunit8", 0, 2.0, 1.0);

    libcellml::UnitsPtr u14 = std::make_shared<libcellml::Units>();
    u14->setName("testunit14");
    u14->addUnit("testunit1", 0, 1.0, 1.0);
    u14->addUnit("testunit9", 0, 2.0, 1.0);

    v1->setUnits(u1);
    v2->setUnits(u2);
    v3->setUnits(u3);
    v4->setUnits(u4);
    v5->setUnits(u5);
    v6->setUnits(u6);
    v7->setUnits(u7);
    v8->setUnits(u8);
    v9->setUnits(u9);
    v10->setUnits(u10);
    v11->setUnits(u11);
    v12->setUnits(u12);
    v13->setUnits(u13);
    v14->setUnits(u14);

    m->addUnits(u1);
    m->addUnits(u2);
    m->addUnits(u3);
    m->addUnits(u4);
    m->addUnits(u5);
    m->addUnits(u6);
    m->addUnits(u7);
    m->addUnits(u8);
    m->addUnits(u9);
    m->addUnits(u10);
    m->addUnits(u11);
    m->addUnits(u12);
    m->addUnits(u13);
    m->addUnits(u14);

    // This one is fine : metre vs meter
    libcellml::Variable::addEquivalence(v1, v2);

    // This one is NOT fine: metre vs pascal
    libcellml::Variable::addEquivalence(v2, v3);

    // This one is fine: pascal vs kg/(m.s^2)
    libcellml::Variable::addEquivalence(v3, v4);

    // This one is fine: m^2/m^2 vs dimensionless
    libcellml::Variable::addEquivalence(v5, v6);
    
    // This one is fine: dimensionless vs steradians
    libcellml::Variable::addEquivalence(v6, v7);

    // This one is fine but complicated: newton/(siever.pascal) = second^2.radian^3.steradian^-4
    libcellml::Variable::addEquivalence(v8, v9);	

    // Fine: testing the multipliers 1000*grams = 1*kilograms 
    // ** NB multipliers not tested!
    libcellml::Variable::addEquivalence(v10, v11);

    // Fine: testing prefix kilo*gram = kilogram
    // ** NB multipliers not tested!
    libcellml::Variable::addEquivalence(v10, v12); 

    // Off by (meter)^1: super-complicated nested units
    libcellml::Variable::addEquivalence(v13, v14);

    validator.validateModel(m);

    EXPECT_EQ(4u, validator.errorCount());

    // Check for expected error messages
    for (size_t i = 0; i < validator.errorCount(); ++i) {
        EXPECT_EQ(expectedErrors.at(i), validator.getError(i)->getDescription());
    }
}








