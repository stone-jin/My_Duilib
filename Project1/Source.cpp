#include "UIlib.h"
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma  comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma  comment(lib, "DuiLib.lib")
#   endif
#endif

class mytest : public CDuiMenu
{
public:
    mytest( CControlUI *pCcontrol, LPCTSTR pszXMLPath )
        : CDuiMenu(pCcontrol, pszXMLPath)
    {
    }
    virtual void Notify( TNotifyUI& msg )
    {
        if ( _tcsicmp( msg.sType, _T( "windowInit" ) ) )
        {
            return;
        }
        return __super::Notify(msg);
    }
protected:
private:
};

class QQ : public WindowImplBase
{
public:
    virtual CDuiString GetSkinFolder()
    {
        return _T( "" );
    }

    virtual CDuiString GetSkinFile()
    {
        return _T("1.xml");
    }

    virtual LPCTSTR GetWindowClassName( void ) const
    {
        return _T( "QQ" );
    }

    virtual CControlUI* CreateControl( LPCTSTR pstrClass )
    {
        if (0 == _tcsicmp( pstrClass, _T( "CSliderTabLayoutUI" ) ))
        {
            return new CSliderTabLayoutUI();
        }

        return NULL;
    }

    virtual void Notify( TNotifyUI& msg )
    {
        ULONG ulHandled = 0;
        do 
        {
            if ( 0 == _tcsicmp( msg.sType, _T( "click" ) ) )
            {
                if ( 0 == _tcsicmp( msg.pSender->GetName(), _T( "click" ) ) )
                {
                    mytest* ptest = new mytest( msg.pSender, _T( "2.xml" ) );
                    if ( NULL == ptest )
                    {
                        break;
                    }
                    POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
                    ptest->Init( *this, pt );
                    ulHandled = 1;
                }
            }
            else if ( 0 == _tcsicmp( msg.sType, _T( "selectchanged" ) ) )
            {
                CSliderTabLayoutUI *pSilder = static_cast<CSliderTabLayoutUI *>( m_PaintManager.FindControl( _T( "silder1" ) ) );

                if ( 0 == _tcsicmp( msg.pSender->GetName(), _T( "header1_option1" ) ) )
                {
                    if ( ( NULL != pSilder ) && ( 0 != pSilder->GetCurSel() ) )
                    {
                        pSilder->SelectItem( 0 );
                        ulHandled = 1;
                    }
                }
                else if ( 0 == _tcsicmp( msg.pSender->GetName(), _T( "header1_option2" ) ))
                {
                    if ( ( NULL != pSilder ) && ( 1 != pSilder->GetCurSel() ) )
                    {
                        pSilder->SelectItem( 1 );
                        ulHandled = 1;
                    }
                }
            }
        } while (0);

        if ( 1 == ulHandled )
        {
            return;
        }
        return __super::Notify( msg );
    }
protected:
private:
};

int APIENTRY WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
    CPaintManagerUI::SetInstance( hInstance );
    QQ *pQQ = new QQ();
    pQQ->Create( NULL, _T( "QQ" ), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE );
    pQQ->CenterWindow();
    pQQ->ShowModal();
    return 0;
}