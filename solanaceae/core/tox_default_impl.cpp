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

std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Friend_Get_Public_Key> ToxDefaultImpl::toxFriendGetPublicKey(uint32_t friend_number) {
	std::vector<uint8_t> pub(TOX_PUBLIC_KEY_SIZE);
	Tox_Err_Friend_Get_Public_Key err = TOX_ERR_FRIEND_GET_PUBLIC_KEY_OK;
	tox_friend_get_public_key(_tox, friend_number, pub.data(), &err);
	if (err == TOX_ERR_FRIEND_GET_PUBLIC_KEY_OK) {
		return {pub, err};
	} else {
		return {std::nullopt, err};
	}
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

std::tuple<std::optional<Tox_Connection>, Tox_Err_Group_Peer_Query> ToxDefaultImpl::toxGroupPeerGetConnectionStatus(uint32_t group_number, uint32_t peer_id) {
	Tox_Err_Group_Peer_Query err = TOX_ERR_GROUP_PEER_QUERY_OK;
	auto res = tox_group_peer_get_connection_status(_tox, group_number, peer_id, &err);
	if (err == TOX_ERR_GROUP_PEER_QUERY_OK) {
		return {res, err};
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

	Tox_Err_Group_State_Queries err = TOX_ERR_GROUP_STATE_QUERIES_OK;
	const auto size = tox_group_get_topic_size(_tox, group_number, &err);
	if (err != TOX_ERR_GROUP_STATE_QUERIES_OK) {
		return std::nullopt;
	}

	topic.resize(size);
	tox_group_get_topic(_tox, group_number, reinterpret_cast<uint8_t*>(topic.data()), &err);
	if (err == TOX_ERR_GROUP_STATE_QUERIES_OK) {
		return topic;
	} else {
		return std::nullopt;
	}
}

std::optional<std::string> ToxDefaultImpl::toxGroupGetName(uint32_t group_number) {
	std::string name;

	Tox_Err_Group_State_Queries err = TOX_ERR_GROUP_STATE_QUERIES_OK;
	const auto size = tox_group_get_name_size(_tox, group_number, &err);
	if (err != TOX_ERR_GROUP_STATE_QUERIES_OK) {
		return std::nullopt;
	}

	name.resize(size);
	tox_group_get_name(_tox, group_number, reinterpret_cast<uint8_t*>(name.data()), &err);

	if (err == TOX_ERR_GROUP_STATE_QUERIES_OK) {
		return name;
	} else {
		return std::nullopt;
	}
}

std::optional<std::vector<uint8_t>> ToxDefaultImpl::toxGroupGetChatId(uint32_t group_number) {
	std::vector<uint8_t> chat_id{};
	chat_id.resize(TOX_GROUP_CHAT_ID_SIZE);

	Tox_Err_Group_State_Queries err = TOX_ERR_GROUP_STATE_QUERIES_OK;
	tox_group_get_chat_id(_tox, group_number, chat_id.data(), &err);
	if (err == TOX_ERR_GROUP_STATE_QUERIES_OK) {
		return chat_id;
	} else {
		return std::nullopt;
	}
}

std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> ToxDefaultImpl::toxGroupSendMessage(uint32_t group_number, Tox_Message_Type type, std::string_view message) {
	Tox_Err_Group_Send_Message err = TOX_ERR_GROUP_SEND_MESSAGE_OK;
	uint32_t message_id = 0;
	tox_group_send_message(_tox, group_number, type, reinterpret_cast<const uint8_t*>(message.data()), message.size(), &message_id, &err);
	if (err == TOX_ERR_GROUP_SEND_MESSAGE_OK) {
		return {message_id, err};
	} else {
		return {std::nullopt, err};
	}
}

Tox_Err_Group_Send_Private_Message ToxDefaultImpl::toxGroupSendPrivateMessage(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, std::string_view message) {
	Tox_Err_Group_Send_Private_Message err = TOX_ERR_GROUP_SEND_PRIVATE_MESSAGE_OK;
	tox_group_send_private_message(_tox, group_number, peer_id, type, reinterpret_cast<const uint8_t*>(message.data()), message.size(), &err);
	return err;
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

