#ifndef __FRAME_HPP__
#define __FRAME_HPP__

/*
frame.hpp

����������� ���� (������� ����� ��� FilePanels, FileEditor, FileViewer)

*/

/* Revision: 1.17 02.11.2001 $ */

/*
Modify:
  02.11.2001 SVS
    ! ������������ �������� � GetTypeName() - ����������� const
  04.10.2001 OT
    ! ������ 956 �����
  18.07.2001 OT
    ! VFMenu
  11.07.2001 OT
    ! ������� CtrlAltShift � Manager
  09.07.2001 OT
    - ����������� MacroMode ��� ��������
  23.06.2001 OT
    - ������� �������� "������� �������"
  20.06.2001 tran
    * Refresh* ���� � cpp �� hpp - ������� ����������.
  30.05.2001 OT
    - ��������� ������������� UnlockRefresh()
  26.05.2001 OT
    + ����� ������� - DynamicallyBorn - ����������, ���������� ��� ����������� ��� ������ ������
    + SetDynamicallyBorn() � GetDynamicallyBorn()
    + ����������� ���������� ����������� ������: LockRefreshCount, LockRefresh(),UnlockRefresh(),Refreshable()
  18.05.2001 DJ
    ! ������� SetExitCode() ������ �����������
  15.05.2001 OT
    ! NWZ -> NFZ
  14.05.2001 OT
    ! ����� GetCanLoseFocus() ���� ����������� � ������ �������� �� ���������
  12.05.2001 DJ
    ! ��������� �� OnChangeFocus ������� ��������� ����������
  12.05.2001 DJ
    + IsTopFrame(), GetMacroMode()
  07.05.2001 DJ
    ! �������� ��������������
  06.05.2001 DJ
    ! �������� #include
  05.05.2001 DJ
    created
*/

#include "scrobj.hpp"

class KeyBar;

enum { MODALTYPE_VIRTUAL,
  MODALTYPE_PANELS,
  MODALTYPE_VIEWER,
  MODALTYPE_EDITOR,
  MODALTYPE_DIALOG,
  MODALTYPE_VMENU,
  MODALTYPE_HELP,
  MODALTYPE_USER
};

class Frame: virtual public ScreenObject
{
  friend class Manager;
  private:
//    Frame **ModalStack;
//    int  ModalStackCount, ModalStackSize;
    Frame *FrameToBack;
    Frame *NextModal,*PrevModal;

  protected:
    int  DynamicallyBorn;
    int  CanLoseFocus;
    int  ExitCode;
    int  KeyBarVisible;
    KeyBar *FrameKeyBar;
    int MacroMode;
    int LockRefreshCount;

  public:
    Frame();
    virtual ~Frame();

//    int ProcessKey(int Key);
//    int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent);

    virtual int GetCanLoseFocus(int DynamicMode=FALSE) { return(CanLoseFocus); };
    void SetCanLoseFocus(int Mode) { CanLoseFocus=Mode; };
    int  GetExitCode() { return ExitCode; };
    virtual void SetExitCode(int Code) { ExitCode=Code; };

    virtual BOOL IsFileModified() {return(FALSE);};

    virtual const char *GetTypeName() {return "[FarModal]";};
    virtual int GetTypeAndName(char *Type,char *Name) {return(MODALTYPE_VIRTUAL);};
    virtual int GetType() { return MODALTYPE_VIRTUAL; }

    virtual void OnDestroy();  // ���������� ����� ������������ ����
    virtual void OnCreate() {};   // ���������� ����� ��������� ����
    virtual void OnChangeFocus(int focus); // ���������� ��� ����� ������
    virtual void Refresh() {OnChangeFocus(1);};  // ������ �������������� :)

    void SetKeyBar(KeyBar *FrameKeyBar);
    void UpdateKeyBar();
    virtual void RedrawKeyBar() { Frame::UpdateKeyBar(); };

    /* $ 12.05.2001 DJ */
    int IsTopFrame();
    virtual int GetMacroMode() { return MacroMode; }
    /* DJ $ */
    void Push(Frame* Modalized);
//    bool Pop();
//    Frame *operator[](int Index);
//    int operator[](Frame *ModalFarame);
//    int ModalCount() {return ModalStackCount;}
    void DestroyAllModal();
    void SetDynamicallyBorn(int Born) {DynamicallyBorn=Born;}
    int GetDynamicallyBorn(){return DynamicallyBorn;};
    void LockRefresh();
    void UnlockRefresh();
    int Refreshable();
    virtual int FastHide();
//    int IndexOf(Frame *aFrame);
    bool RemoveModal(Frame *aFrame);
    void ResizeConsole();
    bool HasSaveScreen();
//    bool ifFullConsole();

};

#endif // __FRAME_HPP__
