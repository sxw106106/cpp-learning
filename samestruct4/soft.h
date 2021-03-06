#ifndef __SOFT_PACKAGE_H
#define __SOFT_PACKAGE_H

#include "ss.h"

class SoftPackageFactory : public ResourceFactory
{
public:
	virtual ~SoftPackageFactory();
	SoftPackageFactory(const CourseInfo &CI);
	static SoftPackageFactory* CreateInstance(const CourseInfo &CI);
	int Book();
protected:
	SoftPackageFactory();	
private:
	static SoftPackageFactory* _instance;
// 	CourseInfo m_CI;
};
#endif