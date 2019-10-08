#!/usr/bin/env bash

function print_header() {
    echo -e "\n***** ${1} *****"
}

#print_header "RUN cppcheck"

./linters/cppcheck/cppcheck project --language=c --enable=all --error-exitcode=1 -I project/include --suppress=missingIncludeSystem

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=c project/include/* project/src/*

print_header "SUCCESS"
