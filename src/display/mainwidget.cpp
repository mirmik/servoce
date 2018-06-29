//#include <zencad/MainWidget.h>
//#include <QtWidgets/QMessageBox>
//#include <QtWidgets/QFileDialog>
//#include <QtWidgets/QInputDialog>
//#include <QtCore/QDebug>
//#include <QtCore/QDir>

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

// occ header files.
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <StlAPI_Writer.hxx>
//#include <StlAPI_ErrorStatus.hxx>

#include <V3d_View.hxx>
#include <AIS_Shape.hxx>

#include <servoce/display.h>
#include <local/display.h>


servoce::disp::MainWidget::MainWidget(QWidget* parent) : QMainWindow(parent) {
    display = new DisplayWidget(this);
    QWidget::setWindowTitle("zenwidget");
    QWidget::setWindowIcon(QIcon(":/industrial-robot.svg"));

    createActions();
    createMenus();

    setCentralWidget(display);
    resize(640, 480);
}

void servoce::disp::MainWidget::createActions() {
    mExitAction = new QAction(tr("Exit"), this);
    mExitAction->setShortcut(tr("Ctrl+Q"));
    mExitAction->setStatusTip(tr("Exit the application"));
    connect(mExitAction, SIGNAL(triggered()), this, SLOT(close()));

    mStlExport = new QAction(tr("Export STL..."), this);
    mStlExport->setStatusTip(tr("Export file with external STL-Mesh format"));
    connect(mStlExport, SIGNAL(triggered()), this, SLOT(export_stl()));

    mScreen = new QAction(tr("Screenshot..."), this);
    mScreen->setStatusTip(tr("Do screen"));
    connect(mScreen, SIGNAL(triggered()), this, SLOT(screenshot()));

    mAboutAction = new QAction(tr("About"), this);
    mAboutAction->setStatusTip(tr("About the application"));
    connect(mAboutAction, SIGNAL(triggered()), this, SLOT(about()));

    mAutoscale = new QAction(tr("Autoscale"), this);
    mAutoscale->setStatusTip(tr("Autoscale"));
    connect(mAutoscale, SIGNAL(triggered()), display, SLOT(autoscale()));

    mOrient1 = new QAction(tr("Orient1"), this);
    mOrient1->setStatusTip(tr("Orient1"));
    connect(mOrient1, SIGNAL(triggered()), this, SLOT(orient1()));

    mOrient2 = new QAction(tr("Orient2"), this);
    mOrient2->setStatusTip(tr("Orient2"));
    connect(mOrient2, SIGNAL(triggered()), this, SLOT(orient2()));
}

void servoce::disp::MainWidget::createMenus() {
    mFileMenu = menuBar()->addMenu(tr("&File"));
    mFileMenu->addAction(mStlExport);
    mFileMenu->addAction(mScreen);
    mFileMenu->addSeparator();
    mFileMenu->addAction(mExitAction);

    mNavigationMenu = menuBar()->addMenu(tr("&Navigation"));
    mNavigationMenu->addAction(mAutoscale);
    mNavigationMenu->addAction(mOrient1);
    mNavigationMenu->addAction(mOrient2);

    mHelpMenu = menuBar()->addMenu(tr("&Help"));
    mHelpMenu->addAction(mAboutAction);
}

void servoce::disp::MainWidget::createToolbars() {

}

void servoce::disp::MainWidget::about() {
    QMessageBox::about(this, tr("About ZenCad Shower"),
        tr("<h2>Shower</h2>"
        "<p>Author: mirmik(mirmikns@yandex.ru) 2018"
        "<p>Widget for display zencad geometry."));
}


void servoce::disp::MainWidget::export_stl() {
    //gxx::println("export_stl");
    bool ok;
    
    QFileDialog fileDialog(this, "Choose file to export");
    fileDialog.setNameFilter("STL-Mesh (*.stl)");
    fileDialog.setDefaultSuffix(".stl");
    ok = fileDialog.exec();

    if (!ok) return;
    QString path = fileDialog.selectedFiles().first();

    QInputDialog *inputDialog = new QInputDialog();
    inputDialog->setTextValue("Test"); // has no effect
    
    double deflection = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                       tr("Amount:"), 0.01, 0, 10, 5, &ok);

    if (display->scn->shapes.size() != 1) {
        exit(1);
        //gxx::panic("TODO");
    } 

    const TopoDS_Shape& shape = display->scn->shapes[0].shp.Shape();
    BRepMesh_IncrementalMesh mesh(shape, deflection);

    if (mesh.IsDone() == false) {
        gxx::panic("Is not done TODO");
    }

    StlAPI_Writer stl_writer;
    //stl_writer.SetDeflection(d);
    //stl_writer.RelativeMode() = false;
    stl_writer.Write(shape, path.toStdString().c_str());
    //QMessageBox msgBox;
    //msgBox.setText(QString::number((int)err));
    //int ret = msgBox.exec();
}

void servoce::disp::MainWidget::screenshot() {
    bool ok;

    //QPixmap pixmap(size()); 
    //render(&pixmap, QPoint(), QRegion(display->rect()));
    
    auto disp = display->grabFrameBuffer();

    QFileDialog fileDialog(this, "Choose file to export");
    fileDialog.setDirectory(QDir::current());
    fileDialog.setNameFilter("png (*.png)");
    fileDialog.setDefaultSuffix(".png");
    ok = fileDialog.exec();

    if (!ok) return;
    QString path = fileDialog.selectedFiles().first();

    QFile file(path);
    disp.save(&file, "PNG");
    file.close();

    //QInputDialog *inputDialog = new QInputDialog();
    //inputDialog->setTextValue("Test"); // has no effect
    
    //double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
      //                                 tr("Amount:"), 0.01, 0, 10, 5, &ok);

    //if (display->display_on_init_list.size() != 1) {
     //   exit(1);
        //gxx::panic("TODO");
    //} 

    //StlAPI_Writer stl_writer;
    //stl_writer.SetDeflection(d);
    //stl_writer.RelativeMode() = false;
    //stl_writer.Write(display->display_on_init_list[0], path.toStdString().c_str());*/
}

void servoce::disp::MainWidget::orient1() {
    display->orient1();
}

void servoce::disp::MainWidget::orient2() {
    display->orient2();
}

/*void servoce::disp::MainWidget::makeBox() {
    TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();
    Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);

    anAisBox->SetColor(Quantity_NOC_AZURE);

    display->getContext()->Display(anAisBox);
}


void servoce::disp::MainWidget::makeCone()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 10.0, 0.0));

    TopoDS_Shape aTopoReducer = BRepPrimAPI_MakeCone(anAxis, 3.0, 1.5, 5.0).Shape();
    Handle(AIS_Shape) anAisReducer = new AIS_Shape(aTopoReducer);

    anAisReducer->SetColor(Quantity_NOC_BISQUE);

    anAxis.SetLocation(gp_Pnt(8.0, 10.0, 0.0));
    TopoDS_Shape aTopoCone = BRepPrimAPI_MakeCone(anAxis, 3.0, 0.0, 5.0).Shape();
    Handle(AIS_Shape) anAisCone = new AIS_Shape(aTopoCone);

    anAisCone->SetColor(Quantity_NOC_CHOCOLATE);

    display->getContext()->Display(anAisReducer);
    display->getContext()->Display(anAisCone);
}

void servoce::disp::MainWidget::makeSphere()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 20.0, 0.0));

    TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 3.0).Shape();
    Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);

    anAisSphere->SetColor(Quantity_NOC_BLUE1);

    display->getContext()->Display(anAisSphere);
}*/