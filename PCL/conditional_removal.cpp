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
#include <pcl/filters/conditional_removal.h>

using namespace std;
int main(int argc, char** argv)
{
	pcl::visualization::CloudViewer viewer("Cloud Viewer");

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud < pcl::PointXYZRGB>);
	//pcl::PLYReader Reader;
	//Reader.read("bun_zipper.ply", *cloud);
	pcl::io::loadPCDFile<pcl::PointXYZRGB>("tabletop.pcd", *cloud); //PCD 파일 읽기

	//조건 정의
	pcl::ConditionAnd<pcl::PointXYZRGB>::Ptr range_cond(new pcl::ConditionAnd<pcl::PointXYZRGB>());
	range_cond->addComparison (pcl::FieldComparison<pcl::PointXYZRGB>::ConstPtr(new
		pcl::FieldComparison<pcl::PointXYZRGB>("z", pcl::ComparisonOps::GT, 0.0)));  //eg. z축으로 0.00보다 큰값(GT:Greater Than))
	range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZRGB>::ConstPtr(new //조건 2 
		pcl::FieldComparison<pcl::PointXYZRGB>("z", pcl::ComparisonOps::LT, 0.8)));  //eg. z축으로 0.08보다 작은값(LT:Less Than)

	//오브젝트 생성 
	pcl::ConditionalRemoval<pcl::PointXYZRGB> condrem;
	condrem.setInputCloud(cloud);        //입력 
	condrem.setCondition(range_cond);    //조건 설정  
	condrem.setKeepOrganized(true);       //	
	condrem.filter(*cloud_filtered);     //필터 적용 

	cout << "Original : " << cloud->width * cloud->height << endl;
	cout << "After conditional_removal  : " << cloud_filtered->width * cloud_filtered->height << endl;
	pcl::io::savePCDFile<pcl::PointXYZRGB>("tabletop_conditional_removal.pcd", *cloud_filtered);

	viewer.showCloud(cloud_filtered);
	//viewer.showCloud(head);
	while (!viewer.wasStopped())
	{
	}

	return (0);
}