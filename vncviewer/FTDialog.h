/* Copyright (C) 2005 TightVNC Team.  All Rights Reserved.
 *    
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
 * TightVNC distribution homepage on the Web: http://www.tightvnc.com/
 *
 */

// -=- FTDialog.h

#ifndef __RFB_WIN32_FTDIALOG_H__
#define __RFB_WIN32_FTDIALOG_H__

#include <windows.h>
#include <commctrl.h>

#include <rfb/FileInfo.h>
#include <vncviewer/FileTransfer.h>
#include <vncviewer/FTListView.h>
#include <vncviewer/FTProgress.h>
#include <vncviewer/resource.h>

namespace rfb {
  namespace win32 {
    class FileTransfer;

    class FTDialog
    {
    public:
      FTDialog(HINSTANCE hInst, FileTransfer *pFT);
      ~FTDialog();
      
      bool createFTDialog(HWND hwndParent);
      bool closeFTDialog();
      void destroyFTDialog();
      
      static BOOL CALLBACK FTDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
      
      void addRemoteLVItems(FileInfo *pFI);
      void reqFolderUnavailable();

      void setStatusText(LPCSTR format,...);

      HWND getWndHandle() { return m_hwndFTDialog; }

      void postCheckTransferQueueMsg();
      void postUploadFilePortionMsg();
      void postDownloadFilePortionMsg();

      FTProgress *m_pProgress;
      
    private:
      FileTransfer *m_pFileTransfer;
      
      HWND m_hwndFTDialog;
      HWND m_hwndLocalPath;
      HWND m_hwndRemotePath;
      HINSTANCE m_hInstance;
      
      void showLocalLVItems();
      void showRemoteLVItems();

      void onLocalItemActivate(LPNMITEMACTIVATE lpnmia);
      void onRemoteItemActivate(LPNMITEMACTIVATE lpnmia);

      void onLocalReload();
      void onRemoteReload();

      void onLocalRButton();
      void onRemoteRButton();
      void showFTMenu(bool copyBtnState, bool createFldBtnState, 
                      bool renameBtnState, bool deleteBtnState, 
                      bool cancelBtnState);
      void onFTMenuCommand(int command);

      void onUpload();
      void onDownload();

      void onLocalRename();
      void onRemoteRename();

      void onLocalDelete();
      void onRemoteDelete();

      void onFTCancel();

      void setIcon(int dest, int idIcon);
      bool initFTDialog();
      bool initFTWndMsgs();
      
      void onLocalOneUpFolder();
      void onRemoteOneUpFolder();
      int makeOneUpFolder(char *pPath);

      void refreshBtnState();
      void setButtonsState();
      
      bool m_bDlgShown;

      UINT m_msgCheckTransferQueue;
      UINT m_msgUploadFilePortion;
      UINT m_msgDownloadFilePortion;

      FTListView *m_pLocalLV;
      FTListView *m_pRemoteLV;

      int m_FTMenuSource;

      char m_szLocalPath[FT_FILENAME_SIZE];
      char m_szRemotePath[FT_FILENAME_SIZE];
      char m_szLocalPathTmp[FT_FILENAME_SIZE];
      char m_szRemotePathTmp[FT_FILENAME_SIZE];

      static const char szCheckTransferQueueText[];
      static const char szUploadFilePortionText[];
      static const char szDownloadFilePortionText[];

      typedef struct tagFTBUTTONSSTATE
      {
        bool uploadBtn;
        bool downloadBtn;
        bool createLocalFldBtn;
        bool createRemoteFldBtn;
        bool renameLocalBtn;
        bool renameRemoteBtn;
        bool deleteLocalBtn;
        bool deleteRemoteBtn;
        bool cancelBtn;
      } FTBUTTONSSTATE;

      FTBUTTONSSTATE m_BtnState;
    };
  }
}

#endif // __RFB_WIN32_FTDIALOG_H__
