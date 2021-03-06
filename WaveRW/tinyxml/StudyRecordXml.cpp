#include "StudyRecordXml.h"
#include <stdio.h>
#include <iostream>
#include <string.h>


using namespace std;

StudyRecordXml::StudyRecordXml()
{

}
/*
{
	LoadXml();
}*/
StudyRecordXml::~StudyRecordXml()
{
	printf("StudyRecordXml::~StudyRecordXml()\n");
	
}

int StudyRecordXml::LoadXml(const char* XmlFilePath)
{
	if(XXml::LoadXml(XmlFilePath)<0)
		return -1;
	
	myDocument = new TiXmlDocument(XmlFilePath);//should declear in header
	myDocument ->LoadFile();
		
	//begin read
	pRootElement = myDocument->RootElement();//StudyHistory
	if(pRootElement == NULL)
		return -1;	
	CurrentPart = atoi(pRootElement->Attribute("part"));
	
	pFirstBookElem = pRootElement->FirstChildElement();
	TiXmlElement *FirstStudyRecordItem = pFirstBookElem ;	 	
 	pLastBookElem = pFirstBookElem;
	
	int index = 0;	
	
	while ( FirstStudyRecordItem != NULL )
	{
		StudyRecordInfo SRI;
		SRI.StudyRecordInfoID = FirstStudyRecordItem->Attribute("ID");
		   
		TiXmlElement *FirstCourseIDItem = FirstStudyRecordItem->FirstChildElement();
		SRI.CourseID= FirstCourseIDItem->FirstChild()->Value();
		
		TiXmlElement *FirstCourseNameItem = FirstCourseIDItem->NextSiblingElement();
		SRI.CourseName = FirstCourseNameItem->FirstChild()->Value();
		
		TiXmlElement *FirstStudy_IntervalItem = FirstCourseNameItem->NextSiblingElement();
		SRI.Study_Interval = atoi(FirstStudy_IntervalItem->FirstChild()->Value());		
		
		TiXmlElement *FirstStudy_TimeItem = FirstStudy_IntervalItem->NextSiblingElement();
		SRI.Study_Time= FirstStudy_TimeItem->FirstChild()->Value();
				
		
		TiXmlElement *FirstFlowerItem = FirstStudy_TimeItem->NextSiblingElement();
		SRI.Flower = atoi(FirstFlowerItem->FirstChild()->Value());
		
		TiXmlElement *FirstFirstGradeItem = FirstFlowerItem->NextSiblingElement();
		SRI.FirstGrade = atoi(FirstFirstGradeItem->FirstChild()->Value());		
		
		//Main score
		TiXmlElement *FirstStudy_ScoreItem = FirstFirstGradeItem->NextSiblingElement();
		SRI.Study_Score = atof(FirstStudy_ScoreItem->FirstChild()->Value());
		
		TiXmlElement *FirstUnAnswerCountItem = FirstStudy_ScoreItem->NextSiblingElement();
		SRI.UnAnswerCount = atof(FirstUnAnswerCountItem->FirstChild()->Value());
		
		
		TiXmlElement *FirstRCountItem = FirstUnAnswerCountItem->NextSiblingElement();
		SRI.RCount = atoi(FirstRCountItem->FirstChild()->Value());
		
		TiXmlElement *FirstWCountItem = FirstRCountItem->NextSiblingElement();
		SRI.WCount = atoi(FirstWCountItem->FirstChild()->Value());
			
		
		TiXmlElement *FirstStudyPersonCountItem = FirstWCountItem->NextSiblingElement();
		SRI.Study_PersonCount= atoi(FirstStudyPersonCountItem->FirstChild()->Value());

		//Sub score
		if( SRI.Study_PersonCount>= 2)		
		{
			//A
			TiXmlElement *FirstPersonA_ScoreItem = FirstStudyPersonCountItem->NextSiblingElement();			
			SRI.PersonA_Score = atof(FirstPersonA_ScoreItem->FirstChild()->Value());						
			
			TiXmlElement *FirstUnAnswerCountAItem = FirstPersonA_ScoreItem->NextSiblingElement();
			SRI.UnAnswerCountA = atof(FirstUnAnswerCountAItem->FirstChild()->Value());				
		
			TiXmlElement *FirstRCountAItem = FirstUnAnswerCountAItem->NextSiblingElement();
			SRI.RCountA = atoi(FirstRCountAItem->FirstChild()->Value());
				
			TiXmlElement *FirstWCountAItem = FirstRCountAItem->NextSiblingElement();
			SRI.WCountA = atoi(FirstWCountAItem->FirstChild()->Value());										
						
			if(SRI.Study_PersonCount>=3)		
			{
				//B
				TiXmlElement *FirstPersonB_ScoreItem = FirstWCountAItem->NextSiblingElement();
				SRI.PersonB_Score = atof(FirstPersonB_ScoreItem->FirstChild()->Value());						
									
				TiXmlElement *FirstUnAnswerCountBItem = FirstPersonB_ScoreItem->NextSiblingElement();
				SRI.UnAnswerCountB = atof(FirstUnAnswerCountBItem->FirstChild()->Value());
			
				TiXmlElement *FirstRCountBItem = FirstUnAnswerCountBItem->NextSiblingElement();
				SRI.RCountB = atoi(FirstRCountBItem->FirstChild()->Value());
					
				TiXmlElement *FirstWCountBItem = FirstRCountBItem->NextSiblingElement();
				SRI.WCountB = atoi(FirstWCountBItem->FirstChild()->Value());
			}
						
		}	
			
		

		index = index + 1;
		
		VStudyRecordInfoArray.push_back(SRI);
//		cout <<" VStudyRecordInfoArray sizeof =" << sizeof(VStudyRecordInfoArray)<< endl;
			
		FirstStudyRecordItem = FirstStudyRecordItem->NextSiblingElement();
		if(FirstStudyRecordItem != NULL)
		    pLastBookElem = FirstStudyRecordItem; 
		
	}
	//end read
	
	cout <<"\nindex = "<< index << "#### Loop done ####" <<endl;
	
	return 1;
}


StudyRecordInfo* StudyRecordXml::GetStudyRecordInfo(string id)
{
    vector<StudyRecordInfo>::iterator iter;
    int i = 0;
    for( iter = VStudyRecordInfoArray.begin(); iter != VStudyRecordInfoArray.end(); ++i , ++iter)
    {
	//int iFound = id.find(iter->StudyRecordInfoID);
	if(iter->StudyRecordInfoID == id)//if (iFound != string::npos )	
	  return &VStudyRecordInfoArray[i];
	 
	
    }
    return NULL;
    
}

vector <StudyRecordInfo>* StudyRecordXml::GetStudyRecordInfo()
{
    return &VStudyRecordInfoArray;
}

int StudyRecordXml::AddItem(StudyRecordInfo info)
{
	if( pRootElement == NULL/* && pLastBookElem == NULL*/)
        {
            LoadXml(m_XmlFilePath);
        }
	if( pRootElement != NULL /*&& pLastBookElem != NULL*/)
	{
		TiXmlElement *pElemLast = (TiXmlElement*)pRootElement->LastChild();
		int newid = 0;
		int lastID = 0;
		char idc[ID_MAX] = {0};
		if(pElemLast==NULL)//first record
		{	
			//lastID = 1000000001;
			sprintf(idc,"%d0000000%d", CurrentPart, 1);//start from 1000000001			
		}
		else
		{
			lastID = atoi( pElemLast->Attribute("ID"));		
			newid = lastID+1;
			sprintf(idc ,"%d",newid);
		}
		
		TiXmlElement *pNewElemStudyRecord = new TiXmlElement("StudyRecord");		
		pNewElemStudyRecord->SetAttribute("ID",idc );
		
		TiXmlElement *pNewElemCourseID = new TiXmlElement("CourseID");	
		TiXmlText *pNewTextCourseID = new TiXmlText(info.CourseID.c_str());
		pNewElemCourseID->LinkEndChild(pNewTextCourseID);
		pNewElemStudyRecord->LinkEndChild(pNewElemCourseID);
		
		TiXmlElement *pNewElemCourseName = new TiXmlElement("CourseName");	
		TiXmlText *pNewTextCourseName = new TiXmlText(info.CourseName.c_str());
		pNewElemCourseName->LinkEndChild(pNewTextCourseName);
		pNewElemStudyRecord->LinkEndChild(pNewElemCourseName);
		
		TiXmlElement *pNewElemStudy_Interval = new TiXmlElement("Study_Interval");
		char Study_Interval_C[5];
		sprintf(Study_Interval_C, "%d", info.Study_Interval);
		TiXmlText *pNewTextStudy_Interval = new TiXmlText(Study_Interval_C);
		pNewElemStudy_Interval->LinkEndChild(pNewTextStudy_Interval);
		pNewElemStudyRecord->LinkEndChild(pNewElemStudy_Interval);
		
		TiXmlElement *pNewElemStudy_Time = new TiXmlElement("Study_Time");	
		TiXmlText *pNewTextStudy_Time = new TiXmlText(info.Study_Time.c_str());
		pNewElemStudy_Time->LinkEndChild(pNewTextStudy_Time);
		pNewElemStudyRecord->LinkEndChild(pNewElemStudy_Time);
		
		TiXmlElement *pNewElemFlower = new TiXmlElement("Flower");	
		char Flower_C[5];
		sprintf(Flower_C, "%d", info.Flower);
		TiXmlText *pNewTextFlower = new TiXmlText(Flower_C);
		pNewElemFlower->LinkEndChild(pNewTextFlower);
		pNewElemStudyRecord->LinkEndChild(pNewElemFlower);
		
		TiXmlElement *pNewElemFirstGrade = new TiXmlElement("FirstGrade");	
		char FirstGrade_C[5];
		sprintf(FirstGrade_C, "%d", info.FirstGrade);
		TiXmlText *pNewTextFirstGrade = new TiXmlText(FirstGrade_C);
		pNewElemFirstGrade->LinkEndChild(pNewTextFirstGrade);
		pNewElemStudyRecord->LinkEndChild(pNewElemFirstGrade);
		
		TiXmlElement *pNewElemStudy_Score = new TiXmlElement("Study_Score");	
		char Study_Score_C[5];
		sprintf(Study_Score_C, "%2.1f", info.Study_Score);
		TiXmlText *pNewTextStudy_Score = new TiXmlText(Study_Score_C);
		pNewElemStudy_Score->LinkEndChild(pNewTextStudy_Score);
		pNewElemStudyRecord->LinkEndChild(pNewElemStudy_Score);
		
		TiXmlElement *pNewElemUnAnswerCount = new TiXmlElement("UnAnswerCount");	
		char UnAnswerCount_C[5];
		sprintf(UnAnswerCount_C, "%d", info.UnAnswerCount);
		TiXmlText *pNewTextUnAnswerCount = new TiXmlText(UnAnswerCount_C);
		pNewElemUnAnswerCount->LinkEndChild(pNewTextUnAnswerCount);
		pNewElemStudyRecord->LinkEndChild(pNewElemUnAnswerCount);
		
		TiXmlElement *pNewElemRCount = new TiXmlElement("RCount");	
		char RCount_C[5];
		sprintf(RCount_C, "%d", info.RCount);
		TiXmlText *pNewTextRCount = new TiXmlText(RCount_C);
		pNewElemRCount->LinkEndChild(pNewTextRCount);
		pNewElemStudyRecord->LinkEndChild(pNewElemRCount);
		
		TiXmlElement *pNewElemWCount = new TiXmlElement("WCount");	
		char WCount_C[5];
		sprintf(WCount_C, "%d", info.WCount);
		TiXmlText *pNewTextWCount = new TiXmlText(WCount_C);
		pNewElemWCount->LinkEndChild(pNewTextWCount);
		pNewElemStudyRecord->LinkEndChild(pNewElemWCount);
		
		
		TiXmlElement *pNewElemStudy_PersonCount = new TiXmlElement("Study_PersonCount");	
		char Study_PersonCount_C[5];
		sprintf(Study_PersonCount_C, "%d", info.Study_PersonCount);
		TiXmlText *pNewTextStudy_PersonCount = new TiXmlText(Study_PersonCount_C);
		pNewElemStudy_PersonCount->LinkEndChild(pNewTextStudy_PersonCount);
		pNewElemStudyRecord->LinkEndChild(pNewElemStudy_PersonCount);
		
		TiXmlElement *pNewElemPersonA_Score = new TiXmlElement("PersonA_Score");	
		char PersonA_Score_C[5];
		sprintf(PersonA_Score_C, "%2.1f", info.PersonA_Score);
		TiXmlText *pNewTextPersonA_Score = new TiXmlText(PersonA_Score_C);
		pNewElemPersonA_Score->LinkEndChild(pNewTextPersonA_Score);
		pNewElemStudyRecord->LinkEndChild(pNewElemPersonA_Score);
		
		TiXmlElement *pNewElemUnAnswerCountA = new TiXmlElement("UnAnswerCountA");	
		char UnAnswerCountA_C[5];
		sprintf(UnAnswerCountA_C, "%d", info.UnAnswerCountA);
		TiXmlText *pNewTextUnAnswerCountA = new TiXmlText(UnAnswerCountA_C);
		pNewElemUnAnswerCountA->LinkEndChild(pNewTextUnAnswerCountA);
		pNewElemStudyRecord->LinkEndChild(pNewElemUnAnswerCountA);
		
		
		TiXmlElement *pNewElemRCountA = new TiXmlElement("RCountA");	
		char RCountA_C[5];
		sprintf(RCountA_C, "%d", info.RCountA);
		TiXmlText *pNewTextRCountA = new TiXmlText(RCountA_C);
		pNewElemRCountA->LinkEndChild(pNewTextRCountA);
		pNewElemStudyRecord->LinkEndChild(pNewElemRCountA);
		
		TiXmlElement *pNewElemWCountA = new TiXmlElement("WCountA");	
		char WCountA_C[5];
		sprintf(WCountA_C, "%d", info.WCountA);
		TiXmlText *pNewTextWCountA = new TiXmlText(WCountA_C);
		pNewElemWCountA->LinkEndChild(pNewTextWCountA);
		pNewElemStudyRecord->LinkEndChild(pNewElemWCountA);
		
		TiXmlElement *pNewElemPersonB_Score = new TiXmlElement("PersonB_Score");	
		char PersonB_Score_C[5];
		sprintf(PersonB_Score_C, "%2.1f", info.PersonB_Score);
		TiXmlText *pNewTextPersonB_Score = new TiXmlText(PersonB_Score_C);
		pNewElemPersonB_Score->LinkEndChild(pNewTextPersonB_Score);
		pNewElemStudyRecord->LinkEndChild(pNewElemPersonB_Score);
		
		TiXmlElement *pNewElemUnAnswerCountB = new TiXmlElement("UnAnswerCountB");	
		char UnAnswerCountB_C[5];
		sprintf(UnAnswerCountB_C, "%d", info.UnAnswerCountB);
		TiXmlText *pNewTextUnAnswerCountB = new TiXmlText(UnAnswerCountB_C);
		pNewElemUnAnswerCountB->LinkEndChild(pNewTextUnAnswerCountB);
		pNewElemStudyRecord->LinkEndChild(pNewElemUnAnswerCountB);
		
		
		TiXmlElement *pNewElemRCountB = new TiXmlElement("RCountB");	
		char RCountB_C[5];
		sprintf(RCountB_C, "%d", info.RCountB);
		TiXmlText *pNewTextRCountB = new TiXmlText(RCountB_C);
		pNewElemRCountB->LinkEndChild(pNewTextRCountB);
		pNewElemStudyRecord->LinkEndChild(pNewElemRCountB);
		
		TiXmlElement *pNewElemWCountB = new TiXmlElement("WCountB");	
		char WCountB_C[5];
		sprintf(WCountB_C, "%d", info.WCountB);
		TiXmlText *pNewTextWCountB = new TiXmlText(WCountB_C);
		pNewElemWCountB->LinkEndChild(pNewTextWCountB);
		pNewElemStudyRecord->LinkEndChild(pNewElemWCountB);
		
		
		//pLastBookElem->LinkEndChild(pNewElemNotif);//adding it to the LastBookElem
		pRootElement->LinkEndChild(pNewElemStudyRecord);//adding it to the LastBookElem
		pLastBookElem = pNewElemStudyRecord;
		printf("[%s:%d]:%s()- #### - !!\n",__FILE__,__LINE__,__func__);
		if(myDocument == NULL)
		{
			perror("myDocument == NULL");	
			return -1;
		}
		
		myDocument->SaveFile();
		//lastID = newid
		return 0;
	}
	else
	    return -1;
}
