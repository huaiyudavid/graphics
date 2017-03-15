# graphics
graphics project

# Compilation Instructions
1. cd into the root directory
2. run ```make```
3. run ```./main```

# Extra Credit
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
