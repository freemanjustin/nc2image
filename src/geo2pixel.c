#include "jmap.h"

void geo2pixel(e *E, float latitude, float longitude, int *y, int *x) {

  float mappedLon, mappedLat;

  float mapWidth    = E->width-1;
  float mapHeight   = E->height-1;

  float lonDelta = (E->mapRight-E->mapLeft); // had a floor on this statement
  float latDelta = (E->mapTop-E->mapBottom);  // had a ceil on this statement

  mappedLon = (longitude - E->mapLeft)*(mapWidth/lonDelta);
  mappedLat = mapHeight - (latitude-E->mapBottom)*(mapHeight/latDelta);

  *x = floor(mappedLon);
  *y = floor(mappedLat);

  return;

}

void pixel2geo(e *E, float *latitude, float *longitude, int y, int x) {


  *longitude = (float)x/(E->mapWidth/E->lonDelta) + E->mapLeft;
  *latitude = E->mapBottom-((float)y - E->mapHeight)/(E->mapHeight/E->latDelta);

  return;

}


/*

function toMercator (lon, lat) {
  var x = lon * 20037508.34 / 180;
  var y = Math.log(Math.tan((90 + lat) * Math.PI / 360)) / (Math.PI / 180);
  y = y * 20037508.34 / 180;

  return [x, y];
  }

function inverseMercator (x, y) {
  var lon = (x / 20037508.34) * 180;
  var lat = (y / 20037508.34) * 180;

  lat = 180/Math.PI * (2 * Math.atan(Math.exp(lat * Math.PI / 180)) - Math.PI / 2);

  return [lon, lat];
  }

*/ 
