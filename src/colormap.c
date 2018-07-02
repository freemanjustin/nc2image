#include "jmap.h"

// some of these functions are derived from ncview
// here is the header from ncview to cover the GPL requirements

/*
 * Ncview by David W. Pierce.  A visual netCDF file viewer.
 * Copyright (C) 1993 through 2010 David W. Pierce
 *
 * This program  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, Version 3, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License, version 3, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * David W. Pierce
 * 6259 Caminito Carrena
 * San Diego, CA  92122
 * pierce@cirrus.ucsd.edu
 */


void init_cmaps_from_data(e *E, colormap cm){
  /* the following are original colormaps from ncview */


  if(cm == gauss3){
    init_cmap_from_data( cmap_3gauss, &E->cmap  );
    return;
  }
  if(cm == detail){
  init_cmap_from_data( cmap_detail, &E->cmap  );
    return;
  }

  if(cm == ssec){
    init_cmap_from_data( cmap_ssec, &E->cmap   );
    return;
  }
  /* A. Shchepetkin: new colormaps are added here */

  if(cm == bright){
    init_cmap_from_data( cmap_bright, &E->cmap );
    return;
  }
  if(cm == banded){
    init_cmap_from_data( cmap_banded, &E->cmap  );
    return;
  }
  if(cm == rainbow){
    init_cmap_from_data( cmap_rainbow, &E->cmap );
    return;
  }
  if(cm == jaisnb){
    init_cmap_from_data( cmap_jaisnb, &E->cmap  );
    return;
  }
  if(cm == jaisnc){
    init_cmap_from_data( cmap_jaisnc, &E->cmap  );
    return;
  }
  if(cm == jaisnd){
    init_cmap_from_data( cmap_jaisnd, &E->cmap  );
    return;
  }
  if(cm == blu_red){
    init_cmap_from_data( cmap_blu_red, &E->cmap );
    return;
  }
  if(cm == manga){
    init_cmap_from_data( cmap_manga, &E->cmap   );
    return;
  }
  if(cm == jet){
    init_cmap_from_data( cmap_jet, &E->cmap    );
    return;
  }
  if(cm == wheel){
    init_cmap_from_data( cmap_wheel, &E->cmap   );
    return;
  }

  /* the following are the rest of the original colormaps from ncview */

  if(cm == saw3){
    init_cmap_from_data( cmap_3saw, &E->cmap    );
    return;
  }
  if(cm == bw){
    init_cmap_from_data( cmap_bw, &E->cmap      );
    return;
  }
  if(cm == defaultncview){
    init_cmap_from_data( cmap_default, &E->cmap );
    return;
  }
  if(cm == extrema){
    init_cmap_from_data( cmap_extrema, &E->cmap );
    return;
  }
  if(cm == helix){
    init_cmap_from_data( cmap_helix, &E->cmap   );
    return;
  }
  if(cm == helix2){
    init_cmap_from_data( cmap_helix2, &E->cmap  );
    return;
  }
  if(cm == hotres){
    init_cmap_from_data( cmap_hotres, &E->cmap  );
    return;
  }

  // j colormaps
  if(cm == magma){
    init_cmap_from_data( cmap_j_magma, &E->cmap);
    return;
  }
  if(cm == inferno){
    init_cmap_from_data( cmap_j_inferno, &E->cmap);
    return;
  }
  if(cm == plasma){
    init_cmap_from_data( cmap_j_plasma, &E->cmap);
    return;
  }
  if(cm == viridis){
    init_cmap_from_data( cmap_j_viridis, &E->cmap);
    return;
  }
  if(cm == parula){
    init_cmap_from_data( cmap_j_parula, &E->cmap);
    return;
  }
  if(cm == artmap){
    init_cmap_from_data( cmap_artmap, &E->cmap);
    return;
  }
  if(cm == davies){
    init_cmap_from_data( cmap_davies, &E->cmap);
    return;
  }
}

void init_cmap_from_data( int *data, cmap *cmap ){

  int	i;

  //fprintf( stderr, "    ... initting cmap >%s< from supplied data\n", colormap_name );

  for( i=0; i<256; i++ ) {
    cmap->r[i] = (unsigned char)data[i*3+0];
    cmap->g[i] = (unsigned char)data[i*3+1];
    cmap->b[i] = (unsigned char)data[i*3+2];
  }
}

void apply_colormap(e *E, cmap colormap, float value, float min_val, float max_val ){

  int index;

  index = (255.0/(max_val - min_val)) * (value - min_val);

  // clamp
  if(index < 0) index = 0;
  else if(index > 255) index = 255;

  E->r = colormap.r[index];
  E->g = colormap.g[index];
  E->b = colormap.b[index];

}
