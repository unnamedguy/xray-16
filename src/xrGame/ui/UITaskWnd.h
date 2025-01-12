#pragma once
#include "xrUICore/Windows/UIWindow.h"
#include "xrUICore/Callbacks/UIWndCallback.h"
#include "xrCore/Containers/AssociativeVector.hpp"
#include "GameTaskDefs.h"
#include "xrUICore/Buttons/UICheckButton.h"

class CUIMapWnd;
class CUIStatic;
class CGameTask;
class CUIXml;
class CUITaskItem;
class CUI3tButton;
class CUIFrameLineWnd;
class CUIFrameWindow;
class CUICheckButton;
class UITaskListWnd;
class UIMapLegend;
class UIHint;

class CUITaskWnd : public CUIWindow, public CUIWndCallback
{
private:
    typedef CUIWindow inherited;

    CUIFrameWindow* m_background;
    CUIFrameLineWnd* m_background2;

    CUIStatic* m_center_background;
    CUIStatic* m_right_bottom_background;
    CUIFrameLineWnd* m_task_split;

    CUIMapWnd* m_pMapWnd;
    CUITaskItem* m_pStoryLineTaskItem;
    CUITaskItem* m_pSecondaryTaskItem;

    CUI3tButton* m_BtnTaskListWnd;
    CUIStatic* m_second_task_index;
    CUIStatic* m_devider;
    u32 m_actual_frame;

    CUI3tButton* m_btn_focus;
    CUI3tButton* m_btn_focus2;

    CUICheckButton* m_cbTreasures;
    CUICheckButton* m_cbQuestNpcs;
    CUICheckButton* m_cbSecondaryTasks;
    CUICheckButton* m_cbPrimaryObjects;
    bool m_bTreasuresEnabled;
    bool m_bQuestNpcsEnabled;
    bool m_bSecondaryTasksEnabled;
    bool m_bPrimaryObjectsEnabled;

    UITaskListWnd* m_task_wnd;
    bool m_task_wnd_show;
    UIMapLegend* m_map_legend_wnd;

public:
    UIHint* hint_wnd;

public:
    CUITaskWnd(UIHint* hint);
    virtual ~CUITaskWnd();
    virtual void SendMessage(CUIWindow* pWnd, s16 msg, void* pData);
    bool Init();
    virtual void Update();
    virtual void Draw();
    void DrawHint();
    virtual void Show(bool status);
    virtual void Reset();

    void ReloadTaskInfo();
    void ShowMapLegend(bool status) const;
    void Switch_ShowMapLegend() const;

    bool IsTreasuresEnabled() const { return m_bTreasuresEnabled; };
    bool IsQuestNpcsEnabled() const { return m_bQuestNpcsEnabled; };
    bool IsSecondaryTasksEnabled() const { return m_bSecondaryTasksEnabled; };
    bool IsPrimaryObjectsEnabled() const { return m_bPrimaryObjectsEnabled; };
    void TreasuresEnabled(bool enable)
    {
        m_bTreasuresEnabled = enable;
        if (m_cbTreasures)
            m_cbTreasures->SetCheck(enable);
    };
    void QuestNpcsEnabled(bool enable)
    {
        m_bQuestNpcsEnabled = enable;
        if (m_cbQuestNpcs)
            m_cbQuestNpcs->SetCheck(enable);
    };
    void SecondaryTasksEnabled(bool enable)
    {
        m_bSecondaryTasksEnabled = enable;
        if (m_cbSecondaryTasks)
            m_cbSecondaryTasks->SetCheck(enable);
    };
    void PrimaryObjectsEnabled(bool enable)
    {
        m_bPrimaryObjectsEnabled = enable;
        if (m_cbPrimaryObjects)
            m_cbPrimaryObjects->SetCheck(enable);
    };

    void Show_TaskListWnd(bool status);

private:
    void TaskSetTargetMap(CGameTask* task);
    void TaskShowMapSpot(CGameTask* task, bool show) const;

    void OnNextTaskClicked();
    void OnPrevTaskClicked();
    void OnShowTaskListWnd(CUIWindow* w, void* d);
    void OnTask1DbClicked(CUIWindow*, void*);
    void OnTask2DbClicked(CUIWindow*, void*);

    void OnShowTreasures(CUIWindow*, void*);
    void OnShowPrimaryObjects(CUIWindow*, void*);
    void OnShowSecondaryTasks(CUIWindow*, void*);
    void OnShowQuestNpcs(CUIWindow*, void*);
};

class CUITaskItem : public CUIWindow
{
private:
    typedef CUIWindow inherited;

    AssociativeVector<shared_str, CUIStatic*> m_info;
    CGameTask* m_owner;

public:
    CUITaskItem();
    virtual ~CUITaskItem() = default;

    virtual void OnFocusReceive();
    virtual void OnFocusLost();
    virtual void Update();
    virtual void OnMouseScroll(float iDirection);
    virtual bool OnMouseAction(float x, float y, EUIMessages mouse_action);
    virtual void SendMessage(CUIWindow* pWnd, s16 msg, void* pData);

    void Init(CUIXml& uiXml, LPCSTR path);
    void InitTask(CGameTask* task);
    CGameTask* OwnerTask() { return m_owner; }
public:
    bool show_hint_can;
    bool show_hint;

protected:
    u32 m_hint_wt;
};
