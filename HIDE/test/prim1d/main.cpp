#include <servoce/wire.h>
#include <servoce/display.h>

int main() {
	auto segment = servoce::make_segment ( {-3, -10, 0}, {-3, 10, 5} );
	auto polysegment = servoce::make_polysegment ( {{-13, -10, 0}, {-13, 10, 5}, {-2, 6, 3}}, /*closed=*/true );
	auto helix = servoce::make_long_helix(1, 20, 10, 0, false);

	servoce::scene scn;
	scn.add(segment);
	scn.add(polysegment);
	scn.add(helix.right(30));

	servoce::display(scn);
}