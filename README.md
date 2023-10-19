# Fixed-Point


## Getting Started
This repository contains a setup for a VS Code devcontainer. The devcontainer and VSCode are the recommended setup. If you have access to GitHub Workspaces, you may start the project in your own GitHub fork.

1.) Install [Docker](https://docs.docker.com/get-docker/) on your System.

2.) Install the official [VS Code](https://code.visualstudio.com/) version from Microsoft. The devcontainer will not work with an OSS derivate of VS Code!!!

3.) Install the [Remote Development](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack) extension for VS Code.

4.) Press "F1" and run "Remote-Containers: Open folder in container" and select this repository.

5.) All build commands can now be accessed by pressing "ctrl+shift+b". Run config on your very first start. Then run build, to build the project and your changes later on.

6.) The tests menu can be opened by clicking on the flask symbol on the side Bar. Run the tests by clicking on the play button or debug a test by clicking on the play button with the bug on it.

### I don't want to use VS Code!!!

We also provide a script for running the build commands. For dependencies please see the Docker file in .devcontainer. Please see the help instructions from helper.sh.
```
Please provide one of the following arguments:
  clean               Deletes the build folder
  config              Creates build folder and configures build System
  c | compile | build Compiles the Project
  t | test            Execute Unit tests, only test that Fail are printed.
```

## The Exercise
Check out the FixedPoint.cpp file in the FixedPoint folder. There you will see the function bodies for the operators +, - and *. The exercise is to implement all three functions. A good example is to look at the already implemented / function as reference. Once all Unit Tests pass, the exercise is considered solved.

Please upload your FixedPoint.cpp on moodle!

## The Fixed Point implementation
The implementation of our fixed point is very straight forward. It uses a datatype T, which can be either int8_t, int16_t, int32_t or int64_t, to encode its Value. Please be aware, that the Value is encoded as a signed Value in two's complement. The second type is the FracBits, which is the number of how many bits are used for encoding the digits after the fixed point. A fixed point with T=int8_t and FracBit=3 would be represented like this:
 ```
 0b 00011.010
 ```
 And constructed like one of those:
 ```
 Fixp<int8_t, 3> A(0b00011010);
 Fixp<int8_t, 3> A(26);
 Fixp<int8_t, 3> A(0x1A);
 ```

### The tests
To pass the exercise all Tests have to be passed by your implementation.

### Help with C++

In this exercise a basic knowledge of C++ tempaltes and operator overloading is assumed.
Please refere to the following links to refreshen or get your knowledge:
[Operator overloading](https://en.cppreference.com/w/cpp/language/operators)
[Templates](https://en.cppreference.com/w/cpp/language/templates)
These links are a recommendation and not exhaustive to the topics, please feel free to use other sources.
