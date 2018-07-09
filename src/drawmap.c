#include "jmap.h"
#define OUTSIDE -1

void draw_map(e *E, colormap cm, bounding_box box){

  int i,j;
  float y2lat, x2lon, nn;

  // create an array of lat and lon indices to lookup nearest neighbor info fast
  int *xlut, *ylut;
  float scale_x, scale_y;

  xlut = malloc(E->width*sizeof(int));
  ylut = malloc(E->height*sizeof(int));

  // create colormap lut
  init_cmaps_from_data(E, cm);

  for(j=0;j<E->height;j++){ // row

    y2lat = E->latDelta * ( ((float)j+1.0)/((float)E->height)) ;
    ylut[j] = find_closest(E->lat, y2lat, box.lat_start, box.lat_end);

    //printf("\tylut[%d] = %d\n", j, ylut[j]);
  /*
    //pixel2geo(E, &y2lat, &x2lon, j, 0);
    // map this pixel to be in the y-range of the data
    y2lat = j;//(float)j/(float)E->latDelta;
    if( (y2lat < E->lat[0]) || (y2lat > E->lat[E->nlat-1]) ){
      // this pixel is outside of data range
      // mark it to make transparent later
      ylut[j] = OUTSIDE;
    }
    else
      ylut[j] = find_closest(E->lat, y2lat, box.lat_start, box.lat_end);
    */
  }

  for(i=0;i<E->width;i++){  // col
    x2lon = E->lonDelta * ( ((float)i+1.0)/((float)E->width));
    xlut[i] = find_closest(E->lon, x2lon, box.lon_start, box.lon_end);
  }


  for(j=0;j<E->height;j++){ // row
    for(i=0;i<E->width;i++){  // col

        //if( (ylut[j] != OUTSIDE) && (xlut[i] != OUTSIDE) && (E->field[ylut[j]][xlut[i]] > -999.0) ){
        //printf("ylut[%d] = %d, xlut[%d] = %d\n",j,ylut[j],i,xlut[i]);
          apply_colormap(E, E->cmap, E->field[ylut[j]][xlut[i]], E->min_val, E->max_val );

          E->image[ ((E->height-j-1) * E->width  + i) * 4 + 0] = (int)E->r;//(int)get_red(E->field[0][(E->nlat-1)-j][i], E->min_val, E->max_val);
          E->image[ ((E->height-j-1) * E->width  + i) * 4 + 1] = (int)E->g;//(int)get_red(E->field[0][(E->nlat-1)-j][i], E->min_val, E->max_val);
          E->image[ ((E->height-j-1) * E->width  + i) * 4 + 2] = (int)E->b;//(int)get_red(E->field[0][(E->nlat-1)-j][i], E->min_val, E->max_val);
          E->image[ ((E->height-j-1) * E->width  + i) * 4 + 3] = 255;
        //}


          /*
          //original
          E->image[ (j * E->width  + i) * 4 + 0] = (int)E->r;//(int)get_red(E->field[0][(E->nlat-1)-j][i], E->min_val, E->max_val);
          E->image[ (j * E->width  + i) * 4 + 1] = (int)E->g;//(int)get_red(E->field[0][(E->nlat-1)-j][i], E->min_val, E->max_val);
          E->image[ (j * E->width  + i) * 4 + 2] = (int)E->b;//(int)get_red(E->field[0][(E->nlat-1)-j][i], E->min_val, E->max_val);
          E->image[ (j * E->width  + i) * 4 + 3] = 255;
        }
        else{ // make fill value transparent
          E->image[ (j * E->width  + i) * 4 + 0 ] = 255;
          E->image[ (j * E->width  + i) * 4 + 1] = 255;
          E->image[ (j * E->width  + i) * 4 + 2] = 255;
          E->image[ (j * E->width  + i) * 4 + 3] = 0;
        }
        */

    }
  }
  free(xlut);
  free(ylut);
}
