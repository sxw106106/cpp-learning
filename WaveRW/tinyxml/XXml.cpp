#include "XXml.h"
#include <stdio.h>


using namespace std;

// XXml::XXml(const char *XmlFilePath)
// {
//     if(XmlFilePath != NULL)
// 	strcpy(m_XmlFilePath, XmlFilePath);
//     
//     myDocument = NULL;
//     pFirstBookElem = NULL; 
//     pLastBookElem= NULL; 
//     pRootElement= NULL;
// }
XXml::XXml()
{
	printf("int XXml::XXml()\n");
}
XXml::~XXml()
{	
	printf("int XXml::~XXml()\n");           
	if(myDocument!=NULL)
	{
		myDocument->SaveFile();
		delete myDocument;           
		myDocument = NULL;        
	}       
    
	pFirstBookElem = NULL; 
	pLastBookElem= NULL; 
	pRootElement= NULL;		
    
}
int XXml::LoadXml(const char* XmlFilePath)
{
	printf("int XXml::LoadXml(const char* XmlFilePath)\n");
	if(XmlFilePath != NULL)
		strcpy(m_XmlFilePath, XmlFilePath);
    
	myDocument = NULL;
	pFirstBookElem = NULL; 
	pLastBookElem= NULL; 
	pRootElement= NULL;
}

int XXml::SaveXml()
{
	myDocument->SaveFile();
}
/*
int XXml::GetFirstChildValue(TiXmlElement *pElement, char *pValue)
{
	if(pElement == NULL || pElement->FirstChild() == NULL)
		return -1;
	
	strcpy (pValue, pElement->FirstChild()->Value() );
	return 0;
	
}
*/