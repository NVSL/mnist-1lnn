# mnist-1lnn
A simple 1-layer neural network to recognize handwritten single digit numbers from the MNIST image files.

## Plan for CSE141 Coding Project  

1.  Make sure code builds
2.  Add some command line options to switch between mnist and emnist.
3.  Make sure you parse the whole emnist database.
4.  Remove/simplify the ASCII-art output.  Stats are good.  Frequent updates and "images" are bad
5.  Remove IO from core training loop.  The core loop should be just compute.
6.  Make it use floats instead of bytes.  US the gray scale information in the images. 2

### Compile and run source code

The repository comes with a pre-configured `makefile`. You can compile the source simply by typing

```
$ make
```

in the project directory. The binary will be created inside the `/bin` folder and can be executed via

```
$ ./bin/mnist-1lnn
```

### Documentation

The  `/doc` folder contains a doxygen configuration file. 
When you run it with doxygen it will create updated [HTML documentation](https://rawgit.com/mmlind/mnist-1lnn/master/doc/html/index.html) in the `/doc/html` folder.

### Screenshots

The `/screenshots` folder contains screenshots of running the program on my 2010 MacBook Pro.


### MNIST Database

The `/data` folder contains the original MNIST database files.

