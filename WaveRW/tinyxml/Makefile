CXX=g++
SRCS=tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp XXml.cpp ../Util.cpp wave.cpp  Convert.cpp  

SRCSVideo+=$(SRCS)
SRCSVideo+=Vxml.cpp VxmlMain.cpp

SRCSL+=$(SRCS)
SRCSL+=Lxml.cpp LxmlMain.cpp 

SRCST+=$(SRCS)
SRCST+=Txml.cpp TxmlMain.cpp

SRCSVersion+=$(SRCS)
SRCSVersion+=VersionXml.cpp VersionXmlMain.cpp

SRCSSetting+=$(SRCS)
SRCSSetting+=SettingXml.cpp SettingXmlMain.cpp

SRCSPartsInfo+=$(SRCS)
SRCSPartsInfo+=PartsInfoXml.cpp PartsInfoXmlMain.cpp

SRCSCourseMainInfo+=$(SRCS)
SRCSCourseMainInfo+=CourseMainInfoXml.cpp CourseMainInfoXmlMain.cpp

SRCSCS+=$(SRCS)
SRCSCS+=CourseStatusXml.cpp CourseStatusXmlMain.cpp

SRCSStudyRecord+=$(SRCS)
SRCSStudyRecord+=StudyRecordXml.cpp StudyRecordXmlMain.cpp

SRCSCGI+=$(SRCS)
SRCSCGI+=CgiXml.cpp CgiXmlMain.cpp

SRCSNot+=$(SRCS)
SRCSNot+=NotifXml.cpp NotifXmlMain.cpp 

OBJS=tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o XXml.o ../Util.o wave.o  Convert.o 



OBJSVideo+=$(OBJS)
OBJSVideo+=Vxml.o VxmlMain.o

OBJSL+=$(OBJS)
OBJSL+=Lxml.o LxmlMain.o 


OBJST+=$(OBJS)
OBJST+=Txml.o TxmlMain.o

OBJSVersion+=$(OBJS)
OBJSVersion+=VersionXml.o VersionXmlMain.o

OBJSSetting+=$(OBJS)
OBJSSetting+=SettingXml.o SettingXmlMain.o

OBJSPartsInfo+=$(OBJS)
OBJSPartsInfo+=PartsInfoXml.o PartsInfoXmlMain.o

OBJSCourseMainInfo+=$(OBJS)
OBJSCourseMainInfo+=CourseMainInfoXml.o CourseMainInfoXmlMain.o

OBJSCS+=$(OBJS)
OBJSCS+=CourseStatusXml.o CourseStatusXmlMain.o

OBJSStudyRecord+=$(OBJS)
OBJSStudyRecord+=StudyRecordXml.o StudyRecordXmlMain.o

OBJSCGI+=$(SRCS)
OBJSCGI+=CgiXml.o CgiXmlMain.o


OBJSNot+=$(OBJS)
OBJSNot+=NotifXml.o NotifXmlMain.o 

PROGRAMVideo=Video

PROGRAML=L

PROGRAMT=TE

PROGRAMVersion=Version

PROGRAMSetting=Setting

PROGRAMPartsInfo=PartsInfo

PROGRAMCourseMainInfo=CourseMainInfo

PROGRAMCourseStatus=CourseStatus

PROGRAMStudyRecord=StudyRecord

PROGRAMCGI=CGI

PROGRAMNot=Not

CFLAG=-o 
CLGAG2= -DPURE_XML_TEST 

all:
	$(CXX) -g  $(SRCSVideo) $(CFLAG) $(PROGRAMVideo)
	$(CXX) -g  $(SRCSL) $(CFLAG) $(PROGRAML)
	$(CXX) -g  $(SRCST) $(CFLAG) $(PROGRAMT)
	$(CXX) -g  $(SRCSVersion) $(CFLAG) $(PROGRAMVersion) 
	$(CXX) -g  $(SRCSSetting) $(CFLAG) $(PROGRAMSetting) 
	$(CXX) -g  $(SRCSPartsInfo) $(CFLAG) $(PROGRAMPartsInfo) 
	$(CXX) -g  $(SRCSCourseMainInfo) $(CFLAG) $(PROGRAMCourseMainInfo) 
	$(CXX) -g  $(SRCSCS) $(CFLAG) $(PROGRAMCourseStatus) 
	$(CXX) -g  $(SRCSStudyRecord) $(CFLAG) $(PROGRAMStudyRecord)
	$(CXX) -g  $(SRCSCGI) $(CFLAG) $(PROGRAMCGI)  
	$(CXX) -g  $(SRCSNot) $(CFLAG) $(PROGRAMNot)   

TE:
	$(CXX) -g  $(SRCST) $(CFLAG) $(PROGRAMT)

VIDEO:
	$(CXX) -g  $(SRCSVideo) $(CFLAG) $(PROGRAMVideo) 

L:
	$(CXX) -g  $(SRCSL)  $(CFLAG) $(PROGRAML) 

VERSION:
	$(CXX) -g  $(SRCSVersion) $(CFLAG) $(PROGRAMVersion) $(CLGAG2)

SR:
	$(CXX) -g  $(SRCSStudyRecord) $(CFLAG) $(PROGRAMStudyRecord) 

ST:
	$(CXX) -g  $(SRCSSetting) $(CFLAG) $(PROGRAMSetting) 

CM:
	$(CXX) -g  $(SRCSCourseMainInfo) $(CFLAG) $(PROGRAMCourseMainInfo) $(CLGAG2)

CS:
	$(CXX) -g  $(SRCSCS) $(CFLAG) $(PROGRAMCourseStatus) 

PI:
	$(CXX) -g  $(SRCSPartsInfo) $(CFLAG) $(PROGRAMPartsInfo) 

CGI:
	$(CXX) -g  $(SRCSCGI) $(CFLAG) $(PROGRAMCGI) 

Not:
	$(CXX) -g  $(SRCSNot) $(CFLAG) $(PROGRAMNot)  $(CFLAG2) 

clean:
	rm $(OBJS) -f
	rm $(OBJSV) -f 
	rm $(OBJSL) -f 
	rm $(OBJSVersion) -f 	
	rm $(OBJSSetting) -f
	rm $(OBJSPartsInfo)  -f
	rm $(OBJSCourseMainInfo) -f
	rm $(OBJSStudyRecord)  -f

	rm $(PROGRAMVersion) -f
	rm $(PROGRAMV) -f 
	rm $(PROGRAML) -f 
	rm $(PROGRAMSetting) -f
	rm $(PROGRAMPartsInfo)  -f
	rm $(PROGRAMCourseMainInfo) -f
	rm $(PROGRAMStudyRecord)  -f
	rm $(PROGRAMCGI)  -f
	rm $(PROGRAMNot)  -f
	rm *~ -f
