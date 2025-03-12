#include "./tox_event_provider_base.hpp"

#include <iostream> // meh

void ToxEventProviderBase::dispatchEvents(const Tox_Events* events) {
	if (events == nullptr) {
		return;
	}

	// forward events to event handlers

	const uint32_t event_count = tox_events_get_size(events);
	for (uint32_t j = 0; j < event_count; ++j) {
		const Tox_Event *event = tox_events_get(events, j);

		switch (tox_event_get_type(event)) {

#define HANDLE_EVENT(e_x, x) \
			case Tox_Event_Type::TOX_EVENT_##e_x: \
				for (auto* tei : _subscribers.at(tox_event_get_type(event))) { \
					if (tei->onToxEvent(tox_event_get_##x(event))) { \
						break; \
					} \
				} \
				break;

	HANDLE_EVENT(SELF_CONNECTION_STATUS, self_connection_status);
	HANDLE_EVENT(FRIEND_REQUEST, friend_request);
	HANDLE_EVENT(FRIEND_CONNECTION_STATUS, friend_connection_status);
	HANDLE_EVENT(FRIEND_LOSSY_PACKET, friend_lossy_packet);
	HANDLE_EVENT(FRIEND_LOSSLESS_PACKET, friend_lossless_packet);
	HANDLE_EVENT(FRIEND_NAME, friend_name);
	HANDLE_EVENT(FRIEND_STATUS, friend_status);
	HANDLE_EVENT(FRIEND_STATUS_MESSAGE, friend_status_message);
	HANDLE_EVENT(FRIEND_MESSAGE, friend_message);
	HANDLE_EVENT(FRIEND_READ_RECEIPT, friend_read_receipt);
	HANDLE_EVENT(FRIEND_TYPING, friend_typing);
	HANDLE_EVENT(FILE_CHUNK_REQUEST, file_chunk_request);
	HANDLE_EVENT(FILE_RECV, file_recv);
	HANDLE_EVENT(FILE_RECV_CHUNK, file_recv_chunk);
	HANDLE_EVENT(FILE_RECV_CONTROL, file_recv_control);
	HANDLE_EVENT(CONFERENCE_INVITE, conference_invite);
	HANDLE_EVENT(CONFERENCE_CONNECTED, conference_connected);
	HANDLE_EVENT(CONFERENCE_PEER_LIST_CHANGED, conference_peer_list_changed);
	HANDLE_EVENT(CONFERENCE_PEER_NAME, conference_peer_name);
	HANDLE_EVENT(CONFERENCE_TITLE, conference_title);
	HANDLE_EVENT(CONFERENCE_MESSAGE, conference_message);
	HANDLE_EVENT(GROUP_PEER_NAME, group_peer_name);
	HANDLE_EVENT(GROUP_PEER_STATUS, group_peer_status);
	HANDLE_EVENT(GROUP_TOPIC, group_topic);
	HANDLE_EVENT(GROUP_PRIVACY_STATE, group_privacy_state);
	HANDLE_EVENT(GROUP_VOICE_STATE, group_voice_state);
	HANDLE_EVENT(GROUP_TOPIC_LOCK, group_topic_lock);
	HANDLE_EVENT(GROUP_PEER_LIMIT, group_peer_limit);
	HANDLE_EVENT(GROUP_PASSWORD, group_password);
	HANDLE_EVENT(GROUP_MESSAGE, group_message);
	HANDLE_EVENT(GROUP_PRIVATE_MESSAGE, group_private_message);
	HANDLE_EVENT(GROUP_CUSTOM_PACKET, group_custom_packet);
	HANDLE_EVENT(GROUP_CUSTOM_PRIVATE_PACKET, group_custom_private_packet);
	HANDLE_EVENT(GROUP_INVITE, group_invite);
	HANDLE_EVENT(GROUP_PEER_JOIN, group_peer_join);
	HANDLE_EVENT(GROUP_PEER_EXIT, group_peer_exit);
	HANDLE_EVENT(GROUP_SELF_JOIN, group_self_join);
	HANDLE_EVENT(GROUP_JOIN_FAIL, group_join_fail);
	HANDLE_EVENT(GROUP_MODERATION, group_moderation);
	// FIXME: get pr merged and update
			case Tox_Event_Type::TOX_EVENT_DHT_GET_NODES_RESPONSE: \
				for (auto* tei : _subscribers.at(tox_event_get_type(event))) { \
					if (tei->onToxEvent(tox_event_get_dht_nodes_response(event))) { \
						break; \
					} \
				} \
				break;
#undef HANDLE_EVENT

			default:
				std::cerr << "TOXEVENT error: unhandled eventtype " << tox_event_get_type(event) << "\n";
				break;
		}
	}
}

void ToxEventProviderBase::subscribe(ToxEventI* object, const Tox_Event_Type event_type) {
	_subscribers.at(event_type).push_back(object);
}

void ToxEventProviderBase::unsubscribe(ToxEventI* object, const Tox_Event_Type event_type) {
	auto& o_vec = _subscribers.at(static_cast<size_t>(event_type));
	for (auto o_it = o_vec.cbegin(); o_it != o_vec.cend(); o_it++) {
		if (*o_it == object) {
			o_vec.erase(o_it);
			break;
		}
	}
}

