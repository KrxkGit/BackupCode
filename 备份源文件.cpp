// ����Դ�ļ�.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "����Դ�ļ�.h"


// ȫ�ֱ���: 
#define WM_COMPLETE WM_APP+1					//���
HINSTANCE hInst;								// ��ǰʵ��
volatile LONG Count = 0;
HWND hMainDlg = NULL;
BOOL bMulti = FALSE;//ѡ��ȫ����Ŀ��


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO:  �ڴ˷��ô��롣
	

	hInst = hInstance;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, MainDlg);
	return 0;
}

VOID OnInit(HWND hDlg)
{
	::hMainDlg = hDlg;
	SendMessage(hDlg, WM_SETICON, 0, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_MY)));

	//TCHAR sz[MAX_PATH];

	HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	ComboBox_AddString(hCombo, _T("ȫ����Ŀ"));

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(_T("*.*"), &fd);
	for (BOOL b = TRUE; b; b = FindNextFile(hFind, &fd)) {
		if (fd.cFileName[0] != _T('.')) {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {//Ŀ¼
				//����Ƿ�ΪVisual Studio��Ŀ
				//wsprintf(sz, _T("%s\\%s.sln"), fd.cFileName, fd.cFileName);//���ǵ�Latex��������ͳһ�������

				//if (GetFileAttributes(sz) == INVALID_FILE_ATTRIBUTES) {//����Ŀ
				//	continue;
				//}
				ComboBox_AddString(hCombo, fd.cFileName);
			}
		}
	}
	FindClose(hFind);
	ComboBox_SetCurSel(hCombo, 0);//Ĭ��ѡ��
}

VOID DoDelete(LPCTSTR sz)
{
	TCHAR szNew[MAX_PATH];
	wsprintf(szNew, _T("/c del %s\\*.log"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.aux"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.dvi"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.lof"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.lot"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.bit"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.idx"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.glo"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.bbl"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.bcf"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.ilg"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.toc"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.ind"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.out"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.blg"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.fdb_latexmk"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.fls"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);

	wsprintf(szNew, _T("/c del %s\\*.run.xml"), sz);
	ShellExecute(NULL, _T("open"), _T("cmd"), szNew, 0, SW_HIDE);
}

VOID NTAPI DoBackup(PTP_CALLBACK_INSTANCE pInstance,PVOID Context)
{
	LPTSTR szNew = (LPTSTR)Context;
	LPTSTR pOpenDirect = NULL;//��������Ŀ¼
	TCHAR szDirect[MAX_PATH];
	GetCurrentDirectory(_countof(szDirect), szDirect);

	_tcscat_s(szDirect, _countof(szDirect), _T("\\"));
	_tcscat_s(szDirect, _countof(szDirect), szNew);

	//ѡ������ɺ��Զ���Ŀ¼
	if (!bMulti) {
		pOpenDirect = new TCHAR[MAX_PATH];
		_tcscpy_s(pOpenDirect, MAX_PATH, szDirect);
		_tcscat_s(pOpenDirect, MAX_PATH, _T("\\"));
	}
	/*****Backup****/
	DoDelete(szDirect);//ɾ��
	
	InterlockedDecrement(&Count);
	SendMessage(hMainDlg, WM_COMPLETE, 0, 0);

	delete[]szNew;
	if (!bMulti) {
		ShellExecute(NULL, _T("open"), pOpenDirect, 0, 0, SW_NORMAL);
		delete[]pOpenDirect;
	}
}

VOID OnBackup(HWND hDlg)//������Ӧ
{
	__try {
		bMulti = FALSE;
		LPTSTR szNew = new TCHAR[MAX_PATH];
		HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
		ComboBox_GetText(hCombo, szNew, MAX_PATH);
		if (lstrcmp(_T("ȫ����Ŀ"), szNew) == 0) {
			bMulti = TRUE;//���ȫ����Ŀ
			//ͳ��
			InterlockedExchange(&Count, ComboBox_GetCount(hCombo) - 1);
			wsprintf(szNew, _T("��ʼ����[%d]"), Count);
			SetDlgItemText(hDlg, IDOK, szNew);
			delete[]szNew;

			for (int i = ComboBox_GetCount(hCombo); i - 1; i--) {
				szNew = new TCHAR[MAX_PATH];
				ComboBox_GetLBText(hCombo, i - 1, szNew);
				TrySubmitThreadpoolCallback(DoBackup, szNew, NULL);
			}
		}
		else {
			InterlockedExchange(&Count, 1);
			wsprintf(szNew, _T("��ʼ����[1]"));
			SetDlgItemText(hDlg, IDOK, szNew);
			ComboBox_GetText(hCombo, szNew, MAX_PATH);
			TrySubmitThreadpoolCallback(DoBackup, szNew, NULL);
		}
		Button_Enable(GetDlgItem(hDlg, IDOK), FALSE);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {

	}
}

INT_PTR CALLBACK MainDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		OnInit(hDlg);
		break;
	case WM_COMPLETE:
	{
		TCHAR szNew[MAX_PATH];
		wsprintf(szNew, _T("��ʼ����[%d]"), Count);
		SetDlgItemText(hDlg, IDOK, szNew);
		if (Count<=0) {
			Button_Enable(GetDlgItem(hDlg, IDOK), TRUE);
		}
	}
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE) {
			HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
			ComboBox_SetCurSel(hCombo, ComboBox_GetCurSel(hCombo));
			SendMessage(hDlg, WM_COMMAND, IDOK, 0);
		}
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDOK:
			OnBackup(hDlg);
			break;
		}
	}
	return (INT_PTR)FALSE;
}
