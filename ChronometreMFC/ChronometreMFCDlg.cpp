// ChronometreMFCDlg.cpp : fichier d'impl�mentation
//

#include "stdafx.h"
#include "ChronometreMFC.h"
#include "ChronometreMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Bo�te de dialogue CChronometreMFCDlg

CChronometreMFCDlg::CChronometreMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChronometreMFCDlg::IDD, pParent)
	, v_parcours(NULL)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChronometreMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST3, m_listBox);
    DDX_Control(pDX, IDC_STATIC0, m_sText);
    DDX_Control(pDX, IDC_BUTTON1, m_bRestart);
    DDX_Control(pDX, IDC_BUTTON2, m_bStop);
    DDX_Control(pDX, IDC_BUTTON3, m_bStart);
    DDX_Control(pDX, IDC_BUTTON4, m_bTour);
}

BEGIN_MESSAGE_MAP(CChronometreMFCDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CChronometreMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CChronometreMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CChronometreMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CChronometreMFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Gestionnaires de messages pour CChronometreMFCDlg

BOOL CChronometreMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// D�finir l'ic�ne de cette bo�te de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fen�tre principale de l'application n'est pas une bo�te de dialogue
	SetIcon(m_hIcon, TRUE);			// D�finir une grande ic�ne
	SetIcon(m_hIcon, FALSE);		// D�finir une petite ic�ne

	// TODO�: ajoutez ici une initialisation suppl�mentaire
	
	return TRUE;  // retourne TRUE, sauf si vous avez d�fini le focus sur un contr�le
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CChronometreMFCDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_CHRONOMETREMFC_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_CHRONOMETREMFC_DIALOG));
	}
}
#endif



// Bouton Restart
void CChronometreMFCDlg::OnBnClickedButton1()
{
	v_parcours->stop();
	v_parcours = new Parcours();
	CChronometreMFCDlg::maxtour = FALSE;
	m_listBox.ResetContent();

	
	// on affiche le boutton restart
	m_bRestart.ShowWindow(FALSE);
	
	// on blocker le bouton start
	m_bStart.EnableWindow(TRUE);
	
	// on deblocker le bouton stop
	m_bStop.EnableWindow(FALSE);

	
	// on deblocker le bouton tour
	m_bTour.EnableWindow(FALSE);
	
	doUpdate();
	UpdateData(FALSE);
	//TODO affiache h dans 1 champ avec conditionnel
}


// Boutton STOP
void CChronometreMFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if(v_parcours == NULL)
		v_parcours = new Parcours();
	v_parcours->stop();

	
	// on deblocker le bouton start
	m_bStart.EnableWindow(TRUE);
	
	// on blocker le bouton stop
	m_bStop.EnableWindow(FALSE);
	
	// on blocker le bouton tour
	m_bTour.EnableWindow(FALSE);
	
	doUpdate();
	UpdateData(FALSE);
}

// Boutton START
void CChronometreMFCDlg::OnBnClickedButton3()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contr�le
	
	// creer le thread chronom�tre initilialis� aux valeurs 
	if(v_parcours == NULL)
		v_parcours = new Parcours();
	v_parcours->start();
	CChronometreMFCDlg::maxtour = FALSE;


	// on affiche le boutton restart
	m_bRestart.ShowWindow(SW_SHOW);
	
	// on blocker le bouton start
	m_bStart.EnableWindow(FALSE);
	
	// on deblocker le bouton stop
	m_bStop.EnableWindow(TRUE);

	
	// on deblocker le bouton tour
	m_bTour.EnableWindow(TRUE);
	doUpdate();
	UpdateData(FALSE);
}

void CChronometreMFCDlg::doUpdate()
{
	Chronometre* v_chrono = v_parcours->getChronometre();
	if (v_chrono!=NULL) {	
		wstring str;
		string time = v_chrono->getCurrentTime()->formatShort();
		str.assign(time.begin(), time.end());
		m_sText.SetWindowText(str.c_str());
	} 
}
//Bouton tour
void CChronometreMFCDlg::OnBnClickedButton4()
{
	doUpdate();
	v_parcours->tour();
	wstring str;
	string etape = v_parcours->getLastEtape();
	str.assign(etape.begin(), etape.end());
	if(v_parcours->getNbTours() <= Parcours::getMaxTours() && !CChronometreMFCDlg::maxtour){
		m_listBox.InsertString(0,str.c_str());
		CChronometreMFCDlg::maxtour = v_parcours->getNbTours() == Parcours::getMaxTours();
	}else{
		m_listBox.DeleteString(0);
		m_listBox.InsertString(0,str.c_str());
	}
	UpdateData(FALSE);
}
