
import os

TESTS_RESOURCE_LOCATION = "${TESTS_RESOURCE_LOCATION}"

def file_contents(file_name):

    with open(os.path.join(TESTS_RESOURCE_LOCATION, file_name)) as f:
        content = f.read()

    return content
