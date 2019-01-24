/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#ifndef _H_CHAT_
#define _H_CHAT_

#include <map>
#include <string>
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include "ui/chatwindow.hpp"

class ChatManager final : public gcn::ActionListener {
public:
	explicit ChatManager(gcn::Container *topContainer);
	~ChatManager();
	void addMessage(const std::string &sender, const std::string &message);
	void action(const gcn::ActionEvent &action) override;

private:
	std::map<std::string, ChatWindow*> windows;
	gcn::Container* top = nullptr;
};

#endif // !_H_CHAT_

 