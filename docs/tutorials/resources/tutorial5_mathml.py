# MathML strings for defining the behaviour of the nGate component
equation1 = \
    '<apply>\
        <eq/>\
        <ci>alpha_n</ci>\
        <apply>\
            <divide/>\
            <apply>\
                <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="per_millivolt_millisecond">0.01</cn>\
                <apply>\
                    <plus/>\
                    <ci>V</ci>\
                    <cn cellml:units="millivolt">10</cn>\
                </apply>\
            </apply>\
            <apply>\
                <minus/>\
                <apply>\
                    <exp/>\
                    <apply>\
                        <divide/>\
                        <apply>\
                            <plus/>\
                            <ci>V</ci>\
                            <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="millivolt">10</cn>\
                        </apply>\
                        <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="millivolt">10</cn>\
                    </apply>\
                </apply>\
                <cn cellml:units="dimensionless">1</cn>\
            </apply>\
        </apply>\
    </apply>'

equation2 = \
    '<apply>\
        <eq/>\
        <ci>beta_n</ci>\
        <apply>\
            <times/>\
            <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="per_millisecond">0.125</cn>\
            <apply>\
                <exp/>\
                <apply>\
                    <divide/>\
                    <ci>V</ci>\
                    <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="millivolt">80</cn>\
                </apply>\
            </apply>\
        </apply>\
    </apply>'

equation3 = \
    '<apply>\
        <eq/>\
        <apply>\
            <diff/>\
            <bvar>\
                <ci>t</ci>\
            </bvar>\
            <ci>n</ci>\
        </apply>\
        <apply>\
            <minus/>\
            <apply>\
                <times/>\
                <ci>alpha_n</ci>\
                <apply>\
                    <minus/>\
                    <cn xmlns:cellml="http://www.cellml.org/cellml/2.0#" cellml:units="dimensionless">1</cn>\
                    <ci>n</ci>\
                </apply>\
            </apply>\
            <apply>\
                <times/>\
                <ci>beta_n</ci>\
                <ci>n</ci>\
            </apply>\
        </apply>\
    </apply>'

# Voltage clamp maths for controlling the environment component
voltage_clamp_maths = \
        '<apply>\
            <eq/>\
            <ci>V</ci>\
            <piecewise>\
                <piece>\
                    <cn cellml:units="millivolt">0</cn>\
                    <apply><lt/><ci>t</ci><cn cellml:units="millisecond">5</cn></apply>\
                </piece>\
                    <piece>\
                    <cn cellml:units="millivolt">0</cn>\
                    <apply><gt/><ci>t</ci><cn cellml:units="millisecond">15</cn></apply>\
                </piece>\
                <otherwise>\
                    <cn cellml:units="millivolt">-85</cn>\
                </otherwise>\
            </piecewise>\
        </apply>'



