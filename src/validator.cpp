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

#include "utilities.h"
#include "xmldoc.h"

#include <libxml/uri.h>

#include "libcellml/component.h"
#include "libcellml/error.h"
#include "libcellml/importsource.h"
#include "libcellml/model.h"
#include "libcellml/namespaces.h"
#include "libcellml/reset.h"
#include "libcellml/units.h"
#include "libcellml/validator.h"
#include "libcellml/variable.h"
#include "libcellml/when.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <set>

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

namespace libcellml {

/**
* @brief The Validator::ValidatorImpl struct.
*
* The private implementation for the Validator class.
*/
struct Validator::ValidatorImpl
{
    Validator *mValidator;

    /**
	    * @brief Validate the @p component using the CellML 2.0 Specification.
	    * @cellml2_10 Validate the @p component using the CellML 2.0 Specification.
	    *
	    * Validate the given @p component and its encapsulated entities using
	    * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
	    *
	    * @param component The component to validate.
	    */
    void validateComponent(const ComponentPtr &component);

    /**
	    * @brief Validate the @p units using the CellML 2.0 Specification.
	    * @cellml2_8 Validate the @p units using the CellML 2.0 Specification.
	    * Validate the given @p units and its encapsulated entities using
	    * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
	    *
	    * @param units The units to validate.
	    * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
	    */
    void validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames);

    /**
	    * @brief Validate the variable connections in the @p model using the CellML 2.0 Specification.
	    * @cellml2_17 Validate the variable connections in the @p model using the CellML 2.0 Specification.
	    * Validate the variable connections in the given @p model using
	    * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
	    *
	    * @param model The model which may contain variable connections to validate.
	    */
    void validateConnections(const ModelPtr &model);

    /**
    * @brief Validate that there are no cycles in the equivalance network in the @p model
    * using the CellML 2.0 Specification.
    * Any errors will be logged in the @c Validator.
    *
    * @param model The model which may contain variable connections to validate.
    * @param hints The helper string returned containing the list(s) of cyclic variables
    */
    bool modelVariablesAreCyclic(const ModelPtr &model, std::vector<std::string> &hints);

    /**
	    * @brief Check if the provided @p name is a valid CellML identifier.
	    *
	    * Check if the provided @p name is a valid CellML identifier according
	    * to the CellML 2.0 specification. This requires a non-zero length Unicode
	    * character sequence containing basic Latin alphanumeric characters or
	    * underscores that does not start with a number.
	    *
	    * @param name The @c std::string name to check the validity of.
	    *
	    * @return @c true if @name is a valid CellML identifier and @c false otherwise.
	    */
    bool isCellmlIdentifier(const std::string &name);

    /**
	    * @brief Validate the @c unit at index @c index from @p units using the CellML 2.0 Specification.
	    *
	    * Validate the @c unit at index @c index from @p units using
	    * the CellML 2.0 Specification. Any errors will be logged in the @c Validator.
	    *
	    * @param index The index of the @c unit to validate from @p units.
	    * @param units The units to validate.
	    * @param unitsNames A vector list of the name attributes of the @p units and its siblings.
	    */
    void validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames);

    /**
	    * @brief Validate the @p variable using the CellML 2.0 Specification.
	    * @cellml2_11 Validate the variable using the CellML 2.0 Specification
	    * Validate the given @p variable using the CellML 2.0 Specification.
	    * Any errors will be logged in the @c Validator.
	    *
	    * @param variable The variable to validate.
	    * @param variableNames A vector list of the name attributes of the @p variable and its siblings.
	    */
    void validateVariable(const VariablePtr &variable, std::vector<std::string> &variableNames);

    /**
	    * @brief Validate the @p reset using the CellML 2.0 Specification.
	    * @cellml2_12 Validate the @p reset using the CellML 2.0 Specification.
	    * Examine the @p reset for conformance to the CellML 2.0 specification.  Any
	    * errors will be logged in the @c Validator.
	    *
	    * @param reset The reset to validate.
	    * @param component The component the reset belongs to.
	    */
    void validateReset(const ResetPtr &reset, const ComponentPtr &component);

    /**
	    * @brief Validate the @p when using the CellML 2.0 specification.
	    * @cellml2_13 Validate the @p when using the CellML 2.0 specification.
	    * Examine the @p when for conformance to the CellML 2.0 specification.  Any
	    * errors will be logged in the @c Validator.
	    *
	    * @param when The when to validate.
	    * @param reset The reset the when belongs to.
	    * @param component The component the reset belongs to.
	    */
    void validateWhen(const WhenPtr &when, const ResetPtr &reset, const ComponentPtr &component);

    /**
	    * @brief Validate the math @p input @c std::string.
	    * @cellml2_14 Validate the math @p input @c std::string.
	    * Validate the math @p input @c std::string using the CellML 2.0 Specification and
	    * the W3C MathML DTD. Any errors will be logged in the @c Validator.
	    *
	    * @param input The math @c std::string to validate.
	    * @param component The component containing the math @c std::string to be validated.
	    */
    void validateMath(const std::string &input, const ComponentPtr &component);

    /**
	    * @brief Populate @p bvarNames with new variables declared in MathML @c bvar elements.
	    *
	    * Populate @p bvarNames with new variables declared in MathML @c bvar elements found within
	    * the XmlNode @p node.
	    *
	    * @param node The @c XmlNode to search for @c bvar element names.
	    * @param bvarNames The @c std::string @c vector to populate with MathML @c bvar element names.
	    */
    void gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames);

    /**
	    * @brief Traverse the node tree for invalid MathML elements.
	    *
	    * Traverse the Xml node tree checking that all MathML elements are listed in the
	    * supported MathML elements table from the CellML specification 2.0 document.
	    *
	    * @param node The node to check children and sibling nodes.
	    * @param component The component the MathML belongs to.
	    */
    void validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component);

    /**
	    * @brief Validate CellML variables and units in MathML @c ci and @c cn variables. Removes CellML units from the @p node.
	    *
	    * Validates CellML variables found in MathML @c ci elements and new variables from @c bvar elements. Validates @c cellml:units
	    * attributes found on @c ci and @c cn elements and removes them from the @c XmlNode @p node to leave MathML that may then
	    * be validated using the MathML DTD.
	    *
	    * @param node The @c XmlNode to validate CellML entities on and remove @c cellml:units from.
	    * @param component The component that the math @c XmlNode @p node is contained within.
	    * @param variableNames A @c vector list of the names of variables found within the @p component.
	    * @param bvarNames A @c vector list of the names of new MathML @c bvar variables in this @c XmlNode @p node.
	    */
    void validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames, const std::vector<std::string> &bvarNames);

    /**
	    * @brief Remove the @c std::string @p pattern from the @c std::string @p input.
	    *
	    * Remove all occurrences of the @c std::string @p pattern from the @c std::string @p input.
	    *
	    * @param input The @c std::string to remove all occurrences of the @p pattern from.
	    * @param pattern The @c std::string to remove from the @c std::string @p input.
	    */
    void removeSubstring(std::string &input, std::string &pattern);

    /**
	    * @brief Check if the provided @p name is a standard unit.
	    *
	    * Checks if the provided @p name is one of the standard units in the
	    * @c Units::StandardUnit @c enum. Returns @c true if @name is a standard unit
	    * and @c false otherwise.
	    *
	    * @param name The @c std::string name to check against the list of standard units.
	    *
	    * @return @c true if @name is a standard unit and @c false otherwise.
	    */
    bool isStandardUnitName(const std::string &name);

    /**
	    * @brief Check if the provided @p name is a standard prefix.
	    *
	    * Checks if the provided @p name is one of the standard prefixes in the
	    * @c Prefix @c enum. Returns @c true if @name is a standard prefix
	    * and @c false otherwise.
	    *
	    * @param name The @c std::string name to check against the list of standard prefixes.
	    *
	    * @return @c true if @name is a standard prefix and @c false otherwise.
	    */
    bool isStandardPrefixName(const std::string &name);

    /**
	    * @brief Check if the provided @p node is a supported MathML element.
	    *
	    * Checks if the provided @p node is one of the supported MathML elements defined in the table
	    * of supported MathML elements from the CellML specification version 2.0 document.
	    *
	    * @param node The @c XmlNode node to check against the list of supported MathML elements.
	    * @return @c true if @node is a supported MathML element and @c false otherwise.
	    */
    bool isSupportedMathMLElement(const XmlNodePtr &node);

    /**
    * @brief Validate that equivalent variable pairs in the @p model
    * have equivalent units.
    * @cellml2_19 Validate that equivalent variable pairs in the @p model
    * have equivalent units
    * Any errors will be logged in the @c Validator.
    *
    * @param model The model containing the variables
    * @param v1 The variable which may contain units.
    * @param v2 The equivalent variable which may contain units.
    * @param hints String containing error messages to be passed back to calling function for logging
    */
    bool unitsAreEquivalent(const ModelPtr &model, const VariablePtr &v1, const VariablePtr &v2, std::string &hints);

    /**
    * @brief Utility function used by unitsAreEquivalent to compare base units of two varaibles
    *
    * @param model The model containing the variables
    * @param unitmap A list of the exponents of base varaibles.
    * @param uName String name of the current variable being investigated.
    * @param standardList Nested map of the conversion between built-in units and the base units they contain
    * @param uExp Exponent of the current unit in its parent.  
    */
    void incrementBaseUnitCount(const ModelPtr &model, std::map<std::string,double> &unitmap, 
        const std::string uName,
	    const std::map< std::string, std::map<std::string, double>> &standardList,
	    const double uExp);

    /**
    * @brief Utility function used by unitsAreEquivalent to compare base units of two varaibles
    *
    * @param model The model containing the variables
    * @param unitmap A list of the exponents of base varaibles.
    * @param uName String name of the current variable being investigated.
    * @param standardList Nested map of the conversion between built-in units and the base units they contain
    * @param uExp Exponent of the current unit in its parent.  
    */
    void decrementBaseUnitCount(const ModelPtr &model, std::map<std::string,
	    double> &unitmap, const std::string uName,
	    const std::map< std::string, std::map<std::string, double>> &standardList,
	    const double uExp);

    bool isValidHTML(const std::string &html);
};

Validator::Validator()
    : mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = this;
}

Validator::~Validator()
{
    delete mPimpl;
}

Validator::Validator(const Validator &rhs)
    : Logger(rhs)
    , mPimpl(new ValidatorImpl())
{
    mPimpl->mValidator = rhs.mPimpl->mValidator;
}

Validator::Validator(Validator &&rhs)
    : Logger(std::move(rhs))
    , mPimpl(rhs.mPimpl)
{
    rhs.mPimpl = nullptr;
}

Validator& Validator::operator=(Validator v)
{
    Logger::operator =(v);
    v.swap(*this);
    return *this;
}

void Validator::swap(Validator &rhs)
{
    std::swap(this->mPimpl, rhs.mPimpl);
}

void Validator::validateModel(const ModelPtr &model)
{
    // Clear any pre-existing errors in the validator instance.
    clearErrors();
    /// @cellml2_4 4.2.1 Check for a valid name format
    if (!mPimpl->isCellmlIdentifier(model->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Model does not have a valid name attribute.");
        err->setModel(model);
        err->setRule(SpecificationRule::MODEL_NAME);
        addError(err);
    }
    /// @cellml2_4 4.2.3 Check for unique encapsulation is not required as more than one cannot be stored
    
    /// @cellml2_4 4.2.2 Check for presence of components in this model.
    if (model->componentCount() > 0) {
        std::vector<std::string> componentNames;
        std::vector<std::string> componentRefs;
        std::vector<std::string> componentImportSources;
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);

            std::string componentName = component->getName();
            if (componentName.length()) {
                if (component->isImport()) {
                    // Check for a component_ref; assumes imported if the import source is not null
					/// @cellml2_7 7.1.2 Check that the name of the component given by the component_ref 
					/// is in a valid format.  NB: Does not check what it refers to.
                    std::string componentRef = component->getImportReference(); 
                    std::string importSource = component->getImportSource()->getUrl(); 
                    bool foundImportError = false;
                    if (!mPimpl->isCellmlIdentifier(componentRef)) {
						
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported component '" + componentName +
                                            "' does not have a valid component_ref attribute.");
                        err->setComponent(component);
                        err->setRule(SpecificationRule::IMPORT_COMPONENT_REF);
                        addError(err);
                        foundImportError = true;
                    }
                    /// @cellml2_7 7.1.2 Check that a xlink:href attribute is present
                    if (!importSource.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of component '" + componentName +
                                            "' does not have a valid locator xlink:href attribute.");
                        err->setImportSource(component->getImportSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                        foundImportError = true;
                    }
                    /// @cellml2_5 5.1.1 Check that xlink:href meets XLink specs
                    else if (!mPimpl->isValidHTML(importSource)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of component '" + componentName +
                                            "' has an invalid URI in the href attribute, '" + importSource + "'. ");
                        err->setImportSource(component->getImportSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                        foundImportError = true;
                    }
                    /// @cellml2_5 5.1.3 Check if we already have another import from the same source with the same component_ref. 
                    if ((componentImportSources.size() > 0) && (!foundImportError)) {
                        // Check for presence of import source and component_ref
                        std::ptrdiff_t foundSourceAt = find(componentImportSources.begin(), componentImportSources.end(), importSource) 
                            - componentImportSources.begin();
                        std::ptrdiff_t foundRefAt = find(componentRefs.begin(), componentRefs.end(), componentRef) 
                            - componentRefs.begin();

                        // Check that they occur at the same point in the list, *and* that we're not out of range
                        // "unsigned" used here to prevent mismatch warning at build time
                        if((unsigned (foundSourceAt) < componentImportSources.size()) && 
                            (unsigned (foundRefAt) < componentRefs.size()) &&            
                            (foundRefAt == foundSourceAt)) {
                            ErrorPtr err = std::make_shared<Error>();
                                err->setDescription("Model '" + model->getName() +
                                                    "' contains multiple imported components from '" + importSource +
                                                    "' with the same component_ref attribute '" + componentRef + "'.");
                                err->setModel(model);
                                err->setRule(SpecificationRule::IMPORT_COMPONENT_REF);
                                addError(err);
                        }
                    }
                    // Push back the unique sources and refs.
                    componentImportSources.push_back(importSource);
                    componentRefs.push_back(componentRef);
                }
				/// @cellml2_10 10.1.1 Check for duplicate component names in this model.
				if(std::find(componentNames.begin(), componentNames.end(), componentName) != componentNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->getName() +
                                        "' contains multiple components with the name '" + componentName +
                                        "'. Valid component names must be unique to their model.");
                    err->setModel(model);
                    addError(err);
                }
                componentNames.push_back(componentName);
            }
            /// @cellml2_4 4.2.1 Validates components in this model.
			/// @cellml2_10 10.1.1 This function call validates the names and other aspects of the components in the model.
            mPimpl->validateComponent(component);
        }
    }
    /// @cellml2_4 4.2.2.5 Check for presence of units in this model 
    if (model->unitsCount() > 0) {
        std::vector<std::string> unitsNames;
        std::vector<std::string> unitsRefs;
        std::vector<std::string> unitsImportSources;
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            UnitsPtr units = model->getUnits(i);
            std::string unitsName = units->getName();
            if (unitsName.length()) {
                if (units->isImport()) {
                    /// @cellml2_6 6.1.2 Check for a units_ref in this import units instance
                    std::string unitsRef = units->getImportReference();
                    std::string importSource = units->getImportSource()->getUrl();
                    bool foundImportError = false;
					/// @cellml2_6 6.1.2 Check that the name given by the units_ref matches the naming specifications
                    if (!mPimpl->isCellmlIdentifier(unitsRef)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Imported units '" + unitsName +
                                            "' does not have a valid units_ref attribute.");
                        err->setUnits(units);
                        err->setRule(SpecificationRule::IMPORT_UNITS_REF);
                        addError(err);
                        foundImportError = true;
                    }
                    /// @cellml2_6 6.1.2 Check that a xlink:href is present 
                    if (!importSource.length()) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of units '" + unitsName +
                                            "' does not have a valid locator xlink:href attribute.");
                        err->setImportSource(units->getImportSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                        foundImportError = true;
                    }
                    /// @cellml2_5 5.1.1 Check that xlink:href meets XLink specs 
                    else if (!mPimpl->isValidHTML(importSource)) {
                        ErrorPtr err = std::make_shared<Error>();
                        err->setDescription("Import of units '" + unitsName +
                                            "' has an invalid URI in the href attribute, '" + importSource + "'. ");
                        err->setImportSource(units->getImportSource());
                        err->setRule(SpecificationRule::IMPORT_HREF);
                        addError(err);
                        foundImportError = true;
                    }

                    /// @cellml2_6 6.1.2 Check if we already have another import from the same source with the same units_ref.
                    /// (This looks for matching enties at the same position in the source and ref vectors).
                    if ((unitsImportSources.size() > 0) && (!foundImportError)) {
                        if ((std::find(unitsImportSources.begin(), unitsImportSources.end(), importSource) - unitsImportSources.begin())
                         == (std::find(unitsRefs.begin(), unitsRefs.end(), unitsRef) - unitsRefs.begin())){
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Model '" + model->getName() +
                                                "' contains multiple imported units from '" + importSource +
                                                "' with the same units_ref attribute '" + unitsRef + "'.");
                            err->setModel(model);
                            err->setRule(SpecificationRule::IMPORT_UNITS_REF);
                            addError(err);
                        }
                    }
                    // Push back the unique sources and refs.
                    unitsImportSources.push_back(importSource);
                    unitsRefs.push_back(unitsRef);
                }
                /// @cellml2_8 8.1.2 Check for duplicate units names in this model.
                if(std::find(unitsNames.begin(), unitsNames.end(), unitsName) != unitsNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Model '" + model->getName() +
                                        "' contains multiple units with the name '" + unitsName +
                                        "'. Valid units names must be unique to their model.");
                    err->setModel(model);
                    err->setRule(SpecificationRule::UNITS_NAME_UNIQUE);
                    addError(err);
                }
                unitsNames.push_back(unitsName);
            }
        }
        for (size_t i = 0; i < model->unitsCount(); ++i) {
            /// @cellml2_4 4.2.2.5 Validates units in this model
			/// @cellml2_8 Validates units in this model
            UnitsPtr units = model->getUnits(i);
            mPimpl->validateUnits(units, unitsNames);
        }
    }
    /// @cellml2_4 4.2.2.2 Validates any connections / variable equivalence networks in the model.
    mPimpl->validateConnections(model);
}

void Validator::ValidatorImpl::validateComponent(const ComponentPtr &component)
{
    /// @cellml2_10 10.1.1 Check for a valid name attribute. 
	if (!isCellmlIdentifier(component->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setComponent(component);
        if (component->isImport()) {
            err->setDescription("Imported component does not have a valid name attribute.");
            err->setRule(SpecificationRule::IMPORT_COMPONENT_NAME);
        } else {
            err->setDescription("Component does not have a valid name attribute.");
            err->setRule(SpecificationRule::COMPONENT_NAME);
        }
        mValidator->addError(err);
    }
    /// @cellml2_10 10.1.2.1 Check the variables in this component.  
    std::vector<std::string> variableNames;
    if (component->variableCount() > 0) {
		/// @cellml2_11 11.1.1 Check for duplicate variable names in imported components
        // Check for duplicate variable names and construct vector of valid names in case
        // we have a variable initial_value set by reference.
        for (size_t i = 0; i < component->variableCount(); ++i) {
            std::string variableName = component->getVariable(i)->getName();
            if (variableName.length()) {
                if (std::find(variableNames.begin(), variableNames.end(), variableName) != variableNames.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->getName() +
                                        "' contains multiple variables with the name '" + variableName +
                                        "'. Valid variable names must be unique to their component.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::VARIABLE_NAME);
                    mValidator->addError(err);
                }
                variableNames.push_back(variableName);
            }
        }
        /// @cellml2_11 11.1.1 Validates variable(s) in a componenet
        for (size_t i = 0; i < component->variableCount(); ++i) {
            VariablePtr variable = component->getVariable(i);
            validateVariable(variable, variableNames);
        }
    }
    /// @cellml2_10 10.1.2.2 Check for presence of resets in this component
    if (component->resetCount() > 0) {
        /// @cellml2_12 12.1.1.2 Check for duplicate order values in resets in this component
        std::vector<int> resetOrders;
        for (size_t i = 0; i < component->resetCount(); ++i) {
            ResetPtr reset = component->getReset(i);
            int resetOrder = reset->getOrder();
            if (reset->isOrderSet()) {
                if (std::find(resetOrders.begin(), resetOrders.end(), resetOrder) != resetOrders.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Component '" + component->getName() +
                                        "' contains multiple resets with order '" + convertIntToString(resetOrder) + "'.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::RESET_ORDER);
                    mValidator->addError(err);
                } else {
                    resetOrders.push_back(resetOrder);
                }
            }
        }
		/// @cellml2_10 10.1.2.2 Validate resets in this component's variables
        for (size_t i = 0; i < component->resetCount(); ++i) {
            ResetPtr reset = component->getReset(i);
            validateReset(reset, component);
        }
    }
    /// @cellml2_10 10.1.2.3 Validate math through the private implementation (for XML handling) in this component
    if (component->getMath().length()) {
        validateMath(component->getMath(), component);
    }
}

void Validator::ValidatorImpl::validateUnits(const UnitsPtr &units, const std::vector<std::string> &unitsNames)
{
	/// @cellml2_8 8.1.1 check that the units' name field is present
    if (!isCellmlIdentifier(units->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setUnits(units);
        if (units->isImport()) {
            err->setDescription("Imported units does not have a valid name attribute.");
            err->setRule(SpecificationRule::IMPORT_UNITS_NAME);
        } else {
            err->setDescription("Units does not have a valid name attribute.");
            err->setRule(SpecificationRule::UNITS_NAME);
        }
        mValidator->addError(err);
    } else {
        /// @cellml2_8 8.1.3 Checks for duplicated names in the standard/built-in units.
        if (isStandardUnitName(units->getName())) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units is named '" + units->getName() +
                                "', which is a protected standard unit name.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNITS_STANDARD);
            mValidator->addError(err);
        }
    }
    if (units->unitCount() > 0) {
        /// @cellml2_8 8.1.4 Validates each unit in units.
        for (size_t i = 0; i < units->unitCount(); ++i) {
            validateUnitsUnit(i, units, unitsNames);
        }
    }
}

void Validator::ValidatorImpl::validateUnitsUnit(size_t index, const UnitsPtr &units, const std::vector<std::string> &unitsNames)
{
    // Validate the unit at the given index.
    std::string reference, prefix, id;
    double exponent, multiplier;

    // NB This function silently sets invalid numbers to 1.0, validator calls should give a better error message than that
    units->getUnitAttributes(index, reference, prefix, exponent, multiplier, id);
	/// @cellml2_9 9.1.1 Check that the unit element has a units reference
    if (isCellmlIdentifier(reference)) {
        if ((std::find(unitsNames.begin(), unitsNames.end(), reference) == unitsNames.end()) &&
            (!isStandardUnitName(reference))) {
			/// @cellml2_8 8.1.1 Check that units point to a standard or local unit base
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Units reference '" + reference + "' in units '" + units->getName() +
                                    "' is not a valid reference to a local units or a standard unit type.");
            err->setUnits(units);
            err->setRule(SpecificationRule::UNIT_UNITS_REF);
            mValidator->addError(err);
        }
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Unit in units '" + units->getName() +
                            "' does not have a valid units reference.");
        err->setUnits(units);
        err->setRule(SpecificationRule::UNIT_UNITS_REF);
        mValidator->addError(err);
    }
    if (prefix.length()) {
        /// cellml2_9 9.1.2.1 Check the prefix. If the prefix is not in the list of valid prefix names, 
		/// check that it is an integer.
        if (!isStandardPrefixName(prefix)) {
            if (!isCellMLInteger(prefix)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Prefix '" + prefix + "' of a unit referencing '" + reference +
                                    "' in units '" + units->getName() +
                                    "' is not a valid integer or a SI prefix.");
                err->setUnits(units);
                err->setRule(SpecificationRule::UNIT_PREFIX);
                mValidator->addError(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateVariable(const VariablePtr &variable, std::vector<std::string> &variableNames)
{
    /// @cellml2_11 11.1.1.1 Check for a valid name attribute. Validator::ValidatorImpl::validateVariable
    if (!isCellmlIdentifier(variable->getName())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable does not have a valid name attribute.");
        err->setVariable(variable);
        err->setRule(SpecificationRule::VARIABLE_NAME);
        mValidator->addError(err);
    }
    /// @cellml2_11 11.1.1.2 Check that this variable specifies units which have an identifier
    if (!isCellmlIdentifier(variable->getUnits())) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Variable '" + variable->getName() +
                            "' does not have a valid units attribute.");
        err->setVariable(variable);
        err->setRule(SpecificationRule::VARIABLE_UNITS);
        mValidator->addError(err);
    } else if (!isStandardUnitName(variable->getUnits())) {
        Component* component = static_cast<Component*>(variable->getParent());
        Model* model = static_cast<Model*>(component->getParent());
		/// @cellml2_11 11.1.2 Check that this variable has units which, if non-standard, are specified in the model
        if (model && !model->hasUnits(variable->getUnits())) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->getName() +
                                "' has an invalid units reference '" + variable->getUnits() +
                                "' that does not correspond with a standard unit or units in the variable's parent component or model.");
            err->setVariable(variable);
            err->setRule(SpecificationRule::VARIABLE_UNITS);
            mValidator->addError(err);
        }
    }
    
    if (variable->getInterfaceType().length()) {
        std::string interfaceType = variable->getInterfaceType();
		/// @cellml2_11 11.1.2.1 If this variable specifies an interface, checks that its type is public, private, 
		/// public_and_private, or none.
        if ((interfaceType != "public") && (interfaceType != "private") &&
            (interfaceType != "none") && (interfaceType != "public_and_private")) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Variable '" + variable->getName() +
                                "' has an invalid interface attribute value '" + interfaceType + "'.");
            err->setVariable(variable);
            err->setRule(SpecificationRule::VARIABLE_INTERFACE);
            mValidator->addError(err);
        }
    }
    
    if (variable->getInitialValue().length()) {
        std::string initialValue = variable->getInitialValue();
        // Check if initial value is a variable reference
		/// @cellml2_11 11.1.2.2 If this variable specifies an initial value, checks that it has a valid reference
        if(!(std::find(variableNames.begin(), variableNames.end(), initialValue) != variableNames.end())) {
            // Otherwise, check that the initial value can be converted to a double
			/// @cellml2_11 11.1.2.2 If the initial value is not a reference, then check it's convertible to a double
            if (!isCellMLReal(initialValue)) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Variable '" + variable->getName() +
                                    "' has an invalid initial value '" + initialValue +
                                    "'. Initial values must be a real number string or a variable reference.");
                err->setVariable(variable);
                err->setRule(SpecificationRule::VARIABLE_INITIAL_VALUE);
                mValidator->addError(err);
            }
        }
    }
}

void Validator::ValidatorImpl::validateReset(const ResetPtr &reset, const ComponentPtr &component)
{
	/// @cellml2_12 12.1.1.2 Check that this reset order is set
    std::string orderString;
    if (reset->isOrderSet()) {
        orderString = "with order '" + convertIntToString(reset->getOrder()) + "'";
    } else {
        orderString = "does not have an order set,";
    }

	/// @cellml2_12 12.1.1.1 Check that this reset references a variable 
    std::string variableString;
    std::string variableContinuation = "";
    if (reset->getVariable() == nullptr) {
        variableString = "does not reference a variable";
        variableContinuation = ",";
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() +
                            "' " + orderString +
                            " " + variableString + ".");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_VARIABLE_REFERENCE);
        mValidator->addError(err);
    } else {
        variableString = "referencing variable '" + reset->getVariable()->getName() + "'";
    }

	/// @cellml2_12 __TODO__ (KRM: I don't understand what this one is doing - why check the order and raise error from component?)
    if (!reset->isOrderSet()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() +
                            "' " + orderString +
                            " " + variableString + ".");
        err->setComponent(component);
        err->setRule(SpecificationRule::RESET_ORDER);
        mValidator->addError(err);
    }

	/// @cellml2_12 12.1.1.2 Checking for duplicate order values for each 'when' entry in this reset
    if (reset->whenCount() > 0) {
        // Check for duplicate when order values.
        std::vector<int> whenOrders;
        for (size_t i = 0; i < reset->whenCount(); ++i) {
            WhenPtr when = reset->getWhen(i);
            if (when->isOrderSet()) {
                int whenOrder = when->getOrder();
                if (std::find(whenOrders.begin(), whenOrders.end(), whenOrder) != whenOrders.end()) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Reset in component '" + component->getName() +
                                        "' " + orderString +
                                        " " + variableString + variableContinuation +
                                        " has multiple whens with order '" + convertIntToString(whenOrder) + "'.");
                    err->setComponent(component);
                    err->setRule(SpecificationRule::RESET_ORDER);
                    mValidator->addError(err);
                } else {
                    whenOrders.push_back(whenOrder);
                }
            }

        }
		/// @cellml2_12 12.1.1.3 Validates all 'when' children
        for (size_t i = 0; i < reset->whenCount(); ++i) {
            WhenPtr when = reset->getWhen(i);
            validateWhen(when, reset, component);
        }
    } else {
		///@cellml2_12 12.1.1.3 Check there is at least one 'when' child
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Reset in component '" + component->getName() +
                            "' " + orderString +
                            " " + variableString + variableContinuation +
                            " does not have at least one child When.");
        err->setReset(reset);
        err->setRule(SpecificationRule::RESET_CHILD);
        mValidator->addError(err);
    }

	/// @cellml2_12 __TODO__ KRM Need to check whether there is an implied 1-to-1 correspondence between 
	/// the 'when' element(s) and the 'order' integers? If so, does it need to be validated?  Is this specified in 
	/// 13.1.1 When specifications?
}

void Validator::ValidatorImpl::validateWhen(const WhenPtr &when, const ResetPtr &reset, const ComponentPtr &component)
{
    std::string orderString;
    std::string resetOrderString;
    std::string resetVariableString;
    std::string resetVariableContinuation;

	/// @cellml2_13 13.1.1 Check that there is an order attribute specified for input when
    if (when->isOrderSet()) {
        orderString = "with order '" + convertIntToString(when->getOrder()) + "'";
    } else {
        orderString = "does not have an order set,";
    }

	/// @cellml2_12 12.1.1.3 Check that there is an order attribute specified for input reset element
    if (reset->isOrderSet()) {
        resetOrderString = "with order '" + convertIntToString(reset->getOrder()) + "'";
    } else {
        resetOrderString = "which does not have an order set,";
    }

	/// @cellml2_12 12.1.1.1 (?) Check that input reset references a variable
    if (reset->getVariable() == nullptr) {
        resetVariableString = "which does not reference a variable";
        resetVariableContinuation = ",";
    } else {
        resetVariableContinuation = "";
        resetVariableString = "referencing variable '" + reset->getVariable()->getName() + "'";
    }

	/// @cellml2_13 13.1.1 Check that input when has an order  (? checks when->isOrder but returns error
	/// from reset?)
    if (!when->isOrderSet()) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString +
                            " " + resetVariableString + resetVariableContinuation +
                            " does not have an order set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_ORDER);
        mValidator->addError(err);
    }

	/// @cellml2_13 13.1.2 13.? Check maths condition of the input component (? Checks component but returns error based on reset?)
    if (when->getCondition().length() > 0) {
        validateMath(when->getCondition(), component);
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString +
                            " " + resetVariableString + resetVariableContinuation +
                            " " + orderString +
                            " does not have a MathML condition set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_CHILD);
        mValidator->addError(err);
    }

	/// @cellml2_13 13.? Check maths value of the input component (? Checks component but returns error based on reset?)
    /// @cellml2_14 14.? Check maths value of the input component (? Checks component but returns error based on reset?)
    if (when->getValue().length() > 0) {
        validateMath(when->getValue(), component);
    } else {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("When in reset " + resetOrderString +
                            " " + resetVariableString + resetVariableContinuation +
                            " " + orderString +
                            " does not have a MathML value set.");
        err->setWhen(when);
        err->setRule(SpecificationRule::WHEN_CHILD);
        mValidator->addError(err);
    }

}

void Validator::ValidatorImpl::validateMath(const std::string &input, const ComponentPtr &component)
{
	/// @cellml2_14 14.1.1 Check input XML is valid for a component
    XmlDocPtr doc = std::make_shared<XmlDoc>();
    // Parse as XML first.
    doc->parse(input);
    // Copy any XML parsing errors into the common validator error handler.
    if (doc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < doc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(doc->getXmlError(i));
            err->setKind(Error::Kind::XML);
            mValidator->addError(err);
        }
    }
    XmlNodePtr node = doc->getRootNode();
	/// @cellml2_14 14.1.1 Check input XML is valid MathML with valid root node for input component
    if (!node) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Could not get a valid XML root node from the math on component '" + component->getName() + "'.");
        err->setKind(Error::Kind::XML);
        err->setComponent(component);
        mValidator->addError(err);
        return;
    } else if (!node->isElement("math", MATHML_NS)) {
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("Math root node is of invalid type '" + node->getName() +
                            "' on component '" + component->getName() +
                            "'. A valid math root node should be of type 'math'.");
        err->setComponent(component);
        err->setKind(Error::Kind::XML);
        mValidator->addError(err);
        return;
    }
    XmlNodePtr nodeCopy = node;
    std::vector<std::string> bvarNames;
    std::vector<std::string> variableNames;
	// making a list of unique variable names inside component
	/// @cellml2_14 __TODO__ Should variable names inside a component be validated to prevent duplicates 
	/// instead of removing silently from check list?
    for (size_t i = 0; i < component->variableCount(); ++i) {
        std::string variableName = component->getVariable(i)->getName();
        if (std::find(variableNames.begin(), variableNames.end(), variableName) == variableNames.end()) {
            variableNames.push_back(variableName);
        }
      
    }

	/// @cellml2_14 14.1.3 Check that the variables in the MathML are supported, see hard-coded list at
	/// bool Validator::ValidatorImpl::isSupportedMathMLElement(const XmlNodePtr &node)
    validateMathMLElements(nodeCopy, component);

    // Get the bvar names in this math element.
    // TODO: may want to do this with XPath instead...
	/// @cellml2_14 __TODO__ Change to XPath instead? 
	/// @cellml2_14 14.? Check that there are no duplicates between bound (bvar) and unbound variable names
    gatherMathBvarVariableNames(nodeCopy, bvarNames);
    // Check that no variable names match new bvar names.
    for (std::string &variableName : variableNames) {
        if (std::find(bvarNames.begin(), bvarNames.end(), variableName) != bvarNames.end())
        {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math in component '" + component->getName() +
                                "' contains '" + variableName + "' as a bvar ci element but it is already a variable name.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
    // Iterate through ci/cn elements and remove cellml units attributes.
    XmlNodePtr mathNode = node;
    validateAndCleanMathCiCnNodes(node, component, variableNames, bvarNames);

    /// @cellml2_14 __TODO__ Is there a better way to do this?  Get the MathML string (with cellml:units attributes already removed)
	/// and remove the CellML namespace.  While the removeSubstring() approach for removing the cellml namespace before 
	/// validating with the MathML DTD is not ideal, libxml does not appear to have a better way to remove a namespace 
	/// declaration from the tree.
    std::string cellml2NamespaceString = std::string(" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\"");
    std::string cleanMathml = mathNode->convertToString();
    removeSubstring(cleanMathml, cellml2NamespaceString);

	/// @cellml2_14 14.? Check 'clean/unitless' math string against W3C MathML 
    // Parse/validate the clean math string with the W3C MathML DTD.
    XmlDocPtr mathmlDoc = std::make_shared<XmlDoc>();
    mathmlDoc->parseMathML(cleanMathml);
    // Copy any MathML validation errors into the common validator error handler.
    if (mathmlDoc->xmlErrorCount() > 0) {
        for (size_t i = 0; i < mathmlDoc->xmlErrorCount(); ++i) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription(mathmlDoc->getXmlError(i));
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
    }
}

void Validator::ValidatorImpl::validateAndCleanMathCiCnNodes(XmlNodePtr &node, const ComponentPtr &component, const std::vector<std::string> &variableNames,
                                                             const std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->getFirstChild();
    std::string textNode;
    bool ciType = node->isElement("ci", MATHML_NS);
    bool cnType = node->isElement("cn", MATHML_NS);
    if (ciType || cnType) {
        if (childNode) {
            if (childNode->isText()) {
                textNode = childNode->convertToString();
                if (hasNonWhitespaceCharacters(textNode)) {
					/// @cellml2_14 14.1.3 Check that ci elements reference a variable or bound variable within the same container
                    if (ciType) {
                        // It's fine in MathML to have whitespace around variable names, we will strip it out when looking for
                        // variable names.
                        textNode.erase(textNode.begin(),find_if_not(textNode.begin(),textNode.end(),[](int c){return isspace(c);}));
                        textNode.erase(find_if_not(textNode.rbegin(),textNode.rend(),[](int c){return isspace(c);}).base(), textNode.end());
                        // Check whether we can find this text as a variable name in this component.
                        if ((std::find(variableNames.begin(), variableNames.end(), textNode) == variableNames.end()) &&
                            (std::find(bvarNames.begin(), bvarNames.end(), textNode) == bvarNames.end())) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("MathML ci element has the child text '" + textNode +
                                                "', which does not correspond with any variable names present in component '" + component->getName() +
                                                "' and is not a variable defined within a bvar element.");
                            err->setComponent(component);
                            err->setKind(Error::Kind::MATHML);
                            mValidator->addError(err);
                        }
                    }
                } else {
					/// @cellml2_14 14.? Check that names of children are not whitespace only __TODO__ Checking whether this needs to be explicit in specs
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("MathML " + node->getName() + " element has a whitespace-only child element.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        } else {
			/// @cellml2_14 14.1.3 Check that element has a child, whether or not it is ci or cn
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("MathML " + node->getName() + " element has no child.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        // Get cellml:units attribute.
        XmlAttributePtr attribute = node->getFirstAttribute();
        std::string unitsName;
        XmlAttributePtr unitsAttribute = nullptr;
        while (attribute) {
            if (attribute->getValue().length() > 0) {
				/// @cellml2_14 14.1.4 Check for units in both cn and ci types and compares to CellML namespace  

                if (attribute->isType("units", CELLML_2_0_NS)) {
                    unitsName = attribute->getValue();
                    unitsAttribute = attribute;
                } else {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Math " + node->getName() + " element has an invalid attribute type '" +
                                        attribute->getName() + "' in the cellml namespace.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
            attribute = attribute->getNext();
        }

        bool checkUnitsIsInComponent = false;
        // Check that cellml:units has been set.
		/// @cellml2_14 14.1.3 Check that ci element does not have units __TODO__ Check that this is clear in specification doc
        if (ciType) {
            if (unitsAttribute != nullptr) {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Math ci element with value '" + textNode +
                                    "' has a cellml:units attribute with name '" + unitsAttribute->getValue() + "'.");
            }
        } else if (cnType) {
			/// @cellml2_14 14.1.4 Check that cn elements has a units name
            if (isCellmlIdentifier(unitsName)) {
                checkUnitsIsInComponent = true;
            } else {
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("Math cn element with the value '" + textNode +
                                    "' does not have a valid cellml:units attribute.");
                err->setComponent(component);
                err->setKind(Error::Kind::MATHML);
                mValidator->addError(err);
            }
        }

        // Check that a specified units is valid.
		/// @cellml2_14  14.1.4 Check that the units exist, either locally in the component or the standard list
        if (checkUnitsIsInComponent) {
            // Check for a matching units in this component.
            Model* model = static_cast<Model*>(component->getParent());
            if (!model->hasUnits(unitsName)) {
                // Check for a matching standard units.
                if (!isStandardUnitName(unitsName)) {
                    ErrorPtr err = std::make_shared<Error>();
                    err->setDescription("Math has a " + node->getName() + " element with a cellml:units attribute '" + unitsName +
                                        "' that is not a valid reference to units in component '" +
                                        component->getName() + "' or a standard unit.");
                    err->setComponent(component);
                    err->setKind(Error::Kind::MATHML);
                    mValidator->addError(err);
                }
            }
        }
        // Now that we've validated this XML node's cellml:units attribute, remove it from the node.
        // This is done so we can validate a "clean" MathML string using the MathML DTD. The math
        // string stored on the component will not be affected.
        if (unitsAttribute) {
            unitsAttribute->removeAttribute();
        }
    } else {
        // Check children for ci/cn elements.
        if (childNode) {
            validateAndCleanMathCiCnNodes(childNode, component, variableNames, bvarNames);
        }
    }
    // Check siblings for ci/cn.
    node = node->getNext();
    if (node) {
        validateAndCleanMathCiCnNodes(node, component, variableNames, bvarNames);
    }
}

void Validator::ValidatorImpl::validateMathMLElements(const XmlNodePtr &node, const ComponentPtr &component)
{

	/// @cellml2_14 14.1.2 Check that each child of a math element is supported, recursive over own children
    XmlNodePtr childNode = node->getFirstChild();
    if (childNode) {
        if (!childNode->isText() && !isSupportedMathMLElement(childNode)) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math has a '" + childNode->getName() + "' element" +
                                " that is not a supported MathML element.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        validateMathMLElements(childNode, component);
    }

    XmlNodePtr nextNode = node->getNext();
    if (nextNode) {
        if (!nextNode->isText() && !isSupportedMathMLElement(nextNode)) {
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("Math has a '" + nextNode->getName() + "' element" +
                                " that is not a supported MathML element.");
            err->setComponent(component);
            err->setKind(Error::Kind::MATHML);
            mValidator->addError(err);
        }
        validateMathMLElements(nextNode, component);
    }
}

void Validator::ValidatorImpl::gatherMathBvarVariableNames(XmlNodePtr &node, std::vector<std::string> &bvarNames)
{
    XmlNodePtr childNode = node->getFirstChild();
    if (node->isElement("bvar", MATHML_NS)) {
        if ((childNode) && (childNode->isElement("ci", MATHML_NS))) {
            XmlNodePtr grandchildNode = childNode->getFirstChild();
            if (grandchildNode) {
                if (grandchildNode->isText()) {
                    std::string textNode = grandchildNode->convertToString();
                    if (hasNonWhitespaceCharacters(textNode)) {
                        bvarNames.push_back(textNode);
                    }
                }
            }
        }
    } else {
        // Check children for bvars.
        if (childNode) {
            gatherMathBvarVariableNames(childNode, bvarNames);
        }
    }
    // Check siblings for bvars.
    node = node->getNext();
    if (node) {
        gatherMathBvarVariableNames(node, bvarNames);
    }
}

void Validator::ValidatorImpl::validateConnections(const ModelPtr &model)
{
	/// @cellml2_17 __TODO__ need checks of 17.1.1-4 as not present here?
	std::string hints;
    std::vector<std::string> hintlist;

	// Check the components in this model.
	if (model->componentCount() > 0) {
		for (size_t i = 0; i < model->componentCount(); ++i) {
			ComponentPtr component = model->getComponent(i);

			// Check the variables in this component.
			for (size_t j = 0; j < component->variableCount(); ++j) {
				VariablePtr variable = component->getVariable(j);

				// Check the equivalent variables in this variable.
				if (variable->equivalentVariableCount() > 0) {
					for (size_t k = 0; k < variable->equivalentVariableCount(); ++k) {
						VariablePtr equivalentVariable = variable->getEquivalentVariable(k);

                        /// @cellml2_17 17.1.2 Check that we do not have a variable equivalent to itself
                        if (variable == equivalentVariable) {
                            ErrorPtr err = std::make_shared<Error>();
                            err->setDescription("Variable '" + variable->getName() +
                                                "' has an equivalent variable '" + equivalentVariable->getName() +
                                                "' equal to itself. "
                            );
                            err->setModel(model);
                            err->setKind(Error::Kind::CONNECTION);
                            mValidator->addError(err);
                        }
						// TODO: validate variable interfaces according to 19.10.8
						/// @cellml2_17 __TODO__ Validate variable interfaces according to 19.10.8
						/// @cellml2_19 19.10.6 Validate that equivalent varaible pairs have equivalent units
						if (!unitsAreEquivalent(model, variable, equivalentVariable, hints)) {
							ErrorPtr err = std::make_shared<Error>();
							err->setDescription("Variable '" + variable->getName() +
								"' has units of '" + variable->getUnits() +
								"' and an equivalent variable '" + equivalentVariable->getName() +
								"' with non-matching units of '" + equivalentVariable->getUnits() +
								"'. The mismatch is: " + hints
							);
							err->setModel(model);
							err->setKind(Error::Kind::UNITS);
							mValidator->addError(err);
						}

						/// @cellml2_18 18.1.3 Don't need to check that connections do not duplicate variable pairs (19.10.4)
                        /// as duplicates are not stored (?).

						if (equivalentVariable->hasEquivalentVariable(variable)) {
							// Check that the equivalent variable has a valid parent component.
							Component* component2 = static_cast<Component*>(equivalentVariable->getParent());
							if (!component2->hasVariable(equivalentVariable)) {
								ErrorPtr err = std::make_shared<Error>();
								err->setDescription("Variable '" + equivalentVariable->getName() +
									"' is an equivalent variable to '" + variable->getName() +
									"' but has no parent component.");
								err->setModel(model);
								err->setKind(Error::Kind::CONNECTION);
								mValidator->addError(err);
							}
						}
						else {
							ErrorPtr err = std::make_shared<Error>();
							err->setDescription("Variable '" + variable->getName() +
								"' has an equivalent variable '" + equivalentVariable->getName() +
								"'  which does not reciprocally have '" + variable->getName() +
								"' set as an equivalent variable.");
							err->setModel(model);
							err->setKind(Error::Kind::CONNECTION);
							mValidator->addError(err);
						}
					}
				}
			}
		}
        /// @cellml2_19 19.10.5 Check that the variable equivalence network does not contain cycles
        if (modelVariablesAreCyclic(model, hintlist)) {
            ErrorPtr err = std::make_shared<Error>();
            std::string des;
            for (size_t i = 0; i < hintlist.size(); ++i) {
                des += hintlist[i] + ", ";
                }
            err->setDescription("Cyclic variables exist, "+ std::to_string(hintlist.size())+" loops found (Variable(Component)). "+des);
            err->setModel(model);
            err->setKind(Error::Kind::UNITS);
            mValidator->addError(err);
            }
 
	}
}

bool Validator::ValidatorImpl::modelVariablesAreCyclic(const ModelPtr &model, std::vector<std::string> &hintlist) {

    /*
        Test for cycles in the equivalent variable setup.
    */

    struct edge {
        VariablePtr n1;
        VariablePtr n2;
        };

    std::vector<VariablePtr> nodelist;
    std::vector<edge> edgelist;

    // Making node2edge map
    std::map <VariablePtr, std::vector<int> > node2edge;
    std::map <VariablePtr, std::vector<int> >::iterator it, otherfriend_it;
    bool loop_found = false;

    // Set up the list of nodes: only include nodes which have two or more connections
    if (model->componentCount() > 0) {
        for (size_t i = 0; i < model->componentCount(); ++i) {
            ComponentPtr component = model->getComponent(i);

            // Check for variables in this component.
            for (size_t j = 0; j < component->variableCount(); ++j) {
                VariablePtr variable = component->getVariable(j);

                // Check for equivalent variables in this variable.
                // Because cycles can only be formed with two or more connections, only save
                // those variables which have more than one equiv connection with variables 
                // that in turn have more than one commection
                if (variable->equivalentVariableCount() >= 2) {
                    nodelist.push_back(variable);
                    node2edge.insert(std::pair<VariablePtr, std::vector<int>>(variable, {})); // empty vector instead of NULL

                    // if equivalent variables of this one have another neighbour in the list the include that edge
                    for (size_t k = 0; k < variable->equivalentVariableCount(); k++) {
                        VariablePtr equivalent = variable->getEquivalentVariable(k);
                        if (std::find(nodelist.begin(), nodelist.end(), equivalent) != nodelist.end()) {
                            // Add the edge to the edgelist
                            edgelist.push_back({ variable,equivalent });
                            }
                        }
                    }
                }
            }

        for (size_t e = 0; e < edgelist.size(); e++) {
            node2edge.at(edgelist[e].n1).push_back(int (e));
            node2edge.at(edgelist[e].n2).push_back(int (e));
            }
        // Removing nodes connected to only one viable edge, and then ... 
        // Removing edges connected to only one viable node ... and then ... rinse and repeat
        bool checking = false;
        VariablePtr otherfriend;
        int edge2go;
        do {
            checking = false;
            for (auto onefriend = node2edge.cbegin(); onefriend != node2edge.cend();) {
                
                if (onefriend->second.size() == 1) {
                    // remove edge from count of viable edges around other node
                    edge2go = onefriend->second[0];
                    // locating other node on edge to go
                    if (edgelist[edge2go].n1 == onefriend->first)
                        otherfriend = edgelist[edge2go].n2;
                    else
                        otherfriend = edgelist[edge2go].n1;

                    otherfriend_it = node2edge.find(otherfriend);
                    if (otherfriend_it != node2edge.end()) {
                        // Update node2edge for other nodes attached to this node -> remove edge2go from list
                        otherfriend_it->second.erase(
                            std::remove(
                                otherfriend_it->second.begin(),
                                otherfriend_it->second.end(), 
                                edge2go), 
                            otherfriend_it->second.end()
                        );
                    }
                    
                    // Removing the edge, cannot delete here as will screw up the indicies of the list
                    edgelist[edge2go].n1 = edgelist[edge2go].n2 = NULL;
                    checking = true;
                    // Removing this node too
                    onefriend = node2edge.erase(onefriend);
                }
                else {
                    ++onefriend;
                    }
                }
            } while (checking);
            
            // Any edges which remain in the node2edge array will be part of a loop.
            std::vector<int> done_edges;
            
            while (node2edge.size()) {
                std::vector<VariablePtr> done_nodes;
                VariablePtr myNode = node2edge.begin()->first;
                auto n2e_it = node2edge.begin();
                bool closed = false;
              
                do {
                    if (n2e_it->second.size() == 0) // then we have run out of edges attached to this node, not a loop
                        break;
                    edge2go = n2e_it->second.back();   

                    // Getting nextNode at the other end of this edge
                    otherfriend = myNode == edgelist[edge2go].n1 ? edgelist[edge2go].n2 : edgelist[edge2go].n1;
                    // Removing myEdge from the node2edge list for myNode
                    n2e_it->second.pop_back();

                    // Update node2edge for other nodes attached to this node -> remove edge2go from list
                    otherfriend_it = node2edge.find(otherfriend);
                    if (otherfriend_it != node2edge.end()) {
                        otherfriend_it->second.erase(
                            std::remove(
                                otherfriend_it->second.begin(),
                                otherfriend_it->second.end(),
                                edge2go),
                            otherfriend_it->second.end()
                        );
                    }

                    // Get next edge
                    n2e_it = node2edge.find(otherfriend);

                    // Adding myNode to the list
                    if (std::find(done_nodes.begin(), done_nodes.end(), otherfriend) != done_nodes.end()) {
                        closed = true;
                        done_nodes.push_back(myNode);
                        done_nodes.push_back(otherfriend);
                        loop_found = true;
                        }
                    else {
                        done_nodes.push_back(myNode);
                        myNode = otherfriend;
                        }
                    } while (!closed);
               
                    std::string des = "";
                    for (size_t i = 0; i < done_nodes.size(); ++i) {
                        des += "'";
                        Component* parent = static_cast<Component*>(done_nodes[i]->getParent());
                        des += done_nodes[i]->getName()+" ("+parent->getName()+")'";
                        if (i != done_nodes.size()-1) des += " <-> ";   
                        }
                    hintlist.push_back("Loop: " + des);

                    // If the node2edge list is empty remove the entry
                    for (auto n2e_it = node2edge.cbegin(); n2e_it != node2edge.cend();) {
                        if (n2e_it->second.size() < 2) // Removing entries with one edge as well, catches overlapping loops 
                            n2e_it = node2edge.erase(n2e_it);    
                        else ++n2e_it; 
                    }
                };
        }
    return loop_found;
}


bool Validator::ValidatorImpl::unitsAreEquivalent(const ModelPtr &model, 
	const VariablePtr &v1, const VariablePtr &v2, std::string &hints)
{
	bool status;
	libcellml::UnitsPtr u1 = std::make_shared<libcellml::Units>();
	libcellml::UnitsPtr u2 = std::make_shared<libcellml::Units>();
	libcellml::UnitsPtr mu = std::make_shared<libcellml::Units>();
	
	// Reduce both sets of units to most basic form and compare them.  NB: Multipliers are not considered
	std::map<std::string, double> unitmap;

	// TODO Can we get the enum list of base units from StandardUnits here instead of hardcoding?
	std::vector<std::string> base = { "second","ampere","metre","kilogram","mole","candela","dimensionless","kelvin" };
	std::map< std::string, std::map<std::string,double> > standardList;

	standardList["ampere"]["ampere"] = 1.0;
	standardList["candela"]["candela"] = 1.0;
	standardList["dimensionless"]["dimensionless"] = 1.0;
	standardList["kelvin"]["kelvin"] = 1.0;
	standardList["kilogram"]["kilogram"] = 1.0;
	standardList["metre"]["metre"] = 1.0;
	standardList["mole"]["mole"] = 1.0;
	standardList["second"]["second"] = 1.0;
	
	standardList["becquerel"]["second"] = -1.0;
	standardList["coulomb"]["second"] = 1.0;
	standardList["coulomb"]["ampere"] = -1.0;
	standardList["farad"]["metre"] = -2.0;
	standardList["farad"]["kilogram"] = -1.0;
	standardList["farad"]["second"] = -4.0;
	standardList["farad"]["ampere"] = 2.0;
	standardList["gram"]["kilogram"] = 1.0;
	standardList["gray"]["metre"] = 2.0;
	standardList["gray"]["second"] = -2.0;
	standardList["henry"]["metre"] = 2.0;
	standardList["henry"]["kilogram"] = 1.0;
	standardList["henry"]["second"] = -2.0;
	standardList["henry"]["ampere"] = -2.0;
	standardList["hertz"]["second"] = -1.0;
	standardList["joule"]["metre"] = 2.0;
	standardList["joule"]["kilogram"] = 1.0;
	standardList["joule"]["second"] = -2.0;
	standardList["katal"]["mole"] = 1.0;
	standardList["katal"]["second"] = -1.0;
	standardList["liter"]["metre"] = 3.0;
	standardList["litre"]["metre"] = 3.0;
	standardList["lumen"]["candela"] = 1.0;
	standardList["lux"]["metre"] = -2.0;
	standardList["lux"]["candela"] = 1.0;
	standardList["meter"]["metre"] = 1.0;
	standardList["newton"]["metre"] = 1.0;
	standardList["newton"]["kilogram"] = 1.0;
	standardList["newton"]["second"] = -2.0;
	standardList["ohm"]["metre"] = 2.0;
	standardList["ohm"]["kilogram"] = 1.0;
	standardList["ohm"]["second"] = -3.0;
	standardList["ohm"]["ampere"] = -2.0;
	standardList["pascal"]["metre"] = -1.0;
	standardList["pascal"]["kilogram"] = 1.0;
	standardList["pascal"]["second"] = -2.0;
	// Special case for radians: set units as dimensionless for testing as m/m=1
	standardList["radian"]["dimensionless"] = 1.0;
	standardList["siemens"]["metre"] = -2.0;
	standardList["siemens"]["kilogram"] = -1.0;
	standardList["siemens"]["second"] = 3.0;
	standardList["siemens"]["ampere"] = 2.0;
	standardList["sievert"]["metre"] = 2.0;
	standardList["sievert"]["second"] = -2.0;
	// Special case for steradians: set units to dimensionless as m2/m2 = 1
	standardList["steradian"]["dimensionless"] = 1.0;
	standardList["tesla"]["kilogram"] = 1.0;
	standardList["tesla"]["second"] = -2.0;
	standardList["tesla"]["ampere"] = -1.0;
	standardList["volt"]["metre"] = 2.0;
	standardList["volt"]["kilogram"] = 1.0;
	standardList["volt"]["second"] = -3.0;
	standardList["volt"]["ampere"] = -1.0;
	standardList["watt"]["metre"] = 2.0;
	standardList["watt"]["kilogram"] = 1.0;
	standardList["watt"]["second"] = -3.0;
	standardList["weber"]["metre"] = 2.0;
	standardList["weber"]["kilogram"] = 1.0;
	standardList["weber"]["second"] = -2.0;
	standardList["weber"]["ampere"] = -1.0;

	for (std::vector<std::string>::iterator pos = base.begin(); pos != base.end(); ++pos) {
		unitmap[*pos] = 0.0;
	}

	std::string myRef, myPre, myId;
	std::map<std::string, double> myBase;
	hints = "";
	
	if (!(v1->getUnits() == "dimensionless")) {
		if (model->hasUnits(v1->getUnits())) {
			u1 = model->getUnits(v1->getUnits());

			incrementBaseUnitCount(model, unitmap, u1->getName(), standardList, 1);
		}
		else {
			return false;
		}
	}
	// Remove same units from second unit to compare
	if (!(v2->getUnits() == "dimensionless")) {
		if (model->hasUnits(v2->getUnits())) {
			u2 = model->getUnits(v2->getUnits());
			decrementBaseUnitCount(model, unitmap, u2->getName(), standardList, 1);
		}
		else {
			return false;
		}
	}
	// Remove "dimensionless" from testing
	unitmap.erase("dimensionless");
	// Check for non-zero entries in the map
	status = true;
	for (const auto &basepair : unitmap) {
		if (basepair.second != 0.0) {
			// Return trigger for error
			hints += basepair.first + "^" + std::to_string(basepair.second) + ", ";
			status = false;
		}
	}
	return status;
}

void Validator::ValidatorImpl::incrementBaseUnitCount(const ModelPtr &model, 
	std::map<std::string,double> &unitmap, const std::string uName, 
	const std::map< std::string, std::map<std::string, double>> &standardList,
	const double uExp) { 
	std::string myRef, myPre, myId;
	double myExp, myMult;
	std::map<std::string, double> myBase;
	libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

	if (model->hasUnits(uName))
		u = model->getUnits(uName);
	else
		return;
		
	if (!u->isBaseUnit()) {
		for (size_t i = 0; i < u->unitCount(); ++i) {
			u->getUnitAttributes(i, myRef, myPre, myExp, myMult, myId);

			if (!isStandardUnitName(myRef))
				incrementBaseUnitCount(model, unitmap, myRef, standardList,uExp*myExp);
			else {
				myBase = standardList.at(myRef);
				for (const auto &iter : myBase) {
					unitmap.at(iter.first) += iter.second*myExp*uExp;
				}
			}
		}
	}
	else {
		unitmap.at(u->getName()) += 1.0;
	}
}

void Validator::ValidatorImpl::decrementBaseUnitCount(const ModelPtr &model, 
	std::map<std::string,double> &unitmap, const std::string uName, 
	const std::map< std::string, std::map<std::string, double>> &standardList, const double uExp) {

	std::string myRef, myPre, myId;
	double myExp, myMult;
	std::map<std::string, double> myBase;
	libcellml::UnitsPtr u = std::make_shared<libcellml::Units>();

	if (model->hasUnits(uName))
		u = model->getUnits(uName);
	else
		return;

	if (!u->isBaseUnit()) {
		for (size_t i = 0; i < u->unitCount(); ++i) {
			u->getUnitAttributes(i, myRef, myPre, myExp, myMult, myId);

			if (!isStandardUnitName(myRef))
				decrementBaseUnitCount(model, unitmap, myRef, standardList, myExp*uExp);
			else {
				myBase = standardList.at(myRef);
				for (const auto &iter : myBase) {
					unitmap.at(iter.first) -= iter.second*myExp*uExp;
				}
			}
		}
	}
	else {
		unitmap.at(u->getName()) -= 1.0;
	}

}

void Validator::ValidatorImpl::removeSubstring(std::string &input, std::string &pattern) {
  std::string::size_type n = pattern.length();
  for (std::string::size_type i = input.find(pattern);
      i != std::string::npos;
      i = input.find(pattern))
      input.erase(i, n);
}

bool Validator::ValidatorImpl::isSupportedMathMLElement(const XmlNodePtr &node)
{
	/// @cellml2_14 14.1.2 Lists the hard-coded supported MathML elements tags

    const std::vector<std::string> supportedMathMLElements =
    {
        "ci", "cn", "sep", "apply", "piecewise", "piece", "otherwise", "eq", "neq", "gt", "lt", "geq", "leq", "and", "or",
        "xor", "not", "plus", "minus", "times", "divide", "power", "root", "abs", "exp", "ln", "log", "floor",
        "ceiling", "min", "max", "rem", "diff", "bvar", "logbase", "degree", "sin", "cos", "tan", "sec", "csc",
        "cot", "sinh", "cosh", "tanh", "sech", "csch", "coth", "arcsin", "arccos", "arctan", "arcsec", "arccsc",
        "arccot", "arcsinh", "arccosh", "arctanh", "arcsech", "arccsch", "arccoth", "pi", "exponentiale",
        "notanumber", "infinity", "true", "false"
    };
    return    !node->getNamespace().compare(MATHML_NS)
           && std::find(supportedMathMLElements.begin(), supportedMathMLElements.end(), node->getName()) != supportedMathMLElements.end();
}

bool Validator::ValidatorImpl::isStandardUnitName(const std::string &name)
{
    bool result = false;
    std::vector<std::string> standardUnitNames =
    {
        "ampere", "becquerel", "candela", "celsius", "coulomb", "dimensionless", "farad", "gram", "gray",
        "henry", "hertz", "joule", "katal", "kelvin", "kilogram", "liter", "litre", "lumen", "lux",
        "meter", "metre", "mole", "newton", "ohm", "pascal", "radian", "second", "siemens", "sievert",
        "steradian", "tesla", "volt", "watt", "weber"
    };
    if (std::find(standardUnitNames.begin(), standardUnitNames.end(), name) != standardUnitNames.end()) {
        result = true;
    }
    return result;
}

bool Validator::ValidatorImpl::isStandardPrefixName(const std::string &name)
{
    bool result = false;
    std::vector<std::string> prefixNames =
    {
        "atto", "centi", "deca", "deci", "exa", "femto", "giga", "hecto", "kilo", "mega", "micro", "milli",
        "nano", "peta", "pico", "tera", "yocto", "yotta", "zepto", "zetta"
    };
    if (std::find(prefixNames.begin(), prefixNames.end(), name) != prefixNames.end()) {
        result = true;
    }
    return result;
}

bool Validator::ValidatorImpl::isCellmlIdentifier(const std::string &name)
{
    bool result = true;
    /// @cellml2_3 3.1.3 Check that length of a name is greater than 0
    if (name.length() > 0) {
        /// @cellml2_3 3.1.4 Check that name does not start with a numeric character.
        if (isdigit(name[0])) {
            result = false;
            ErrorPtr err = std::make_shared<Error>();
            err->setDescription("CellML identifiers must not begin with a European numeric character [0-9].");
            err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM);
            mValidator->addError(err);
        } else {
            /// @cellml2_3 3.1.2 Check that name consists of Basic Latin alphanumeric characters and underscores only.
            if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos) {
                result = false;
                ErrorPtr err = std::make_shared<Error>();
                err->setDescription("CellML identifiers must not contain any characters other than [a-zA-Z0-9_].");
                err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_LATIN_ALPHANUM);
                mValidator->addError(err);
            }
        }
    } else {
        result = false;
        ErrorPtr err = std::make_shared<Error>();
        err->setDescription("CellML identifiers must contain one or more basic Latin alphabetic characters.");
        err->setRule(SpecificationRule::DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM);
        mValidator->addError(err);
    }
    return result;
}

bool Validator::ValidatorImpl::isValidHTML(const std::string &html) {

    /// @cellml2_5 5.1.1 Check string is a valid html attribute according to XLink specs, but using libxml2 
    if (xmlParseURI(html.c_str()) == NULL) {
        return false;
    }
    return true;
}

}
