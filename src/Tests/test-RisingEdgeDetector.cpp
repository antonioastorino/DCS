#include "test-RisingEdgeDetector.hpp"

void risingEdgeDetectorTest() {
	DCSLog::printTestName("Rising edge detector");
	DCSEngine::initialize(5);
	DCSAnd and0("And0");
	DCSNot not0("Not0");
	DCSUnitDelay del0("Del0");
	DCSUnitDelay del1("Del1");
	DCSInput in0("In0");
	DCSOutput out0("Out0");

	in0.makeSignal(transitions{5,20});
	
	in0.connect(&and0, 0, 0, "In");
	in0.connect(&not0, 0, 0);
	not0.connect(&del0, 0, 0);
	del0.connect(&del1, 0, 0);
	del1.connect(&and0, 0, 1);
	and0.connect(&out0, 0, 0, "Out");
	
	DCSEngine::run(20);
}
