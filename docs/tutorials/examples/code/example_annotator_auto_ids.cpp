#include <libcellml>

void main()
{
    // Parse a model from the example library.



    // Create an Annotator instance.
    auto annotator = libcellml::Annotator::create();

    // ---------- OPTION 1: Automatic ids for everything -------------------------
    //
    // Submit the model to the Annotator, and instruct it to create and assign a
    // set of unique ids to any annotatable item in the model.
    // Note that this function replaces any previously stored model within the
    // Annotator, and rebuilds the internal index with respect to this model.
    // There is no need to either build the index first (as all the ids will
    // be altered anyway) or afterwards (as it's built during the assignment
    // process).
    annotator->assignAllIds(model);

    // ---------- OPTION 2: Automatic ids by type -----------------------
    //
    // First submit the model to the Annotator and build its index.
    annotator->buildModelIndex(model);

    // Next, specify the type of item to assign automatic ids to using the
    // Type enumeration options.  This will assign every Variable in the model
    // a unique id string.
    annotator->assignIds(libcellml::Annotator::Type::VARIABLE);

    // ---------- OPTION 3: Automatic id by item -------------------------
    // Finally, you can submit single items for automatic id.
    // There are two ways to do this as shown below.  Note that when you use the
    // built-in Annotator functions to assign ids, there is no need to rebuild the
    // annotator's index.
    //
    // The two options below are identical.
    //
    // EITHER Submit an AnyItem struct (a pair of Type enum, and the item) ...
    AnyItem myComponentRef = std::make_pair(libcellml::Annotator::Type::COMPONENT_REF, model->component(0));
    annotator->assignId(myComponentRef);

    // ... OR submit both the Type enum and the item as separate arguments.
    annotator->assignId(libcellml::Annotator::Type::COMPONENT_REF, model->component(0));
}