#include "StdAfx.h"
#include "CDuiMenu.h"

namespace DuiLib
{
    CDuiMenu::CDuiMenu( CControlUI *pCcontrol, LPCTSTR pszXMLPath )
        : m_pControl( pCcontrol )
        , m_strXMLPath(pszXMLPath)
    {
    }

    /*virtual */CDuiMenu::~CDuiMenu()
    {

    }

    /*virtual */void CDuiMenu::Init( HWND hWndParent, POINT ptPos )
    {
        Create( hWndParent, _T( "MenuWnd" ), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
        ::ClientToScreen( hWndParent, &ptPos );
        ::SetWindowPos( *this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
    }

    /*virtual */CDuiString CDuiMenu::GetSkinFolder()
    {
        return _T( "" );
    }

    /*virtual */CDuiString CDuiMenu::GetSkinFile()
    {
        return m_strXMLPath;
    }

    /*virtual */LPCTSTR CDuiMenu::GetWindowClassName( void ) const
    {
        return _T( "CDuiMenu" );
    }

    /*virtual */void CDuiMenu::OnFinalMessage( HWND hWnd )
    {
        delete this;
        return;
    }

    /*virtual */LRESULT CDuiMenu::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
    {
        LRESULT lRes = 0;
        BOOL bHandled = FALSE;
        bool bHandled2 = false;

        switch ( uMsg )
        {
            case WM_KILLFOCUS:
                lRes = OnKillFocus( uMsg, wParam, lParam, bHandled ); 
                break;
            case WM_KEYDOWN:
                lRes = OnKeyDown( uMsg, wParam, lParam, bHandled );
                break;
            case WM_MOUSEWHEEL:
                bHandled = TRUE;
                break;
            default:
                break;
        }

        if ( ( TRUE != bHandled ) && m_PaintManager.MessageHandler( uMsg, wParam, lParam, lRes ) )
        {
            return lRes;
        }

        if ( TRUE == bHandled )
        {
            return 0;
        }

        return __super::HandleMessage( uMsg, wParam, lParam);
    }

    /*virtual */LRESULT CDuiMenu::OnKillFocus( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
    {
        Close();
        bHandled = TRUE;
        return 0;
    }

    /*virtual */LRESULT CDuiMenu::OnKeyDown( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
    {
        if ( VK_ESCAPE == wParam )
        {
            Close();
            bHandled = TRUE;
        }
        return 0;
    }
}