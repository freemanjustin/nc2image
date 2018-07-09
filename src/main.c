// freeman.justin@gmail.com

#include "jmap.h"


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

int main(int argc,char **argv)
{
    e	*E;
    int i,j;
    int row,col;
    int index;

    bounding_box box;

    colormap cm;

    int   nx,ny;
    int   ii,jj;


	// malloc the work struct
	E = malloc(sizeof(e));
	if(E==NULL) fail("malloc failed\n");

	// parse command line arguments
	if(argc < 5){
		fail("./nc2png [netcdf file] [scale] [colormap] [output.png]\n");
	}
	else{
		get_command_line_arg_as_string(&E->input_file, argv[1]);
    get_command_line_arg_as_string(&E->field_name, argv[2]);
    get_command_line_arg_as_int(&E->scale, argv[3]);
    get_command_line_arg_as_string(&E->colormap_name, argv[4]);
		get_command_line_arg_as_string(&E->fname, argv[5]);
	}

  // figure out what colormap was requested
  if(strncmp(E->colormap_name,"gauss3", 6)==0)
    cm = gauss3;
  else if(strncmp(E->colormap_name,"detail", 6)==0)
    cm = detail;
  else if(strncmp(E->colormap_name,"ssec", 4)==0)
    cm = ssec;
  else if(strncmp(E->colormap_name,"bright", 6)==0)
    cm = bright;
  else if(strncmp(E->colormap_name,"banded", 6)==0)
    cm = banded;
  else if(strncmp(E->colormap_name,"rainbow", 7)==0)
    cm = rainbow;
  else if(strncmp(E->colormap_name,"jaisnb", 6)==0)
    cm = jaisnb;
  else if(strncmp(E->colormap_name,"jaisnb", 6)==0)
    cm = jaisnb;
  else if(strncmp(E->colormap_name,"jaisnc", 6)==0)
    cm = jaisnc;
  else if(strncmp(E->colormap_name,"jaisnd", 6)==0)
    cm = jaisnd;
  else if(strncmp(E->colormap_name,"blu_red", 7)==0)
    cm = blu_red;
  else if(strncmp(E->colormap_name,"manga", 5)==0)
    cm = manga;
  else if(strncmp(E->colormap_name,"jet", 3)==0)
    cm = jet;
  else if(strncmp(E->colormap_name,"wheel", 5)==0)
    cm = wheel;
  else if(strncmp(E->colormap_name,"saw3", 4)==0)
    cm = saw3;
  else if(strncmp(E->colormap_name,"bw", 2)==0)
    cm = bw;
  else if(strncmp(E->colormap_name,"defaultncview", 13)==0)
    cm = defaultncview;
  else if(strncmp(E->colormap_name,"extrema", 7)==0)
    cm = extrema;
  else if(strncmp(E->colormap_name,"helix", 5)==0)
    cm = helix;
  else if(strncmp(E->colormap_name,"helix2", 6)==0)
    cm = helix2;
  else if(strncmp(E->colormap_name,"hotres", 6)==0)
    cm = hotres;
  else if(strncmp(E->colormap_name,"magma", 5)==0)
    cm = magma;
  else if(strncmp(E->colormap_name,"plasma", 6)==0)
    cm = plasma;
  else if(strncmp(E->colormap_name,"viridis", 7)==0)
    cm = viridis;
  else if(strncmp(E->colormap_name,"parula", 6)==0)
    cm = parula;
  else if(strncmp(E->colormap_name,"artmap", 6)==0)
    cm = artmap;
  else if(strncmp(E->colormap_name,"davies", 6)==0)
    cm = davies;
  else if(strncmp(E->colormap_name,"inferno", 7)==0)
    cm = inferno;
  else{
    printf("unknown colormap requested. your choices are:\n");
    printf("\tgauss3, detail, ssec, bright, banded, rainbow, jaisnb,\n");
    printf("\tjaisnc, jaisnd, blu_red, manga, jet, wheel, saw3, bw,\n");
    printf("\tdefaultncview, extrema, helix, helix2, hotres, magma,\n");
    printf("\tinferno, plasma, viridis, parula, artmap, davies\n");
    exit(0);
  }

  // read the netcdf data
  E->lat_name = malloc(80);
  E->lon_name = malloc(80);
  //E->field_name = malloc(80);

  //sprintf(E->lat_name,"yt_ocean");
  //sprintf(E->lon_name,"xt_ocean");
  //sprintf(E->field_name,"eta_t");

  // sprintf(E->lat_name,"x"); // this is rows
  // sprintf(E->lon_name,"y"); // this is cols
  // sprintf(E->field_name,"field");

  sprintf(E->lat_name,"x"); // this is rows
  sprintf(E->lon_name,"y"); // this is cols
  //sprintf(E->field_name,"Pso");

  //printf("field_name = %s\n", E->field_name);

  E->night = 0; // assume not night time!
  read_data(E);

  //printf("done read data\n");

  // redo the lat and lon arrays to be integers from 1 to nlat, 1 to nlon
  
  for(i=0;i<E->nlat;i++)
    E->lat[i] = i+1;
  for(i=0;i<E->nlon;i++)
    E->lon[i] = i+1;

    box.min_lat = E->lat[0];
    box.max_lat = E->lat[E->nlat-1];
    box.min_lon = E->lon[0];
    box.max_lon = E->lon[E->nlon-1];

    // these are the indexes into the data array
    box.lon_start = find_closest(E->lon, box.min_lon, 0, E->nlon-1);//floor(E->lon[0]);
    box.lon_end = find_closest(E->lon, box.max_lon, 0, E->nlon-1);//ceil(E->lon[E->nlon-1]);
    box.lat_start = find_closest(E->lat, box.min_lat, 0, E->nlat-1);//ceil(E->lat[E->nlat-1]);
    box.lat_end = find_closest(E->lat, box.max_lat, 0, E->nlat-1);//floor(E->lat[0]);


    // image dimensions
    //int scale = E->scale;  // scale factor should be dynamically calculated
    E->width  = (box.lon_end-box.lon_start);
    E->height = (box.lat_end-box.lat_start);
    //printf("## width = %d, height = %d\n", E->width, E->height);

    // map bounds for the drawing function
    E->mapLeft = box.min_lon;//E->lon[box.lon_start];//floor(E->lon[0]);
    E->mapRight = box.max_lon;//E->lon[box.lon_end];//ceil(E->lon[E->nlon-1]);
    E->mapTop = box.max_lat;//E->lat[box.lat_end];//ceil(E->lat[E->nlat-1]);
    E->mapBottom = box.min_lat;//E->lat[box.lat_start];//floor(E->lat[0]);

    E->mapWidth    = E->width;  // had E->width-1
    E->mapHeight   = E->height; // had E->height-1

    E->lonDelta = (E->mapRight-E->mapLeft); // had a floor on this statement
    E->latDelta = (E->mapTop-E->mapBottom);  // had a ceil on this statement

    //printf("width = %d\nheight = %d\n", E->width, E->height);

    //printf("west = %f\teast = %f\n", E->mapLeft, E->mapRight);
    //printf("south = %f\tnorth = %f\n", E->mapBottom, E->mapTop);

    //printf("E->lonDelta = %f\n",E->lonDelta);
    //printf("E->latDelta = %f\n", E->latDelta);

    // allocate memory for the image data
    // this is for a rgba png file
    if ((E->image = (char *) malloc(E->height*E->width*4*sizeof(char)) ) == NULL) {
        fail("failed to allocate memory for image \n");
    }

    /*
    // figure out min and max values
		E->min_val = 999.0;
		E->max_val = -999.0;
		for(i=box.lat_start;i<box.lat_end;i++){
			for(j=box.lon_start;j<box.lon_end;j++){

				if(E->field[i][j] > -999.0){
					if(E->field[i][j] < E->min_val)
						E->min_val = E->field[i][j];

					if(E->field[i][j] > E->max_val)
						E->max_val = E->field[i][j];
				}
			}
		}

    //E->min_val = 0.0;
    //E->max_val = 1.0;
		printf("min_val = %f\nmax_val = %f\n", E->min_val, E->max_val);
    */

    //cm = rainbow;
    //draw_map(E, rainbow, box);
    draw_map(E, cm, box);

    // apply scale factor
    float scaleFactor = E->scale;
    int scaledImageWidth = E->width*E->scale;
    int scaledImageHeight = E->height*E->scale;

    char *scaled_image = (char *) malloc(scaledImageWidth*scaledImageHeight*4*sizeof(char));

    if( (scaledImageWidth != E->width) && (scaledImageHeight != E->height) ){
    
      for (int y=0; y < scaledImageHeight; y++){
        for (int x=0; x < scaledImageWidth; x++) {

          //int sourceImageX = (int)max(x * 1.0f / scaleFactor, (float)(E->width - 1));
          //int sourceImageY = (int)max(y * 1.0f / scaleFactor, (float)(E->height - 1));

          int sourceImageX = (int)(x * 1.0f / scaleFactor);
          if(sourceImageX > (E->width - 1))
            sourceImageX = (E->width - 1);

          int sourceImageY = (int)(y * 1.0f / scaleFactor);
          if(sourceImageY > (E->height - 1))
            sourceImageY = (E->height - 1);
          
          // source image pixel value
          E->r = E->image[ (sourceImageY * E->width  + sourceImageX) * 4 + 0];
          E->g = E->image[ (sourceImageY * E->width  + sourceImageX) * 4 + 1];
          E->b = E->image[ (sourceImageY * E->width + sourceImageX) * 4 + 2];

          // set scale image pixel value
          scaled_image[ (y * scaledImageWidth  + x) * 4 + 0] = (int)E->r;
          scaled_image[ (y * scaledImageWidth  + x) * 4 + 1] = (int)E->g;
          scaled_image[ (y * scaledImageWidth  + x) * 4 + 2] = (int)E->b;
          scaled_image[ (y * scaledImageWidth  + x) * 4 + 3] = 255;
        }
      } 

      if(E->night == 1){
        char* fname_night;
        fname_night = malloc(256*sizeof(char));
        sprintf(fname_night,"night_%s", E->fname);
        stbi_write_png(fname_night, scaledImageWidth, scaledImageHeight, 4, (const void *)scaled_image, 0);
        free(fname_night);
      }
      else
        stbi_write_png(E->fname, scaledImageWidth, scaledImageHeight, 4, (const void *)scaled_image, 0);
    }
    else{
      if(E->night == 1){
        char* fname_night;
        fname_night = malloc(256*sizeof(char));
        sprintf(fname_night,"night_%s", E->fname);
        stbi_write_png(fname_night, scaledImageWidth, scaledImageHeight, 4, (const void *)scaled_image, 0);
        free(fname_night);
      }
      else{
        // write the image
        stbi_write_png(E->fname, E->width, E->height, 4, (const void *)E->image, 0);
      }
    }

	return 0;
}
