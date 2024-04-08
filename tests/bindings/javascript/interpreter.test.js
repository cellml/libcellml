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

describe("Interpreter tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })
    test('Checking Interpreter model manipulation.', () => {
        const i = new libcellml.Interpreter()
        const p = new libcellml.Parser(true)

        m = p.parseModel(basicModel)
        a = new libcellml.Analyser()

        a.analyseModel(m)

        expect(i.model()).toBe(null)

        i.setModel(a.model())

        expect(i.model()).toBeDefined()

        i.initialiseVariables()
        i.computeComputedConstants()
        i.computeRates()
        i.computeVariables()
    })
})