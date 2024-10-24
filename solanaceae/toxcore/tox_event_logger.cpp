#include "./tox_event_logger.hpp"

bool ToxEventLogger::onToxEvent(const Tox_Event_Conference_Connected*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_CONFERENCE_CONNECTED) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Conference_Invite*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_CONFERENCE_INVITE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Conference_Message*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_CONFERENCE_MESSAGE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Conference_Peer_List_Changed*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_CONFERENCE_PEER_LIST_CHANGED) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Conference_Peer_Name*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_CONFERENCE_PEER_NAME) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Conference_Title*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_CONFERENCE_TITLE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_File_Chunk_Request* e) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FILE_CHUNK_REQUEST)
		<< " frd:" << tox_event_file_chunk_request_get_friend_number(e)
		<< " fnb:" << tox_event_file_chunk_request_get_file_number(e)
		<< " pos:" << tox_event_file_chunk_request_get_position(e)
		<< " len:" << tox_event_file_chunk_request_get_length(e)
		<< "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_File_Recv* e) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FILE_RECV)
		<< " frd:" << tox_event_file_recv_get_friend_number(e)
		<< " fnb:" << tox_event_file_recv_get_file_number(e)
		<< " fnm:" << std::string_view{reinterpret_cast<const char*>(tox_event_file_recv_get_filename(e)), tox_event_file_recv_get_filename_length(e)}
		<< " sze:" << tox_event_file_recv_get_file_size(e)
		<< " knd:" << tox_event_file_recv_get_kind(e)
		<< "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_File_Recv_Chunk*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FILE_RECV_CHUNK) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_File_Recv_Control* e) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FILE_RECV_CONTROL)
		<< " frd:" << tox_event_file_recv_control_get_friend_number(e)
		<< " fnb:" << tox_event_file_recv_control_get_file_number(e)
		<< " ctl:" << tox_event_file_recv_control_get_control(e)
		<< "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Connection_Status*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_CONNECTION_STATUS) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Lossless_Packet*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_LOSSLESS_PACKET) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Lossy_Packet*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_LOSSY_PACKET) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Message*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_MESSAGE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Name*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_NAME) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Read_Receipt*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_READ_RECEIPT) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Request*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_REQUEST) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Status*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_STATUS) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Status_Message*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_STATUS_MESSAGE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Friend_Typing*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_FRIEND_TYPING) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Self_Connection_Status*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_SELF_CONNECTION_STATUS) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Peer_Name*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PEER_NAME) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Peer_Status*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PEER_STATUS) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Topic*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_TOPIC) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Privacy_State*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PRIVACY_STATE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Voice_State*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_VOICE_STATE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Topic_Lock*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_TOPIC_LOCK) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Peer_Limit*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PEER_LIMIT) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Password*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PASSWORD) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Message*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_MESSAGE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Private_Message*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PRIVATE_MESSAGE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Custom_Packet*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_CUSTOM_PACKET) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Custom_Private_Packet*) {
	// too spammy for now
	//_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Invite*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_INVITE) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Peer_Join*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PEER_JOIN) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Peer_Exit* e) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_PEER_EXIT)
		<< " grp:" << tox_event_group_peer_exit_get_group_number(e)
		<< " per:" << tox_event_group_peer_exit_get_peer_id(e)
		<< " xtp:" << tox_event_group_peer_exit_get_exit_type(e)
		<< " nam:" << std::string_view{reinterpret_cast<const char*>(tox_event_group_peer_exit_get_name(e)), tox_event_group_peer_exit_get_name_length(e)}
		<< " prt:" << std::string_view{reinterpret_cast<const char*>(tox_event_group_peer_exit_get_part_message(e)), tox_event_group_peer_exit_get_part_message_length(e)}
		<< "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Self_Join*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_SELF_JOIN) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Join_Fail*) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_JOIN_FAIL) << "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Group_Moderation* e) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_GROUP_MODERATION)
		<< " grp:" << tox_event_group_moderation_get_group_number(e)
		<< " typ:" << tox_event_group_moderation_get_mod_type(e)
		<< " src:" << tox_event_group_moderation_get_source_peer_id(e)
		<< " trg:" << tox_event_group_moderation_get_target_peer_id(e)
		<< "\n";
	return false;
}

bool ToxEventLogger::onToxEvent(const Tox_Event_Dht_Get_Nodes_Response* e) {
	_out << "TOX_EVENT: " << tox_event_to_string(TOX_EVENT_DHT_GET_NODES_RESPONSE)
		//<< " pub:" << tox_event_dht_get_nodes_response_get_public_key(e)
		//<< " ip:" << tox_event_dht_get_nodes_response_get_ip(e)
		//<< " prt:" << tox_event_dht_get_nodes_response_get_port(e)
		<< "\n";
	return false;
}

void ToxEventLogger::subscribeAll(ToxEventProviderI& tep) {
	// TODO: loop + max event
	tep.subscribe(this, TOX_EVENT_SELF_CONNECTION_STATUS);

	tep.subscribe(this, TOX_EVENT_FRIEND_REQUEST);
	tep.subscribe(this, TOX_EVENT_FRIEND_CONNECTION_STATUS);
	tep.subscribe(this, TOX_EVENT_FRIEND_LOSSY_PACKET);
	tep.subscribe(this, TOX_EVENT_FRIEND_LOSSLESS_PACKET);

	tep.subscribe(this, TOX_EVENT_FRIEND_NAME);
	tep.subscribe(this, TOX_EVENT_FRIEND_STATUS);
	tep.subscribe(this, TOX_EVENT_FRIEND_STATUS_MESSAGE);

	tep.subscribe(this, TOX_EVENT_FRIEND_MESSAGE);
	tep.subscribe(this, TOX_EVENT_FRIEND_READ_RECEIPT);
	tep.subscribe(this, TOX_EVENT_FRIEND_TYPING);

	tep.subscribe(this, TOX_EVENT_FILE_CHUNK_REQUEST);
	tep.subscribe(this, TOX_EVENT_FILE_RECV);
	tep.subscribe(this, TOX_EVENT_FILE_RECV_CHUNK);
	tep.subscribe(this, TOX_EVENT_FILE_RECV_CONTROL);

	tep.subscribe(this, TOX_EVENT_CONFERENCE_INVITE);
	tep.subscribe(this, TOX_EVENT_CONFERENCE_CONNECTED);
	tep.subscribe(this, TOX_EVENT_CONFERENCE_PEER_LIST_CHANGED);
	tep.subscribe(this, TOX_EVENT_CONFERENCE_PEER_NAME);
	tep.subscribe(this, TOX_EVENT_CONFERENCE_TITLE);

	tep.subscribe(this, TOX_EVENT_CONFERENCE_MESSAGE);

	tep.subscribe(this, TOX_EVENT_GROUP_PEER_NAME);
	tep.subscribe(this, TOX_EVENT_GROUP_PEER_STATUS);
	tep.subscribe(this, TOX_EVENT_GROUP_TOPIC);
	tep.subscribe(this, TOX_EVENT_GROUP_PRIVACY_STATE);
	tep.subscribe(this, TOX_EVENT_GROUP_VOICE_STATE);
	tep.subscribe(this, TOX_EVENT_GROUP_TOPIC_LOCK);
	tep.subscribe(this, TOX_EVENT_GROUP_PEER_LIMIT);
	tep.subscribe(this, TOX_EVENT_GROUP_PASSWORD);
	tep.subscribe(this, TOX_EVENT_GROUP_MESSAGE);
	tep.subscribe(this, TOX_EVENT_GROUP_PRIVATE_MESSAGE);
#if !NDEBUG
	// TOO spammy
	tep.subscribe(this, TOX_EVENT_GROUP_CUSTOM_PACKET);
	tep.subscribe(this, TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET);
#endif
	tep.subscribe(this, TOX_EVENT_GROUP_INVITE);
	tep.subscribe(this, TOX_EVENT_GROUP_PEER_JOIN);
	tep.subscribe(this, TOX_EVENT_GROUP_PEER_EXIT);
	tep.subscribe(this, TOX_EVENT_GROUP_SELF_JOIN);
	tep.subscribe(this, TOX_EVENT_GROUP_JOIN_FAIL);
	tep.subscribe(this, TOX_EVENT_GROUP_MODERATION);

	// too spammy
	//tep.subscribe(this, TOX_EVENT_DHT_GET_NODES_RESPONSE);
}

