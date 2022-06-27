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
const { modelString } = require('./resources')

let libcellml = null

describe("Generator tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })
    test('Checking Generator profile manipulation.', () => {
        const g = new libcellml.Generator()
        const gP = new libcellml.GeneratorProfile(libcellml.Profile.C)

        expect(g.profile().commentString()).toBe("/* [CODE] */\n")

        gP.setProfile(libcellml.Profile.PYTHON)
        g.setProfile(gP)

        expect(g.profile().commentString()).toBe("# [CODE]\n")
    })
    test('Checking Generator model manipulation.', () => {
        const g = new libcellml.Generator()
        const p = new libcellml.Parser()

        m = p.parseModel(modelString)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        expect(g.model()).toBe(null)

        g.setModel(a.model())

        expect(g.model()).toBeDefined()
        expect(g.model().stateCount()).toBe(1)
    })
        test('Checking Generator code generation.', () => {
        const g = new libcellml.Generator()
        const p = new libcellml.Parser()

        m = p.parseModel(modelString)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        g.setModel(a.model())

        expect(g.interfaceCode().length).toBeGreaterThan(900)
        expect(g.implementationCode().length).toBeGreaterThan(1000)
    })
})
