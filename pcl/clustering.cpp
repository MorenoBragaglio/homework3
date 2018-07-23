#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <sstream>

int main(int argc, char **argv) 
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr in_cloud(new pcl::PointCloud<pcl::PointXYZ> ()),
                                      subsamp_cloud(new pcl::PointCloud<pcl::PointXYZ> ());
  
  // Load a cloud from file
  if ( pcl::io::loadPCDFile( "MapSave.pcd", *in_cloud ) < 0)
  {
    std::cout << "Error loading model cloud." << std::endl;
    return (-1);
  }
  
  // Downsample the cloud
  pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
  voxel_grid.setInputCloud (in_cloud);
  voxel_grid.setLeafSize (0.01, 0.01, 0.01);
  voxel_grid.filter ( *subsamp_cloud );
  
  // Create a KD tree
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
  tree->setInputCloud (subsamp_cloud);

  std::vector<pcl::PointIndices> cluster_indices;
  // Divides the point cloud into smaller, correlated, parts (clusters)
  pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
  // Set distance threshold
  ec.setClusterTolerance (0.15);
  ec.setMinClusterSize (50);
  //ec.setMaxClusterSize (25000);
  // Set the KD tree that will be used to look for points neighbors
  ec.setSearchMethod (tree);
  ec.setInputCloud (subsamp_cloud);
  // Get the clusters (i.e., the point indices that belong to each cluster)
  ec.extract (cluster_indices);
  
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();

  std::string base_name("Cluster");  
  int j = 0;
  // Iterate for each cluster...
  for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); 
       it != cluster_indices.end (); ++it)
  {
    // Create a cloud for each cluster
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);
    // Iterate for each index
    for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
      cloud_cluster->points.push_back (subsamp_cloud->points[*pit]);
      
    cloud_cluster->width = cloud_cluster->points.size ();
    cloud_cluster->height = 1;
    cloud_cluster->is_dense = true;
  
    std::stringstream sbuf;
    sbuf<<base_name; 
    sbuf<<j;
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> 
      cluster_color(cloud_cluster, rand()%256, rand()%256, rand()%256);
    // Visualize this cluster
    viewer->addPointCloud<pcl::PointXYZ> ( cloud_cluster, cluster_color, sbuf.str());
    
    j++;
  }
  
  // Wait until the visualizer is closed
  while (!viewer->wasStopped ())
  {
    viewer->spinOnce ( 1 );
  }
}
