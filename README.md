# mnist-1lnn

A simple 1-layer neural network to recognize handwritten single digit numbers from the MNIST image files.

### Compile and run source code

The repository comes with a pre-configured `makefile`. You can compile the source simply by typing

```
$ make
```

in the project directory. The binary will be created inside the `/bin` folder and can be executed via

```
$ ./bin/mnist-1lnn
```

### MNIST Database

The `/data` folder contains the original MNIST database files.

`gzip.gzip` contains the larger inputs we use.  `make` will unpack them.

