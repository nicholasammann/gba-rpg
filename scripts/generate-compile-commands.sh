#!/bin/bash

# pipx is needed to install compiledb (python package) on your system
if command -v pipx &> /dev/null; then
    echo "pipx is installed."
else
    echo "Error: pipx is NOT installed, please install"
    return 1
fi

if pipx list | grep -q "compiledb"; then
    echo "compiledb is installed via pipx."
else
    echo "Error: compiledb is missing, please install with 'pipx install compiledb'"
    return 1
fi

# need to install compiledb python package
compiledb make -j16
