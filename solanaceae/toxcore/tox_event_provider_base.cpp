#include "./tox_event_provider_base.hpp"

void ToxEventProviderBase::dispatchEvents(const Tox_Events* events) {
	if (events == nullptr) {
		return;
	}

	// forward events to event handlers

	// TODO: make order independent (construct string and lookup event id)
#define HANDLE_EVENT(x) \
	for (size_t i = 0; i < tox_events_get_##x##_size(events); i++) { \
		for (auto* tei : _subscribers.at(event_type_index)) { \
			if (tei->onToxEvent(tox_events_get_##x(events, i))) { \
				break; \
			} \
		} \
	} \
	event_type_index++;

	size_t event_type_index = 0;

	// IMPORTANT: the order defines the type
	HANDLE_EVENT(self_connection_status);

	HANDLE_EVENT(friend_request);
	HANDLE_EVENT(friend_connection_status);
	HANDLE_EVENT(friend_lossy_packet);
	HANDLE_EVENT(friend_lossless_packet);

	HANDLE_EVENT(friend_name);
	HANDLE_EVENT(friend_status);
	HANDLE_EVENT(friend_status_message);

	HANDLE_EVENT(friend_message);
	HANDLE_EVENT(friend_read_receipt);
	HANDLE_EVENT(friend_typing);

	HANDLE_EVENT(file_chunk_request);
	HANDLE_EVENT(file_recv);
	HANDLE_EVENT(file_recv_chunk);
	HANDLE_EVENT(file_recv_control);

	HANDLE_EVENT(conference_invite);
	HANDLE_EVENT(conference_connected);
	HANDLE_EVENT(conference_peer_list_changed);
	HANDLE_EVENT(conference_peer_name);
	HANDLE_EVENT(conference_title);

	HANDLE_EVENT(conference_message);

	HANDLE_EVENT(group_peer_name);
	HANDLE_EVENT(group_peer_status);
	HANDLE_EVENT(group_topic);
	HANDLE_EVENT(group_privacy_state);
	HANDLE_EVENT(group_voice_state);
	HANDLE_EVENT(group_topic_lock);
	HANDLE_EVENT(group_peer_limit);
	HANDLE_EVENT(group_password);
	HANDLE_EVENT(group_message);
	HANDLE_EVENT(group_private_message);
	HANDLE_EVENT(group_custom_packet);
	HANDLE_EVENT(group_custom_private_packet);
	HANDLE_EVENT(group_invite);
	HANDLE_EVENT(group_peer_join);
	HANDLE_EVENT(group_peer_exit);
	HANDLE_EVENT(group_self_join);
	HANDLE_EVENT(group_join_fail);
	HANDLE_EVENT(group_moderation);
#undef HANDLE_EVENT
}

void ToxEventProviderBase::subscribe(ToxEventI* object, const Tox_Event_Type event_type) {
	_subscribers.at(event_type).push_back(object);
}

