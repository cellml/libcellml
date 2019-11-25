math_header = '<math xmlns="http://www.w3.org/1998/Math/MathML" xmlns:cellml="http://www.cellml.org/cellml/2.0#">'
equation1 = \
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
                    <cn cellml:units="dimensionless">1</cn>\
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
equation2 = \
    '<apply>\
        <eq/>\
        <ci>i_K</ci>\
        <apply>\
            <times/>\
            <ci>g_K</ci>\
            <apply>\
                <minus/>\
                <ci>V</ci>\
                <ci>E_K</ci>\
            </apply>\
            <apply>\
                <power/>\
                <ci>n</ci>\
                <ci>gamma</ci>\
            </apply>\
        </apply>\
    </apply>'
math_footer = '</math>'