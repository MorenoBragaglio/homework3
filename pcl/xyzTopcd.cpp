#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <stdio.h>

int main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ> cloud;

  // Fill in the cloud data
  cloud.width    = 1000;
  cloud.height   = 1;
  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);

  FILE* xyz = fopen(argv[1], "r");

  size_t i = 0;
  float x,y,z;
  while( !feof(xyz) )
  {
    fscanf( xyz, "%f %f %f\n", &x, &y, &z );
    if( i >= cloud.width ) {
	cloud.width += 1000;
	cloud.points.resize (cloud.width * cloud.height);
    }
    cloud.points[i].x = x;
    cloud.points[i].y = y;
    cloud.points[i].z = z;

    i++;
  }
  fclose(xyz);
  cloud.width = i;
  cloud.points.resize (cloud.width * cloud.height );

  pcl::io::savePCDFileASCII ("MapSave.pcd", cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to MapSave.pcd." << std::endl;

  return (0);
}
