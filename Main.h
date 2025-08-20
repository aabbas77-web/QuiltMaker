//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <vector.h>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#define		Round(x)	(((x)-int(x)>=0.5)?int(x)+1:int(x))
//---------------------------------------------------------------------------
#ifdef _DEMO_
const AnsiString c_strDemo =
	"[Demo]";
#else
const AnsiString c_strDemo =
	"";
#endif // _DEMO_
//---------------------------------------------------------------------------
typedef enum{stEof=-1,stContinousLine=0,stContinousArc=1,stDiscreteLine} ql_StitchType;
//---------------------------------------------------------------------------
const AnsiString c_strCompany =
	"AliSoft";
//---------------------------------------------------------------------------
const AnsiString c_strQuiltMaker =
	"QuiltMaker V1.0";
//---------------------------------------------------------------------------
const AnsiString c_strDemoVersionMessage =
	"This Option Exists Only In The Full Version...";
//---------------------------------------------------------------------------
const AnsiString c_strErrorInOpenQuiltingFile =
	"Couldn`t Open Quilting File...";
//---------------------------------------------------------------------------
const AnsiString c_strErrorInSaveQuiltingFile =
	"Couldn`t Save Quilting File...";
//---------------------------------------------------------------------------
const AnsiString c_strUntitledFile =
	"Untitled.qlt";
//---------------------------------------------------------------------------
const int MaxVertexCount=20000;
//---------------------------------------------------------------------------
//----------------------------Quilting---------------------------------------
//---------------------------------------------------------------------------
struct ql_Stitch
{
	int Type;
	TPoint Start;
    TPoint End;
    TPoint Center;
    int Direction;
    int Speed;    
};
//---------------------------------------------------------------------------
typedef vector<ql_Stitch> ql_File; 
//---------------------------------------------------------------------------
typedef vector<int> ql_Entities;
//---------------------------------------------------------------------------
typedef vector<ql_Entities> ql_Layers;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TMainMenu *MainMenu1;
	TAction *AFile;
	TAction *AFileOpen;
	TAction *AFileSave;
	TAction *AFileSaveAs;
	TAction *AFileExit;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *N1;
	TMenuItem *Save1;
	TMenuItem *SaveAs1;
	TMenuItem *Exit1;
	TOpenDialog *OpenDialogDAT;
	TSaveDialog *SaveDialogDAT;
	TPanel *PanelDisplay;
	TControlBar *ControlBar1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TImageList *ImageList;
	TAction *AZoom;
	TAction *AZoomAll;
	TAction *AZoomWindow;
	TAction *AZoomIn;
	TAction *AZoomOut;
	TAction *APanWindow;
	TAction *ZoomToPrev;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TStatusBar *StatusBar1;
	TToolBar *ToolBar2;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TAction *AFileNew;
	TToolButton *ToolButton10;
	TMenuItem *New1;
	TMenuItem *Zoom1;
	TMenuItem *ZoomAll1;
	TMenuItem *ZoomWindow1;
	TMenuItem *ZoomIn1;
	TMenuItem *ZoomOut1;
	TMenuItem *PanWindow1;
	TMenuItem *ZoomToPrev1;
	TAction *ASnap;
	TAction *ASnapDlg;
	TAction *ASnapGrid;
	TAction *ASnapPolar;
	TAction *ASnapGrips;
	TAction *ASnapPoint;
	TAction *ASnapNear;
	TAction *ASnapEnd;
	TAction *ASnapMid;
	TAction *ASnapCenter;
	TAction *ASnapPerpendicular;
	TAction *ASnapTangent;
	TToolBar *ToolBar3;
	TToolButton *ToolButton12;
	TToolButton *ToolButton13;
	TToolButton *ToolButton14;
	TToolButton *ToolButton15;
	TToolButton *ToolButton16;
	TToolButton *ToolButton17;
	TToolButton *ToolButton18;
	TToolButton *ToolButton19;
	TToolButton *ToolButton20;
	TToolButton *ToolButton21;
	TMenuItem *Snap1;
	TMenuItem *SnapGrid1;
	TMenuItem *SnapPolar1;
	TMenuItem *SnapGrips1;
	TMenuItem *SnapPoint1;
	TMenuItem *SnapNear1;
	TMenuItem *SnapEnd1;
	TMenuItem *SnapMid1;
	TMenuItem *SnapCenter1;
	TMenuItem *SnapPerpendicular1;
	TMenuItem *SnapTangent1;
	TAction *AEdit;
	TAction *AEditEntProp;
	TAction *AEditCopy;
	TAction *AEditMove;
	TAction *AEditRotate;
	TAction *AEditScale;
	TAction *AEditMirror;
	TAction *AEditErase;
	TAction *AEditUndo;
	TAction *AEditRedo;
	TAction *AEditCutCB;
	TAction *AEditCopyCB;
	TAction *AEditPasteCB;
	TMenuItem *AEdit1;
	TMenuItem *Undo1;
	TMenuItem *Redo1;
	TMenuItem *N3;
	TMenuItem *CutToCB1;
	TMenuItem *CopyToCB1;
	TMenuItem *PasteFromCB1;
	TMenuItem *N4;
	TMenuItem *Properties1;
	TMenuItem *N5;
	TMenuItem *Copy1;
	TMenuItem *Move1;
	TMenuItem *Rotate1;
	TMenuItem *Scale1;
	TMenuItem *Mirror1;
	TMenuItem *N6;
	TMenuItem *Erase1;
	TToolBar *ToolBar4;
	TToolButton *ToolButton11;
	TToolButton *ToolButton22;
	TToolButton *ToolButton23;
	TToolButton *ToolButton24;
	TToolButton *ToolButton25;
	TToolButton *ToolButton26;
	TToolButton *ToolButton27;
	TToolButton *ToolButton28;
	TToolButton *ToolButton29;
	TToolButton *ToolButton30;
	TToolButton *ToolButton31;
	TToolButton *ToolButton32;
	TToolButton *ToolButton33;
	TToolButton *ToolButton34;
	TToolButton *ToolButton35;
	TToolButton *ToolButton36;
	TAction *AHelp;
	TAction *AHelpContents;
	TAction *AHelpAbout;
	TMenuItem *Help1;
	TMenuItem *Contents1;
	TMenuItem *N7;
	TMenuItem *About1;
	TAction *AFileExport;
	TMenuItem *Export1;
	TMenuItem *N8;
	TAction *AFileImport;
	TMenuItem *ExportQuilting1;
	TToolButton *ToolButton37;
	TToolButton *ToolButton38;
	TToolButton *ToolButton39;
	TPanel *PanelFileList;
	TGroupBox *GroupBox1;
	TListBox *ListBoxOpenedFiles;
	TAction *AFileClose;
	TMenuItem *Close1;
	TMenuItem *N2;
	TPopupMenu *PopupMenuFileList;
	TMenuItem *Close2;
	TToolBar *ToolBar5;
	TToolButton *ToolButton40;
	TAction *ADraw;
	TAction *ADrawPolyline;
	TMenuItem *Draw1;
	TMenuItem *ADrawPolyline1;
	TAction *ADrawArcCSE;
	TAction *ADrawArcSEM;
	TAction *ADrawArcSME;
	TAction *ADrawCircleCR;
	TAction *ADrawCircleCD;
	TAction *ADrawCircle2P;
	TAction *ADrawCircle3P;
	TAction *ADrawEllipse;
	TMenuItem *N9;
	TMenuItem *ArcCSE1;
	TMenuItem *ArcSEM1;
	TMenuItem *ArcSME1;
	TMenuItem *N10;
	TMenuItem *Circle2P1;
	TMenuItem *Circle3P1;
	TMenuItem *CircleCD1;
	TMenuItem *CircleCR1;
	TMenuItem *N11;
	TMenuItem *Ellipse1;
	TToolButton *ToolButton41;
	TToolButton *ToolButton42;
	TToolButton *ToolButton43;
	TToolButton *ToolButton44;
	TToolButton *ToolButton45;
	TToolButton *ToolButton46;
	TToolButton *ToolButton47;
	TToolButton *ToolButton48;
	TToolButton *ToolButton49;
	TToolButton *ToolButton50;
	TToolButton *ToolButton51;
	TAction *ADrawLine;
	TAction *ADrawRectangle;
	TAction *AEditSetJump;
	TMenuItem *SetJump1;
	TToolButton *ToolButton52;
	TAction *AEditSetNormal;
	TMenuItem *SetNormal1;
	TToolButton *ToolButton53;
	TSaveDialog *SaveDialogQLT;
	TOpenDialog *OpenDialogQLT;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall AFileExecute(TObject *Sender);
	void __fastcall AFileOpenExecute(TObject *Sender);
	void __fastcall AFileSaveExecute(TObject *Sender);
	void __fastcall AFileSaveAsExecute(TObject *Sender);
	void __fastcall AFileExitExecute(TObject *Sender);
	void __fastcall AZoomExecute(TObject *Sender);
	void __fastcall AZoomAllExecute(TObject *Sender);
	void __fastcall AZoomWindowExecute(TObject *Sender);
	void __fastcall AZoomInExecute(TObject *Sender);
	void __fastcall AZoomOutExecute(TObject *Sender);
	void __fastcall APanWindowExecute(TObject *Sender);
	void __fastcall ZoomToPrevExecute(TObject *Sender);
	void __fastcall AFileNewExecute(TObject *Sender);
	void __fastcall ASnapExecute(TObject *Sender);
	void __fastcall ASnapDlgExecute(TObject *Sender);
	void __fastcall ASnapGridExecute(TObject *Sender);
	void __fastcall ASnapPolarExecute(TObject *Sender);
	void __fastcall ASnapGripsExecute(TObject *Sender);
	void __fastcall ASnapPointExecute(TObject *Sender);
	void __fastcall ASnapNearExecute(TObject *Sender);
	void __fastcall ASnapEndExecute(TObject *Sender);
	void __fastcall ASnapMidExecute(TObject *Sender);
	void __fastcall ASnapCenterExecute(TObject *Sender);
	void __fastcall ASnapPerpendicularExecute(TObject *Sender);
	void __fastcall ASnapTangentExecute(TObject *Sender);
	void __fastcall PanelDisplayResize(TObject *Sender);
	void __fastcall AEditExecute(TObject *Sender);
	void __fastcall AEditEntPropExecute(TObject *Sender);
	void __fastcall AEditCopyExecute(TObject *Sender);
	void __fastcall AEditMoveExecute(TObject *Sender);
	void __fastcall AEditRotateExecute(TObject *Sender);
	void __fastcall AEditScaleExecute(TObject *Sender);
	void __fastcall AEditMirrorExecute(TObject *Sender);
	void __fastcall AEditEraseExecute(TObject *Sender);
	void __fastcall AEditUndoExecute(TObject *Sender);
	void __fastcall AEditRedoExecute(TObject *Sender);
	void __fastcall AEditCutCBExecute(TObject *Sender);
	void __fastcall AEditCopyCBExecute(TObject *Sender);
	void __fastcall AEditPasteCBExecute(TObject *Sender);
	void __fastcall AHelpExecute(TObject *Sender);
	void __fastcall AHelpContentsExecute(TObject *Sender);
	void __fastcall AHelpAboutExecute(TObject *Sender);
	void __fastcall AFileExportExecute(TObject *Sender);
	void __fastcall AFileImportExecute(TObject *Sender);
	void __fastcall ListBoxOpenedFilesClick(TObject *Sender);
	void __fastcall AFileCloseExecute(TObject *Sender);
	void __fastcall ADrawExecute(TObject *Sender);
	void __fastcall ADrawPolylineExecute(TObject *Sender);
	void __fastcall ADrawArcCSEExecute(TObject *Sender);
	void __fastcall ADrawArcSEMExecute(TObject *Sender);
	void __fastcall ADrawArcSMEExecute(TObject *Sender);
	void __fastcall ADrawCircleCRExecute(TObject *Sender);
	void __fastcall ADrawCircleCDExecute(TObject *Sender);
	void __fastcall ADrawCircle2PExecute(TObject *Sender);
	void __fastcall ADrawCircle3PExecute(TObject *Sender);
	void __fastcall ADrawEllipseExecute(TObject *Sender);
	void __fastcall ADrawLineExecute(TObject *Sender);
	void __fastcall ADrawRectangleExecute(TObject *Sender);
	void __fastcall AEditSetJumpExecute(TObject *Sender);
	void __fastcall AEditSetNormalExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall SolveEllipse(TPoint Start,TPoint End,TPoint Center,TPoint &Radius);
	bool __fastcall LoadQuiltingFile(AnsiString strFileName);
	bool __fastcall SaveQuiltingFileAsDAT(AnsiString strFileName);
	bool __fastcall SaveQuiltingFileAsQLT(AnsiString strFileName);
	bool __fastcall OpenQuiltingFileAsQLT(AnsiString strFileName);
	void __fastcall DrawQuiltingFile(AnsiString strFileName);
	void __fastcall NewDocument(AnsiString strFileName);
	void __fastcall OpenDATFile(AnsiString strFileName);
	void __fastcall ExtractLayers(ql_Layers &Layers);
	void __fastcall SaveDATFile(AnsiString strFileName);
    HWND ghwVec;   // VeCAD window to display draw
    int  SBarH;    // height of status bar
    AnsiString m_strFileName;
    bool TheEnd;

    ql_File QuiltingFile;

    int m_nDotLineStyleIndex;
    int m_nSoildLineStyleIndex;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
