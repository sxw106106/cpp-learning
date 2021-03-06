#include "client.h"
#include <iostream>
 
#define TEST_FIFO "/tmp/client_fifo"
void UTIL_DeleteFile( const char *szFile )
{
	if( unlink( szFile ) == 0 )
	{	
		//UTIL_LogPrint( "deleted \"%s\"\n", szFile );
	}
	else
	{
#ifdef WIN32
		//UTIL_LogPrint( "error deleting \"%s\"\n", szFile );
#else
		//UTIL_LogPrint( "error deleting \"%s\" - %s\n", szFile, strerror( errno ) );
#endif
	}
}

bool UTIL_CheckFile( const char *szFile )
{
	// check if file exists

	FILE *pFile = NULL;

	if( ( pFile = fopen( szFile, "r" ) ) == NULL )
		return false;

	fclose( pFile );

	return true;
}


int client(OpType OT_In, int para1)
//int client(std::string grade , std::string hash)
{
	printf("[%s:%d]:%s()- #### - !!\n",__FILE__,__LINE__,__func__);
	int server_fifo_fd;
	int client_fifo_fd;
	int res;
	
	char client_fifo_name[NAME_SIZE];
	
	MessageClient MC1;
	MC1.client_pid = getpid();
	Message_Book MB;
	Message_Status MS;
	Message_LimitInfo ML;
	
	sprintf(client_fifo_name, CLIENT_FIFO_NAME, MC1.client_pid);

	//if (mkfifo(client_fifo_name, 0777) == -1)
	
//	if(UTIL_CheckFile(SERVER_FIFO_NAME))
//	{
//		UTIL_DeleteFile(TEST_FIFO);
//		cout <<"Delete "<< TEST_FIFO<< endl;
//	}


	if (mkfifo(TEST_FIFO, 0777) == -1)
	{
	    fprintf(stderr, "Sorry, create client fifo failure!\n");
	//    exit(EXIT_FAILURE);
	}
	    //BUG:: Using the following , when server_fifo exist but server has'nt start , it will keep waiting in open
	    //FIXME::use O_NONBLOCK to exit when server hasn't start
	//server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
	server_fifo_fd = open( SERVER_FIFO_NAME, O_WRONLY/*|O_NONBLOCK*/ );
	if (server_fifo_fd == -1)
	{
	    fprintf(stderr, "Sorry, open server fifo failure!\n");
	    exit(EXIT_FAILURE);
	}    
	
// 	int OT = MC1.OT;
// 	OT = Status;
	
	switch(OT_In)
	{
	    case OT_Add:
	    {
		
		MC1.OT = OT_Add;
		printf("\n writing Add \n");
		write(server_fifo_fd, &MC1, sizeof(MC1));
	    }
	    break;
	    case OT_Book:
	    {
		 // the following should be in parameter
	    ////////////////////Construct the Message_Book Begin////////////////////
		
		//Construct the MessageClient		
		
		MC1.OT = OT_Book;		
		MB.MC = MC1;
		
		//Construct the CourseInfo
		CourseInfo CI1;			
		int itask = para1;//static
		
		switch(itask)
		{
			
			
		     case 1:
			strcpy( CI1.Hash, "f745ac66364bb66a4e7051e8f235373ec93e9534");
			strcpy( CI1.Name, "STXD_01");
			strcpy( CI1.ID, "741");
			break;
		     	     
		     case 2:
			strcpy( CI1.Hash, "957126a39ec1cea5c04325183431cfba83db2d8d");
			strcpy( CI1.Name, "STXD_02");
			strcpy( CI1.ID, "742");
			break;

		      case 3:
			strcpy( CI1.Hash, "73122919e0781cd7bbb481101fdcf7c262b6cb56");
			strcpy( CI1.Name, "STXD_03");
			strcpy( CI1.ID, "743");
			break;	

		      case 4:
			strcpy( CI1.Hash, "78b5cfa2ac6fb54b1f4176e5dae21905745a6830");
			strcpy( CI1.Name, "STXD_04");
			strcpy( CI1.ID, "744");
			break;	
     		     
		      case 5:
			strcpy( CI1.Hash, "151a58f0bdeb54f7ac6b0d7a63adfda36aed9f4e");
			strcpy( CI1.Name, "STXD_05");
			strcpy( CI1.ID, "745");
			break;	
     		     
		      case 6:
			strcpy( CI1.Hash, "40a2b55a1e8695ce8deb4be181fe1a93114fdb3f");
			strcpy( CI1.Name, "STXD_06");
			strcpy( CI1.ID, "746");
			break;	
     		     
		      case 7:
			strcpy( CI1.Hash, "31720f59e2fe9ecc28c57cea9de755146bdcf316");
			strcpy( CI1.Name, "STXD_07");
			strcpy( CI1.ID, "747");
			break;	
     		     
		      case 8:
			strcpy( CI1.Hash, "11d60edc23f8e4079b27fa5480d62258e67bd582");
			strcpy( CI1.Name, "STXD_08");
			strcpy( CI1.ID, "748");
			break;	

 		      case 9:
			strcpy( CI1.Hash, "7e99359687762997588bd5f02143d90ea230571c");
			strcpy( CI1.Name, "STXD_09");
			strcpy( CI1.ID, "749");
			break;	
    		     
 		      case 10:
			strcpy( CI1.Hash, "9dc3272d23d52b5618192fe1a70cb8a029683082");
			strcpy( CI1.Name, "STXD_10");
			strcpy( CI1.ID, "750");
			break;	
    		     
 		      case 11:
			strcpy( CI1.Hash, "8eed114349a887d94e83870a4d378a9f9eeeeaf9");
			strcpy( CI1.Name, "STXD_04");
			strcpy( CI1.ID, "751");
			break;	
    		     
 		      case 12:
			strcpy( CI1.Hash, "92a85884dfa175531c67a579f05763811f365664");
			strcpy( CI1.Name, "STXD_04");
			strcpy( CI1.ID, "752");
			break;	
    		     case 23:
			strcpy( CI1.Hash, "cbf2fccb489c05a6e07f6ebc7e9af433c0d1c347");
			strcpy( CI1.Name, "STXD_23");
			strcpy( CI1.ID, "723");
			break;
		
		      default:
			return -1;

		}
		CI1.Grade = 3;				
		//strcpy( CI1.Path, "/tmp/hdd/volumes/HDD/第1阶/unit1");
		strcpy( CI1.Path, "/tmp/hdd/volumes/HDD1/BT/");
		CI1.Level = 1 ;

		MB.CI = CI1;
	
		////////////////////Construct the Message_Book Complete////////////////////
		printf("\n writing Book \n");
		write(server_fifo_fd, &MB, sizeof(MB));
	    }
		break;
		
	case OT_UnBook:
	    {
			
		
		MC1.OT = OT_UnBook;		
		MB.MC = MC1;
		
		//Construct the CourseInfo
		CourseInfo CI1;			
		int itask = para1;//static
		
		switch(itask)
		{
			
		     case 1:
			strcpy( CI1.Hash, "c0a9ac469799ef1f4f042960ecb1278e44dea730");
			strcpy( CI1.Name, "STXD_01");
			strcpy( CI1.ID, "741");
			break;
		     	     
		     case 2:
			strcpy( CI1.Hash, "957126a39ec1cea5c04325183431cfba83db2d8d");
			strcpy( CI1.Name, "STXD_02");
			strcpy( CI1.ID, "742");
			break;

		      case 3:
			strcpy( CI1.Hash, "73122919e0781cd7bbb481101fdcf7c262b6cb56");
			strcpy( CI1.Name, "STXD_03");
			strcpy( CI1.ID, "743");
			break;	

		      case 4:
			strcpy( CI1.Hash, "78b5cfa2ac6fb54b1f4176e5dae21905745a6830");
			strcpy( CI1.Name, "STXD_04");
			strcpy( CI1.ID, "744");
			break;	
     		     
		      case 5:
			strcpy( CI1.Hash, "151a58f0bdeb54f7ac6b0d7a63adfda36aed9f4e");
			strcpy( CI1.Name, "STXD_05");
			strcpy( CI1.ID, "745");
			break;	
     		     
		      case 6:
			strcpy( CI1.Hash, "40a2b55a1e8695ce8deb4be181fe1a93114fdb3f");
			strcpy( CI1.Name, "STXD_06");
			strcpy( CI1.ID, "746");
			break;	
     		     
		      case 7:
			strcpy( CI1.Hash, "31720f59e2fe9ecc28c57cea9de755146bdcf316");
			strcpy( CI1.Name, "STXD_07");
			strcpy( CI1.ID, "747");
			break;	
     		     
		      case 8:
			strcpy( CI1.Hash, "11d60edc23f8e4079b27fa5480d62258e67bd582");
			strcpy( CI1.Name, "STXD_08");
			strcpy( CI1.ID, "748");
			break;	

 		      case 9:
			strcpy( CI1.Hash, "7e99359687762997588bd5f02143d90ea230571c");
			strcpy( CI1.Name, "STXD_09");
			strcpy( CI1.ID, "749");
			break;	
    		     
 		      case 10:
			strcpy( CI1.Hash, "9dc3272d23d52b5618192fe1a70cb8a029683082");
			strcpy( CI1.Name, "STXD_10");
			strcpy( CI1.ID, "750");
			break;	
    		     
 		      case 11:
			strcpy( CI1.Hash, "8eed114349a887d94e83870a4d378a9f9eeeeaf9");
			strcpy( CI1.Name, "STXD_04");
			strcpy( CI1.ID, "751");
			break;	
    		     
 		      case 12:
			strcpy( CI1.Hash, "92a85884dfa175531c67a579f05763811f365664");
			strcpy( CI1.Name, "STXD_04");
			strcpy( CI1.ID, "752");
			break;	
        		
		      default:
			return -1;
		}
		CI1.Grade = 3;				
		//strcpy( CI1.Path, "/tmp/hdd/volumes/HDD/第1阶/unit1");
		strcpy( CI1.Path, "/tmp/hdd/volumes/HDD1/BT/");
		CI1.Level = 1 ;

		MB.CI = CI1;
	
		////////////////////Construct the Message_Book Complete////////////////////
		printf("\n writing UnBook \n");
		write(server_fifo_fd, &MB, sizeof(MB));
	    }
		break;
	    case OT_Status:
	    {
		////////////////////Construct the Message_Status Begin////////////////////
		
		
		MC1.OT = OT_Status;
		MS.MC = MC1;
		JobInfoC JIC1;
		char id[11]={0};
		sprintf(id, "%d" , para1);
		strcpy(JIC1.ID ,id );//this should be the course_id not the task_id		
		printf("JIC1.ID : %s ",JIC1.ID );
		MS.JIC = JIC1;
		printf("MS.JIC.ID : %s ", MS.JIC.ID );
		////////////////////Construct the Message_Status Complete////////////////////
		printf("\nclient is writing Status to server\n");
		write(server_fifo_fd, &MS, sizeof(MS));
	    }
		break;
	    case OT_LimitSpeed:
	    {
		////////////////////Construct the Message_LimitInfo Begin////////////////////
		 
		 
		 MC1.OT = OT_LimitSpeed;
		 ML.MC = MC1;
		 LimitInfo LI1;
		 LI1.DownloadSpeedLimitTo = 20;//20kB/s
		 LI1.UploadSpeedLimitTo = 10;//10kB/s
		 strcpy( LI1.ModuleName , "AV");
		 ML.LI = LI1;
		 
		 ////////////////////Construct the Message_LimitInfo Begin////////////////////
		 printf("\n writing Limit \n");
		 write(server_fifo_fd, &ML, sizeof(Message_LimitInfo));
	    }
		break;
	    default:
		break;	 
	
	}
//	client_fifo_fd = open(client_fifo_name, O_RDONLY);
	client_fifo_fd = open(TEST_FIFO, O_RDONLY);
	if (client_fifo_fd == -1)
	{
	    fprintf(stderr, "Sorry, client fifo open failure!\n");
	    exit(EXIT_FAILURE);
	}

	ResultInfo RI;
	memset( &RI, 0 , sizeof(RI));	
	
	switch(OT_In)
	{
	    case OT_Book:
	    {
		res = read(client_fifo_fd, &RI, sizeof(RI));
		std::cout<< "Result: " << RI.result << endl;
	    }
		break;
	    case OT_Status:
	    {	res = read(client_fifo_fd, &MS, sizeof(Message_Status));
		std::cout << endl<<"******************Receive pid : " << MS.MC.client_pid <<" Percent : " << MS.JIC.Percent << std::endl;
	    }
		break;
	    case OT_LimitSpeed:
	    {
		res = read(client_fifo_fd, &RI, sizeof(RI));
		std::cout<< "Result: " << RI.result << endl;
	    }
		break;
	    default:
	    {
		res = read(client_fifo_fd, &RI, sizeof(RI));
		std::cout<< "Result: " << RI.result << endl;
		
	    }
		break;	 
	
	}
    
// 	if (res > 0)
// 	{
// 	    std::cout << "Receive pid : " << RI.MC.client_pid <<" result : " << RI.result << std::endl;
// 	}

	close(client_fifo_fd);
	close(server_fifo_fd);
	unlink(client_fifo_name);
	printf("[%s:%d]:%s()- #### - !!\n",__FILE__,__LINE__,__func__);
	exit(EXIT_SUCCESS);
	//return SUCCEED;
}

