#include "Factory.h"

void Factory::fillScene(Scene &scene) {
	for(auto group: groups) {
		group(&scene);
	}
}
