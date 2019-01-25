#!/bin/bash

# Generate and upload code coverage to codecov.io

if [[ "${CODE_COVERAGE}" == "ON" ]]; then
    lcov --capture --directory . --output-file coverage.info
    lcov --remove coverage.info '/usr/*' --output-file coverage.info # filter system-files
    lcov --list coverage.info
    # Uploading to CodeCov
    bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
fi