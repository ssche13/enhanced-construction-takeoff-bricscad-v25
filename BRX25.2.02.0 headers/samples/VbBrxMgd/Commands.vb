'// Property of Bricsys NV. All rights reserved.
'// This file is part of the BRX SDK, and its use is subject to the terms
'// of the BRX SDK license agreement.
'/////////////////////////////////////////////////////////////////////////

Imports System.Text
Imports System.Runtime.InteropServices
Imports System.IO

Imports _AcAp = Bricscad.ApplicationServices
Imports _AcBr = Teigha.BoundaryRepresentation
Imports _AcCm = Teigha.Colors
Imports _AcDb = Teigha.DatabaseServices
Imports _AcEd = Bricscad.EditorInput
Imports _AcGe = Teigha.Geometry
Imports _AcGi = Teigha.GraphicsInterface
Imports _AcGs = Teigha.GraphicsSystem
Imports _AcGsk = Bricscad.GraphicsSystem
Imports _AcPl = Bricscad.PlottingServices
Imports _AcBrx = Bricscad.Runtime
Imports _AcTrx = Teigha.Runtime
Imports _AcWnd = Bricscad.Windows
Imports _AdWnd = Bricscad.Windows
Imports _AcRbn = Bricscad.Ribbon
Imports _AcLy = Teigha.LayerManager
Imports _AcIo = Teigha.Export_Import 'Bricsys specific
Imports _AcGbl = Bricscad.Global 'Bricsys specific
Imports _AcQad = Bricscad.Quad 'Bricsys specific
Imports _AcInt = Bricscad.Internal
Imports _AcPb = Bricscad.Publishing
Imports _AcMg = Teigha.ModelerGeometry 'Bricsys specific
Imports _AcLic = Bricscad.Licensing 'Bricsys specific
Imports _AcMec = Bricscad.MechanicalComponents 'Bricsys specific
Imports _AcBim = Bricscad.Bim 'Bricsys specific
Imports _AcDm = Bricscad.DirectModeling 'Bricsys specific
Imports _AcIfc = Bricscad.Ifc 'Bricsys specific
Imports _AcRhn = Bricscad.Rhino 'Bricsys specific
Imports _AcCiv = Bricscad.Civil 'Bricsys specific
Imports _AcGc = Bricscad.Parametric 'Bricsys specific
Imports _AcHlr = Bricscad.Hlr 'Bricsys specific

Imports Bricscad.ApplicationServices
Imports Teigha.Colors
Imports Teigha.DatabaseServices
Imports Bricscad.EditorInput
Imports Teigha.Geometry
Imports Teigha.GraphicsInterface
Imports Teigha.GraphicsSystem
Imports Bricscad.GraphicsSystem
Imports Bricscad.PlottingServices
Imports Bricscad.Runtime
Imports Teigha.Runtime
Imports Bricscad.Windows
Imports Bricscad.Ribbon

' COM
Imports BricscadDb
Imports BricscadApp

Namespace CsBrxMgd
    Public Class Commands
        Implements IExtensionApplication
        ' Methods
        <DllImport("brx25.dll", CallingConvention:=CallingConvention.Cdecl, CharSet:=CharSet.Unicode)>
        Private Shared Function acutPrintf(ByVal str As String) As IntPtr
        End Function

        Public Sub Initialize() Implements IExtensionApplication.Initialize
            Application.ShowAlertDialog("The commands class is Initialized")
        End Sub

        Public Sub Terminate() Implements IExtensionApplication.Terminate
            Application.ShowAlertDialog("The commands class is Terminated")
        End Sub

        <LispFunction("lisp01")>
        Public Shared Function lisp01(ByVal pArgs As ResultBuffer) As ResultBuffer
            Dim editor As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            If (Not pArgs Is Nothing) Then
                Dim inArray As New List(Of TypedValue)(pArgs.AsArray)
                Return New ResultBuffer(inArray.ToArray)
            End If
            Return Nothing
        End Function

        <LispFunction("lisp02")>
        Public Shared Function lisp02(ByVal pArgs As ResultBuffer) As String
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim result As String = String.Empty
            If (pArgs Is Nothing) Then
                Return result
            End If
            Dim tv As TypedValue
            For Each tv In pArgs
                Select Case CType(tv.TypeCode, LispDataType)
                    Case LispDataType.Double
                        result = (result & " real ")
                        Exit Select
                    Case LispDataType.Point2d
                        result = (result & " Point2d ")
                        Exit Select
                    Case LispDataType.Int16
                        result = (result & " int16 ")
                        Exit Select
                    Case LispDataType.Text
                        result = (result & " Text ")
                        Exit Select
                    Case LispDataType.ObjectId
                        result = (result & " ObjectId ")
                        Exit Select
                    Case LispDataType.Point3d
                        result = (result & " Point3d ")
                        Exit Select
                    Case LispDataType.Int32
                        result = (result & " int32 ")
                        Exit Select
                    Case LispDataType.ListBegin
                        result = (result & "(")
                        Exit Select
                    Case LispDataType.ListEnd
                        result = (result & ")")
                        Exit Select
                    Case LispDataType.Nil
                        result = (result & " NIL ")
                        Exit Select
                    Case LispDataType.T_atom
                        result = (result & " T ")
                        Exit Select
                End Select
            Next
            Return result
        End Function

        <CommandMethod("samp01")>
        Public Shared Sub samp01()
            DatabaseSample.do_addLine()
        End Sub

        <CommandMethod("samp02")>
        Public Sub samp02()
            Dim doc As Document = _AcAp.Application.DocumentManager.MdiActiveDocument
            Dim editor As Editor = doc.Editor
            DatabaseSample.do_addLine()
            Dim manager As _AcDb.TransactionManager = doc.TransactionManager
            Using transaction As Transaction = manager.StartTransaction
                Dim lineId As ObjectId = editor.SelectLast().Value.Item(0).ObjectId
                Dim line As Line = TryCast(lineId.GetObject(OpenMode.ForWrite), Line)
                line.ColorIndex = 1 'make it red
                transaction.Commit()
            End Using
        End Sub

        <CommandMethod("samp03")>
        Public Shared Sub samp03()
            DatabaseSample.do_addLayer()
        End Sub

        <CommandMethod("samp04")>
        Public Shared Sub samp04()
            ComSamples.do_comSSet()
        End Sub

        <CommandMethod("samp05")>
        Public Shared Sub samp05()
            Dim application As AcadApplication = TryCast(_AcAp.Application.AcadApplication, AcadApplication)
            If (application Is Nothing) Then
                Throw New System.Exception("Could Not Get Application")
            End If
            Dim document As AcadDocument = application.ActiveDocument
            Dim form As New BrxMgdForm(document)
            _AcAp.Application.ShowModalDialog(_AcAp.Application.MainWindow, form)
        End Sub

        <CommandMethod("samp06")>
        Public Shared Sub samp06()
            Dim editor As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Commands.acutPrintf(vbLf & "PInvoke Worked, This was a managed string but now its native: ")
        End Sub

        <CommandMethod("samp07")>
        Public Shared Sub samp07()
            Dim editor As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            _AcAp.Application.SetSystemVariable("OSMODE", &HBF)
            Dim osmode As Object = Application.GetSystemVariable("OSMODE")
            editor.WriteMessage("{0}", New Object() {osmode})
        End Sub

        <CommandMethod("samp08")>
        Public Shared Sub samp08()
            DatabaseSample.do_addPolyLine()
        End Sub

        <CommandMethod("samp09")>
        Public Shared Sub samp09()
            DatabaseSample.do_addCircle()
        End Sub

        <CommandMethod("samp10")>
        Public Shared Sub samp10()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim doc As Document
            For Each doc In _AcAp.Application.DocumentManager
                ed.WriteMessage(vbLf & "Document {0}, Textsize={1}, UCS={2}:", New Object() {doc.Name, doc.Database.Textsize, doc.Editor.CurrentUserCoordinateSystem})
            Next
            ed.WriteMessage(vbLf & "MdiActiveDocument {0}:", New Object() {Application.DocumentManager.MdiActiveDocument.Name})
        End Sub

        <CommandMethod("samp11")>
        Public Shared Sub samp11()
            DatabaseSample.do_performanceTest()
        End Sub

        <CommandMethod("samp12")>
        Public Shared Sub samp12()
            ComSamples.do_performanceTest()
        End Sub

        <CommandMethod("samp13")>
        Public Shared Sub samp13()
            DatabaseSample.do_readDwgFile()
        End Sub

        <CommandMethod("samp14")>
        Public Shared Sub samp14()
            EditorSample.do_MainWindow()
        End Sub

        <CommandMethod("samp15")>
        Public Shared Sub samp15()
            Application.ShowAlertDialog("Hover the cursor over Block References")
            AddHandler _AcAp.Application.DocumentManager.MdiActiveDocument.Editor.PointMonitor, New PointMonitorEventHandler(AddressOf EditorSample.OnPointMonitor)
        End Sub

        <CommandMethod("samp16")>
        Public Shared Sub samp16()
            RemoveHandler _AcAp.Application.DocumentManager.MdiActiveDocument.Editor.PointMonitor, New PointMonitorEventHandler(AddressOf EditorSample.OnPointMonitor)
        End Sub

        <CommandMethod("samp17")>
        Public Shared Sub samp17()
            DatabaseSample.do_createTable()
        End Sub

        <CommandMethod("samp18")>
        Public Shared Sub samp18()
            EditorSample.do_getString()
        End Sub

        <CommandMethod("samp19")>
        Public Shared Sub samp19()
            EditorSample.do_getKeyWords()
        End Sub

        <CommandMethod("samp20")>
        Public Shared Sub samp20()
            EditorSample.do_getPoint()
        End Sub

        <CommandMethod("samp21")>
        Public Shared Sub samp21()
            EditorSample.do_getDistance()
        End Sub

        <CommandMethod("samp22")>
        Public Shared Sub samp22()
            EditorSample.do_getEntity()
        End Sub

        <CommandMethod("samp23")>
        Public Shared Sub samp23()
            EditorSample.do_getEntity2()
        End Sub

        <CommandMethod("samp24")>
        Public Shared Sub samp24()
            Application.ShowAlertDialog("Draw a few points " & vbLf & "re-run the command to toggle visuals")
            If (Commands.mDrawOverrule Is Nothing) Then
                Commands.mDrawOverrule = New BricscadDrawOverrule
                Overrule.AddOverrule(RXObject.GetClass(GetType(DBPoint)), Commands.mDrawOverrule, False)
                Overrule.Overruling = True
            Else
                Overrule.RemoveOverrule(RXObject.GetClass(GetType(DBPoint)), Commands.mDrawOverrule)
                Overrule.Overruling = False
                Commands.mDrawOverrule = Nothing
            End If
            Application.DocumentManager.MdiActiveDocument.Editor.Regen()
        End Sub

        <CommandMethod("samp25")>
        Public Shared Sub samp25()
            EditorSample.do_getSelectionSet()
        End Sub

        <CommandMethod("samp26")>
        Public Shared Sub samp26()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim PPR1 As PromptPointResult = ed.GetPoint("Pick Point near object")
            If (PPR1.Status = PromptStatus.OK) Then
                Dim snap As Point3d = ed.Snap("nearest", PPR1.Value)
                ed.WriteMessage(vbLf & "{0} {1}", New Object() {PPR1.Value, snap})
            End If
        End Sub

        <CommandMethod("samp27")>
        Public Shared Sub samp27()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim res As PromptSelectionResult = ed.SelectPrevious
            ed.WriteMessage(vbLf & "{0} {1}", New Object() {res, res.Value.Count})
        End Sub

        <CommandMethod("samp28")>
        Public Shared Sub samp28()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim col As New Point3dCollection
            Dim PPR1 As PromptPointResult = ed.GetPoint("Get Point")
            If (PPR1.Status = PromptStatus.OK) Then
                col.Add(PPR1.Value)
            End If
            Dim ppo As New PromptPointOptions("Get next Point")
            ppo.UseBasePoint = True
            ppo.BasePoint = PPR1.Value
            Dim PPR2 As PromptPointResult = ed.GetPoint(ppo)
            If (PPR2.Status = PromptStatus.OK) Then
                col.Add(PPR2.Value)
            End If
            Dim res As PromptSelectionResult = ed.SelectFence(col)
            ed.WriteMessage(vbLf & "{0} {1}", New Object() {res, res.Value.Count})
        End Sub

        <CommandMethod("samp29")>
        Public Shared Sub samp29()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim PPR1 As PromptPointResult = ed.GetPoint("Get Point")
            If (PPR1.Status = PromptStatus.OK) Then
                Dim PPR2 As PromptPointResult = ed.GetCorner("Get Corner", PPR1.Value)
                If (PPR2.Status = PromptStatus.OK) Then
                    Dim res As PromptSelectionResult = ed.SelectWindow(PPR1.Value, PPR2.Value)
                    If Not (res.Value Is Nothing) Then
                        ed.WriteMessage(vbLf & "Nothing selected!")
                    Else
                        ed.WriteMessage(vbLf & "{0} {1}", New Object() {res, res.Value.Count})
                    End If
                End If
            End If
        End Sub

        <CommandMethod("samp30")>
        Public Shared Sub samp30()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim dlg As New _AcWnd.ColorDialog
            If (dlg.ShowDialog = DialogResult.OK) Then
                ed.WriteMessage(vbLf & "Color = {0}", New Object() {dlg.Color})
            End If
        End Sub

        <CommandMethod("samp31")>
        Public Shared Sub samp31()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim dlg As New _AcWnd.LinetypeDialog
            dlg.Linetype = HostApplicationServices.WorkingDatabase.Celtype
            If (dlg.ShowDialog = DialogResult.OK) Then
                ed.WriteMessage(vbLf & "LineType ObjectId = {0}", New Object() {dlg.Linetype})
            End If
        End Sub

        <CommandMethod("samp32")>
        Public Shared Sub samp32()
            Dim ed As Editor = _AcAp.Application.DocumentManager.MdiActiveDocument.Editor
            Dim dlg As New _AcWnd.OpenFileDialog("Test", "Drawing", "dwg", "Bricscad File Nav", (_AcWnd.OpenFileDialog.OpenFileDialogFlags.AllowMultiple Or _AcWnd.OpenFileDialog.OpenFileDialogFlags.AllowAnyExtension))
            If (dlg.ShowDialog = DialogResult.OK) Then
                Dim file As String
                For Each file In dlg.GetFilenames()
                    ed.WriteMessage(file)
                Next
            End If
        End Sub

        <CommandMethod("samp33")>
        Public Shared Sub samp33()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim dlg As New _AcWnd.SaveFileDialog("Test", "Drawing", "dwg", "Bricscad File Nav", _AcWnd.SaveFileDialog.SaveFileDialogFlags.AllowAnyExtension)
            If (dlg.ShowDialog = DialogResult.OK) Then
                ed.WriteMessage(dlg.Filename)
            End If
        End Sub

        <CommandMethod("samp34")>
        Public Shared Sub samp34()
            Dim ed As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim a As String = _AcBrx.Converter.AngleToString(3.1415926535897931)
            Dim b As String = _AcBrx.Converter.AngleToString(121.135, _AcBrx.AngularUnitFormat.DegreesMinutesSeconds, 5)
            Dim c As String = _AcBrx.Converter.DistanceToString(3.1415926535897931)
            Dim d As String = _AcBrx.Converter.DistanceToString(3.1415926535897931, _AcBrx.DistanceUnitFormat.Architectural, -1)
            ed.WriteMessage(vbLf & "AngleToString {0}", New Object() {a})
            ed.WriteMessage(vbLf & "AngleToString {0}", New Object() {b})
            ed.WriteMessage(vbLf & "DistanceToString {0}", New Object() {c})
            ed.WriteMessage(vbLf & "DistanceToString {0}", New Object() {d})
            ed.WriteMessage(vbLf & "StringToAngle {0}", New Object() {_AcBrx.Converter.StringToAngle(a)})
            ed.WriteMessage(vbLf & "StringToAngle {0}", New Object() {_AcBrx.Converter.StringToAngle(b, _AcBrx.AngularUnitFormat.DegreesMinutesSeconds)})
            ed.WriteMessage(vbLf & "StringToDistance {0}", New Object() {_AcBrx.Converter.StringToDistance(c)})
            ed.WriteMessage(vbLf & "StringToDistance {0}", New Object() {_AcBrx.Converter.StringToDistance(d, _AcBrx.DistanceUnitFormat.Architectural)})
        End Sub

        ' Fields
        Friend Shared mDrawOverrule As BricscadDrawOverrule
    End Class
End Namespace

