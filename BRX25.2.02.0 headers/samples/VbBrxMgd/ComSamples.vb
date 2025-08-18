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
    Public Class ComSamples
        ' Methods
        Public Shared Function ComSelectionSet(ByVal filter As Object()) As ObjectIdCollection
            Dim application As AcadApplication = TryCast(_AcAp.Application.AcadApplication, AcadApplication)
            If (application Is Nothing) Then
                Throw New System.Exception("Could Not Get Application")
            End If
            Dim setids As New ObjectIdCollection
            Dim selection As AcadSelectionSet = application.ActiveDocument.SelectionSets.Add("samp04Set")
            Try
                selection.SelectOnScreen(New Integer() {0}, filter)
                Dim obj As AcadObject
                For Each obj In selection
                    setids.Add(New ObjectId(New IntPtr(obj.ObjectID)))
                Next
            Finally
                selection.Delete()
            End Try
            Return setids
        End Function

        Public Shared Sub do_comSSet()
            Dim editor As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Using action As Transaction = HostApplicationServices.WorkingDatabase.TransactionManager.StartTransaction
                Dim id As ObjectId
                For Each id In ComSamples.ComSelectionSet(New Object() {"POINT,LINE,CIRCLE,INSERT"})
                    Dim ent As Entity = TryCast(action.GetObject(id, OpenMode.ForWrite), Entity)
                    If (Not ent Is Nothing) Then
                        ent.Layer = "0"
                    End If
                Next
                action.Commit()
            End Using
        End Sub

        Public Shared Sub do_performanceTest()
            Dim editor As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim sw As Stopwatch = Stopwatch.StartNew
            Dim app As AcadApplication = TryCast(_AcAp.Application.AcadApplication, AcadApplication)
            If (app Is Nothing) Then
                Throw New NullReferenceException("Could Not Get Application")
            End If
            Dim count As Integer = 0
            Dim item As AcadEntity
            For Each item In app.ActiveDocument.ModelSpace
                count += 1
            Next
            editor.WriteMessage(vbLf & "{0} Entities found in {1} Milliseconds", New Object() {count, sw.ElapsedMilliseconds})
        End Sub

    End Class
End Namespace

