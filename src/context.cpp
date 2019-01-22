/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include "context.hpp"
using namespace std;

Context::Context(ContextName type, gcn::Container *topContainer) : 
    parent(topContainer), name(type)
{
	top.setWidth(parent->getWidth());
	top.setHeight(parent->getHeight());
}

Context::~Context() {
    parent->remove(&top);
}

ContextName const Context::getName() {
    return name;
}
