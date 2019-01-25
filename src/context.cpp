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

void Context::enter() {
	parent->add(&top);
}

void Context::leave() {
	parent->remove(&top);
}

void Context::addWidget(gcn::Widget * widget, int x, int y){
	top.add(widget, x, y);
}

/**
 *  Helper function to insert widgets centered w.r.t. a parent
 *  \param widget widget to insert
 */
void Context::addCenteredWidget(gcn::Widget * widget) {
	int x = (top.getWidth() - widget->getWidth()) / 2;
	int y = (top.getHeight() - widget->getHeight()) / 2;

	addWidget(widget, x, y);
}
