


#include <iostream>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/io.h>
#include <pcl/point_cloud.h>

#include <pcl/PolygonMesh.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <pcl/io/vtk_lib_io.h>

#include<pcl/io/io.h>
#include<pcl/io/pcd_io.h>//pcd Read and write class related header files.
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h> //Point type header files supported in PCL.
#include<pcl/filters/radius_outlier_removal.h>

using namespace std;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer) 
{
	viewer.setBackgroundColor(1.0, 0.5, 1.0); //Set the background color
}
int main(int argc, char** argv)
{
	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile<pcl::PointXYZ>("table_scene_lms400.pcd", *cloud); //내부적으로 reader.read() 호출 



	std::cout << "Orignal" << cloud->width * cloud->height << std::endl; //cloud_filtered->points.size()

	pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;
	outrem.setInputCloud(cloud); //입력
	outrem.setRadiusSearch(0.01); //탐색 범위 0.01
	outrem.setMinNeighborsInRadius(10); //최소 보유 포인트 수 10개
	outrem.filter(*cloud_filtered); //필터적용

	pcl::PCDWriter writer;
	writer.write<pcl::PointXYZ>("Radius_Outlier_Removal.pcd", *cloud_filtered, false);

	std::cout << "After Remove noise" << cloud_filtered->width * cloud_filtered->height << std::endl; //cloud_filtered->points.size()

	outrem.setNegative(true);
	outrem.filter(*cloud_filtered); //필터적용
	writer.write<pcl::PointXYZ>("Radius_Outlier_Removal_Neg.pcd", *cloud_filtered, false);

	viewer.showCloud(cloud_filtered);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}


