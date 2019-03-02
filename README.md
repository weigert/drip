# drip
Melting Image Filter

## Description:
A C++ program capable of taking a (small) image and spitting out a "melted" version. You can choose the degree of melting as an input parameter. 

The melting process is "continuous". This allows to create smooth GIFs of melting images.

The output of the drip file is a file with the name of the original file, and appended a tag connoting the degree of melting.
(i.e. outputNUM.png)

## Instructions:
Compile from source using the makefile in drip/source/. Only uses standard libraries and CImg (header included).

Then use drip/deploy/filter.sh to run the command repeatedly for n-frames. You can also use the binary directly to do it for a single frame. I prefer doing this in a deploy folder, because it generates lots of images.

You should preferably use this for small images, because my code is inefficient as hell.

The original motivation was to do some image region detection and analysis, but I singled out this cool effect I observed and wrapped it to make GIFS.

## Converting to GIF
Use the imagemagick command convert:

#convert -delay $5 output*.png -loop 0 movie.gif

