# Microsoft Developer Studio Project File - Name="propgrid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=propgrid - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "propgrid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "propgrid.mak" CFG="propgrid - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "propgrid - Win32 DLL Universal Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Universal Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Universal Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Universal Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "propgrid - Win32 Universal Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Universal Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Universal Release" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Universal Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "propgrid - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "propgrid - Win32 DLL Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivudll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivudll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswunivu" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270u_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswunivu" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270u_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivu" /i ".\include" /d WXDLLNAME=wxmswuniv270u_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivu" /i ".\include" /d WXDLLNAME=wxmswuniv270u_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270u_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27u_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270u_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27u_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivuddll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivuddll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270ud_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270ud_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivud" /i ".\include" /d WXDLLNAME=wxmswuniv270ud_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswunivud" /i ".\include" /d WXDLLNAME=wxmswuniv270ud_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270ud_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27ud_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270ud_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27ud_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivdll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivdll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswuniv" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswuniv" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmswuniv270_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\lib\vc_dll\mswuniv" /i ".\include" /d WXDLLNAME=wxmswuniv270_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "__WXMSW__" /d "__WXUNIVERSAL__" /i ".\lib\vc_dll\mswuniv" /i ".\include" /d WXDLLNAME=wxmswuniv270_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswunivddll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswunivddll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270d_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswunivd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmswuniv270d_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswunivd" /i ".\include" /d WXDLLNAME=wxmswuniv270d_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXUNIVERSAL__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswunivd" /i ".\include" /d WXDLLNAME=wxmswuniv270d_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270d_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27d_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmswuniv27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmswuniv270d_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmswuniv27d_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswudll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswudll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswu" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270u_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\mswu" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270u_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i ".\lib\vc_dll\mswu" /i ".\include" /d WXDLLNAME=wxmsw270u_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "__WXMSW__" /d "_UNICODE" /i ".\lib\vc_dll\mswu" /i ".\include" /d WXDLLNAME=wxmsw270u_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270u_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27u_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27u_core.lib wxbase27u.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270u_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27u_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswuddll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswuddll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270ud_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270ud_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswud" /i ".\include" /d WXDLLNAME=wxmsw270ud_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /d "_UNICODE" /i ".\lib\vc_dll\mswud" /i ".\include" /d WXDLLNAME=wxmsw270ud_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270ud_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27ud_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexud.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27ud_core.lib wxbase27ud.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270ud_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27ud_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswdll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswdll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\msw" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_dll\msw" /I ".\include" /W4 /Fd.\..\..\lib\vc_dll\wxmsw270_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "__WXMSW__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "__WXMSW__" /i ".\lib\vc_dll\msw" /i ".\include" /d WXDLLNAME=wxmsw270_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "__WXMSW__" /i ".\lib\vc_dll\msw" /i ".\include" /d WXDLLNAME=wxmsw270_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27_core.lib wxbase27.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27_propgrid.lib" /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_dll"
# PROP BASE Intermediate_Dir "vc_mswddll\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_dll"
# PROP Intermediate_Dir "vc_mswddll\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270d_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_dll\mswd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_dll\wxmsw270d_propgrid_vc_custom.pdb /I ".\..\..\include" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "WXUSINGDLL" /D "WXMAKINGDLL_PROPGRID" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswd" /i ".\include" /d WXDLLNAME=wxmsw270d_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
# ADD RSC /l 0x409 /d "_DEBUG" /d "__WXMSW__" /d "__WXDEBUG__" /i ".\lib\vc_dll\mswd" /i ".\include" /d WXDLLNAME=wxmsw270d_propgrid_vc_custom /d "WXUSINGDLL" /i ".\..\..\include" /d WXMAKINGDLL_PROPGRID
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270d_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27d_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"
# ADD LINK32 wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib wxmsw27d_core.lib wxbase27d.lib /nologo /dll /machine:i386 /out:".\..\..\lib\vc_dll\wxmsw270d_propgrid_vc_custom.dll" /libpath:".\..\..\lib\vc_dll" /implib:".\..\..\lib\vc_dll\wxmsw27d_propgrid.lib" /debug /libpath:"..\..\..\lib\vc_dll"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivu\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivu\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswunivu" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27u_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswunivu" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27u_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27u_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27u_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivud\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivud\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27ud_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27ud_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27ud_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27ud_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswuniv\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswuniv\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswuniv" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswuniv" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmswuniv27_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "__WXUNIVERSAL__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswunivd\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswunivd\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27d_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswunivd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmswuniv27d_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXUNIVERSAL__" /D "__WXDEBUG__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27d_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmswuniv27d_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswu\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswu\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswu" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27u_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\mswu" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27u_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27u_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27u_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswud\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswud\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27ud_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswud" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27ud_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /D "_UNICODE" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27ud_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27ud_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_msw\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_msw\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\msw" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /I ".\lib\vc_lib\msw" /I ".\include" /W4 /Fd.\..\..\lib\vc_lib\wxmsw27_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "__WXMSW__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27_propgrid.lib"

!ELSEIF  "$(CFG)" == "propgrid - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\..\..\lib\vc_lib"
# PROP BASE Intermediate_Dir "vc_mswd\propgrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\..\..\lib\vc_lib"
# PROP Intermediate_Dir "vc_mswd\propgrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27d_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /I ".\lib\vc_lib\mswd" /I ".\include" /W4 /Zi /Gm /GZ /Fd.\..\..\lib\vc_lib\wxmsw27d_propgrid.pdb /I ".\..\..\include" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "__WXMSW__" /D "__WXDEBUG__" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27d_propgrid.lib"
# ADD LIB32 /nologo /out:".\..\..\lib\vc_lib\wxmsw27d_propgrid.lib"

!ENDIF

# Begin Target

# Name "propgrid - Win32 DLL Universal Unicode Release"
# Name "propgrid - Win32 DLL Universal Unicode Debug"
# Name "propgrid - Win32 DLL Universal Release"
# Name "propgrid - Win32 DLL Universal Debug"
# Name "propgrid - Win32 DLL Unicode Release"
# Name "propgrid - Win32 DLL Unicode Debug"
# Name "propgrid - Win32 DLL Release"
# Name "propgrid - Win32 DLL Debug"
# Name "propgrid - Win32 Universal Unicode Release"
# Name "propgrid - Win32 Universal Unicode Debug"
# Name "propgrid - Win32 Universal Release"
# Name "propgrid - Win32 Universal Debug"
# Name "propgrid - Win32 Unicode Release"
# Name "propgrid - Win32 Unicode Debug"
# Name "propgrid - Win32 Release"
# Name "propgrid - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\.\..\..\src\propgrid\advprops.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\propgrid\extras.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\propgrid\manager.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\propgrid\odcombo.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\propgrid\propgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\.\..\..\src\propgrid\props.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\src\msw\version.rc

!IF  "$(CFG)" == "propgrid - Win32 DLL Universal Unicode Release"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Universal Unicode Debug"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Universal Release"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Universal Debug"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Unicode Release"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Unicode Debug"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Release"


!ELSEIF  "$(CFG)" == "propgrid - Win32 DLL Debug"


!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Unicode Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Universal Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Unicode Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "propgrid - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF

# End Source File
# End Group
# End Target
# End Project

