# drip
Melting Image Filter

Article: http://weigert.vsos.ethz.ch/2019/03/01/glitchy-image-filter/

## Description:
A C++ program capable of taking a (small, recommended ~200 PX Dimension) image and spitting out a "melted" version. You can choose the degree of melting as an input parameter. 

The melting process is "continuous". This allows to create smooth GIFs of melting images.

The output of the drip file is a file with the name of the original file, and appended a tag connoting the degree of melting.
(i.e. outputNUM.png)

## Instructions:
Compile from source using the makefile in drip/source/. Only uses standard libraries and CImg (header included).

Then use drip/deploy/filter.sh to run the command repeatedly for n-frames. You can also use the binary directly to do it for a single frame. I prefer doing this in a deploy folder, because it generates lots of output images.

You should preferably use this for small images, because my code is inefficient as hell.

You may have to chmod the binary.

The original motivation was to do some image region detection and analysis, but I singled out this cool effect I observed and wrapped it to make GIFS.

### Usage:
    Multiple Frames: *100 frames with stepsize 5*
    > filter.sh image.png 5 100
    
    Single Frame: *Drip-degree 100*
    > ./drip image.png 100

## Converting to GIF
    Use the imagemagick command convert: *20 Milliseconds between frames, use all output*.png, loop forever, output movie.gif*
    > convert -delay 20 output*.png -loop 0 movie.gif
    
    If you want to convert and scale (because you're maybe applying it to small images, as my code is horrible):
    > convert -delay 20 output*.png -resize 1000% -loop 0 movie.gif
    
    Reverse the GIF too (plays forward and backwards)
    > convert output*.png -coalesce -duplicate 1,-2-1 \ -loop 0 movie.gif
