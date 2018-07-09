// freeman.justin@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <math.h>

// netCDF header
#include "netcdf.h"

#include "jutil.h"

// colormaps
// static defined
#include "colormaps_bright.h"
#include "colormaps_banded.h"
#include "colormaps_rainbow.h"
#include "colormaps_jaisnb.h"
#include "colormaps_jaisnc.h"
#include "colormaps_jaisnd.h"
#include "colormaps_blu_red.h"
#include "colormaps_manga.h"
#include "colormaps_jet.h"
#include "colormaps_wheel.h"

/* the following are original colormaps from ncview */
#include "colormaps_3gauss.h"
#include "colormaps_3saw.h"
#include "colormaps_bw.h"
#include "colormaps_default.h"
#include "colormaps_detail.h"
#include "colormaps_extrema.h"
#include "colormaps_helix.h"
#include "colormaps_helix2.h"
#include "colormaps_hotres.h"
#include "colormaps_ssec.h"

// jcoolormaps
#include "magma.h"
#include "inferno.h"
#include "plasma.h"
#include "viridis.h"
#include "parula.h"

#include "artmap.h"
#include "davies.h"

#define fail(...) jmap_fail(__LINE__,__func__,__FILE__,__VA_ARGS__)

#define pi  (M_PI)
#define earthradius (6356750.52)
#define deg2rad (M_PI/180.0)
#define rad2deg (180.0/M_PI)

#define max(x,y) (((x) > (y)) ? (x) : (y))
#define min(x,y) (((x) < (y)) ? (x) : (y))

#define FALSE (0)
#define TRUE  (1)

typedef struct{
  int r[256];
  int g[256];
  int b[256];
}cmap;

typedef enum {
  gauss3,
  detail,
  ssec,
  bright,
  banded,
  rainbow,
  jaisnb,
  jaisnc,
  jaisnd,
  blu_red,
  manga,
  jet,
  wheel,
  saw3,
  bw,
  defaultncview,
  extrema,
  helix,
  helix2,
  hotres,
  magma,
  inferno,
  plasma,
  viridis,
  parula,
  artmap,
  davies
}colormap;

typedef struct{

  int   lat_start;
  int   lat_end;
  int   lon_start;
  int   lon_end;
  float min_lat;
  float max_lat;
  float min_lon;
  float max_lon;

}bounding_box;

typedef struct {

    char*   input_string;
    char*   fname;
    char*   input_file;
    char*   colormap_name;

    char*   lat_name;
    char*   lon_name;
    char*   field_name;

    float   mapLeft;
    float   mapRight;
    float   mapTop;
    float   mapBottom;

    int     mapWidth;
    int     mapHeight;

    float   lonDelta;
    float   latDelta;

    int     width;
    int     height;
    char*   image;

    float     r;
    float     g;
    float     b;

    size_t  nlat;
    size_t  nlon;
    float *lat;
    float *lon;
    double **field;
    float min_val;
    float max_val;

    int scale;
    cmap  cmap;

    int   do_shiftgrid;

    // for the cloud classifier:
    int night;

}e;

// prototypes
void jmap_fail( const int, const char*, const char*, const char*, ... );

// netcdf functions
void read_data( e* );

void geo2pixel(e *E, float latitide, float longitude, int *x, int *y);
void pixel2geo(e *E, float *latitude, float *longitude, int y, int x) ;

//search
int midpoint(int low, int high);
int binary_search(int A[], int key, int imin, int imax);
int find_closest_int(int A[], int key, int imin, int imax);
int find_closest(float *A, float key, float imin, float imax);

//colormaps
void init_cmaps_from_data(e *E, colormap cm);
void init_cmap_from_data( int *data, cmap *cmap );
void apply_colormap(e *E, cmap colormap, float value, float min_val, float max_val );

// draw_map
void draw_map(e *E, colormap cm, bounding_box box);
