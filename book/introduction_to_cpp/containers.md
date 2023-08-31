# Containers
<!--
Add page on containers (arrays, vectors, maps, pairs, ...).
-->

**Containers** are types of C++ variables that hold a collection of objects. There are [many container types](https://en.cppreference.com/w/cpp/container) in the standard C++ library, but here we'll just introduce two of the most commonly used ones:

- `std::vector`, which is similar to a `list` in Python; and
- `std::map`, which would be the equivalent of a `dict` in Python.

A key difference with respect to Python is that C++ is stricter about variable types. For instance, in Python you can make a list and add whatever stuff you want to it, e.g. 

```python
l = list()
l.append(10)
l.append(3.14)
l.append("I'm a string!")
```

C++ containers do not work like that. You have to declare beforehand exactly what type your container will hold. So for instance a `std::vector<double>` can only hold doubles, while a `std::vector<std::string>` can only contain strings. Similarly, a `std::map<std::string, int>` will be like a dictionary where the dictionary keys are all strings, and the values are all integers. (Type specifications like `<double>` and `<std::string, int>` are referred to as a **template parameters**.)


## std::vector

Here's an example program that demonstrates typical operations with `std::vector` objects:


```cpp
#include <iostream>
#include <vector>
#include <string>

int main ()
{

  //
  // Example #1
  //

  // Create a vector<double> of length 0
  std::vector<double> v1;   

  // Extend the vector by appending a few values
  v1.push_back(1.1);
  v1.push_back(2.2);
  v1.push_back(3.3);

  // Read a value back using .at(index)
  // and save it to a variable.
  double v1_1 = v1.at(1);

  // We can also read values using [index]
  double v1_2 = v1[2];

  // Get the current size of the vector
  int v1_size = v1.size();

  // Let's print some info
  std::cout << "v1: size: " << v1_size << std::endl;
  std::cout << "v1: elements: " 
            << v1.at(0) << ", " << v1.at(1) << ", " << v1.at(2) 
            << std::endl;
  std::cout << "v1_1: "  << v1_1 << std::endl; 
  std::cout << "v1_2: "  << v1_2 << std::endl; 


  //
  // Example #2
  //

  // Create a vector<int> of length 10
  std::vector<int> v2(10);   

  // Assign some values directly
  v2[0] = 0;  // Could also do v2.at(0) = 0
  v2[1] = 1;  // Could also do v2.at(1) = 1

  // Assign the rest of the elements using a loop.
  // For fun, let's do a Fibonacci sequence.
  for (size_t i = 2; i < v2.size(); i++)
  {
    v2[i] = v2[i-1] + v2[i-2];
  }

  // Let's print the content of v2 on a single line using a loop
  std::cout << "v2:";
  for (size_t i = 0; i < v2.size(); i++)
  {
    std::cout << " " << v2[i];
  }
  std::cout << std::endl;

  // Once again, now with an alternative way of looping 
  // through the values in a vector
  std::cout << "v2: ";
  for (int value: v2)
  {
    std::cout << value << " ";
  }
  std::cout << std::endl;


  //
  // Example #3 -- other ways to initialize vectors
  //

  // Create a vector<double> of length 5, with all 
  // elements intitialised to 1.0
  std::vector<double> v3(5, 1.0);   

  // Create a vector<std::string> of length 3, 
  // with all elements initialised differently
  std::vector<std::string> v4 = {"AAA", "BBB", "CCC"};

  
  // We're done
  return 0;
}
```


It's important to note that, despite it's name, the `std::vector` class should not be thought of as a *mathematical* vector. For instance, if you have two `std::vector<double>` objects `a` and `b`, C++ will *not* understand the code `std::vector<double> c = a + b;` to mean mathematical vector addition. You should simply think of `std::vector` as a container, much like a Python list. 

If you need a type that behaves like a mathematical vector, much like `numpy.array` in Python, a good alternative is to use the `arma::vec` class from [Armadillo](intro_to_armadillo.md).

For more details on `std::vector`, see the [technical documentation](https://en.cppreference.com/w/cpp/container/vector).


## std::map


Here's an example program that demonstrates typical operations with `std::map` objects:


```cpp
#include <iostream>
#include <map>
#include <string>

int main ()
{

  // Create an empty map<std::string, int> 
  // i.e. a map whith string keys and integer values
  std::map<std::string, int> country_codes;

  // Create new (or modify existing) entries in the map
  country_codes["Norway"] = 47;
  country_codes["Bolivia"] = 591;
  country_codes["Egypt"] = 20;
  
  // Read out values
  int code_norway = country_codes.at("Norway");
  std::cout << "code_norway: " << code_norway << std::endl;

  // Note: Beware when using [key] rather than 
  // .at(key) to read out values from a map, 
  // as the [key] operator will *always* create
  // a new entry if the key doesn't exist yet!

  // Example: This will compile and run, even though
  // we never put a value in for Sweden in our map!
  int code_sweden = country_codes["Sweden"];
  std::cout << "code_sweden: " << code_sweden << std::endl;

  // If we instead had used country_codes.at("Sweden") to
  // read out the value, we would have gotten an error message
  // at runtime. That would have helped us notice that we 
  // forgot to add Sweden in our map.

  // We can loop over key-value pairs in a map by 
  // using a corresponding std::pair type. So for this
  // example we need to use a std::pair<std::string, int>, 
  // like this:

  std::cout << std::endl;
  std::cout << "Loop over all key-value pairs: " << std::endl;

  for (std::pair<std::string, int> p: country_codes)
  {
    std::cout << p.first << " : " << p.second << std::endl;
  }

  // We're done
  return 0;
}
```

Detailed documentation for `std::map` can be found [here](https://en.cppreference.com/w/cpp/container/map).


## Containers of containers

Keep in mind that you can put containers inside other containers, which can sometimes be useful. Here's a silly example, where we construct a map of type string &rarr; vector-of-strings:

```cpp
std::map<std::string, std::vector<std::string>> countries_europe;

countries_europe["C"] = {"Croatia", "Cyprus", "Czechia"};
countries_europe["D"] = {"Denmark"};
```

