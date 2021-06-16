#include <iostream>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/io.h>
#include <pcl/point_cloud.h>
#include <pcl/PolygonMesh.h>

#include <pcl/io/vtk_lib_io.h>
#include<pcl/io/io.h>
#include<pcl/io/pcd_io.h>//pcd Read and write class related header files.
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h> //Point type header files supported in PCL.
#include <pcl/octree/octree_search.h> 
#include <pcl/kdtree/kdtree_flann.h>
#include <vector>
#include <ctime>
#include <cmath>

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
	pcl::io::loadPCDFile<pcl::PointXYZRGB>("cloud_cluster_0.pcd", *cloud); //���������� reader.read() ȣ�� 


 // �ð��� Ȯ���� ���� ���� ���� (255,255,255)
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].r = 255;
        cloud->points[i].g = 255;
        cloud->points[i].b = 255;
    }

    //Octree ������Ʈ ���� 
    float resolution = 0.03f; //���� ũ�� ����(Set octree voxel resolution)
    pcl::octree::OctreePointCloudSearch<pcl::PointXYZRGB> octree(resolution);
    octree.setInputCloud(cloud);       // �Է� 
    octree.addPointsFromInputCloud();  //Octree ���� (Build Octree)

    //������(searchPoint) ���� ��� #1(x,y,z ��ǥ ����)
    //pcl::PointXYZRGB searchPoint;
    //searchPoint.x = 0.026256f;
      //searchPoint.y = -1.464739f;
      //searchPoint.z = 0.929567f;

    //������(searchPoint) ���� ��� #2(3000��° ����Ʈ)
    pcl::PointXYZRGB searchPoint = cloud->points[3000];

    //������ ��ǥ ��� 
    std::cout << "searchPoint :" << searchPoint.x << " " << searchPoint.y << " " << searchPoint.z << std::endl;

    //�������� ������ ������ ���� �ϴ� �ϴ� ����Ʈ Ž��(Voxel Neighbor Search)
    std::vector<int> pointIdxVec;  //����� ����Ʈ�� Index ����(Save the result vector of the voxel neighbor search) 

    if (octree.voxelSearch(searchPoint, pointIdxVec))
    {
        //�ð��� Ȯ���� ���Ͽ� ���� ���� (255,0,0)
        for (size_t i = 0; i < pointIdxVec.size(); ++i) {
            cloud->points[pointIdxVec[i]].r = 255;
            cloud->points[pointIdxVec[i]].g = 0;
            cloud->points[pointIdxVec[i]].b = 0;
        }
    }

    // ���������� ����� ������ K��°������ ����Ʈ Ž�� (K nearest neighbor search)
    int K = 50;   // Ž���� ����Ʈ �� ���� 
    std::vector<int> pointIdxNKNSearch; //Save the index result of the K nearest neighbor
    std::vector<float> pointNKNSquaredDistance;  //Save the index result of the K nearest neighbor

    if (octree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
    {
        //�ð��� Ȯ���� ���Ͽ� ���� ���� (0,255,0)
        for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i) {
            cloud->points[pointIdxNKNSearch[i]].r = 0;
            cloud->points[pointIdxNKNSearch[i]].g = 255;
            cloud->points[pointIdxNKNSearch[i]].b = 0;
        }
    }

    // Ž���� ���� �� ��� 
    std::cout << "K = 50 nearest neighbors:" << pointIdxNKNSearch.size() << endl;

    //���������� ������ �ݰ泻 ����Ʈ Ž�� (Neighbor search within radius)
    float radius = 0.02; //Ž���� �ݰ� ����(Set the search radius)
    std::vector<int> pointIdxRadiusSearch;  //Save the index of each neighbor
    std::vector<float> pointRadiusSquaredDistance;  //Save the square of the Euclidean distance between each neighbor and the search point

    if (octree.radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
    {
        //�ð��� Ȯ���� ���Ͽ� ���� ���� (0,0,255)
        for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i) {
            cloud->points[pointIdxRadiusSearch[i]].r = 0;
            cloud->points[pointIdxRadiusSearch[i]].g = 0;
            cloud->points[pointIdxRadiusSearch[i]].b = 255;
        }
    }

    // Ž���� ���� �� ��� 
    std::cout << "Radius 0.02 nearest neighbors: " << pointIdxRadiusSearch.size() << endl;

    // ������ ����ƮŬ���� ���� 
    pcl::io::savePCDFile<pcl::PointXYZRGB>("Octree_AllinOne.pcd", *cloud);

	viewer.showCloud(cloud);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}


