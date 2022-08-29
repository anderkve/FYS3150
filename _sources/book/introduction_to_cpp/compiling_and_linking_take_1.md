# Compiling and linking, take 1

Say we have saved our [](sec:hello_world) program to a file `main.cpp`. Before we can run it, we need to **build** it --- that is, convert our human-readable C++ code into executable machine code. The build process consists of two steps:

1. **Compilation**: Translating each **source file** (`.cpp` file) into a corresponding **object file** (`.o` file) with machine code.
2. **Linking**: Combine multiple object files into a single **executable**, i.e. a program we can run.

```{note}
Informally, the entire process of compiling + linking is often referred to simply as **"compiling the code"**. But we should not forget that the technical term "compilation" actually only refers to the first step. To avoid confusion, it is often useful to  say **"building the code"** when referring to the entire process, as we do here.
```

We will use the common C++ compiler `g++` for building our code.

**Compilation**: To compile `main.cpp`, we run the following terminal command:
```sh
g++ -c main.cpp
```
Here the option `-c` means "just compile, don't link". This produces an object file `main.o`. 

**Linking**: To do the linking step, we pass this object file (`main.o`) as input to `g++`:
```sh
g++ main.o -o main.exe
```
Here the option `-o main.exe` just means that we give the resulting program the name `main.exe`. (We could have picked any file name, and we didn't have to use the `.exe` suffix.) 

To run our fantastic program, we do 
```sh
./main.exe
```
which should produce the familiar output
```sh
Hello, World!
```

Hooray, we have compiled, linked and run our first C++ program!

```{note}
In this simple example it may not seem like we're doing much "linking" at all --- there's only one object file, right? Well, not really: Under the hood, our object file `main.o` is linked to object files from the standard C++ library.
```


## Compiling and linking in one go

We can do compilation + linking with a single command:
```sh
g++ main.cpp -o main.exe
```
The compiler will then (1) compile `main.cpp` into `main.o`, (2) link `main.o` to create `main.exe`, and (3) delete `main.o`. Such shorthand commands are often useful. But it will pay off in the long run to remember that there really are two different things going on here. To quote [this nice article](https://www.cprogramming.com/compilingandlinking.html) by Alex Allain:

> Knowing the difference between the compilation phase and the link phase can make it easier to hunt for bugs. Compiler errors are usually syntactic in nature --- a missing semicolon, an extra parenthesis. Linking errors usually have to do with missing or multiple definitions. If you get an error that a function or variable is defined multiple times from the linker, that's a good indication that the error is that two of your source code files have the same function or variable. 

We will see this more clearly when we start creating larger projects with many files.

But now, let's get back to writing code. Next topic: variables.
