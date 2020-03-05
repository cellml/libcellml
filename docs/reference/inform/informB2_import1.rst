.. _informB2_1:

.. _inform_import1:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    At present (TODO) the location specified by the :code:`href` attribute
    must be a locally available file (not online).  The path may either be
    absolute from the root directory, or relative to the importing model's
    location.

    For example, here's a model based around casting for The Wizard of Oz.
    In the main model (the one doing the importing), the component
    used to play Dorothy is defined by importing a :code:`component`
    named :code:`judy_garland` from the file called
    :code:`role_of_dorothy.cellml` and setting its reference in the main
    file to be the component named :code:`dorothy`.

    Note the file structure - the path to the imported file is specified
    relative to the importing file, in this case :code:`role_of_dorothy.cellml`
    sits inside a folder called :code:`characters`.


    oz_model.cellml

    .. code-block:: xml

      <model name="oz">
        <import xlink:href="characters/role_of_dorothy.cellml">
        	<component name="dorothy" component_ref="judy_garland" />
        </import>
        ...
      </model>

    characters/dorothy.cellml

    .. code-block:: xml

      <model name="candidates_for_dorothy">
        <component name="judy_garland"> ... </component>
        ...
        <import xlink:href="toto.cellml">
        	<component name="judy_garlands_dog" component_ref="a_terrier_called_terry"/>
        </import>
      </model>

    characters/role_of_toto.cellml

    .. code-block:: xml

      <model name="candidates_for_toto">
        <component name="a_terrier_called_terry"> ... </component>
        <component name="scooby_doo"> ... </component>
      </model>

    The component representing Toto could be imported in one of two ways, both
    giving identical model representations. Either directly from the
    :code:`role_of_toto.cellml` file, or indirectly via the
    :code:`role_of_dorothy.cellml` file:

    .. code-block:: xml

      <model name="oz">
        <import xlink:href="characters/role_of_dorothy.cellml">
        	<component name="dorothy" component_ref="judy_garland" />
        </import>

        <!-- Either directly from the "role_of_toto.cellml" file -->
        <import xlink:href="characters/role_of_toto.cellml">
        	<component name="toto" component_ref="a_terrier_called_terry" />
        </import>

        <!-- OR indirectly through the role_of_dorothy.cellml" file -->
        <import xlink:href="characters/role_of_dorothy.cellml">
        	<component name="toto" component_ref="judy_garlands_dog" />
        </import>
      </model>
