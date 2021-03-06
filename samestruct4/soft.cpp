#include "soft.h"
SoftPackageFactory* SoftPackageFactory::_instance = 0;

SoftPackageFactory::~SoftPackageFactory()
{ 
	printf("** deconstructing SoftPackageFactory **\n"); 
	if(!_instance)
		delete _instance;
}
SoftPackageFactory::SoftPackageFactory()
{	
	
}
SoftPackageFactory::SoftPackageFactory(const CourseInfo &CI)
{
	m_CI = CI;
	m_CI.SendbySM = 9;
	printf("** constructing SoftPackageFactory **\n");
}

SoftPackageFactory* SoftPackageFactory::CreateInstance(const CourseInfo &CI)
{
	if(_instance == 0)
	{
		printf("** new SoftPackageFactory **\n");
		_instance = new SoftPackageFactory(CI);
	}
	
	return _instance;
}


int SoftPackageFactory::Book()
{
	printf("book SoftPackage ID = %s \t SendbySM = %d \n", m_CI.ID, m_CI.SendbySM);
	
}
