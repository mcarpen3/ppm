#!/bin/bash

# make the target
make compile

# run the target with args
./pi $@

#convert PPM to jpg for browser view
ffmpeg -i test.ppm test.jpg

# view the PPM
ffplay -fs test.ppm