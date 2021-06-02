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
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
using namespace std;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer) 
{
	viewer.setBackgroundColor(1.0, 0.5, 1.0); //Set the background color
}
int main(int argc, char** argv)
{
	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_f(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::io::loadPCDFile<pcl::PointXYZRGB>("RANSAC_plane_true.pcd", *cloud); //내부적으로 reader.read() 호출 



	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);

	std::vector<pcl::PointIndices> cluster_indices;       // 군집화된 결과물의 Index 저장, 다중 군집화 객체는 cluster_indices[0] 순으로 저장 
  // 군집화 오브젝트 생성  
	pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
	ec.setInputCloud(cloud);       // 입력   
	ec.setClusterTolerance(0.02);  // 2cm  
	ec.setMinClusterSize(100);     // 최소 포인트 수 
	ec.setMaxClusterSize(25000);   // 최대 포인트 수
	ec.setSearchMethod(tree);      // 위에서 정의한 탐색 방법 지정 
	ec.extract(cluster_indices);   // 군집화 적용 

	std::cout << "Orignal" << cloud->width * cloud->height << std::endl; //cloud_filtered->points.size()

	int j = 0;
	for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
	{
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZRGB>);
		for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit)
			cloud_cluster->points.push_back(cloud->points[*pit]);
		cloud_cluster->width = cloud_cluster->points.size();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;

		// 포인트수 출력
		std::cout << "PointCloud representing the Cluster: " << cloud_cluster->points.size() << " data points." << std::endl;
		std::stringstream ss;
		ss << "cloud_cluster_" << j << ".pcd";
		pcl::PCDWriter writer;
		writer.write<pcl::PointXYZRGB>(ss.str(), *cloud_cluster, false); //*
		j++;
	}

	viewer.showCloud(cloud);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}


