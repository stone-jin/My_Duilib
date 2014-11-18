#ifndef __CDUI_MENU_H__
#define __CDUI_MENU_H__

#pragma once
#include "UIlib.h"

namespace DuiLib
{
    class UILIB_API CDuiMenu :public WindowImplBase
    {
    public:
        CDuiMenu( CControlUI *pCcontrol, LPCTSTR pszXMLPath );
        virtual ~CDuiMenu();
        virtual void Init( HWND hWndParent, POINT ptPos );
        virtual CDuiString GetSkinFolder();
        virtual CDuiString GetSkinFile();
        virtual LPCTSTR GetWindowClassName( void ) const;
        virtual void OnFinalMessage( HWND hWnd );
        virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
        virtual LRESULT OnKillFocus( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled );
        virtual LRESULT OnKeyDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled );
    protected:
    private:
        CDuiString m_strXMLPath;
        CControlUI *m_pControl;
    };
}

#endif
