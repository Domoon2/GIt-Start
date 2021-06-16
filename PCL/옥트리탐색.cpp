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
	pcl::io::loadPCDFile<pcl::PointXYZRGB>("cloud_cluster_0.pcd", *cloud); //내부적으로 reader.read() 호출 


 // 시각적 확인을 위해 색상 통일 (255,255,255)
    for (size_t i = 0; i < cloud->points.size(); ++i) {
        cloud->points[i].r = 255;
        cloud->points[i].g = 255;
        cloud->points[i].b = 255;
    }

    //Octree 오브젝트 생성 
    float resolution = 0.03f; //복셀 크기 설정(Set octree voxel resolution)
    pcl::octree::OctreePointCloudSearch<pcl::PointXYZRGB> octree(resolution);
    octree.setInputCloud(cloud);       // 입력 
    octree.addPointsFromInputCloud();  //Octree 생성 (Build Octree)

    //기준점(searchPoint) 설정 방법 #1(x,y,z 좌표 지정)
    //pcl::PointXYZRGB searchPoint;
    //searchPoint.x = 0.026256f;
      //searchPoint.y = -1.464739f;
      //searchPoint.z = 0.929567f;

    //기준점(searchPoint) 설정 방법 #2(3000번째 포인트)
    pcl::PointXYZRGB searchPoint = cloud->points[3000];

    //기준점 좌표 출력 
    std::cout << "searchPoint :" << searchPoint.x << " " << searchPoint.y << " " << searchPoint.z << std::endl;

    //기준점과 동일한 복셀내 존재 하는 하는 포인트 탐색(Voxel Neighbor Search)
    std::vector<int> pointIdxVec;  //결과물 포인트의 Index 저장(Save the result vector of the voxel neighbor search) 

    if (octree.voxelSearch(searchPoint, pointIdxVec))
    {
        //시각적 확인을 위하여 색상 변경 (255,0,0)
        for (size_t i = 0; i < pointIdxVec.size(); ++i) {
            cloud->points[pointIdxVec[i]].r = 255;
            cloud->points[pointIdxVec[i]].g = 0;
            cloud->points[pointIdxVec[i]].b = 0;
        }
    }

    // 기준점에서 가까운 순서중 K번째까지의 포인트 탐색 (K nearest neighbor search)
    int K = 50;   // 탐색할 포인트 수 설정 
    std::vector<int> pointIdxNKNSearch; //Save the index result of the K nearest neighbor
    std::vector<float> pointNKNSquaredDistance;  //Save the index result of the K nearest neighbor

    if (octree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
    {
        //시각적 확인을 위하여 색상 변경 (0,255,0)
        for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i) {
            cloud->points[pointIdxNKNSearch[i]].r = 0;
            cloud->points[pointIdxNKNSearch[i]].g = 255;
            cloud->points[pointIdxNKNSearch[i]].b = 0;
        }
    }

    // 탐색된 점의 수 출력 
    std::cout << "K = 50 nearest neighbors:" << pointIdxNKNSearch.size() << endl;

    //기준점에서 지정된 반경내 포인트 탐색 (Neighbor search within radius)
    float radius = 0.02; //탐색할 반경 설정(Set the search radius)
    std::vector<int> pointIdxRadiusSearch;  //Save the index of each neighbor
    std::vector<float> pointRadiusSquaredDistance;  //Save the square of the Euclidean distance between each neighbor and the search point

    if (octree.radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
    {
        //시각적 확인을 위하여 색상 변경 (0,0,255)
        for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i) {
            cloud->points[pointIdxRadiusSearch[i]].r = 0;
            cloud->points[pointIdxRadiusSearch[i]].g = 0;
            cloud->points[pointIdxRadiusSearch[i]].b = 255;
        }
    }

    // 탐색된 점의 수 출력 
    std::cout << "Radius 0.02 nearest neighbors: " << pointIdxRadiusSearch.size() << endl;

    // 생성된 포인트클라우드 저장 
    pcl::io::savePCDFile<pcl::PointXYZRGB>("Octree_AllinOne.pcd", *cloud);

	viewer.showCloud(cloud);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}


