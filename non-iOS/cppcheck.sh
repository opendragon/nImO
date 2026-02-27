#!/bin/sh

cmake -DCMAKE_EXPORT_COMPILE_COMMAND=ON .
cppcheck --check-level=exhaustive --inconclusive --inline-suppr --enable=all --disable=information --safety --std=c++17 --cppcheck-build-dir=build_cppcheck \
    --checkers-report=checkers_report.txt --suppressions-list=cppcheck-suppress.txt --max-ctu-depth=4 \
    --project=compile_commands.json -i../SQLite -i../ThirdParty | tee check.txt
