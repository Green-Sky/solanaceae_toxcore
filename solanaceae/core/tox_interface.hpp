#pragma once

#include <tox/tox.h>

#include <string_view>
#include <vector>
#include <string>
#include <tuple>
#include <optional>

// TODO: c++20 span

// defines the full interface for tox
// HACK: raw
struct ToxI_raw {
	virtual ~ToxI_raw(void) {}

	virtual Tox_Connection toxSelfGetConnectionStatus(void) = 0;
	virtual uint32_t toxIterationInterval(void) = 0;

	virtual std::vector<uint8_t> toxSelfGetAddress(void) = 0;
	virtual std::string toxSelfGetAddressStr(void); // has default impl

	virtual void toxSelfSetNospam(uint32_t nospam) = 0;
	virtual uint32_t toxSelfGetNospam(void) = 0;

	virtual std::vector<uint8_t> toxSelfGetPublicKey(void) = 0;
	//virtual void toxSelfGetSecretKey(const Tox *tox, uint8_t *secret_key);

	virtual Tox_Err_Set_Info toxSelfSetName(std::string_view name) = 0;
	virtual std::string toxSelfGetName(void) = 0;

	virtual Tox_Err_Set_Info toxSelfSetStatusMessage(std::string_view status_message) = 0;
	virtual std::string toxSelfGetStatusMessage(void) = 0;

	virtual void toxSelfSetStatus(Tox_User_Status status) = 0;
	virtual Tox_User_Status toxSelfGetStatus(void) = 0;

	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> toxFriendAdd(const std::vector<uint8_t>& address, std::string_view message) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> toxFriendAddNorequest(const std::vector<uint8_t>& public_key) = 0;
	virtual Tox_Err_Friend_Delete toxFriendDelete(uint32_t friend_number) = 0;
	virtual std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Friend_Get_Public_Key> toxFriendGetPublicKey(uint32_t friend_number) = 0;


	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Send_Message> toxFriendSendMessage(uint32_t friend_number, Tox_Message_Type type, std::string_view message) = 0;

	// TODO: array? make it type agnostic?
	virtual std::vector<uint8_t> toxHash(const std::vector<uint8_t>& data);

	// files

	// conferece
	//bool tox_conference_delete(Tox *tox, uint32_t conference_number, Tox_Err_Conference_Delete *error);
	//uint32_t tox_conference_peer_count(const Tox *tox, uint32_t conference_number, Tox_Err_Conference_Peer_Query *error);
	//size_t tox_conference_peer_get_name_size(const Tox *tox, uint32_t conference_number, uint32_t peer_number,
	//bool tox_conference_peer_get_name(const Tox *tox, uint32_t conference_number, uint32_t peer_number, uint8_t *name,
	//bool tox_conference_peer_get_public_key(const Tox *tox, uint32_t conference_number, uint32_t peer_number,
	//bool tox_conference_peer_number_is_ours(const Tox *tox, uint32_t conference_number, uint32_t peer_number,
	//uint32_t tox_conference_offline_peer_count(const Tox *tox, uint32_t conference_number,
	//size_t tox_conference_offline_peer_get_name_size(const Tox *tox, uint32_t conference_number,
	//bool tox_conference_offline_peer_get_name(const Tox *tox, uint32_t conference_number, uint32_t offline_peer_number,
	//bool tox_conference_offline_peer_get_public_key(const Tox *tox, uint32_t conference_number,
	//uint64_t tox_conference_offline_peer_get_last_active(const Tox *tox, uint32_t conference_number,
	//bool tox_conference_set_max_offline(Tox *tox, uint32_t conference_number, uint32_t max_offline_peers, Tox_Err_Conference_Set_Max_Offline *error);
	//bool tox_conference_invite(Tox *tox, uint32_t friend_number, uint32_t conference_number, Tox_Err_Conference_Invite *error);
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Join> toxConferenceJoin(uint32_t friend_number, const std::vector<uint8_t>& cookie) = 0;
	virtual Tox_Err_Conference_Send_Message toxConferenceSendMessage(uint32_t conference_number, Tox_Message_Type type, std::string_view message) = 0;
	//size_t tox_conference_get_title_size(const Tox *tox, uint32_t conference_number, Tox_Err_Conference_Title *error);
	//bool tox_conference_get_title(const Tox *tox, uint32_t conference_number, uint8_t *title, Tox_Err_Conference_Title *error);
	//bool tox_conference_set_title(Tox *tox, uint32_t conference_number, const uint8_t *title, size_t length, Tox_Err_Conference_Title *error);
	//size_t tox_conference_get_chatlist_size(const Tox *tox);
	//void tox_conference_get_chatlist(const Tox *tox, uint32_t *chatlist);
	//Tox_Conference_Type tox_conference_get_type(const Tox *tox, uint32_t conference_number, Tox_Err_Conference_Get_Type *error);
	//bool tox_conference_get_id(const Tox *tox, uint32_t conference_number, uint8_t *id);
	//uint32_t tox_conference_by_id(const Tox *tox, const uint8_t *id, Tox_Err_Conference_By_Id *error);
	//bool tox_conference_get_uid(const Tox *tox, uint32_t conference_number, uint8_t *uid);
	//uint32_t tox_conference_by_uid(const Tox *tox, const uint8_t *uid, Tox_Err_Conference_By_Uid *error);


	virtual Tox_Err_Friend_Custom_Packet toxFriendSendLossyPacket(uint32_t friend_number, const std::vector<uint8_t>& data) = 0;
	virtual Tox_Err_Friend_Custom_Packet toxFriendSendLosslessPacket(uint32_t friend_number, const std::vector<uint8_t>& data) = 0;

	// dht
	// udp
	// tcp

	// group

	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_New> toxGroupNew(Tox_Group_Privacy_State privacy_state, std::string_view group_name, std::string_view name) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_Join> toxGroupJoin(const std::vector<uint8_t>& chat_id, std::string_view name, std::string_view password) = 0;
	virtual std::optional<bool> toxGroupIsConnected(uint32_t group_number) = 0; // only 1 error type, skip
	//virtual Tox_Err_Group_Disconnect toxGroupDisconnect(uint32_t group_number) = 0;
	virtual Tox_Err_Group_Reconnect toxGroupReconnect(uint32_t group_number) = 0;
	virtual Tox_Err_Group_Leave toxGroupLeave(uint32_t group_number, std::string_view part_message) = 0;

	//virtual Tox_Err_Group_Self_Name_Set toxGroupSelfSetName(uint32_t group_number, std::string_view name) = 0;
	virtual std::optional<std::string> toxGroupSelfGetName(uint32_t group_number) = 0; // only 1 error type, skip
	//virtual Tox_Err_Group_Self_Status_Set toxGroupSelfSetStatus(uint32_t group_number, Tox_User_Status status) = 0;
	//virtual Tox_User_Status toxGroupSelfGetStatus(uint32_t group_number, Tox_Err_Group_Self_Query *error) = 0;
	//virtual Tox_Group_Role toxGroupSelfGetRole(uint32_t group_number, Tox_Err_Group_Self_Query *error) = 0;
	//virtual uint32_t toxGroupSelfGetPeerId(uint32_t group_number, Tox_Err_Group_Self_Query *error) = 0;
	//virtual std::vector<uint8_t> toxGroupSelfGetPublicKey(uint32_t group_number, Tox_Err_Group_Self_Query *error) = 0;

	virtual std::tuple<std::optional<std::string>, Tox_Err_Group_Peer_Query> toxGroupPeerGetName(uint32_t group_number, uint32_t peer_id) = 0;
	//virtual Tox_User_Status toxGroupPeerGetStatus(uint32_t group_number, uint32_t peer_id, Tox_Err_Group_Peer_Query *error) = 0;
	//virtual Tox_Group_Role toxGroupPeerGetRole(uint32_t group_number, uint32_t peer_id, Tox_Err_Group_Peer_Query *error) = 0;
	virtual std::tuple<std::optional<Tox_Connection>, Tox_Err_Group_Peer_Query> toxGroupPeerGetConnectionStatus(uint32_t group_number, uint32_t peer_id) = 0;
	//virtual std::vector<uint8_t> toxGroupPeerGetPublicKey(uint32_t group_number, uint32_t peer_id, Tox_Err_Group_Peer_Query *error) = 0;

	virtual Tox_Err_Group_Topic_Set toxGroupSetTopic(uint32_t group_number, std::string_view topic) = 0;
	virtual std::optional<std::string> toxGroupGetTopic(uint32_t group_number) = 0; // only 1 error type, skip

	virtual std::optional<std::string> toxGroupGetName(uint32_t group_number) = 0; // only 1 error type, skip
	virtual std::optional<std::vector<uint8_t>> toxGroupGetChatId(uint32_t group_number) = 0; // only 1 error type, skip
	// TODO: str

	//virtual uint32_t toxGroupGetNumberGroups(void) = 0;

	//virtual Tox_Group_Privacy_State toxGroupGetPrivacyState(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual Tox_Group_Voice_State toxGroupGetVoiceState(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual Tox_Group_Topic_Lock toxGroupGetTopicLock(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual uint16_t toxGroupGetPeerLimit(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual std::string toxGroupGetPassword(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;

	// returns message_id
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> toxGroupSendMessage(uint32_t group_number, Tox_Message_Type type, std::string_view message) = 0;
	virtual Tox_Err_Group_Send_Private_Message toxGroupSendPrivateMessage(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, std::string_view message) = 0;

	virtual Tox_Err_Group_Send_Custom_Packet toxGroupSendCustomPacket(uint32_t group_number, bool lossless, const std::vector<uint8_t>& data) = 0;
	virtual Tox_Err_Group_Send_Custom_Private_Packet toxGroupSendCustomPrivatePacket(uint32_t group_number, uint32_t peer_id, bool lossless, const std::vector<uint8_t>& data) = 0;

	virtual Tox_Err_Group_Invite_Friend toxGroupInviteFriend(uint32_t group_number, uint32_t friend_number) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_Invite_Accept> toxGroupInviteAccept(uint32_t friend_number, const std::vector<uint8_t>& invite_data, std::string_view name, std::string_view password) = 0;
	//virtual Tox_Err_Group_Founder_Set_Password toxGroupFounderSetPassword(uint32_t group_number, std::string_view password) = 0;
	//virtual Tox_Err_Group_Founder_Set_Topic_Lock toxGroupFounderSetTopicLock(uint32_t group_number, Tox_Group_Topic_Lock topic_lock) = 0;
	//virtual Tox_Err_Group_Founder_Set_Voice_State toxGroupFounderSetVoiceState(uint32_t group_number, Tox_Group_Voice_State voice_state) = 0;
	//virtual Tox_Err_Group_Founder_Set_Privacy_State toxGroupFounderSetPrivacyState(uint32_t group_number, Tox_Group_Privacy_State privacy_state) = 0;
	//virtual Tox_Err_Group_Founder_Set_Peer_Limit toxGroupFounderSetPeerLimit(uint32_t group_number, uint16_t max_peers) = 0;
	//virtual Tox_Err_Group_Set_Ignore toxGroupSetIgnore(uint32_t group_number, uint32_t peer_id, bool ignore) = 0;
	//virtual Tox_Err_Group_Mod_Set_Role toxGroupModSetRole(uint32_t group_number, uint32_t peer_id, Tox_Group_Role role) = 0;
	//virtual Tox_Err_Group_Mod_Kick_Peer toxGroupModKickPeer(uint32_t group_number, uint32_t peer_id) = 0;

};

// HACK: work around zppbits inability to pass string_view as parameter ( https://github.com/eyalz800/zpp_bits/issues/107 )
struct ToxI : public ToxI_raw {
	Tox_Err_Set_Info toxSelfSetName_str(const std::string& name) {
		return toxSelfSetName(name);
	}

	Tox_Err_Set_Info toxSelfSetStatusMessage_str(const std::string& status_message) {
		return toxSelfSetStatusMessage(status_message);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> toxFriendAdd_str(const std::vector<uint8_t>& address, const std::string& message) {
		return toxFriendAdd(address, message);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Send_Message> toxFriendSendMessage_str(uint32_t friend_number, Tox_Message_Type type, const std::string& message) {
		return toxFriendSendMessage(friend_number, type, message);
	}

	Tox_Err_Conference_Send_Message toxConferenceSendMessage_str(uint32_t conference_number, Tox_Message_Type type, const std::string& message) {
		return toxConferenceSendMessage(conference_number, type, message);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_New> toxGroupNew_str(Tox_Group_Privacy_State privacy_state, const std::string& group_name, const std::string& name) {
		return toxGroupNew(privacy_state, group_name, name);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Join> toxGroupJoin_str(const std::vector<uint8_t>& chat_id, const std::string& name, const std::string& password) {
		return toxGroupJoin(chat_id, name, password);
	}

	Tox_Err_Group_Leave toxGroupLeave_str(uint32_t group_number, const std::string& part_message) {
		return toxGroupLeave(group_number, part_message);
	}

	Tox_Err_Group_Topic_Set toxGroupSetTopic_str(uint32_t group_number, const std::string& topic) {
		return toxGroupSetTopic(group_number, topic);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> toxGroupSendMessage_str(uint32_t group_number, Tox_Message_Type type, const std::string& message) {
		return toxGroupSendMessage(group_number, type, message);
	}

	Tox_Err_Group_Send_Private_Message toxGroupSendPrivateMessage_str(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, const std::string& message) {
		return toxGroupSendPrivateMessage(group_number, peer_id, type, message);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Invite_Accept> toxGroupInviteAccept_str(uint32_t friend_number, const std::vector<uint8_t>& invite_data, const std::string& name, const std::string& password) {
		return toxGroupInviteAccept(friend_number, invite_data, name, password);
	}
};

