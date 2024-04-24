#!/usr/bin/env bash

find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -not -path './build/*' -exec clang-format -style=file -i --verbose {} \;
