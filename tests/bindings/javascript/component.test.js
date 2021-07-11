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


const libCellMLModule = require('libcellml.js/libcellml.common')
let libcellml = null

describe("Component tests", () => {
    beforeAll(async () => {
        libcellml = await libCellMLModule()
    })
    test('Checking Component set source component.', () => {
        const c = new libcellml.Component()
        const iS = new libcellml.ImportSource()

        expect(c.requiresImports()).toBe(false)

        c.setSourceComponent(iS, "imported_component_name")
        expect(c.requiresImports()).toBe(true)
    })
    test('Checking Component component count.', () => {
        const c = new libcellml.Component()
        const c1 = new libcellml.Component()

        expect(c.componentCount()).toBe(0)

        c.addComponent(c1)
        expect(c.componentCount()).toBe(1)
    })
    test('Checking Component math.', () => {
        const c = new libcellml.Component()

        expect(c.math()).toBe("")

        c.setMath("some_math")
        expect(c.math()).toBe("some_math")

        c.appendMath("_and_more_math")
        expect(c.math()).toBe("some_math_and_more_math")

        c.removeMath()
        expect(c.math()).toBe("")
    })
    test('Checking Component clone.', () => {
        const c = new libcellml.Component("mine")
        let iS = new libcellml.ImportSource()
        iS.setUrl("someplace")

        c.setMath("some_math")
        c.setImportSource(iS)

        const cClone = c.clone()
        expect(cClone.name()).toBe("mine")
        expect(cClone.math()).toBe("some_math")
        expect(cClone.importSource().url()).toBe("someplace")
    })
    test('Checking Component encapsulation id.', () => {
        const c = new libcellml.Component()

        expect(c.encapsulationId()).toBe("")

        c.setEncapsulationId("bob")
        expect(c.encapsulationId()).toBe("bob")

        c.removeEncapsulationId()
        expect(c.encapsulationId()).toBe("")
    })
    test('Checking Component import source.', () => {
        const c = new libcellml.Component()
        let iS = new libcellml.ImportSource()
        iS.setUrl("someplace")

        expect(c.isImport()).toBe(false)

        c.setImportSource(iS)
        expect(c.isImport()).toBe(true)
        expect(c.importSource().url()).toBe("someplace")
    })
    test('Checking Component import reference.', () => {
        const c = new libcellml.Component()

        expect(c.importReference()).toBe("")

        c.setImportReference("over_here")
        expect(c.importReference()).toBe("over_here")
    })
    test('Checking Units is resolved.', () => {
        const c = new libcellml.Component()

        expect(c.isResolved()).toBe(true)

        let iS = new libcellml.ImportSource()
        iS.setUrl("someplace")

        c.setImportSource(iS)
        c.setImportReference("this_thing")
        expect(c.isResolved()).toBe(false)
    })
})
