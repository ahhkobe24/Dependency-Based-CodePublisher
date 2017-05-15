////////////////////////////////////////////////////////////////////////////////
// DependAnal.cpp -  Define a class to generate html files                   //
// Ver 1.0                                                                   //
// Application: CSE687 Pr#2, Spring 2017                                     //
// Platform:    Win 10 Pro, Visual Studio 2015                              //
// Author:      Xia Hua                                                    //
//              xhua02@syr.edu                                            //  
////////////////////////////////////////////////////////////////////////////


#include "Publisher.h"
#include "../Nosqldb/NoSqlDb.h"

#ifdef TEST_DepemdA
int main()
{
		NoSqlDb<intData> idb;
	
		Element<intData> ielem1;
		ielem1.name = "elem1";
		ielem1.category = "test";
		ielem1.data = 1;
	
		idb.saveRecord(ielem1.name, ielem1);
	
		Element<intData> ielem2;
		ielem2.name = "elem2";
		ielem2.category = "test";
		ielem2.data = 2;
	
		idb.saveRecord(ielem2.name, ielem2);
	
		Element<intData> ielem3;
		ielem3.name = "elem3";
		ielem3.category = "test";
		ielem3.data = 3;
	
		idb.saveRecord(ielem3.name, ielem3);
	
		Element<intData> ielem4;
		ielem3.name = "elem4";
		ielem3.category = "test";
		ielem3.data = 4;


		Publisher hg(idb);
		hg.setFiles("../Publisher/Publisher.h");
		hg.constrHtml();

	return 0;
}
#endif