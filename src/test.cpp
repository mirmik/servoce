#include <servoce/test.h>
#include <servoce/wire.h>
#include <servoce/display.h>

#include <Geom_Circle.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <BRepFeat_MakeCylindricalHole.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <gp_Lin.hxx>

#include <vector>

void test() {
	servoce::scene scn;

	double d_p = 76.;
	double r_p = d_p / 2.;
	Handle(Geom_Circle) pitchCircle = new Geom_Circle(gp::XOY(),r_p );

	//
// Радиус и касательная к верхней точке
   gp_Lin radLin(gp::Origin(),gp_Dir(0.,1.,0.));
   gp_Lin tanLin(gp_Pnt(0.,r_p,0.),gp_Dir(1.,0.,0.));
//
// Базовая окружность
   double angle = 20./180.*M_PI;
   double d_b = d_p*cos(angle);
   double r_b = d_b / 2.;
   Handle(Geom_Circle) baseCircle = new Geom_Circle(gp::XOY(),r_b);
//
// Прямая под углом 20 град
   gp_Trsf trsf;
   gp_Ax1 ax1(gp_Pnt(0.,r_p,0.), gp_Dir(0.,0.,1.));
   trsf.SetRotation(ax1,angle);
   gp_Lin actLin = tanLin.Transformed( trsf );



   //
// Эвольвента
   double phi = tan(angle);
   double phi_0 = M_PI/2.+angle - phi;
// Поставим точки
   double h_phi = M_PI/100.;
   //Handle(AIS_Point) aisPoint;
   Handle(Geom_CartesianPoint) geomPoint;
   //Handle(Prs3d_PointAspect) pointAspect = aisDrawer->PointAspect();
   //pointAspect->SetColor(Quantity_NOC_RED);
   //pointAspect->SetTypeOfMarker (Aspect_TOM_POINT);
   //pointAspect->SetScale(3.);
   std::vector<gp_Pnt> pnt;
   double x, y, z=0.;
   for( int i=0; i<50; i++ ) {
      phi = i*h_phi;
      double cs = cos(phi + phi_0);
      double sn = sin(phi + phi_0);
      x = r_b*(cs+phi*sn);
      y = r_b*(sn-phi*cs);
      pnt.emplace_back(x,y,0);
      //geomPoint = new Geom_CartesianPoint(gp_Pnt(x,y,0.));
      //aisPoint = new AIS_Point(geomPoint);
      //myAISContext->Display(aisPoint,FALSE);
   }
   //myAISContext->DisplayAll();



   //
// Интерполяция
// Определяем массив из n_point точек
   Handle(TColgp_HArray1OfPnt) points = new TColgp_HArray1OfPnt(1,pnt.size()+1);
   for(int i=0; i<pnt.size(); i++ )
      points->SetValue(i+1,pnt[i]);
// Создаем объект класса
   GeomAPI_Interpolate interpolate(points,Standard_False,Precision::Approximation());
// Выполняем интерполяцию
   interpolate.Perform();
// Возвращается построенная BSpline-кривая
   Handle(Geom_BSplineCurve) toothCurve = interpolate.Curve();



double r_d = 10;

   // Ставим три точки: 0 -- конец дуги впадины, 1 -- угловая, 2 -- конец эвольвенты
// Точка 2 лежит на базовой окружности
   pnt[2] = toothCurve->Value(toothCurve->FirstParameter());
// Переносим ее по радиусу на окружность впадин
   phi = acos( pnt[2].X()/r_b );
   pnt[1].SetCoord(r_d*cos(phi),r_d*sin(phi),0.);
// и сдвигаемся на такое же расстояние по окружности впаден
   phi -= (r_b-r_d) / r_d;
   pnt[0].SetCoord(r_d*cos(phi),r_d*sin(phi),0.);
//
// Строим сопряжение между дугой окружности впаден и эвольвентой (кривая Безье)
// Задаем опорные точки
   TColgp_Array1OfPnt array1OfPnt(1,3);
   array1OfPnt.SetValue(1, pnt[0]);
   array1OfPnt.SetValue(2, pnt[1]);
   array1OfPnt.SetValue(3, pnt[2]);
// Строим кривую
   Handle(Geom_BezierCurve) filletCurve = new Geom_BezierCurve(array1OfPnt);



   scn.add(servoce::wire(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(toothCurve))));
   scn.add(servoce::wire(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(filletCurve))));
   servoce::display(scn);
/*
   //
// ----- Строим контур сектора зуба
   BRepBuilderAPI_MakeWire mkWireTooth;
   TopoDS_Edge wireEdge;
//
// Ребро: по окружности впаден справа
// Ставим две точки: 0 -- середина дуги впадины, 1 -- конец кривой сопряжения
   double phi0 = M_PI*(0.5 - module/r_p/4.);
   double phi1 = phi;
   wireEdge = BRepBuilderAPI_MakeEdge(dedenCircle,phi0,phi1);
   mkWireTooth.Add(wireEdge);
//
// Ребро: по кривой сопряжения
   wireEdge = BRepBuilderAPI_MakeEdge(filletCurve);
   mkWireTooth.Add(wireEdge);
//
// Ребро: по эвольвенте
   wireEdge = BRepBuilderAPI_MakeEdge(toothCurve);
   mkWireTooth.Add(wireEdge);
//
// Отражаем правую эвольвенту зуба относительно его средней линии
   phi = M_PI/2./n_t;
   gp_Ax2 ax2(gp_Pnt(0.,0.,0.), gp_Dir(d_p*cos(phi),d_p*sin(phi),0.));
   Handle(Geom_Curve) toothMirr = Handle (Geom_Curve)::DownCast(toothCurve->Mirrored (ax2));
// Дуга верхушки зуба
   pnt[0] = toothCurve->Value(toothCurve->LastParameter());
   pnt[1] = toothMirr->Value(toothMirr->LastParameter());
   phi0 = acos( pnt[0].X()/r_a);
   phi1 = acos( pnt[1].X()/r_a);
   wireEdge = BRepBuilderAPI_MakeEdge(addenCircle,phi0,phi1);
   mkWireTooth.Add(wireEdge);
//
// Ребро: по левой эвольвенте
   wireEdge = BRepBuilderAPI_MakeEdge(toothMirr);
   mkWireTooth.Add(wireEdge);
//
// Отражаем правую кривую сопряжения
   Handle(Geom_Curve) filletMirr = Handle (Geom_Curve)::DownCast(filletCurve->Mirrored (ax2));
   wireEdge = BRepBuilderAPI_MakeEdge(filletMirr);
   mkWireTooth.Add(wireEdge);
//
// Ребро: по окружности впаден слева
// Ставим две точки: 0 -- середина дуги впадины, 1 -- конец кривой сопряжения
   phi0 = M_PI*(0.5 + 3.*module/r_p/4.);
   pnt[0] = filletMirr->Value(filletMirr->FirstParameter());
   phi1 = acos( pnt[0].X()/r_d);
   wireEdge = BRepBuilderAPI_MakeEdge(dedenCircle,phi1,phi0);
   mkWireTooth.Add(wireEdge);




      TopoDS_Wire toothWire = mkWireTooth.Wire();
   BRepBuilderAPI_MakeWire mkWireGear(toothWire);
// Поворачиваем и присоединяем
   phi = 2.*M_PI/n_t;
   trsf.SetRotation(gp_Ax1(gp::Origin(), gp_Dir(0.,0.,1.)),phi);
   TopLoc_Location location(trsf);
   for( int i=1; i<n_t; i++ ) {
      toothWire.Move(location);
      mkWireGear.Add(toothWire);
   }




   //
// Строим грань по контуру
   BRepBuilderAPI_MakeFace mkFace(mkWireGear.Wire());
//
// Выдавливаем грань
   BRepPrimAPI_MakePrism mkPrism(mkFace.Shape(), gp_Vec(0.0, 0.0, 10.));
   TopoDS_Shape gear = mkPrism.Shape();
//
// отверстие 10 мм
   gp_Ax1 axHole(gp::Origin(), gp_Dir(0.,0.,1.));
   Standard_Real d_hole = 10.;
   BRepFeat_MakeCylindricalHole mkHole;
   mkHole.Init(gear, axHole);
   mkHole.Perform(d_hole/2.0);
   gear = mkHole.Shape();




   // Углубление
   TopoDS_Shape ring;
   {
   // Точки профиля
      TColgp_Array1OfPnt array1OfPnt(1,5);
      double r = 10.;
      double w = 20.;
      array1OfPnt(1) = gp_Pnt( r, 0.0, 0.0 );
      array1OfPnt(2) = gp_Pnt( r+w, 0.0, 0.0);
      array1OfPnt(3) = gp_Pnt( r+w, 0.0, -1.0);
      array1OfPnt(4) = gp_Pnt( r, 0.0, -1.0);
      array1OfPnt(5) = gp_Pnt(r, 0.0, 0.0 );
   // Строим по ним контур
      BRepBuilderAPI_MakeWire mkWire;
      for ( int i = 1; i < 5; i++) {
         BRepBuilderAPI_MakeEdge mkEdge(array1OfPnt(i), array1OfPnt(i+1));
         mkWire.Add(mkEdge);
      }
   // Превращаем контур в грань
      TopoDS_Face face = BRepBuilderAPI_MakeFace(mkWire.Wire());
   // Revolve the face around an axis
      gp_Ax1 ax1(gp_Pnt(0,0,0),gp_Dir(0,0,1));
      ring = BRepPrimAPI_MakeRevol(face, ax1).Shape();
   }
//
// Делаем улубление сверху
   gp_Trsf move = gp_Trsf();
   move.SetTranslation(gp_Pnt(0,0,0), gp_Pnt(0,0, 10.0));
   TopoDS_Shape moved_ring =
               BRepBuilderAPI_Transform(ring, move, false);
   gear = BRepAlgoAPI_Cut(gear, moved_ring).Shape();
// и снизу
   move.SetTranslation(gp_Pnt(0,0,0), gp_Pnt(0,0, 1.0));
   moved_ring = BRepBuilderAPI_Transform(ring, move, false);
   gear = BRepAlgoAPI_Cut(gear, moved_ring).Shape();*/
}