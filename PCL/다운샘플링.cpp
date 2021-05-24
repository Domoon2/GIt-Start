#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/vlp_grabber.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/console/parse.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>

using namespace std;
int main(int argc, char** argv)
{
	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::io::loadPCDFile<pcl::PointXYZ>("table_scene_lms400.pcd", *cloud); //PCD 파일 읽기



	cout << "Original: " << cloud->points.size() << " (" << pcl::getFieldsList(*cloud) << ")" << endl; //포인트 수

	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);   //입력
	sor.setLeafSize(0.01f, 0.01f, 0.01f);
	sor.filter(*cloud_filtered); //출력


	cout << " After Downsampling:" << cloud_filtered->points.size() << "( " << pcl::getFieldsList(*cloud_filtered) << ")" << endl;

	pcl::io::savePCDFile<pcl::PointXYZ>("table_scene_lms400_downsampled.pcd", *cloud_filtered);

	viewer.showCloud(cloud_filtered);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}