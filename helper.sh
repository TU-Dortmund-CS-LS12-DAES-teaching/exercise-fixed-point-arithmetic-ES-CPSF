#!/bin/bash

clean () {
  rm -rf build/
  rm compile_commands.json
}

config () {
  rm -rf build ; rm compile_commands.json ; mkdir build ; cd build ; cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. ; mv compile_commands.json ../
}

compile () {
  cd build ; make
}

test () {
  ./build/bin/UnitTest --gtest_brief=1
}

case $1 in
  clean)
    clean
    ;;
  config)
    config
    ;;
  c | compile | build)
    compile
    ;;
  t | test)
    test
    ;;
  *)
    if [ $1 ]; then
      echo "Unknown argument: $1"
    fi
    echo "Please provide one of the following arguments:"
    echo "  clean               Deletes the build folder"
    echo "  config              Creates build folder and configures build System"
    echo "  c | compile | build Compiles the Project"
    echo "  t | test            Execute Unit tests, only test that Fail are printed."
    exit
  ;;
esac
