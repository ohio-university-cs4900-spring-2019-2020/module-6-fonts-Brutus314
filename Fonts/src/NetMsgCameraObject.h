#pragma once

#include "NetMsg.h"
#include "Vector.h"
#include "WO.h"
#include "WOFTGLString.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {
	class NetMsgCameraObject : public NetMsg {
	public:
		NetMsgMacroDeclaration(NetMsgCameraObject);

		//NetMsgCameraObject();
		//virtual ~NetMsgCameraObject();
		virtual bool toStream(NetMessengerStreamBuffer& os) const;
		virtual bool fromStream(NetMessengerStreamBuffer& is);
		virtual void onMessageArrived();
		virtual std::string toString() const;

		Vector location;
		Vector look;
		std::string name;
	protected:
		static bool is_inserted;
		static WO* object;
		static WOFTGLString* banner;
	};
}

#endif