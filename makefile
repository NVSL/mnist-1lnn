INPUTS=gzip/emnist-byclass-train-images-idx3-ubyte #gzip/emnist-byclass-train-labels-idx1-ubyte gzip/emnist-byclass-test-images-idx3-ubyte gzip/emnist-byclass-test-labels-idx1-ubyte

all: main $(INPUTS)

main: 
	gcc -o bin/mnist-1lnn -Iutil main.c 1lnn.c util/screen.c util/mnist-utils.c util/mnist-stats.c


gzip.zip:
	wget http://www.itl.nist.gov/iaui/vip/cs_links/EMNIST/gzip.zip -O $@

$(INPUTS): gzip.zip
	unzip -o $<
	gunzip -f gzip/*.gz
