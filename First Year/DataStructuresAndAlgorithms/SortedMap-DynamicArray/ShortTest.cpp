#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
#include <iostream>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());

    //my tests
    SortedMap sm1(relatie1);
    SortedMap sm2(relatie1);
    sm1.add(1, 3);
    sm1.add(5, 2);
    sm1.add(2, 7);

    sm2.add(1, 1);
    sm2.add(5, 9);
    assert(sm1.updateValues(sm2) == 2);
    SMIterator it1 = sm1.iterator();
    it1.first();
    TElem e1 = it1.getCurrent();
    assert(e1.second == 1);
    it1.next();
    e1 = it1.getCurrent();
    assert(e1.second == 7);
    it1.next();
    e1 = it1.getCurrent();
    assert(e1.second == 9);
    it1.next();
}

