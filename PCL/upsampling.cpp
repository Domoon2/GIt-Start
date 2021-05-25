#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/vlp_grabber.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/console/parse.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/surface/mls.h>

using namespace std;
int main(int argc, char** argv)
{
	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::io::loadPCDFile<pcl::PointXYZ>("table_scene_lms400_downsampled.pcd", *cloud); //PCD 파일 읽기
	cout << "Loaded " << cloud->width * cloud->height << endl;
	
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ> filter;  //Filtering object
	filter.setInputCloud(cloud);

	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree; //Ovject for searching
	filter.setSearchMethod(kdtree);

	filter.setSearchRadius(0.03);

	filter.setUpsamplingMethod(pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointXYZ>::SAMPLE_LOCAL_PLANE);

	filter.setUpsamplingRadius(0.03);

	filter.setUpsamplingStepSize(0.02);

	filter.process(*filtered_cloud);

	cout << "Original: " << cloud->points.size() << " (" << pcl::getFieldsList(*cloud) << ")" << endl; //포인트 수

	pcl::VoxelGrid<pcl::PointXYZ> sor;


	pcl::io::savePCDFile<pcl::PointXYZ>("table_scene_lms400_upsampled1.pcd", *filtered_cloud);
	cout << "After UpSampling " << filtered_cloud->width * filtered_cloud->height <<endl;

	viewer.showCloud(filtered_cloud);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}