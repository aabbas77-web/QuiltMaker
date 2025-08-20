//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("QuiltMaker.res");
USEFORM("Main.cpp", FormMain);
USEUNIT("quilt_Messages.cpp");
USEUNIT("api_VecApi.cpp");
USEUNIT("quilt_Strings.cpp");
USEFORM("About.cpp", FormAbout);
//---------------------------------------------------------------------------
#include "api_VecApi.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
        // load vecad.dll
        if(vlStartup()==FALSE)
        {
            MessageDlg("VECAD52.DLL is not found",mtError,TMsgDlgButtons()<<mbOK,0);
            exit(0);
        }
        else
        {
			Application->Initialize();
			Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->Run();
        }
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
