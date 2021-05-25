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
#include <pcl/filters/passthrough.h>

using namespace std;
int main(int argc, char** argv)
{
	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud < pcl::PointXYZRGB>);
	//pcl::PLYReader Reader;
	//Reader.read("bun_zipper.ply", *cloud);
	pcl::io::loadPCDFile<pcl::PointXYZRGB>("tabletop.pcd", *cloud); //PCD 파일 읽기

	pcl::PassThrough<pcl::PointXYZRGB> pass;
	pass.setInputCloud(cloud);
	pass.setFilterFieldName("z");
	pass.setFilterLimits(0.7, 1.5);
	//pass.setFilterLimitsNegative(true);
	pass.filter(*cloud_filtered);

	cout << "Original : " << cloud->width * cloud->height << endl;
	cout << "After PASSTHROUGH  : " << cloud_filtered->width * cloud_filtered->height << endl;
	pcl::io::savePCDFile<pcl::PointXYZRGB>("tabletop_passthrough.pcd", *cloud_filtered);

	viewer.showCloud(cloud_filtered);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}