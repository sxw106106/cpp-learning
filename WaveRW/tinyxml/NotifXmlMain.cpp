#include "NotifXml.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc , char** argv)
{
	if(argc<2)
	{
		cout<< "Usage: Version filename" << endl;
		return -1;
	}

	NotifyXml *pNotifyXmlObj = new NotifyXml();
	pNotifyXmlObj->LoadXml(argv[1]);
	
	
	Notif notif;
	notif.Notif_ID = "201208071200005";
	notif.Title = "Titlexx";
	notif.Content = "Cont   e n     \n tx    xx";
	notif.StartTime = "201107071210003";
	notif.EndTime = "201108081330003";
//	notif.Readed = 0;
	cout << pNotifyXmlObj->AddItem(notif) << endl;
	
	
	cout << pNotifyXmlObj->RemoveItem("201108071200004") << endl;
	
	cout << pNotifyXmlObj->GetNoticeListVersion() << endl;
	
	vector<Notif> VN,*pVUN;
	
//	pVUN= pNotifyXmlObj->GetUnReadNotif();
	
	vector <Notif>::iterator iter;
	
	int i =0;
	
	
	cout <<"Read:" << endl;
	VN = *pNotifyXmlObj->GetNotif();
	for( iter = VN.begin(); iter != VN.end(); ++i , ++iter)
	{
	    cout << i<<" " ;
	    cout << (*iter).Notif_ID << "\t" << (*iter).Title << "\t"<< (*iter).Content << "\t"<< (*iter).StartTime << "\t"<< (*iter).EndTime << endl;
	}
	
	/*
	cout <<"UnRead:" << endl;
	i =0;
	for( iter =pVUN->begin(); iter != pVUN->end(); ++i , ++iter)
	{
	    cout << i<<" " ;
	    cout << (*iter).Notif_ID << "\t" << (*iter).Title << "\t"<< (*iter).Content << "\t"<< (*iter).StartTime << "\t"<< (*iter).EndTime << endl;
	}
	*/
	//cout << pNotifyXmlObj->UpdateReaded("201108031215001") << endl;
	//cout << pNotifyXmlObj->UpdateReaded("201108041215002", 0) << endl;
	
	//BUG::Segmentation fault (core dumped)
	
	delete pNotifyXmlObj;
	pNotifyXmlObj = NULL;
	
	return 0;
}
 
