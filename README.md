# drip
Melting Image Filter

## Description:
A C++ program capable of taking a (small) image and spitting out a "melted" version. You can choose the degree of melting as an input parameter. 

The melting process is "continuous". This allows to create smooth GIFs of melting images.

The output of the drip file is a file with the name of the original file, and appended a tag connoting the degree of melting.
(i.e. image.png#_dripped.png#)



## Instructions:


## Converting to GIF
#convert -delay $5 $2*.png -loop 0 $6

