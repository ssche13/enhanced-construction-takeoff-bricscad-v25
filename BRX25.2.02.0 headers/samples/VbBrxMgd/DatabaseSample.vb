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

Namespace CsBrxMgd
    Public Class DatabaseSample
        ' Methods
        Public Shared Function AddToModelSpace(ByVal ParamArray list As Entity()) As ObjectIdCollection
            Dim ids As New ObjectIdCollection
            Dim database As Database = HostApplicationServices.WorkingDatabase
            Using action As Transaction = database.TransactionManager.StartTransaction
                Dim blockTable As BlockTable = TryCast(action.GetObject(database.BlockTableId, OpenMode.ForRead), BlockTable)
                If (blockTable Is Nothing) Then
                    Throw New NullReferenceException("blockTable == null")
                End If
                Dim blockTableRecord As BlockTableRecord = TryCast(action.GetObject(blockTable.Item(BlockTableRecord.ModelSpace), OpenMode.ForWrite), BlockTableRecord)
                If (blockTableRecord Is Nothing) Then
                    Throw New NullReferenceException("blockTableRecord == null")
                End If
                Dim ent As Entity
                For Each ent In list
                    ids.Add(blockTableRecord.AppendEntity(ent))
                    action.AddNewlyCreatedDBObject(ent, True)
                Next
                action.Commit()
            End Using
            Return ids
        End Function

        Public Shared Sub do_addCircle()
            Using circle As New Circle(New Point3d(0, 0, 0), Vector3d.ZAxis, 3)
                Using ellipse As New Ellipse(New Point3d(0, 0, 0), Vector3d.ZAxis, Vector3d.YAxis, 0.6, 0, 6.2831853071795862)
                    DatabaseSample.AddToModelSpace(New Entity() {circle, ellipse})
                End Using
            End Using
        End Sub

        Public Shared Sub do_addLayer()
            Dim database As Database = HostApplicationServices.WorkingDatabase
            Using action As _AcDb.Transaction = database.TransactionManager.StartTransaction
                Dim layerTable As LayerTable = TryCast(action.GetObject(database.LayerTableId, OpenMode.ForWrite), LayerTable)
                If (layerTable Is Nothing) Then
                    Throw New NullReferenceException("LayerTable == null")
                End If
                If Not layerTable.Has("CoolLayer") Then
                    Using myLayer As New LayerTableRecord
                        myLayer.Name = "CoolLayer"
                        myLayer.Color = _AcCm.Color.FromRgb(&HFF, 0, &HFF)
                        layerTable.Add(myLayer)
                        action.AddNewlyCreatedDBObject(myLayer, True)
                    End Using
                End If
                action.Commit()
            End Using
        End Sub

        Public Shared Sub do_addLine()
            Dim startPoint As New Point3d(0, 0, 0)
            Dim endPoint As New Point3d(100, 100, 0)
            Using line As New Line(startPoint, endPoint)
                DatabaseSample.AddToModelSpace(New Entity() {line})
            End Using
        End Sub

        Public Shared Sub do_addPolyLine()
            Using pline1 As New _AcDb.Polyline(4)
                pline1.AddVertexAt(0, New Point2d(0, 0), 0.1, 0, 0)
                pline1.AddVertexAt(1, New Point2d(0, 100), 0.1, 0, 0)
                pline1.AddVertexAt(2, New Point2d(100, 100), 0.1, 0, 0)
                pline1.AddVertexAt(3, New Point2d(100, 0), 0.1, 0, 0)
                pline1.Closed = True
                Using pline2 As _AcDb.Polyline = TryCast(pline1.Clone, _AcDb.Polyline)
                    pline2.TransformBy(Matrix3d.Rotation(0.261799388, Vector3d.ZAxis, New Point3d(50, 50, 0)))
                    Using pline3 As _AcDb.Polyline = TryCast(pline1.Clone, _AcDb.Polyline)
                        pline3.TransformBy(Matrix3d.Rotation(0.523598776, Vector3d.ZAxis, New Point3d(50, 50, 0)))
                        DatabaseSample.AddToModelSpace(New Entity() {pline1, pline2, pline3})
                    End Using
                End Using
            End Using
        End Sub

        Public Shared Sub do_createTable()
            Dim database As Database = HostApplicationServices.WorkingDatabase
            Using table As New Table
                table.SetDatabaseDefaults(database)
                table.Position = Point3d.Origin
                table.SetSize(6, 3)
                table.GenerateLayout()
                table.RecomputeTableBlock(True)
                Dim row As Integer
                For row = 0 To table.Rows.Count - 1
                    Dim col As Integer
                    For col = 0 To table.Columns.Count - 1
                        table.SetTextString(row, col, "BricsCAD")
                    Next col
                Next row
                table.RecomputeTableBlock(True)
                DatabaseSample.AddToModelSpace(New Entity() {table})
            End Using
        End Sub

        Public Shared Sub do_performanceTest()
            Dim editor As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Dim database As Database = HostApplicationServices.WorkingDatabase
            If (database Is Nothing) Then
                Throw New NullReferenceException("database is null")
            End If
            Dim manager As _AcDb.TransactionManager = database.TransactionManager
            If (manager Is Nothing) Then
                Throw New NullReferenceException("manager is null")
            End If
            Using action As Transaction = manager.StartTransaction
                Dim countEnts As Integer = 0
                Dim sw As Stopwatch = Stopwatch.StartNew
                Dim blockTableRecord As BlockTableRecord = TryCast(action.GetObject(database.CurrentSpaceId, OpenMode.ForRead, False), BlockTableRecord)
                If (blockTableRecord Is Nothing) Then
                    Throw New NullReferenceException("blockTableRecord is null")
                End If
                Dim entityId As ObjectId
                For Each entityId In blockTableRecord
                    Dim entity As Entity = TryCast(action.GetObject(entityId, OpenMode.ForRead, False), Entity)
                    If (entity Is Nothing) Then
                        Throw New NullReferenceException("entity is null")
                    End If
                    countEnts += 1
                Next
                editor.WriteMessage(vbLf & "{0} Entities found in {1} Milliseconds", New Object() {countEnts, sw.ElapsedMilliseconds})
                action.Commit()
            End Using
        End Sub

        Public Shared Sub do_readDwgFile()
            Dim editor As Editor = Application.DocumentManager.MdiActiveDocument.Editor
            Using db As Database = New Database(False, True)
                db.ReadDwgFile(DatabaseSample.SelectDrawingFile("c:\"), FileShare.Read, True, Nothing)
                editor.WriteMessage(vbLf & "ApproxNumObjects = {0}", New Object() {db.ApproxNumObjects})
            End Using
        End Sub

        Private Shared Function SelectDrawingFile(ByVal initialDirectory As String) As String
            Dim dialog As New System.Windows.Forms.OpenFileDialog With {
                .Filter = "dwg files (*.dwg)|*.dwg",
                .InitialDirectory = initialDirectory,
                .Title = "Select a Drawing file"
            }
            If (dialog.ShowDialog <> DialogResult.OK) Then
                Return Nothing
            End If
            Return dialog.FileName
        End Function

    End Class
End Namespace

