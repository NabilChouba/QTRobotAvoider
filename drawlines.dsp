# Microsoft Developer Studio Project File - Name="drawlines" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=drawlines - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "drawlines.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "drawlines.mak" CFG="drawlines - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "drawlines - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "drawlines - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "drawlines - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# ADD CPP /nologo /MD /W3 /O1 /I "$(QTDIR)\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D "NO_DEBUG" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib winmm.lib wsock32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib winmm.lib wsock32.lib imm32.lib wsock32.lib winmm.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "drawlines - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /ZI /Od /I "$(QTDIR)\include" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "UNICODE" /D "QT_THREAD_SUPPORT" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib winmm.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib winmm.lib wsock32.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "drawlines - Win32 Release"
# Name "drawlines - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\confRobot.cpp
# End Source File
# Begin Source File

SOURCE=.\confSigmoid.cpp
# End Source File
# Begin Source File

SOURCE=.\connect.cpp
# End Source File
# Begin Source File

SOURCE=.\enveronement.cpp
# End Source File
# Begin Source File

SOURCE=.\FixedPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\FormCourbe.cpp
# End Source File
# Begin Source File

SOURCE=.\frameChoitArth.cpp
# End Source File
# Begin Source File

SOURCE=.\mocconfRobot.cpp
# End Source File
# Begin Source File

SOURCE=.\mocconfSigmoid.cpp
# End Source File
# Begin Source File

SOURCE=.\mocconnect.cpp
# End Source File
# Begin Source File

SOURCE=.\mocFormCourbe.cpp
# End Source File
# Begin Source File

SOURCE=.\mocframe.cpp
# End Source File
# Begin Source File

SOURCE=.\robot.cpp
# End Source File
# Begin Source File

SOURCE=.\sigmoid.cpp
# End Source File
# Begin Source File

SOURCE=.\vecteur.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtalFloat.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\confRobot.h

!IF  "$(CFG)" == "drawlines - Win32 Release"

!ELSEIF  "$(CFG)" == "drawlines - Win32 Debug"

# Begin Custom Build
InputPath=.\confRobot.h

"mocconfRobot.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe confRobot.h -o mocconfRobot.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\confSigmoid.h

!IF  "$(CFG)" == "drawlines - Win32 Release"

!ELSEIF  "$(CFG)" == "drawlines - Win32 Debug"

# Begin Custom Build
InputPath=.\confSigmoid.h

"mocconfSigmoid.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe confSigmoid.h -o mocconfSigmoid.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connect.h

!IF  "$(CFG)" == "drawlines - Win32 Release"

# Begin Custom Build
InputPath=.\connect.h

"mocconnect.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe connect.h -o mocconnect.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "drawlines - Win32 Debug"

# Begin Custom Build
InputPath=.\connect.h

"mocconnect.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe connect.h -o mocconnect.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\enveronement.h
# End Source File
# Begin Source File

SOURCE=.\FixedPoint.h
# End Source File
# Begin Source File

SOURCE=.\FormCourbe.h

!IF  "$(CFG)" == "drawlines - Win32 Release"

!ELSEIF  "$(CFG)" == "drawlines - Win32 Debug"

# Begin Custom Build
InputPath=.\FormCourbe.h

"mocFormCourbe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe FormCourbe.h -o mocFormCourbe.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\frameChoitArth.h

!IF  "$(CFG)" == "drawlines - Win32 Release"

# Begin Custom Build
InputPath=.\frameChoitArth.h

"mocframe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe frameChoitArth.h -o mocframe.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "drawlines - Win32 Debug"

# Begin Custom Build
InputPath=.\frameChoitArth.h

"mocframe.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%QTDIR%\bin\moc.exe frameChoitArth.h -o mocframe.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\imge.h
# End Source File
# Begin Source File

SOURCE=.\network.h
# End Source File
# Begin Source File

SOURCE=.\obstacle.h
# End Source File
# Begin Source File

SOURCE=.\robot.h
# End Source File
# Begin Source File

SOURCE=.\sigmoid.h
# End Source File
# Begin Source File

SOURCE=.\vecteur.h
# End Source File
# Begin Source File

SOURCE=.\VirtalFloat.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Interfaces"

# PROP Default_Filter "ui"
# End Group
# End Target
# End Project
