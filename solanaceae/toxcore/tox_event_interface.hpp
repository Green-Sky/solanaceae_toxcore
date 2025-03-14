#pragma once

#include <tox/tox_events.h>

#include <string_view>
#include <vector>

// defines the full event interface for tox event subscription
struct ToxEventI {
	virtual ~ToxEventI(void) {}

	// TODO: rename to onEvent()
#define VIRT_EVENT(x) virtual bool onToxEvent(const x*) { return false; }

	// return true if the event is handled and should not be given down the chain

	VIRT_EVENT(Tox_Event_Conference_Connected)
	VIRT_EVENT(Tox_Event_Conference_Invite)
	VIRT_EVENT(Tox_Event_Conference_Message)
	VIRT_EVENT(Tox_Event_Conference_Peer_List_Changed)
	VIRT_EVENT(Tox_Event_Conference_Peer_Name)
	VIRT_EVENT(Tox_Event_Conference_Title)

	VIRT_EVENT(Tox_Event_File_Chunk_Request)
	VIRT_EVENT(Tox_Event_File_Recv)
	VIRT_EVENT(Tox_Event_File_Recv_Chunk)
	VIRT_EVENT(Tox_Event_File_Recv_Control)

	VIRT_EVENT(Tox_Event_Friend_Connection_Status)
	VIRT_EVENT(Tox_Event_Friend_Lossless_Packet)
	VIRT_EVENT(Tox_Event_Friend_Lossy_Packet)
	VIRT_EVENT(Tox_Event_Friend_Message)
	VIRT_EVENT(Tox_Event_Friend_Name)
	VIRT_EVENT(Tox_Event_Friend_Read_Receipt)
	VIRT_EVENT(Tox_Event_Friend_Request)
	VIRT_EVENT(Tox_Event_Friend_Status)
	VIRT_EVENT(Tox_Event_Friend_Status_Message)
	VIRT_EVENT(Tox_Event_Friend_Typing)

	VIRT_EVENT(Tox_Event_Self_Connection_Status)

	VIRT_EVENT(Tox_Event_Group_Peer_Name)
	VIRT_EVENT(Tox_Event_Group_Peer_Status)
	VIRT_EVENT(Tox_Event_Group_Topic)
	VIRT_EVENT(Tox_Event_Group_Privacy_State)
	VIRT_EVENT(Tox_Event_Group_Voice_State)
	VIRT_EVENT(Tox_Event_Group_Topic_Lock)
	VIRT_EVENT(Tox_Event_Group_Peer_Limit)
	VIRT_EVENT(Tox_Event_Group_Password)
	VIRT_EVENT(Tox_Event_Group_Message)
	VIRT_EVENT(Tox_Event_Group_Private_Message)
	VIRT_EVENT(Tox_Event_Group_Custom_Packet)
	VIRT_EVENT(Tox_Event_Group_Custom_Private_Packet)
	VIRT_EVENT(Tox_Event_Group_Invite)
	VIRT_EVENT(Tox_Event_Group_Peer_Join)
	VIRT_EVENT(Tox_Event_Group_Peer_Exit)
	VIRT_EVENT(Tox_Event_Group_Self_Join)
	VIRT_EVENT(Tox_Event_Group_Join_Fail)
	VIRT_EVENT(Tox_Event_Group_Moderation)

	VIRT_EVENT(Tox_Event_Dht_Nodes_Response)

#undef VIRT_EVENT
};

// defines the interface where to subscribe
// tox event enum is defined differently than what we expect for utils
struct ToxEventProviderI {
	static constexpr const char* version {"2"};

	using enumType = Tox_Event_Type;

	// TODO: keep in sync with utils
	struct SubscriptionReference {
		ToxEventProviderI& _ep;
		ToxEventI* _object {nullptr};
		std::vector<enumType> _subs;

		SubscriptionReference(ToxEventProviderI& ep, ToxEventI* object) :
			_ep(ep), _object(object)
		{
		}

		~SubscriptionReference(void) {
			for (const enumType et : _subs) {
				_ep.unsubscribe(_object, et);
			}
		}

		SubscriptionReference& subscribe(const enumType event_type) {
			_ep.subscribe(_object, event_type);
			_subs.push_back(event_type);
			return *this;
		}
	};


	virtual ~ToxEventProviderI(void) {}

	virtual void subscribe(ToxEventI* object, const Tox_Event_Type event_type) = 0;
	virtual void unsubscribe(ToxEventI* object, const Tox_Event_Type event_type) = 0;

	SubscriptionReference newSubRef(ToxEventI* object) {
		return SubscriptionReference{*this, object};
	}
};

constexpr Tox_Event_Type tox_event_from_string(const std::string_view str) {
#define CASE_E_TYPE(x) if (str == #x) return Tox_Event_Type::x;

	CASE_E_TYPE(TOX_EVENT_SELF_CONNECTION_STATUS)

	CASE_E_TYPE(TOX_EVENT_FRIEND_REQUEST)
	CASE_E_TYPE(TOX_EVENT_FRIEND_CONNECTION_STATUS)
	CASE_E_TYPE(TOX_EVENT_FRIEND_LOSSY_PACKET)
	CASE_E_TYPE(TOX_EVENT_FRIEND_LOSSLESS_PACKET)

	CASE_E_TYPE(TOX_EVENT_FRIEND_NAME)
	CASE_E_TYPE(TOX_EVENT_FRIEND_STATUS)
	CASE_E_TYPE(TOX_EVENT_FRIEND_STATUS_MESSAGE)

	CASE_E_TYPE(TOX_EVENT_FRIEND_MESSAGE)
	CASE_E_TYPE(TOX_EVENT_FRIEND_READ_RECEIPT)
	CASE_E_TYPE(TOX_EVENT_FRIEND_TYPING)

	CASE_E_TYPE(TOX_EVENT_FILE_CHUNK_REQUEST)
	CASE_E_TYPE(TOX_EVENT_FILE_RECV)
	CASE_E_TYPE(TOX_EVENT_FILE_RECV_CHUNK)
	CASE_E_TYPE(TOX_EVENT_FILE_RECV_CONTROL)

	CASE_E_TYPE(TOX_EVENT_CONFERENCE_INVITE)
	CASE_E_TYPE(TOX_EVENT_CONFERENCE_CONNECTED)
	CASE_E_TYPE(TOX_EVENT_CONFERENCE_PEER_LIST_CHANGED)
	CASE_E_TYPE(TOX_EVENT_CONFERENCE_PEER_NAME)
	CASE_E_TYPE(TOX_EVENT_CONFERENCE_TITLE)

	CASE_E_TYPE(TOX_EVENT_CONFERENCE_MESSAGE)

	CASE_E_TYPE(TOX_EVENT_GROUP_PEER_NAME)
	CASE_E_TYPE(TOX_EVENT_GROUP_PEER_STATUS)
	CASE_E_TYPE(TOX_EVENT_GROUP_TOPIC)
	CASE_E_TYPE(TOX_EVENT_GROUP_PRIVACY_STATE)
	CASE_E_TYPE(TOX_EVENT_GROUP_VOICE_STATE)
	CASE_E_TYPE(TOX_EVENT_GROUP_TOPIC_LOCK)
	CASE_E_TYPE(TOX_EVENT_GROUP_PEER_LIMIT)
	CASE_E_TYPE(TOX_EVENT_GROUP_PASSWORD)
	CASE_E_TYPE(TOX_EVENT_GROUP_MESSAGE)
	CASE_E_TYPE(TOX_EVENT_GROUP_PRIVATE_MESSAGE)
	CASE_E_TYPE(TOX_EVENT_GROUP_CUSTOM_PACKET)
	CASE_E_TYPE(TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET)
	CASE_E_TYPE(TOX_EVENT_GROUP_INVITE)
	CASE_E_TYPE(TOX_EVENT_GROUP_PEER_JOIN)
	CASE_E_TYPE(TOX_EVENT_GROUP_PEER_EXIT)
	CASE_E_TYPE(TOX_EVENT_GROUP_SELF_JOIN)
	CASE_E_TYPE(TOX_EVENT_GROUP_JOIN_FAIL)
	CASE_E_TYPE(TOX_EVENT_GROUP_MODERATION)

	CASE_E_TYPE(TOX_EVENT_DHT_NODES_RESPONSE)

	return Tox_Event_Type::TOX_EVENT_INVALID;

#undef CASE_E_TYPE
}

// why do you exists?
static inline std::string_view tox_event_to_string(const Tox_Event_Type e) {
	return tox_event_type_to_string(e);
}

