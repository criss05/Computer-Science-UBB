#include <assert.h>
#include "Matrix.h"
#include <iostream>

using namespace std;

void testAll() {
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);


	Matrix m2(4, 4);
	m2.modify(1, 1, 6);
	m2.modify(3, 3, 9);
	m2.modify(0, 2, 37);
	m2.modify(0, 1, 7);
	m2.modify(0, 0, 90);

	assert(m2.positionOf(90) == make_pair(0, 0));
	assert(m2.positionOf(9) == make_pair(3, 3));
	assert(m2.positionOf(10) == make_pair(-1, -1));
}