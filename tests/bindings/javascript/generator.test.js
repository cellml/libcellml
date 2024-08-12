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

const loadLibCellML = require('libcellml.js/libcellml.common')
const { basicModel } = require('./resources')

let libcellml = null

describe("Generator tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })
    test('Checking Generator profile manipulation.', () => {
        const g = new libcellml.Generator()
        const gP = new libcellml.GeneratorProfile(libcellml.GeneratorProfile.Profile.C)

        expect(g.profile().commentString()).toBe("/* [CODE] */\n")

        gP.setProfile(libcellml.GeneratorProfile.Profile.PYTHON)
        g.setProfile(gP)

        expect(g.profile().commentString()).toBe("# [CODE]\n")
    })
    test('Checking Generator model manipulation.', () => {
        const g = new libcellml.Generator()
        const p = new libcellml.Parser(true)

        m = p.parseModel(basicModel)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        expect(g.model()).toBeNull()

        g.setModel(a.model())

        expect(g.model()).toBeDefined()
        expect(g.model().stateCount()).toBe(1)
    })
    test('Checking Generator code generation.', () => {
        const g = new libcellml.Generator()
        const p = new libcellml.Parser(true)

        m = p.parseModel(basicModel)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        g.setModel(a.model())

        const interface_lines = g.interfaceCode().split('\n')
        expect(interface_lines.length).toBe(44)

        const implementation_lines = g.implementationCode().split('\n')
        expect(implementation_lines.length).toBe(66)

        const equation_line_1 = libcellml.Generator.equationCode(a.model().equation(0).ast())
        expect(equation_line_1.length).toBe(14)

        const gp = new libcellml.GeneratorProfile(libcellml.GeneratorProfile.Profile.PYTHON)
        const equation_line_2 = libcellml.Generator.equationCodeByProfile(a.model().equation(0).ast(), gp)
        expect(equation_line_2.length).toBe(14)
    })
})
