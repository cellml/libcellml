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

const modelString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \
<model name=\"model\" xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\"> \
    <units name=\"per_second\"> \
        <unit exponent=\"-1\" units=\"second\"/> \
    </units> \
    <component name=\"component\"> \
        <variable name=\"time\" units=\"second\"/> \
        <variable name=\"x\" units=\"dimensionless\" initial_value=\"0\"/> \
        <math xmlns=\"http://www.w3.org/1998/Math/MathML\"> \
            <apply> \
                <eq/> \
                <apply> \
                    <diff/> \
                    <bvar> \
                        <ci>time</ci> \
                    </bvar> \
                    <ci>x</ci> \
                </apply> \
                <cn cellml:units=\"per_second\">1</cn> \
            </apply> \
        </math> \
    </component> \
</model> \
"

module.exports = {
    modelString
}
