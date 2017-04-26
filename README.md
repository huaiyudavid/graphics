# CS3258 Intro to Graphics Project
Author: Huaiyu Yang

A command line interface for manipulating TIFF images and rendering basic shapes to the screen.

# Compilation Instructions
1. `cd` into the root directory
2. run ```make```
3. run ```./main```

# Manual
Note: Brackets specify parameters and should not be included when actually using the command.

Note: Be sure to only have 1 delimiter (comma, space) between each argument. Consecutive delimiters with no arguments in between will be interpreted as a 0 argument.

## Dummy Commands
The following commands take floating point arguments and simply echo what they're supposed to do:

```
move [x,y,z]
```
move the pen to (x, y, z)

```
draw [x,y,z]
```
draw with the pen to (x, y, z)

```
color [v,h,s]
```
set the color to v, h, s

## TIFF Reader/Writer
```
tiffread [f]
```
read a tiff file with filename `f`

```
tiffstat [f]
```
print the parameters of tiff image with filename `f`

```
tiffwrite [f,x0,y0,xc,yc]
```
write a tiff file to filename `f` from the box (x0, y0, xc, yc)

Note: `tiffread` must be executed first before `tiffwrite` can be used.

## Resizer
Note: Both of these commands require `tiffread` to be executed first before they can be used.


Both of these commands take non-negative floating point arguments:

```
resize [xscale,yscale]
```
resize by xscale in x and yscale in y

```
zoom [s]
```
scales the image in both directions by the amount s

prints out the dimensions of the new image for easy writing

## 3D Transformations
All of the following commands take floating point arguments:
```
push
```
push the current transformation matrix on the stack

```
pop
```
pop the top of the matrix stack and store it into the current transformation matrix

```
translate [x,y,z]
```
translate the origin by the vector <x, y, z>

```
scale [sx,sy,sz]
``` 
scale in x by s<sub>x</sub>, scale in y by s<sub>y</sub>, and scale in z by s<sub>z</sub>

```
rotate [theta,ax,ay,az]
```
rotate theta degrees about the axis (a<sub>x</sub>, a<sub>y</sub>, a<sub>z</sub>)

```
ortho [l,r,b,t,n,f]
```
implement an orthographic projection

```
perspective [theta,a,n,f]
```
implement a perspective transform

```
lookat [fx,fy,fz,ax,ay,az,ux,uy,uz]
```
change the point of view

```
vertex [x,y,z]
```
draw a line between two points

Note: be sure to call `reset` before drawing to render on a black screen.

```
reset
```
clears the screen and the matrix stack

# Extra Credit
## Tiffwriting the Drawings
The drawings drawn with `vertex` can be written into TIFF files by using the `tiffwrite` command above. The max width and height of the image is the size of the window (default set to 512x512). Be sure to call `reset` before making the drawing if you want the image background to be black.

## Dealing with Borders
Change the border handling with 
```
border [bordertype]
```
where `[bordertype]` is one of `zero`, `freeze`, or `circular`.

__Test images are:__

images/eeyore2x[bordertype].tif

__Comments:__

* `zero` seems to cause a black border around the edges
* `freeze` gets rid of the black border and instead solidifys the original border
* `circular` (done with filter width 100) seems to be similar to `freeze` but is more affected by the internal colors of the image

## Different Filters
Change the filter type with
```
select [filtertype]
```
where `[filtertype]` is one of `lanczos`, `gaussian`, `mitchell`, `hamming`, `bsplcubic` (B-spline cubic), `catmullrom`, `tent`, or `box`.

`lancozs`, `gaussian`, `tent`, and `box` have an optional argument that changes the width of the filter:
```
select [filtertype] [filterwidth]
```
where `[filterwidth]` is a positive number.

__Test images are:__

images/lenna-[filtertype].tif

images/slenna-[filtertype].tif

images/slenna-width100.tif

__Comments:__
* `lanczos` is probably the most visually pleasing one, keeping the image clearer than the rest and not distorting the text too much
* `guassian` blurs the picture pretty badly
* `mitchell` performs very similarly to `lanczos`
* `hamming` also blurs the image a little bit
* `bsplcubic` also blurs a little bit, albeit less than the others that blur, and is a little less vibrant than `lanczos`
* `catmullrom` yields similar results to `mitchell`
* `tent` is very blurry and gets rid of distinct edges
* `box` makes the image very sharp and a little blocky (in that the pixels don't blend together really well)
* increasing the width of the filter to a very large size adds many unwanted artifacts in the resulting image

## Negative Scale Factors
Invert the image in either the horizontal (x) axis or vertical (y) axis by giving negative scales values.

__Test images are:__

images/slenna-negative.tif

__Comments:__
* resizing properly scales the image, such that it is as if the image were scaled with positive scale and then inverted

## Efficiency
While no optimization was made in the order in which resizing the axes occurred, a small optimization was made regarding to filter application on the image. When resampling the image on either axis, a weighted average of the sample values needed to be found with the weights being the values of the filter at the specific pixel distances. Since these filter values are the same across rows when scaling horizontally and across columns when scaling vertically, the filter values were calculated once for a single row/column and then stored for use when sampling the remaining rows/columns. This saves a lot of computationally intensive calculations with the filter, especially when using a Lanczos filter. In fact, due to the precomputation, finding the filter values in the remaining rows/columns becomes an O(1) operation as opposed to an O(filterwidth) operation.
