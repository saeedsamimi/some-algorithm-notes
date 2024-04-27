#!/usr/bin/env bash

find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -not -path './build/*' -not -path './googletest/*' -exec clang-format -style=file -i --verbose {} \;
