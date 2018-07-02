#include "jmap.h"

// check this google post about binary searches:
// http://googleresearch.blogspot.com.au/2006/06/extra-extra-read-all-about-it-nearly.html
int midpoint(int low, int high){

  return  (((unsigned int)low + (unsigned int)high) >> 1);

}

int binary_search(int A[], int key, int imin, int imax)
{
  // continue searching while [imin,imax] is not empty
  while (imax >= imin)
    {
      // calculate the midpoint for roughly equal partition
      int imid = midpoint(imin, imax);
      if(A[imid] == key)
        // key found at index imid
        return imid;
      // determine which subarray to search
      else if (A[imid] < key)
        // change min index to search upper subarray
        imin = imid + 1;
      else
        // change max index to search lower subarray
        imax = imid - 1;
    }
  // key was not found
  return -1;
}


int find_closest_int(int A[], int key, int imin, int imax)
{
  // continue searching while [imin,imax] is not empty
  while (imax >= imin){
    // calculate the midpoint for roughly equal partition
    int imid = midpoint(imin, imax);
    if(A[imid] == key)
      // key found at index imid
      return imid;
    // determine which subarray to search
    else if (A[imid] < key)
      // change min index to search upper subarray
      imin = imid + 1;
    else
      // change max index to search lower subarray
      imax = imid - 1;
  }
  // key was not found, return closest
  if (imax <= 0) return 0;
  if (imin >= imax) return imax;
  if ((key - A[imax]) < (A[imin] - key)) return imax;
  return imin;
}


int find_closest(float *A, float key, int imin, int imax)
{
  // continue searching while [imin,imax] is not empty
  while (imax >= imin){
    // calculate the midpoint for roughly equal partition
    int imid = midpoint(imin, imax);
    if(A[imid] == key)
      // key found at index imid
      return imid;
    // determine which subarray to search
    else if (A[imid] < key)
      // change min index to search upper subarray
      imin = imid + 1;
    else
      // change max index to search lower subarray
      imax = imid - 1;
  }
  // key was not found, return closest
  if (imax <= 0) return 0;
  if (imin >= imax) return imax;
  if ((key - A[imax]) < (A[imin] - key)) return imax;
  return imin;
}
