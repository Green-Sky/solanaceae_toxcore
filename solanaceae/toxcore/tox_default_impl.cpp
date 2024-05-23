#include "./tox_default_impl.hpp"

Tox_Connection ToxDefaultImpl::toxSelfGetConnectionStatus(void) {
	return tox_self_get_connection_status(_tox);
}

uint32_t ToxDefaultImpl::toxIterationInterval(void) {
	return tox_iteration_interval(_tox);
}

std::vector<uint8_t> ToxDefaultImpl::toxSelfGetAddress(void) {
	std::vector<uint8_t> self_addr{};
	self_addr.resize(TOX_ADDRESS_SIZE);
	tox_self_get_address(_tox, self_addr.data());
	return self_addr;
}

void ToxDefaultImpl::toxSelfSetNospam(uint32_t nospam) {
	tox_self_set_nospam(_tox, nospam);
}

uint32_t ToxDefaultImpl::toxSelfGetNospam(void) {
	return tox_self_get_nospam(_tox);
}

std::vector<uint8_t> ToxDefaultImpl::toxSelfGetPublicKey(void) {
	std::vector<uint8_t> self_pub{};
	self_pub.resize(TOX_PUBLIC_KEY_SIZE);
	tox_self_get_public_key(_tox, self_pub.data());
	return self_pub;
}

Tox_Err_Set_Info ToxDefaultImpl::toxSelfSetName(std::string_view name) {
	Tox_Err_Set_Info err = TOX_ERR_SET_INFO_OK;
	tox_self_set_name(_tox, reinterpret_cast<const uint8_t*>(name.data()), name.size(), &err);
	return err;
}

std::string ToxDefaultImpl::toxSelfGetName(void) {
	std::string name;
	name.resize(tox_self_get_name_size(_tox));
	tox_self_get_name(_tox, reinterpret_cast<uint8_t*>(name.data()));
	return name;
}

Tox_Err_Set_Info ToxDefaultImpl::toxSelfSetStatusMessage(std::string_view status_message) {
	Tox_Err_Set_Info err = TOX_ERR_SET_INFO_OK;
	tox_self_set_status_message(_tox, reinterpret_cast<const uint8_t*>(status_message.data()), status_message.size(), &err);
	return err;
}

std::string ToxDefaultImpl::toxSelfGetStatusMessage(void) {
	std::string status;
	status.resize(tox_self_get_status_message_size(_tox));
	tox_self_get_status_message(_tox, reinterpret_cast<uint8_t*>(status.data()));
	return status;
}

void ToxDefaultImpl::toxSelfSetStatus(Tox_User_Status status) {
	tox_self_set_status(_tox, status);
}

Tox_User_Status ToxDefaultImpl::toxSelfGetStatus(void) {
	return tox_self_get_status(_tox);
}

std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> ToxDefaultImpl::toxFriendAdd(const std::vector<uint8_t>& address, std::string_view message) {
	// TODO: check size
	Tox_Err_Friend_Add err = TOX_ERR_FRIEND_ADD_OK;
	auto res = tox_friend_add(_tox, address.data(), reinterpret_cast<const uint8_t*>(message.data()), message.size(), &err);
	if (err == TOX_ERR_FRIEND_ADD_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> ToxDefaultImpl::toxFriendAddNorequest(const std::vector<uint8_t>& public_key) {
	// TODO: check size
	Tox_Err_Friend_Add err = TOX_ERR_FRIEND_ADD_OK;
	auto res = tox_friend_add_norequest(_tox, public_key.data(), &err);
	if (err == TOX_ERR_FRIEND_ADD_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Friend_Delete ToxDefaultImpl::toxFriendDelete(uint32_t friend_number) {
	Tox_Err_Friend_Delete err = TOX_ERR_FRIEND_DELETE_OK;
	tox_friend_delete(_tox, friend_number, &err);
	return err;
}

std::tuple<std::optional<uint32_t>, Tox_Err_Friend_By_Public_Key> ToxDefaultImpl::toxFriendByPublicKey(const std::vector<uint8_t>& public_key) {
	// TODO: check size
	Tox_Err_Friend_By_Public_Key err = TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK;
	auto res = tox_friend_by_public_key(_tox, public_key.data(), &err);
	if (err == TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

bool ToxDefaultImpl::toxFriendExists(uint32_t friend_number) {
	return tox_friend_exists(_tox, friend_number);
}

size_t ToxDefaultImpl::toxSelfGetFriendListSize(void) {
	return tox_self_get_friend_list_size(_tox);
}

std::vector<uint32_t> ToxDefaultImpl::toxSelfGetFriendList(void) {
	std::vector<uint32_t> friend_list;
	friend_list.resize(tox_self_get_friend_list_size(_tox));
	tox_self_get_friend_list(_tox, friend_list.data());
	return friend_list;
}

std::optional<std::vector<uint8_t>> ToxDefaultImpl::toxFriendGetPublicKey(uint32_t friend_number) {
	std::vector<uint8_t> pub(TOX_PUBLIC_KEY_SIZE);
	Tox_Err_Friend_Get_Public_Key err = TOX_ERR_FRIEND_GET_PUBLIC_KEY_OK;
	tox_friend_get_public_key(_tox, friend_number, pub.data(), &err);
	if (err == TOX_ERR_FRIEND_GET_PUBLIC_KEY_OK) {
		return pub;
	} else {
		return std::nullopt;
	}
}

std::optional<uint64_t> ToxDefaultImpl::toxFriendGetLastOnline(uint32_t friend_number) {
	Tox_Err_Friend_Get_Last_Online err = TOX_ERR_FRIEND_GET_LAST_ONLINE_OK;
	auto res = tox_friend_get_last_online(_tox, friend_number, &err);
	if (res == TOX_ERR_FRIEND_GET_LAST_ONLINE_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

std::optional<std::string> ToxDefaultImpl::toxFriendGetName(uint32_t friend_number) {
	std::string name;
	Tox_Err_Friend_Query err = TOX_ERR_FRIEND_QUERY_OK;
	const auto size = tox_friend_get_name_size(_tox, friend_number, &err);
	if (err != TOX_ERR_FRIEND_QUERY_OK) {
		return std::nullopt;
	}
	name.resize(size);
	tox_friend_get_name(_tox, friend_number, reinterpret_cast<uint8_t*>(name.data()), &err);
	if (err == TOX_ERR_FRIEND_QUERY_OK) {
		return name;
	} else {
		return std::nullopt;
	}
}

std::optional<std::string> ToxDefaultImpl::toxFriendGetStatusMessage(uint32_t friend_number) {
	std::string status;
	Tox_Err_Friend_Query err = TOX_ERR_FRIEND_QUERY_OK;
	const auto size = tox_friend_get_status_message_size(_tox, friend_number, &err);
	if (err != TOX_ERR_FRIEND_QUERY_OK) {
		return std::nullopt;
	}
	status.resize(size);
	tox_friend_get_status_message(_tox, friend_number, reinterpret_cast<uint8_t*>(status.data()), &err);
	if (err == TOX_ERR_FRIEND_QUERY_OK) {
		return status;
	} else {
		return std::nullopt;
	}
}

std::optional<Tox_User_Status> ToxDefaultImpl::toxFriendGetStatus(uint32_t friend_number) {
	Tox_Err_Friend_Query err = TOX_ERR_FRIEND_QUERY_OK;
	auto res = tox_friend_get_status(_tox, friend_number, &err);
	if (err == TOX_ERR_FRIEND_QUERY_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

std::optional<Tox_Connection> ToxDefaultImpl::toxFriendGetConnectionStatus(uint32_t friend_number) {
	Tox_Err_Friend_Query err = TOX_ERR_FRIEND_QUERY_OK;
	auto res = tox_friend_get_connection_status(_tox, friend_number, &err);
	if (err == TOX_ERR_FRIEND_QUERY_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

std::optional<bool> ToxDefaultImpl::toxFriendGetTyping(uint32_t friend_number) {
	Tox_Err_Friend_Query err = TOX_ERR_FRIEND_QUERY_OK;
	auto res = tox_friend_get_typing(_tox, friend_number, &err);
	if (err == TOX_ERR_FRIEND_QUERY_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

Tox_Err_Set_Typing ToxDefaultImpl::toxSelfSetTyping(uint32_t friend_number, bool typing) {
	Tox_Err_Set_Typing err = TOX_ERR_SET_TYPING_OK;
	tox_self_set_typing(_tox, friend_number, typing, &err);
	return err;
}

std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Send_Message> ToxDefaultImpl::toxFriendSendMessage(uint32_t friend_number, Tox_Message_Type type, std::string_view message) {
	Tox_Err_Friend_Send_Message err = TOX_ERR_FRIEND_SEND_MESSAGE_OK;
	auto res = tox_friend_send_message(_tox, friend_number, type, reinterpret_cast<const uint8_t*>(message.data()), message.size(), &err);
	if (err == TOX_ERR_FRIEND_SEND_MESSAGE_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_File_Control ToxDefaultImpl::toxFileControl(uint32_t friend_number, uint32_t file_number, Tox_File_Control control) {
	Tox_Err_File_Control err = TOX_ERR_FILE_CONTROL_OK;
	tox_file_control(_tox, friend_number, file_number, control, &err);
	return err;
}

Tox_Err_File_Seek ToxDefaultImpl::toxFileSeek(uint32_t friend_number, uint32_t file_number, uint64_t position) {
	Tox_Err_File_Seek err = TOX_ERR_FILE_SEEK_OK;
	tox_file_seek(_tox, friend_number, file_number, position, &err);
	return err;
}

std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_File_Get> ToxDefaultImpl::toxFileGetFileID(uint32_t friend_number, uint32_t file_number) {
	Tox_Err_File_Get err = TOX_ERR_FILE_GET_OK;
	std::vector<uint8_t> id(TOX_FILE_ID_LENGTH);
	tox_file_get_file_id(_tox, friend_number, file_number, id.data(), &err);
	if (err == TOX_ERR_FILE_GET_OK) {
		return {id, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<uint32_t>, Tox_Err_File_Send> ToxDefaultImpl::toxFileSend(uint32_t friend_number, uint32_t kind, uint64_t file_size, const std::vector<uint8_t>& file_id, std::string_view filename) {
	// TODO: check file_id size
	Tox_Err_File_Send err = TOX_ERR_FILE_SEND_OK;
	auto res = tox_file_send(_tox, friend_number, kind, file_size, file_id.data(), reinterpret_cast<const uint8_t*>(filename.data()), filename.size(), &err);
	if (err == TOX_ERR_FILE_SEND_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_File_Send_Chunk ToxDefaultImpl::toxFileSendChunk(uint32_t friend_number, uint32_t file_number, uint64_t position, const std::vector<uint8_t>& data) {
	Tox_Err_File_Send_Chunk err = TOX_ERR_FILE_SEND_CHUNK_OK;
	tox_file_send_chunk(_tox, friend_number, file_number, position, data.data(), data.size(), &err);
	return err;
}

Tox_Err_Conference_Delete ToxDefaultImpl::toxConferenceDelete(uint32_t conference_number) {
	Tox_Err_Conference_Delete err = TOX_ERR_CONFERENCE_DELETE_OK;
	tox_conference_delete(_tox, conference_number, &err);
	return err;
}

std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Peer_Query> ToxDefaultImpl::toxConferencePeerCount(uint32_t conference_number) {
	Tox_Err_Conference_Peer_Query err = TOX_ERR_CONFERENCE_PEER_QUERY_OK;
	const auto res = tox_conference_peer_count(_tox, conference_number, &err);
	if (err == TOX_ERR_CONFERENCE_PEER_QUERY_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<std::string>, Tox_Err_Conference_Peer_Query>  ToxDefaultImpl::toxConferencePeerGetName(uint32_t conference_number, uint32_t peer_number) {
	std::string name;
	Tox_Err_Conference_Peer_Query err = TOX_ERR_CONFERENCE_PEER_QUERY_OK;

	const auto size = tox_conference_peer_get_name_size(_tox, conference_number, peer_number, &err);
	if (err != TOX_ERR_CONFERENCE_PEER_QUERY_OK) {
		return {std::nullopt, err};
	}
	name.resize(size);
	tox_conference_peer_get_name(_tox, conference_number, peer_number, reinterpret_cast<uint8_t*>(name.data()), &err);
	if (err == TOX_ERR_CONFERENCE_PEER_QUERY_OK) {
		return {name, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Conference_Peer_Query> ToxDefaultImpl::toxConferencePeerGetPublicKey(uint32_t conference_number, uint32_t peer_number) {
	std::vector<uint8_t> public_key(TOX_PUBLIC_KEY_SIZE);
	Tox_Err_Conference_Peer_Query err = TOX_ERR_CONFERENCE_PEER_QUERY_OK;
	tox_conference_peer_get_public_key(_tox, conference_number, peer_number, public_key.data(), &err);
	if (err == TOX_ERR_CONFERENCE_PEER_QUERY_OK) {
		return {public_key, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<bool>, Tox_Err_Conference_Peer_Query> ToxDefaultImpl::toxConferencePeerNumberIsOurs(uint32_t conference_number, uint32_t peer_number) {
	Tox_Err_Conference_Peer_Query err = TOX_ERR_CONFERENCE_PEER_QUERY_OK;
	const auto res = tox_conference_peer_number_is_ours(_tox, conference_number, peer_number, &err);
	if (err == TOX_ERR_CONFERENCE_PEER_QUERY_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Conference_Set_Max_Offline ToxDefaultImpl::toxConferenceSetMaxOffline(uint32_t conference_number, uint32_t max_offline_peers) {
	Tox_Err_Conference_Set_Max_Offline err = TOX_ERR_CONFERENCE_SET_MAX_OFFLINE_OK;
	tox_conference_set_max_offline(_tox, conference_number, max_offline_peers, &err);
	return err;
}

Tox_Err_Conference_Invite ToxDefaultImpl::toxConferenceInvite(uint32_t friend_number, uint32_t conference_number) {
	Tox_Err_Conference_Invite err = TOX_ERR_CONFERENCE_INVITE_OK;
	tox_conference_invite(_tox, friend_number, conference_number, &err);
	return err;
}

std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Join> ToxDefaultImpl::toxConferenceJoin(uint32_t friend_number, const std::vector<uint8_t>& cookie) {
	Tox_Err_Conference_Join err = TOX_ERR_CONFERENCE_JOIN_OK;
	auto res = tox_conference_join(_tox, friend_number, cookie.data(), cookie.size(), &err);
	if (err == TOX_ERR_CONFERENCE_JOIN_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Conference_Send_Message ToxDefaultImpl::toxConferenceSendMessage(uint32_t conference_number, Tox_Message_Type type, std::string_view message) {
	Tox_Err_Conference_Send_Message err = TOX_ERR_CONFERENCE_SEND_MESSAGE_OK;
	tox_conference_send_message(_tox, conference_number, type, reinterpret_cast<const uint8_t*>(message.data()), message.size(), &err);
	return err;
}

std::tuple<std::optional<std::string>, Tox_Err_Conference_Title> ToxDefaultImpl::toxConferenceGetTitle(uint32_t conference_number) {
	std::string title;
	Tox_Err_Conference_Title err = TOX_ERR_CONFERENCE_TITLE_OK;

	const auto size = tox_conference_get_title_size(_tox, conference_number, &err);
	if (err != TOX_ERR_CONFERENCE_TITLE_OK) {
		return {std::nullopt, err};
	}
	title.resize(size);
	tox_conference_get_title(_tox, conference_number, reinterpret_cast<uint8_t*>(title.data()), &err);
	if (err == TOX_ERR_CONFERENCE_TITLE_OK) {
		return {title, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Conference_Title ToxDefaultImpl::toxConferenceSetTitle(uint32_t conference_number, std::string_view title) {
	Tox_Err_Conference_Title err = TOX_ERR_CONFERENCE_TITLE_OK;
	tox_conference_set_title(_tox, conference_number, reinterpret_cast<const uint8_t*>(title.data()), title.size(), &err);
	return err;
}

std::vector<uint32_t> ToxDefaultImpl::toxConferenceGetChatlist(void) {
	std::vector<uint32_t> list;
	const auto size = tox_conference_get_chatlist_size(_tox);
	list.resize(size);
	tox_conference_get_chatlist(_tox, list.data());
	return list;
}

std::tuple<std::optional<Tox_Conference_Type>, Tox_Err_Conference_Get_Type> ToxDefaultImpl::toxConferenceGetType(uint32_t conference_number) {
	Tox_Err_Conference_Get_Type err = TOX_ERR_CONFERENCE_GET_TYPE_OK;
	const auto ret = tox_conference_get_type(_tox, conference_number, &err);
	if (err == TOX_ERR_CONFERENCE_GET_TYPE_OK) {
		return {ret, err};
	} else {
		return {std::nullopt, err};
	}
}

std::optional<std::vector<uint8_t>> ToxDefaultImpl::toxConferenceGetID(uint32_t conference_number) {
	std::vector<uint8_t> id(TOX_CONFERENCE_ID_SIZE);
	const auto ret = tox_conference_get_id(_tox, conference_number, id.data());
	if (ret) {
		return id;
	} else {
		return std::nullopt;
	}
}

std::tuple<std::optional<uint32_t>, Tox_Err_Conference_By_Id> ToxDefaultImpl::toxConferenceByID(const std::vector<uint8_t>& id) {
	if (id.size() != TOX_CONFERENCE_ID_SIZE) {
		return {std::nullopt, TOX_ERR_CONFERENCE_BY_ID_NOT_FOUND};
	}

	Tox_Err_Conference_By_Id err = TOX_ERR_CONFERENCE_BY_ID_OK;
	const auto res = tox_conference_by_id(_tox, id.data(), &err);
	if (err == TOX_ERR_CONFERENCE_BY_ID_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Friend_Custom_Packet ToxDefaultImpl::toxFriendSendLossyPacket(uint32_t friend_number, const std::vector<uint8_t>& data) {
	Tox_Err_Friend_Custom_Packet err = TOX_ERR_FRIEND_CUSTOM_PACKET_OK;
	tox_friend_send_lossy_packet(_tox, friend_number, data.data(), data.size(), &err);
	return err;
}

Tox_Err_Friend_Custom_Packet ToxDefaultImpl::toxFriendSendLosslessPacket(uint32_t friend_number, const std::vector<uint8_t>& data) {
	Tox_Err_Friend_Custom_Packet err = TOX_ERR_FRIEND_CUSTOM_PACKET_OK;
	tox_friend_send_lossless_packet(_tox, friend_number, data.data(), data.size(), &err);
	return err;
}

std::vector<uint8_t> ToxDefaultImpl::toxSelfGetDHTID(void) {
	std::vector<uint8_t> id(tox_public_key_size());
	tox_self_get_dht_id(_tox, id.data());
	return id;
}

std::tuple<std::optional<uint16_t>, Tox_Err_Get_Port> ToxDefaultImpl::toxSelfGetUDPPort(void) {
	Tox_Err_Get_Port err = TOX_ERR_GET_PORT_OK;
	const auto res = tox_self_get_udp_port(_tox, &err);
	if (err == TOX_ERR_GET_PORT_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<uint16_t>, Tox_Err_Get_Port> ToxDefaultImpl::toxSelfGetTCPPort(void) {
	Tox_Err_Get_Port err = TOX_ERR_GET_PORT_OK;
	const auto res = tox_self_get_tcp_port(_tox, &err);
	if (err == TOX_ERR_GET_PORT_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

uint32_t ToxDefaultImpl::toxGroupMaxTopicLength(void) {
	return tox_group_max_topic_length();
}

uint32_t ToxDefaultImpl::toxGroupMaxPartLength(void) {
	return tox_group_max_part_length();
}

uint32_t ToxDefaultImpl::toxGroupMaxMessageLength(void) {
	return tox_group_max_message_length();
}

uint32_t ToxDefaultImpl::toxGroupMaxCustomLossyPacketLength(void) {
	return tox_group_max_custom_lossy_packet_length();
}

uint32_t ToxDefaultImpl::toxGroupMaxCustomLosslessPacketLength(void) {
	return tox_group_max_custom_lossless_packet_length();
}

uint32_t ToxDefaultImpl::toxGroupMaxGroupNameLength(void) {
	return tox_group_max_group_name_length();
}

uint32_t ToxDefaultImpl::toxGroupMaxPasswordSize(void) {
	return tox_group_max_password_size();
}

uint32_t ToxDefaultImpl::toxGroupChatIdSize(void) {
	return tox_group_chat_id_size();
}

uint32_t ToxDefaultImpl::toxGroupPeerPublicKeySize(void) {
	return tox_group_peer_public_key_size();
}

std::tuple<std::optional<uint32_t>, Tox_Err_Group_New> ToxDefaultImpl::toxGroupNew(Tox_Group_Privacy_State privacy_state, std::string_view group_name, std::string_view name) {
	Tox_Err_Group_New err = TOX_ERR_GROUP_NEW_OK;
	auto res = tox_group_new(_tox, privacy_state, reinterpret_cast<const uint8_t*>(group_name.data()), group_name.size(), reinterpret_cast<const uint8_t*>(name.data()), name.size(), &err);
	if (err == TOX_ERR_GROUP_NEW_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<uint32_t>, Tox_Err_Group_Join> ToxDefaultImpl::toxGroupJoin(const std::vector<uint8_t>& chat_id, std::string_view name, std::string_view password) {
	Tox_Err_Group_Join err = TOX_ERR_GROUP_JOIN_OK;
	// TODO: check size
	auto res = tox_group_join(_tox, chat_id.data(), reinterpret_cast<const uint8_t*>(name.data()), name.size(), reinterpret_cast<const uint8_t*>(password.data()), password.size(), &err);
	if (err == TOX_ERR_GROUP_JOIN_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::optional<bool> ToxDefaultImpl::toxGroupIsConnected(uint32_t group_number) {
	Tox_Err_Group_Is_Connected err = TOX_ERR_GROUP_IS_CONNECTED_OK;
	auto res = tox_group_is_connected(_tox, group_number, &err);
	if (err == TOX_ERR_GROUP_IS_CONNECTED_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

Tox_Err_Group_Disconnect ToxDefaultImpl::toxGroupDisconnect(uint32_t group_number) {
	Tox_Err_Group_Disconnect err = TOX_ERR_GROUP_DISCONNECT_OK;
	tox_group_disconnect(_tox, group_number, &err);
	return err;
}

Tox_Err_Group_Reconnect ToxDefaultImpl::toxGroupReconnect(uint32_t group_number) {
	Tox_Err_Group_Reconnect err = TOX_ERR_GROUP_RECONNECT_OK;
	tox_group_reconnect(_tox, group_number, &err);
	return err;
}

Tox_Err_Group_Leave ToxDefaultImpl::toxGroupLeave(uint32_t group_number, std::string_view part_message) {
	Tox_Err_Group_Leave err = TOX_ERR_GROUP_LEAVE_OK;
	tox_group_leave(_tox, group_number, reinterpret_cast<const uint8_t*>(part_message.data()), part_message.size(), &err);
	return err;
}

Tox_Err_Group_Self_Name_Set ToxDefaultImpl::toxGroupSelfSetName(uint32_t group_number, std::string_view name) {
	Tox_Err_Group_Self_Name_Set err = TOX_ERR_GROUP_SELF_NAME_SET_OK;
	tox_group_self_set_name(_tox, group_number, reinterpret_cast<const uint8_t*>(name.data()), name.size(), &err);
	return err;
}

std::optional<std::string> ToxDefaultImpl::toxGroupSelfGetName(uint32_t group_number) {
	std::string name;

	Tox_Err_Group_Self_Query err = TOX_ERR_GROUP_SELF_QUERY_OK;
	const auto size = tox_group_self_get_name_size(_tox, group_number, &err);
	if (err != TOX_ERR_GROUP_SELF_QUERY_OK) {
		return std::nullopt;
	}

	name.resize(size);
	tox_group_self_get_name(_tox, group_number, reinterpret_cast<uint8_t*>(name.data()), &err);

	if (err == TOX_ERR_GROUP_SELF_QUERY_OK) {
		return name;
	} else {
		return std::nullopt;
	}
}

Tox_Err_Group_Self_Status_Set ToxDefaultImpl::toxGroupSelfSetStatus(uint32_t group_number, Tox_User_Status status) {
	Tox_Err_Group_Self_Status_Set err = TOX_ERR_GROUP_SELF_STATUS_SET_OK;
	tox_group_self_set_status(_tox, group_number, status, &err);
	return err;
}

std::optional<Tox_User_Status> ToxDefaultImpl::toxGroupSelfGetStatus(uint32_t group_number) {
	Tox_Err_Group_Self_Query err = TOX_ERR_GROUP_SELF_QUERY_OK;
	auto res = tox_group_self_get_status(_tox, group_number, &err);
	if (err == TOX_ERR_GROUP_SELF_QUERY_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

std::optional<Tox_Group_Role> ToxDefaultImpl::toxGroupSelfGetRole(uint32_t group_number) {
	Tox_Err_Group_Self_Query err = TOX_ERR_GROUP_SELF_QUERY_OK;
	auto res = tox_group_self_get_role(_tox, group_number, &err);
	if (err == TOX_ERR_GROUP_SELF_QUERY_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

std::optional<uint32_t> ToxDefaultImpl::toxGroupSelfGetPeerId(uint32_t group_number) {
	Tox_Err_Group_Self_Query err = TOX_ERR_GROUP_SELF_QUERY_OK;
	auto res = tox_group_self_get_peer_id(_tox, group_number, &err);
	if (err == TOX_ERR_GROUP_SELF_QUERY_OK) {
		return res;
	} else {
		return std::nullopt;
	}
}

std::optional<std::vector<uint8_t>> ToxDefaultImpl::toxGroupSelfGetPublicKey(uint32_t group_number) {
	std::vector<uint8_t> public_key(TOX_GROUP_PEER_PUBLIC_KEY_SIZE);
	Tox_Err_Group_Self_Query err = TOX_ERR_GROUP_SELF_QUERY_OK;
	tox_group_self_get_public_key(_tox, group_number, public_key.data(), &err);
	if (err == TOX_ERR_GROUP_SELF_QUERY_OK) {
		return public_key;
	} else {
		return std::nullopt;
	}
}

std::tuple<std::optional<std::string>, Tox_Err_Group_Peer_Query> ToxDefaultImpl::toxGroupPeerGetName(uint32_t group_number, uint32_t peer_id) {
	std::string name;

	Tox_Err_Group_Peer_Query err = TOX_ERR_GROUP_PEER_QUERY_OK;
	const auto size = tox_group_peer_get_name_size(_tox, group_number, peer_id, &err);
	if (err != TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {std::nullopt, err};
	}

	name.resize(size);
	tox_group_peer_get_name(_tox, group_number, peer_id, reinterpret_cast<uint8_t*>(name.data()), &err);

	if (err == TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {name, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<Tox_User_Status>, Tox_Err_Group_Peer_Query> ToxDefaultImpl::toxGroupPeerGetStatus(uint32_t group_number, uint32_t peer_id) {
	Tox_Err_Group_Peer_Query err = TOX_ERR_GROUP_PEER_QUERY_OK;
	auto res = tox_group_peer_get_status(_tox, group_number, peer_id, &err);
	if (err == TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<Tox_Group_Role>, Tox_Err_Group_Peer_Query> ToxDefaultImpl::toxGroupPeerGetRole(uint32_t group_number, uint32_t peer_id) {
	Tox_Err_Group_Peer_Query err = TOX_ERR_GROUP_PEER_QUERY_OK;
	auto res = tox_group_peer_get_role(_tox, group_number, peer_id, &err);
	if (err == TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {res, err};
	} else{
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<Tox_Connection>, Tox_Err_Group_Peer_Query> ToxDefaultImpl::toxGroupPeerGetConnectionStatus(uint32_t group_number, uint32_t peer_id) {
	Tox_Err_Group_Peer_Query err = TOX_ERR_GROUP_PEER_QUERY_OK;
	auto res = tox_group_peer_get_connection_status(_tox, group_number, peer_id, &err);
	if (err == TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Group_Peer_Query> ToxDefaultImpl::toxGroupPeerGetPublicKey(uint32_t group_number, uint32_t peer_id) {
	std::vector<uint8_t> public_key(TOX_GROUP_PEER_PUBLIC_KEY_SIZE);
	Tox_Err_Group_Peer_Query err = TOX_ERR_GROUP_PEER_QUERY_OK;
	tox_group_peer_get_public_key(_tox, group_number, peer_id, public_key.data(), &err);
	if (err == TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {public_key, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Group_Topic_Set ToxDefaultImpl::toxGroupSetTopic(uint32_t group_number, std::string_view topic) {
	Tox_Err_Group_Topic_Set err = TOX_ERR_GROUP_TOPIC_SET_OK;
	tox_group_set_topic(_tox, group_number, reinterpret_cast<const uint8_t*>(topic.data()), topic.size(), &err);
	return err;
}

std::optional<std::string> ToxDefaultImpl::toxGroupGetTopic(uint32_t group_number) {
	std::string topic;

	Tox_Err_Group_State_Query err = TOX_ERR_GROUP_STATE_QUERY_OK;
	const auto size = tox_group_get_topic_size(_tox, group_number, &err);
	if (err != TOX_ERR_GROUP_STATE_QUERY_OK) {
		return std::nullopt;
	}

	topic.resize(size);
	tox_group_get_topic(_tox, group_number, reinterpret_cast<uint8_t*>(topic.data()), &err);
	if (err == TOX_ERR_GROUP_STATE_QUERY_OK) {
		return topic;
	} else {
		return std::nullopt;
	}
}

std::optional<std::string> ToxDefaultImpl::toxGroupGetName(uint32_t group_number) {
	std::string name;

	Tox_Err_Group_State_Query err = TOX_ERR_GROUP_STATE_QUERY_OK;
	const auto size = tox_group_get_name_size(_tox, group_number, &err);
	if (err != TOX_ERR_GROUP_STATE_QUERY_OK) {
		return std::nullopt;
	}

	name.resize(size);
	tox_group_get_name(_tox, group_number, reinterpret_cast<uint8_t*>(name.data()), &err);

	if (err == TOX_ERR_GROUP_STATE_QUERY_OK) {
		return name;
	} else {
		return std::nullopt;
	}
}

std::optional<std::vector<uint8_t>> ToxDefaultImpl::toxGroupGetChatId(uint32_t group_number) {
	std::vector<uint8_t> chat_id{};
	chat_id.resize(TOX_GROUP_CHAT_ID_SIZE);

	Tox_Err_Group_State_Query err = TOX_ERR_GROUP_STATE_QUERY_OK;
	tox_group_get_chat_id(_tox, group_number, chat_id.data(), &err);
	if (err == TOX_ERR_GROUP_STATE_QUERY_OK) {
		return chat_id;
	} else {
		return std::nullopt;
	}
}

size_t ToxDefaultImpl::toxGroupGetNumberGroups(void) {
	return tox_group_get_number_groups(_tox);
}

std::vector<uint32_t> ToxDefaultImpl::toxGroupGetList(void) {
	std::vector<uint32_t> group_list;

	size_t group_count = tox_group_get_number_groups(_tox);
	// HACK: we guess number until we have count
	for (uint32_t i = 0; i < group_count + 10'000u && group_list.size() < group_count; i++) {
		Tox_Err_Group_Self_Query err = TOX_ERR_GROUP_SELF_QUERY_OK;
		tox_group_self_get_peer_id(_tox, i, &err);
		if (err == TOX_ERR_GROUP_SELF_QUERY_OK) {
			group_list.push_back(i);
		}
	}

	return group_list;
}

std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> ToxDefaultImpl::toxGroupSendMessage(uint32_t group_number, Tox_Message_Type type, std::string_view message) {
	Tox_Err_Group_Send_Message err = TOX_ERR_GROUP_SEND_MESSAGE_OK;
	uint32_t message_id = tox_group_send_message(_tox, group_number, type, reinterpret_cast<const uint8_t*>(message.data()), message.size(), &err);
	if (err == TOX_ERR_GROUP_SEND_MESSAGE_OK) {
		return {message_id, err};
	} else {
		return {std::nullopt, err};
	}
}

std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Private_Message> ToxDefaultImpl::toxGroupSendPrivateMessage(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, std::string_view message) {
	Tox_Err_Group_Send_Private_Message err = TOX_ERR_GROUP_SEND_PRIVATE_MESSAGE_OK;
	uint32_t message_id = tox_group_send_private_message(_tox, group_number, peer_id, type, reinterpret_cast<const uint8_t*>(message.data()), message.size(), &err);
	if (err == TOX_ERR_GROUP_SEND_PRIVATE_MESSAGE_OK) {
		return {message_id, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Group_Send_Custom_Packet ToxDefaultImpl::toxGroupSendCustomPacket(uint32_t group_number, bool lossless, const std::vector<uint8_t>& data) {
	Tox_Err_Group_Send_Custom_Packet err = TOX_ERR_GROUP_SEND_CUSTOM_PACKET_OK;
	tox_group_send_custom_packet(_tox, group_number, lossless, data.data(), data.size(), &err);
	return err;
}

Tox_Err_Group_Send_Custom_Private_Packet ToxDefaultImpl::toxGroupSendCustomPrivatePacket(uint32_t group_number, uint32_t peer_id, bool lossless, const std::vector<uint8_t>& data) {
	Tox_Err_Group_Send_Custom_Private_Packet err = TOX_ERR_GROUP_SEND_CUSTOM_PRIVATE_PACKET_OK;
	tox_group_send_custom_private_packet(_tox, group_number, peer_id, lossless, data.data(), data.size(), &err);
	return err;
}

Tox_Err_Group_Invite_Friend ToxDefaultImpl::toxGroupInviteFriend(uint32_t group_number, uint32_t friend_number) {
	Tox_Err_Group_Invite_Friend err = TOX_ERR_GROUP_INVITE_FRIEND_OK;
	tox_group_invite_friend(_tox, group_number, friend_number, &err);
	return err;
}

std::tuple<std::optional<uint32_t>, Tox_Err_Group_Invite_Accept> ToxDefaultImpl::toxGroupInviteAccept(uint32_t friend_number, const std::vector<uint8_t>& invite_data, std::string_view name, std::string_view password) {
	Tox_Err_Group_Invite_Accept err = TOX_ERR_GROUP_INVITE_ACCEPT_OK;
	auto res = tox_group_invite_accept(_tox, friend_number, invite_data.data(), invite_data.size(), reinterpret_cast<const uint8_t*>(name.data()), name.size(), reinterpret_cast<const uint8_t*>(password.data()), password.size(), &err);
	if (err == TOX_ERR_GROUP_INVITE_ACCEPT_OK) {
		return {res, err};
	} else {
		return {std::nullopt, err};
	}
}

