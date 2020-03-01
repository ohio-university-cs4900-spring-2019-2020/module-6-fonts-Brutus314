#include <sstream>

#include "NetMsgCameraObject.h"
#include "ManagerEnvironmentConfiguration.h"
#include "ManagerGLView.h"
#include "GLViewFonts.h"
#include "WorldContainer.h"
#include "MGLFTGLString.h"

#include <cmath>

using namespace Aftr;

NetMsgMacroDefinition(NetMsgCameraObject);

bool NetMsgCameraObject::is_inserted = false;
WO* NetMsgCameraObject::object = nullptr;
WOFTGLString* NetMsgCameraObject::banner = nullptr;

// Memory handling
/*NetMsgCameraObject::~NetMsgCameraObject() {
	delete object;
}*/

// Send location as payload
bool NetMsgCameraObject::toStream(NetMessengerStreamBuffer& os) const {
	os << location.x << location.y << location.z;
	os << look.x << look.y << look.z;
	os << name;
	return true;
}

// Receive location as payload
bool NetMsgCameraObject::fromStream(NetMessengerStreamBuffer& is) {
	is >> location.x >> location.y >> location.z;
	is >> look.x >> look.y >> look.z;
	is >> name;
	return true;
}

// Update position, and add to world if it isn't already
void NetMsgCameraObject::onMessageArrived() {
	// These checks are needed to actually initialize object due to manager dependencies
	if (object == nullptr) object = WO::New(ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl", Vector(1, 1, 1));
	if (banner == nullptr) {
		banner = WOFTGLString::New(ManagerEnvironmentConfiguration::getSMM() + "/fonts/COMIC.TTF", 30);
		banner->getModelT<MGLFTGLString>()->setFontColor(aftrColor4f(1.0f, 0.0f, 0.0f, 1.0f));
		banner->getModelT<MGLFTGLString>()->setSize(10, 10);
		banner->getModelT<MGLFTGLString>()->setText(name);
		banner->setText(name);
	}
	Vector cam_pos = ManagerGLView::getGLView()->getCamera()->getPosition();
	Mat4 m;
	m = Mat4T<float>::scaleIdentityMat(Vector(1, 1, 1)).rotate(Vector(1, 0, 0), PI / 2);
	m = m.rotate(Vector(0, 0, 1), atan2(location.y - cam_pos.y, location.x - cam_pos.x) - (PI / 2));
	// Update the position and look direction
	object->setPosition(location);
	object->getModel()->setLookDirection(look);
	banner->setPosition(location + Vector(0, 0, 10)); // Make the banner a little above the model
	banner->getModel()->setDisplayMatrix(m);
	if (!is_inserted) {
		ManagerGLView::getGLView()->getWorldContainer()->push_back(object);
		ManagerGLView::getGLView()->getWorldContainer()->push_back(banner);
		is_inserted = true;
	}
}

// For debug purposes
std::string NetMsgCameraObject::toString() const {
	std::stringstream ss;

	ss << NetMsg::toString();
	ss << "  Payload: \n"
		<< "Position: x = " << location.x << " y = " << location.y << " z = " << location.z << "\n"
		<< "Look: x = " << look.x << " y = " << look.y << " z = " << look.z << "\n"
		<< "Name: " << name << "\n";
	return ss.str();
}
