./nc2png [netcdf file] [field_to_plot] [scale] [colormap] [output.png]

Colormap choices are:

gauss3, detail, ssec, bright, banded, rainbow, jaisnb,
jaisnc, jaisnd, blu_red, manga, jet, wheel, saw3, bw,
defaultncview, extrema, helix, helix2, hotres, magma,
tinferno, plasma, viridis, parula, artmap, davies

For the cloud classify project, the field names are

Pir
Pso

To conver the images to jpg (to use an imputs to the transfer learing
VGG16 model) use the following command (VGG16 want 224x224 3 channel inputs):

./nc2image sample.nc Pso 8 magma test.png
convert test.png -colorspace sRGB -type truecolor test.jpg

will need to add this to the slurm run script.

