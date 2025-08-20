//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.hpp>
#include <math.h>
#include <stdio.h>
#pragma hdrstop

#include "Main.h"
#include "api_VecApi.h"
#include "quilt_Messages.h"
#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
const int ALISOFT_REG_CODE_5_2 = 330001309;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SolveEllipse(TPoint Start,TPoint End,TPoint Center,TPoint &Radius)
{
	double Sx,Sy,Ex,Ey,Tx,Ty;
    double MakamX,MakamY;
    double ValueX,ValueY;
    Sx = Start.x;
    Sy = Start.y;
    Ex = End.x;
    Ey = End.y;
    Tx = Center.x;
    Ty = Center.y;

    MakamX = 2*Ey*Ty-Ey*Ey+Sy*Sy-2*Sy*Ty;
    MakamY = -Ex*Ex+2*Ex*Tx+Sx*Sx-2*Sx*Tx;
    ValueX = -(-
		Ex*Ex*Sy*Sy+2*Ex*Ex*Sy*Ty-Ex*Ex*Ty*Ty+Sx*Sx*Ty*Ty+2*Ex*Tx*Sy*Sy-
		4*Ex*Tx*Sy*Ty+2*Ex*Tx*Ty*Ty-2*Ey*Ey*Sx*Tx-
		Tx*Tx*Sy*Sy+2*Tx*Tx*Sy*Ty+Ey*Ey*Sx*Sx-2*Tx*Tx*Ey*Ty+Tx*Tx*Ey*Ey-
		2*Ey*Ty*Sx*Sx+4*Ey*Ty*Sx*Tx-2*Sx*Tx*Ty*Ty);
    ValueY = (-
		Ex*Ex*Sy*Sy+2*Ex*Ex*Sy*Ty-Ex*Ex*Ty*Ty+Sx*Sx*Ty*Ty+2*Ex*Tx*Sy*Sy-
		4*Ex*Tx*Sy*Ty+2*Ex*Tx*Ty*Ty-2*Ey*Ey*Sx*Tx-
		Tx*Tx*Sy*Sy+2*Tx*Tx*Sy*Ty+Ey*Ey*Sx*Sx-2*Tx*Tx*Ey*Ty+Tx*Tx*Ey*Ey-
		2*Ey*Ty*Sx*Sx+4*Ey*Ty*Sx*Tx-2*Sx*Tx*Ty*Ty); 

    Radius.x = 0;
    Radius.y = 0;

    if((MakamX <= 0.0) || (MakamY <= 0.0) || (ValueX <= 0.0) || (ValueY <= 0.0))
    {
	    Radius.x = sqrt((Sx-Tx)*(Sx-Tx)+(Sy-Ty)*(Sy-Ty));
    	Radius.y = Radius.x;
        return;
    }

    if((MakamX != 0.0) && (MakamY != 0.0))
    {
	    if(ValueX/MakamX >= 0.0)
        {
        	Radius.x = sqrt(ValueX/MakamX);
        }
	    if(ValueY/MakamY >= 0.0)
        {
        	Radius.y = sqrt(ValueY/MakamY);
        }
        return;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::LoadQuiltingFile(AnsiString strFileName)
{
	try
    {
        TStringList *m_pList;
        try
        {
            m_pList = new TStringList();

            m_pList->LoadFromFile(strFileName);
            for(int i=0;i<m_pList->Count;)
            {
                if(m_pList->Strings[i] == "")
                {
                    m_pList->Delete(i);
                }
                else
                {
                    i++;
                }
            }

            QuiltingFile.clear();
            AnsiString strText;
            ql_Stitch QuiltingStitch;
            int nPos;
            for(int i=0;i<m_pList->Count;i++)
            {
                strText = m_pList->Strings[i].Trim();

                // Type
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.Type = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // X1
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.Start.x = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // Y1
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.Start.y = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // X2
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.End.x = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // Y2
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.End.y = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // X3
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.Center.x = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // Y3
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.Center.y = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // Direction
                nPos = strText.Pos(' ');
                if(nPos < 0)	break;
                QuiltingStitch.Direction = StrToInt(strText.SubString(1,nPos-1));
                strText.Delete(1,nPos);

                // Speed
                QuiltingStitch.Speed = StrToInt(strText);

                QuiltingFile.push_back(QuiltingStitch);
            }
        }
        __finally
        {
	        if(m_pList)
    	    {
        	    delete m_pList;
            	m_pList = NULL;
	        }
        }
        return true;
    }
    catch(...)
    {
		MessageDlg(c_strErrorInOpenQuiltingFile,mtError,TMsgDlgButtons()<<mbOK,0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::SaveQuiltingFileAsDAT(AnsiString strFileName)
{
	try
    {
        TStringList *m_pList;
        try
        {
            m_pList = new TStringList();
            ql_Stitch QuiltingStitch;
            AnsiString strText;
            int nCount = QuiltingFile.size();
            if(nCount <= 0)	return false;

            QuiltingStitch = QuiltingFile[nCount-1];
            if(QuiltingStitch.Type != stEof)
            {
				QuiltingStitch.Type = stEof;
                QuiltingStitch.Start = QuiltingStitch.End;
                QuiltingStitch.End = Point(0,0);
                QuiltingStitch.Center = Point(0,0);
                QuiltingStitch.Direction = 0;
                QuiltingStitch.Speed = 0;
                QuiltingFile.push_back(QuiltingStitch);
            }

            for(int i=0;i<QuiltingFile.size();i++)
            {
             	QuiltingStitch = QuiltingFile[i];

                strText = IntToStr(QuiltingStitch.Type);
                strText += " ";
                strText += IntToStr(QuiltingStitch.Start.x);
                strText += " ";
                strText += IntToStr(QuiltingStitch.Start.y);
                strText += " ";
                strText += IntToStr(QuiltingStitch.End.x);
                strText += " ";
                strText += IntToStr(QuiltingStitch.End.y);
                strText += " ";
                strText += IntToStr(QuiltingStitch.Center.x);
                strText += " ";
                strText += IntToStr(QuiltingStitch.Center.y);
                strText += " ";
                strText += IntToStr(QuiltingStitch.Direction);
                strText += " ";
                strText += IntToStr(QuiltingStitch.Speed);

                m_pList->Add(strText);
            }
        }
        __finally
        {
	        if(m_pList)
    	    {
            	m_pList->SaveToFile(strFileName);
        	    delete m_pList;
            	m_pList = NULL;
	        }
        }
        return true;
    }
    catch(...)
    {
		MessageDlg(c_strErrorInSaveQuiltingFile,mtError,TMsgDlgButtons()<<mbOK,0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::SaveQuiltingFileAsQLT(AnsiString strFileName)
{
	try
    {
    	FILE *file;
        try
        {
            ql_Stitch QuiltingStitch;
            int nCount = QuiltingFile.size();
            if(nCount <= 0)	return false;

            QuiltingStitch = QuiltingFile[nCount-1];
            if(QuiltingStitch.Type != stEof)
            {
				QuiltingStitch.Type = stEof;
                QuiltingStitch.Start = QuiltingStitch.End;
                QuiltingStitch.End = Point(0,0);
                QuiltingStitch.Center = Point(0,0);
                QuiltingStitch.Direction = 0;
                QuiltingStitch.Speed = 0;
                QuiltingFile.push_back(QuiltingStitch);
            }

            file=fopen(strFileName.c_str(),"wb");
    		fwrite(&nCount,sizeof(int),1,file);
            for(int i=0;i<QuiltingFile.size();i++)
            {
             	QuiltingStitch = QuiltingFile[i];
    			fwrite(&QuiltingStitch,sizeof(ql_Stitch),1,file);
            }
        }
        __finally
        {
    		fclose(file);
        }
        return true;
    }
    catch(...)
    {
		MessageDlg(c_strErrorInSaveQuiltingFile,mtError,TMsgDlgButtons()<<mbOK,0);
        return false;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::OpenQuiltingFileAsQLT(AnsiString strFileName)
{
	try
    {
    	FILE *file;
        try
        {
            ql_Stitch QuiltingStitch;
            int nCount;
            QuiltingFile.clear();
            file=fopen(strFileName.c_str(),"rb");
    		fread(&nCount,sizeof(int),1,file);
            for(int i=0;i<nCount;i++)
            {
    			fread(&QuiltingStitch,sizeof(ql_Stitch),1,file);
             	QuiltingFile.push_back(QuiltingStitch);
            }
        }
        __finally
        {
    		fclose(file);
        }
        return true;
    }
    catch(...)
    {
		MessageDlg(c_strErrorInOpenQuiltingFile,mtError,TMsgDlgButtons()<<mbOK,0);
        return false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::NewDocument(AnsiString strFileName)
{
    if(TheEnd) return;

    int DocIndex = vlFileNew(ghwVec,"");
    vlPropPut(VD_DWG_FILENAME,DocIndex,strFileName.c_str());
    ListBoxOpenedFiles->Items->AddObject(ExtractFileName(strFileName),(TObject *)DocIndex);

    // Background Color
//    vlPropPutInt(VD_DWG_COLPAGE,-1,0x00C0DCC0);

    // Grid Color
//    vlPropPutInt(VD_GRID_COLOR,-1,clNavy);
//    vlPropPutInt(VD_GRID_BCOLOR,-1,clNavy);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenDATFile(AnsiString strFileName)
{
    if(!LoadQuiltingFile(strFileName))	return;
    DrawQuiltingFile(strFileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawQuiltingFile(AnsiString strFileName)
{
    Caption = c_strDemo+" "+c_strQuiltMaker+" ["+strFileName+"]";
	NewDocument(strFileName);
    
    // Add Dot Line Style
//    m_nDotLineStyleIndex = vlStLineAdd("DotLineStyle","0, -100, 0, -100");

    ql_Stitch QuiltingStitch;
    int nObjIndex;
	for(UINT i=0;i<QuiltingFile.size();i++)
    {
		QuiltingStitch = QuiltingFile[i];
        switch(QuiltingStitch.Type)
        {
         	case stEof:// End Of File
            {
             	break;
            }
         	case stContinousLine:// Continous Line
            {
//    			m_nSoildLineStyleIndex = vlStLineIndex("Solid",0);
//            	vlStLineActive(m_nSoildLineStyleIndex);
				nObjIndex = vlAddLine(QuiltingStitch.Start.x,QuiltingStitch.Start.y,QuiltingStitch.End.x,QuiltingStitch.End.y);
                vlPropPutInt(VD_ENT_COLOR,nObjIndex,clBlack);
             	break;
            }
         	case stContinousArc:// Continous Arc
            {
                TPoint Radius;
                double Xcen, Ycen, RadH, RadV, Ang0, AngArc, AngRot;
                TPoint Start,End;
                double t;

            	SolveEllipse(QuiltingStitch.Start,QuiltingStitch.End,QuiltingStitch.Center,Radius);

//    			m_nSoildLineStyleIndex = vlStLineIndex("Solid",0);
//            	vlStLineActive(m_nSoildLineStyleIndex);

                if(!QuiltingStitch.Direction)
                {
	                Start = QuiltingStitch.Start;
	                End = QuiltingStitch.End;
                }
                else
				{
	                Start = QuiltingStitch.End;
	                End = QuiltingStitch.Start;
				}
                Xcen = QuiltingStitch.Center.x;
                Ycen = QuiltingStitch.Center.y;
                RadH = Radius.x;
                RadV = Radius.y;

                if(Start.x - QuiltingStitch.Center.x != 0.0)
	                Ang0 = int(360.0+RadToDeg(ArcTan2(Radius.x*(Start.y - QuiltingStitch.Center.y),Radius.y*(Start.x - QuiltingStitch.Center.x)))) % 360;
                else
                {
					if(Start.y - QuiltingStitch.Center.y >= 0.0)
		                Ang0 = int(360.0 + 90.0) % 360;
                    else
		                Ang0 = int(360.0 - 90.0) % 360;
                }

                if(End.x - QuiltingStitch.Center.x != 0.0)
	                t = int(360.0+RadToDeg(ArcTan2(Radius.x*(End.y - QuiltingStitch.Center.y),Radius.y*(End.x - QuiltingStitch.Center.x)))) % 360;
                else
                {
					if(End.y - QuiltingStitch.Center.y >= 0.0)
		                t = int(360.0 + 90.0) % 360;
                    else
		                t = int(360.0 - 90.0) % 360;
                }

                AngArc = int(360.0 + t - Ang0) % 360;
                nObjIndex = vlAddArcEx(Xcen, Ycen, RadH, RadV, Ang0, AngArc, 0);
                vlPropPutInt(VD_ENT_COLOR,nObjIndex,clBlack);
             	break;
            }
         	case stDiscreteLine:// Discrete Line
            {
//    			m_nDotLineStyleIndex = vlStLineIndex("DotLineStyle",0);
//            	vlStLineActive(m_nDotLineStyleIndex);
				nObjIndex = vlAddLine(QuiltingStitch.Start.x,QuiltingStitch.Start.y,QuiltingStitch.End.x,QuiltingStitch.End.y);
                vlPropPutInt(VD_ENT_COLOR,nObjIndex,clBlue);
             	break;
            }
        }
    }

    // Show All
    vlZoom(VL_ZOOM_ALL);
    vlUpdate();
    vlExecute(VC_ZOOM_ALL);
    vlUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ExtractLayers(ql_Layers &Layers)
{
    Layers.clear();
    if(TheEnd) return;

    int LayersCount;
    int EntitiesCount;
    int DocIndex;
    int LayerIndex;
    bool EntityVisible;
    bool EntityDeleted;
    int LayerEntitiesCount;
    bool LayerVisible;
    bool LayerPrint;

    LayersCount=vlLayerCount();
    Layers.resize(LayersCount);

    DocIndex=vlDocGetActive();
    EntitiesCount=vlPropGetInt(VD_DWG_N_ENT,DocIndex);
    for(int EntityIndex=0;EntityIndex<EntitiesCount;EntityIndex++)
    {
        LayerIndex=vlPropGetInt(VD_ENT_LAYER,EntityIndex);
        LayerVisible=vlPropGetInt(VD_LAYER_VISIBLE,LayerIndex);
        LayerPrint=!vlPropGetInt(VD_LAYER_NOPRINT,LayerIndex);
        LayerEntitiesCount=vlPropGetInt(VD_LAYER_N_REF,LayerIndex);
        if((LayerEntitiesCount>0) && LayerVisible && LayerPrint)
        {
            EntityVisible=vlPropGetInt(VD_ENT_ONSCREEN,EntityIndex);
            EntityDeleted=vlPropGetInt(VD_ENT_DELETED,EntityIndex);
            if(EntityVisible && (!EntityDeleted))
                Layers[LayerIndex].push_back(EntityIndex);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveDATFile(AnsiString strFileName)
{
    if(TheEnd) return;
    ql_Layers Layers;
    ExtractLayers(Layers);

    int LayersCount;
    int EntitiesCount;
    int EntityType;
    AnsiString LayerName;
    int PointsCount;
    double x,y;
    int EntColor;
    int LayerIndex;
    double Param;
    int EntityIndex;
    ql_Stitch QuiltingStitch;

    // Start Export
    QuiltingFile.clear();
    LayersCount=Layers.size();
    for(int LayerIndex=0;LayerIndex<LayersCount;LayerIndex++)
    {
        EntitiesCount=Layers[LayerIndex].size();
        if(EntitiesCount<=0)    continue;

        for(int k=0;k<EntitiesCount;k++)
        {
            EntityIndex = Layers[LayerIndex][k];
            EntityType = vlPropGetInt(VD_ENT_TYPE,EntityIndex);
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                {
                    EntColor = vlPropGetInt(VD_ENT_COLOR,EntityIndex);
                    if(EntColor == clBlack)
	                    QuiltingStitch.Type = stContinousLine;
                    else
	                    QuiltingStitch.Type = stDiscreteLine;

                    PointsCount = vlPropGetInt(VD_POLY_N_VER,EntityIndex);

                    vlPolyVerGet(EntityIndex,0,&x,&y,&Param);
                    QuiltingStitch.Start = Point(Round(x),Round(y));
                    QuiltingStitch.Center = Point(0,0);
                    for(int PointIndex=1;PointIndex<PointsCount;PointIndex++)
                    {
                        vlPolyVerGet(EntityIndex,PointIndex,&x,&y,&Param);
                        QuiltingStitch.End = Point(Round(x),Round(y));
                        QuiltingStitch.Direction = 0;
                        QuiltingStitch.Speed = 500;
                        QuiltingFile.push_back(QuiltingStitch);

                    	QuiltingStitch.Start = QuiltingStitch.End;
                    }
                    break;
                }
                case VL_ENT_LINE:// Line
                {
                    EntColor = vlPropGetInt(VD_ENT_COLOR,EntityIndex);
                    if(EntColor == clBlack)
	                    QuiltingStitch.Type = stContinousLine;
                    else
	                    QuiltingStitch.Type = stDiscreteLine;

                    x = vlPropGetDbl(VD_LINE_X1,EntityIndex);
                    y = vlPropGetDbl(VD_LINE_Y1,EntityIndex);
                    QuiltingStitch.Start = Point(Round(x),Round(y));

                    x = vlPropGetDbl(VD_LINE_X2,EntityIndex);
                    y = vlPropGetDbl(VD_LINE_Y2,EntityIndex);
                    QuiltingStitch.End = Point(Round(x),Round(y));

                    QuiltingStitch.Center = Point(0,0);
                    QuiltingStitch.Direction = 0;
                    QuiltingStitch.Speed = 500;

                    QuiltingFile.push_back(QuiltingStitch);
                    QuiltingStitch.Start = QuiltingStitch.End;
                    break;
                }
                case VL_ENT_ARC	:// Arc
                {
                    QuiltingStitch.Type = stContinousArc;

                    x = vlPropGetDbl(VD_ARC_XS,EntityIndex);
                    y = vlPropGetDbl(VD_ARC_YS,EntityIndex);
                    QuiltingStitch.Start = Point(Round(x),Round(y));

                    x = vlPropGetDbl(VD_ARC_XE,EntityIndex);
                    y = vlPropGetDbl(VD_ARC_YE,EntityIndex);
                    QuiltingStitch.End = Point(Round(x),Round(y));

                    x = vlPropGetDbl(VD_ARC_X,EntityIndex);
                    y = vlPropGetDbl(VD_ARC_Y,EntityIndex);
                    QuiltingStitch.Center = Point(Round(x),Round(y));

                    x = vlPropGetDbl(VD_ARC_ANGARC,EntityIndex);
                    QuiltingStitch.Direction = (x>=0)?0:1;

                    QuiltingStitch.Speed = 500;

                    QuiltingFile.push_back(QuiltingStitch);
                    QuiltingStitch.Start = QuiltingStitch.End;
                    break;
                }
            }
        }
    }
	SaveQuiltingFileAsDAT(strFileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height - 30;

    TheEnd=false;

    // Register your copy of Vecad.dll
    vlRegistration(ALISOFT_REG_CODE_5_2);

    // Set message handler function
    vlSetMsgHandler(DwgProc);

    // Create VeCAD StatusBar
    vlStatBarCreate( PanelDisplay->Handle, &SBarH );

    // Create VeCAD window, size will be set in OnSize()
    ghwVec = vlWndCreate( PanelDisplay->Handle, VL_WS_CHILD|VL_WS_SCROLL|VL_WS_BORDER, 0,0,400,300 );
    if(ghwVec)
    {
        ::PostMessage( PanelDisplay->Handle, WM_SIZE, 0, 0 );
        vlPropPut( VD_WND_EMPTYTEXT, (int)ghwVec,(c_strDemo+" "+c_strCompany+" "+c_strQuiltMaker).c_str());
    }

    m_strFileName="Untitled";
    Caption=c_strDemo+" "+c_strQuiltMaker;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PanelDisplayResize(TObject *Sender)
{
    if(TheEnd) return;

    int w, h;
    vlGetWinSize( PanelDisplay->Handle, &w, &h );
    if(w>0 && h>0)
    {
        // Resize drawing window
      	vlWndResize( ghwVec, 0, 0, w, h - SBarH );

        // Resize statusbar
        vlStatBarResize();

        // Update View
        vlZoom(VL_ZOOM_ALL);
        vlUpdate();
        vlExecute(VC_ZOOM_ALL);
        vlUpdate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileNewExecute(TObject *Sender)
{
	NewDocument(c_strUntitledFile);
    Caption = c_strDemo+" "+c_strQuiltMaker+" ["+c_strUntitledFile+"]";
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileOpenExecute(TObject *Sender)
{
	if(OpenDialogQLT->Execute())
    {
    	OpenQuiltingFileAsQLT(OpenDialogQLT->FileName);
        DrawQuiltingFile(OpenDialogQLT->FileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileImportExecute(TObject *Sender)
{
	if(OpenDialogDAT->Execute())
    {
    	OpenDATFile(OpenDialogDAT->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileSaveExecute(TObject *Sender)
{
    int DocIndex = vlDocGetActive();
    char cFileName[256];
    AnsiString strFileName;
    vlPropGet(VD_DWG_PATHNAME,DocIndex,cFileName);
    strFileName = cFileName;
    if(strFileName.UpperCase().Pos(".DAT") > 0)
		SaveDATFile(strFileName);
    else
    if(strFileName.UpperCase().Pos(".QLT") > 0)
		SaveQuiltingFileAsQLT(strFileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileSaveAsExecute(TObject *Sender)
{
	if(SaveDialogQLT->Execute())
    {
		SaveQuiltingFileAsQLT(SaveDialogQLT->FileName);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExportExecute(TObject *Sender)
{
	#ifdef _DEMO_
	MessageDlg(c_strDemoVersionMessage,mtInformation,TMsgDlgButtons()<<mbOK,0);
    #else
	if(SaveDialogDAT->Execute())
    {
		SaveDATFile(SaveDialogDAT->FileName);
    }
    #endif // _DEMO_
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileCloseExecute(TObject *Sender)
{
    int DocIndex = vlDocGetActive();
	int nDocPos = ListBoxOpenedFiles->Items->IndexOfObject((TObject *)DocIndex);
    if(nDocPos < 0)	return;
	ListBoxOpenedFiles->Items->Delete(nDocPos);
	vlExecute(VC_FILE_CLOSE);
    ListBoxOpenedFiles->ItemIndex = 0;
    ListBoxOpenedFilesClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExitExecute(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AZoomExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomAllExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_ALL);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomWindowExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_WIN);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomInExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_IN);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomOutExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_OUT);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APanWindowExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_PAN);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ZoomToPrevExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_PREV);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapDlgExecute(TObject *Sender)
{
	vlExecute(VC_SNAP_DLG);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapGridExecute(TObject *Sender)
{
	ASnapGrid->Checked = !ASnapGrid->Checked;
	vlExecute(VC_SNAP_GRID);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapPolarExecute(TObject *Sender)
{
	ASnapPolar->Checked = !ASnapPolar->Checked;
	vlExecute(VC_SNAP_POLAR);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapGripsExecute(TObject *Sender)
{
	ASnapGrips->Checked = !ASnapGrips->Checked;
	vlExecute(VC_SNAP_GRIPS);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapPointExecute(TObject *Sender)
{
	ASnapPoint->Checked = !ASnapPoint->Checked;
	vlExecute(VC_SNAP_POINT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapNearExecute(TObject *Sender)
{
	ASnapNear->Checked = !ASnapNear->Checked;
	vlExecute(VC_SNAP_NEAR);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapEndExecute(TObject *Sender)
{
	ASnapEnd->Checked = !ASnapEnd->Checked;
	vlExecute(VC_SNAP_END);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapMidExecute(TObject *Sender)
{
	ASnapMid->Checked = !ASnapMid->Checked;
	vlExecute(VC_SNAP_MID);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapCenterExecute(TObject *Sender)
{
	ASnapCenter->Checked = !ASnapCenter->Checked;
	vlExecute(VC_SNAP_CEN);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapPerpendicularExecute(TObject *Sender)
{
	ASnapPerpendicular->Checked = !ASnapPerpendicular->Checked;
	vlExecute(VC_SNAP_PERP);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapTangentExecute(TObject *Sender)
{
	ASnapTangent->Checked = !ASnapTangent->Checked;
	vlExecute(VC_SNAP_TANG);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditEntPropExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_ENTPROP);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditCopyExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_COPY);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditMoveExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_MOVE);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditRotateExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_ROTATE);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditScaleExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_SCALE);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditMirrorExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_MIRROR);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditEraseExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_ERASE);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditUndoExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_UNDO);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditRedoExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_REDO);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditCutCBExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_CBCUT);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditCopyCBExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_CBCOPY);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditPasteCBExecute(TObject *Sender)
{
	vlExecute(VC_EDIT_CBPASTE);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AEditSetJumpExecute(TObject *Sender)
{
	bool First;
	int iEnt, iLayer;
    int EntityType;
	First = true;
	while(true)
    {
	  	if(First)
        {
		    iEnt = vlGetEntity( VL_EI_FIRST, VL_SELECTION, 0 );
		    First = false;
  		}
        else
        {
	    	iEnt = vlGetEntity(VL_EI_NEXT, 0, 0 );
  		}
  		if(iEnt >= 0)
  		{
            EntityType = vlPropGetInt(VD_ENT_TYPE,iEnt);
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                case VL_ENT_LINE:// Line
                {
        			vlPropPutInt(VD_ENT_COLOR,iEnt,clBlue);
                    break;
                }
            }
  		}
        else
        {
    		break;  
  		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditSetNormalExecute(TObject *Sender)
{
	bool First;
	int iEnt, iLayer;
    int EntityType;
	First = true;
	while(true)
    {
	  	if(First)
        {
		    iEnt = vlGetEntity( VL_EI_FIRST, VL_SELECTION, 0 );
		    First = false;
  		}
        else
        {
	    	iEnt = vlGetEntity(VL_EI_NEXT, 0, 0 );
  		}
  		if(iEnt >= 0)
  		{
            EntityType = vlPropGetInt(VD_ENT_TYPE,iEnt);
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                case VL_ENT_LINE:// Line
                {
        			vlPropPutInt(VD_ENT_COLOR,iEnt,clBlack);
                    break;
                }
            }
  		}
        else
        {
    		break;  
  		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpContentsExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpAboutExecute(TObject *Sender)
{
	FormAbout->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListBoxOpenedFilesClick(TObject *Sender)
{
	if(ListBoxOpenedFiles->ItemIndex < 0)	return;
	int DocIndex = int(ListBoxOpenedFiles->Items->Objects[ListBoxOpenedFiles->ItemIndex]);
    vlDocSetActive(DocIndex);
    char cFileName[256];
    vlPropGet(VD_DWG_PATHNAME,DocIndex,cFileName);
    Caption = c_strDemo+" "+c_strQuiltMaker+" ["+AnsiString(cFileName)+"]";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawLineExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_LINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawRectangleExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_RECT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawPolylineExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_POLYLINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcCSEExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_ARC_CSE);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcSEMExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_ARC_SEM);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcSMEExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_ARC_SME);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircleCRExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_CIRC_CR);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircleCDExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_CIRC_CD);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircle2PExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_CIRC_2P);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircle3PExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_CIRC_3P);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawEllipseExecute(TObject *Sender)
{
	vlExecute(VC_DRAW_ELLIPSE);	
}
//---------------------------------------------------------------------------

