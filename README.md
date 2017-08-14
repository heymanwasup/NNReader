
# NNReader (RootCore)

This package is based on `https://github.com/lwtnn/lwtnn` 

This framework can read the deeplearning model training from keras, loop test events and generate signal/background MVA distributions and roc curve.


## Check out the package :
`mkdir NNReader_rootcore`\
`cd NNReader_rootcore`\
`git clone git@github.com:heymanwasup/NNReader`
## Setup the rootcore 
`setupATLAS`\
`source NNReader/bootstrap/setup.sh`
## compile the package
`rc build`
## run a model
`main <rungtag> <category>`

eg. `main test_scale 0`
 
The `runtag` is a str to represent a dedicated training process. \
The `category` has to be in {0,1,2,3}, these numbers correspond to four categories: `[2jet,3jet] X [even, odd]`.\
The `categroy%2` represents even(0) and odd(1) events, and `2+(category>>1)%2` represents the number of jets.

# NNReader (Standalone)

This is a standalone eventloop framework which dont have strong dependant on the Boost:: packages.

# Usage:

`git clone git@github.com:heymanwasup/NNReader`\
`cd NNReader/Standalone`\
`source setup.sh`\
`make`


