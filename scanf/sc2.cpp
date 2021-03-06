#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#include <vector>


struct JobInfo{
		string ID;
		int Priority;
		string Partition;
		string Space;
		string Name;
		string Status;
		double Size;
		double Downloaded;
		string TimeLeft;
		string Percent;
		double DwRate;
		double UpRate;
		int Npeers;
		
		JobInfo()
		{
			ID="";
			Priority=0;
			Partition="";
			Space="";
			Name="";
			Status="";
			Size=0;
			Downloaded=0;
			TimeLeft="";
			Percent="";
			DwRate=0;
			UpRate=0;
			Npeers=0;
		}
	};
int  splitString(const string & strSrc, const std::string& strDelims, vector<string>& strDest)  
{  
        typedef std::string::size_type ST;  
        string delims = strDelims;  
        std::string STR;  
        if(delims.empty()) 
			delims = "\n\r";  
      
        ST pos=0, LEN = strSrc.size();  
        while(pos < LEN )
		{
            STR="";   
            while( (delims.find(strSrc[pos]) != std::string::npos) && (pos < LEN) ) 
				++pos;  
            if(pos==LEN) 
				return strDest.size();  
            while( (delims.find(strSrc[pos]) == std::string::npos) && (pos < LEN) ) 
				STR += strSrc[pos++];  
            //std::cout << "[" << STR << "]";  
            if( ! STR.empty() ) 
				strDest.push_back(STR);
        }
        return strDest.size();  
} 

void printVJ(const vector<JobInfo> &vJI)
{
	printf("vJI.size = %d \n", vJI.size());
	for(vector<JobInfo>::const_iterator  citer= vJI.begin(); citer!=vJI.end();  citer++)
	{
		printf("ID:%-4s  Percent:%4s  DwRate:%6.1f  Downloaded:%3.2f  Status:%-11s  Name:%s \n", citer->ID.c_str(), citer->Percent.c_str(), citer->DwRate,  citer->Downloaded,citer->Status.c_str(), citer->Name.c_str());
	}	
}
int GetVectorJobStatus(vector<JobInfo> &vJI, const char* list_path)
{
	printf("\n ############# GetVectorJobStatus begin ########### \n");
	
	FILE *pf;	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pf = fopen( list_path, "r");
	if( pf == NULL )
		return -1;
	
	vector<string> vstr;
	
	 
	for(int out_index = 0; (read = getline(&line, &len, pf)) != -1 ;out_index++)
	{		
		vstr.clear();
		splitString(line," ",vstr );
	
		int i = 0 ;
		JobInfo ji;
		
		int jump_size = 0;
		for(vector<string>::const_iterator  citer = vstr.begin(); citer != vstr.end();i++, citer++)
		{										
			const char *ci_cstr = (*citer).c_str();
// 			printf("we got : %s\t", (*citer).c_str());
			
			if(0 == i)
			{
				jump_size = 0;
				if(strchr(ci_cstr,'*'))
				{					
					char cid[5];
					memset(cid, 0 , sizeof(cid));
					strncpy(cid, ci_cstr, strlen(ci_cstr)-1);
					ji.ID = cid;
				}
				else
				{	
					ji.ID = (ci_cstr);
				}
				
// 				printf(" ID : %s ", ji.ID.c_str());
				/*if(strchr( ci_cstr,'*')!= NULL)
					ji.errorMark = '*';	*/		
			}
			else if(1 == i)
			{
				ji.Percent = ci_cstr;
// 				printf(" percent: %s ",ci_cstr);
			}
			else if(2 == i)
			{
				if(strncasecmp(ci_cstr, "None",strlen("None")) == 0)
				{
					ji.Downloaded = 0.0;
					jump_size++;
// 					printf(" jump_size = %d ", jump_size );
				}
				else
				{
					ji.Downloaded = atof(ci_cstr);
				}
// 				printf(" Downloaded: %3.2f ",ci_cstr);
			}
			else if((3-jump_size) == i)
			{
				//strncpy(ji.haveUnit , ci_cstr, strlen(ci_cstr));
			}
			else if((4-jump_size) == i)
			{
				//strncpy(ji.etaStr ,ci_cstr, strlen(ci_cstr));		
				char cnum = ci_cstr[0];
				if( cnum >=48  && cnum  <= 57 )//数字
				{					
					jump_size--;
// 					printf(" jump_size = %d  5-jump_size = %d ", jump_size, 5-jump_size);
				}
			}
			else if((5-jump_size) == i)
			{
				ji.UpRate = atof(ci_cstr);				
			}
			else if((6-jump_size) == i)
			{
				ji.DwRate = atof(ci_cstr);	
			}
			else if((7-jump_size) == i)
			{
// 				strncpy(ji.ratioStr , ci_cstr, strlen(ci_cstr));
			}
			else if((8-jump_size) == i)
			{
				ji.Status = ci_cstr;
				printf(" Status ##: %s ",ci_cstr);
				
				if(strstr(ci_cstr , "Up") != NULL || strstr(ci_cstr , "Down") != NULL )
				{
					printf(" Status reset##: Downloading ");
					ji.Status ="Downloading";
				}
			}
			else if((9-jump_size) == i)
			{
				ji.Name = ci_cstr;
				
				if(strchr(ci_cstr, '&') != NULL )
				{
					jump_size = jump_size-2;					
				}
				
				if(strchr(ci_cstr, '\n') != NULL || strchr(ci_cstr, '\r') != NULL)
				{
					printf(" find a return line in name  sub it\n");
					ji.Name = ji.Name.substr(0, ji.Name.size()-1);
				}
				
				
				printf(" Name: %s ",ji.Name.c_str());
			}
		}//for
		if(out_index == 0  )//忽略第一个 header
			continue;
		
		vJI.push_back(ji);				
	
	}//for
	
 	vJI.pop_back();	//忽略最后一个 SUM
	
	printVJ(vJI);
	
	fclose(pf);
	free(line);
	return 0;
}

int main(int argc, char **argv)
{
	if(argc<2)
	{
		printf("sc file\n");
		return -1;
	}
	vector<JobInfo> vJI;
	GetVectorJobStatus(vJI,argv[1]);
}
