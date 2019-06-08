#include <servoce/servoce.h>
#include <servoce/display.h>
#include <Font_BRepTextBuilder.hxx>

#include <nos/dprint.h>

int main() {
	Font_BRepTextBuilder builder;

	Font_BRepFont font("/home/mirmik/project/privdocs/bujin/poster/fonts/keetano_katakana.ttf", 10);
	//Font_FTFont ffont;
	//Font_TextFormatter formatter;

	dprln(0);
	NCollection_String collection("Mirmik was Here");

	dprln(1);
	//formatter.Append(collection, ffont);

	dprln(2);
	TopoDS_Shape text = builder.Perform (font, collection);

	servoce::shape shp(text);
	auto m = servoce::make_linear_extrude(shp, 5);

	dprln(3);
	servoce::scene scn;
	dprln(4);
	scn.add(m);

	dprln(5);
	servoce::display(scn);
}