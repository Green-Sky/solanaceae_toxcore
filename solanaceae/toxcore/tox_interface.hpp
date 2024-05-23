#pragma once

//#include <tox/tox.h>
#include "./toxcore_enums.hpp"

#include <string_view>
#include <vector>
#include <string>
#include <tuple>
#include <optional>

// TODO: c++20 span
// TODO: use span in utils

// TODO: asyncable

// defines the full interface for tox
// HACK: raw
struct ToxI_raw {
	static constexpr const char* version {"9"};

	virtual ~ToxI_raw(void) {}

	// TODO: tox version
	// size stuff
	// options? (no)
	// get save data?
	// bootstrap
	// add tcp relay

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
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Friend_By_Public_Key> toxFriendByPublicKey(const std::vector<uint8_t>& public_key) = 0;
	virtual bool toxFriendExists(uint32_t friend_number) = 0;
	virtual size_t toxSelfGetFriendListSize(void) = 0;
	virtual std::vector<uint32_t> toxSelfGetFriendList(void) = 0;
	virtual std::optional<std::vector<uint8_t>> toxFriendGetPublicKey(uint32_t friend_number) = 0;
	virtual std::optional<uint64_t> toxFriendGetLastOnline(uint32_t friend_number) = 0;
	virtual std::optional<std::string> toxFriendGetName(uint32_t friend_number) = 0;
	virtual std::optional<std::string> toxFriendGetStatusMessage(uint32_t friend_number) = 0;
	virtual std::optional<Tox_User_Status> toxFriendGetStatus(uint32_t friend_number) = 0;
	virtual std::optional<Tox_Connection> toxFriendGetConnectionStatus(uint32_t friend_number) = 0;
	virtual std::optional<bool> toxFriendGetTyping(uint32_t friend_number) = 0;
	virtual Tox_Err_Set_Typing toxSelfSetTyping(uint32_t friend_number, bool typing) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Send_Message> toxFriendSendMessage(uint32_t friend_number, Tox_Message_Type type, std::string_view message) = 0;

	// files
	// TODO: array? make it type agnostic?
	virtual std::vector<uint8_t> toxHash(const std::vector<uint8_t>& data);
	virtual Tox_Err_File_Control toxFileControl(uint32_t friend_number, uint32_t file_number, Tox_File_Control control) = 0;
	virtual Tox_Err_File_Seek toxFileSeek(uint32_t friend_number, uint32_t file_number, uint64_t position) = 0;
	virtual std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_File_Get> toxFileGetFileID(uint32_t friend_number, uint32_t file_number) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_File_Send> toxFileSend(uint32_t friend_number, uint32_t kind, uint64_t file_size, const std::vector<uint8_t>& file_id, std::string_view filename) = 0;
	virtual Tox_Err_File_Send_Chunk toxFileSendChunk(uint32_t friend_number, uint32_t file_number, uint64_t position, const std::vector<uint8_t>& data) = 0;

	// conferece
	virtual Tox_Err_Conference_Delete toxConferenceDelete(uint32_t conference_number) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Peer_Query> toxConferencePeerCount(uint32_t conference_number) = 0;
	virtual std::tuple<std::optional<std::string>, Tox_Err_Conference_Peer_Query>  toxConferencePeerGetName(uint32_t conference_number, uint32_t peer_number) = 0;
	virtual std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Conference_Peer_Query> toxConferencePeerGetPublicKey(uint32_t conference_number, uint32_t peer_number) = 0;
	// TODO: simplify return value
	virtual std::tuple<std::optional<bool>, Tox_Err_Conference_Peer_Query> toxConferencePeerNumberIsOurs(uint32_t conference_number, uint32_t peer_number) = 0;
	// TODO: do offline conf stuff
	//uint32_t tox_conference_offline_peer_count(const Tox *tox, uint32_t conference_number,
	//size_t tox_conference_offline_peer_get_name_size(const Tox *tox, uint32_t conference_number,
	//bool tox_conference_offline_peer_get_name(const Tox *tox, uint32_t conference_number, uint32_t offline_peer_number,
	//bool tox_conference_offline_peer_get_public_key(const Tox *tox, uint32_t conference_number,
	//uint64_t tox_conference_offline_peer_get_last_active(const Tox *tox, uint32_t conference_number,
	// TODO: 2 value enum, use bool instead?
	virtual Tox_Err_Conference_Set_Max_Offline toxConferenceSetMaxOffline(uint32_t conference_number, uint32_t max_offline_peers) = 0;
	virtual Tox_Err_Conference_Invite toxConferenceInvite(uint32_t friend_number, uint32_t conference_number) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Join> toxConferenceJoin(uint32_t friend_number, const std::vector<uint8_t>& cookie) = 0;
	virtual Tox_Err_Conference_Send_Message toxConferenceSendMessage(uint32_t conference_number, Tox_Message_Type type, std::string_view message) = 0;
	virtual std::tuple<std::optional<std::string>, Tox_Err_Conference_Title>  toxConferenceGetTitle(uint32_t conference_number) = 0;
	virtual Tox_Err_Conference_Title toxConferenceSetTitle(uint32_t conference_number, std::string_view title) = 0;
	virtual std::vector<uint32_t> toxConferenceGetChatlist(void) = 0;
	virtual std::tuple<std::optional<Tox_Conference_Type>, Tox_Err_Conference_Get_Type> toxConferenceGetType(uint32_t conference_number) = 0;
	virtual std::optional<std::vector<uint8_t>> toxConferenceGetID(uint32_t conference_number) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Conference_By_Id> toxConferenceByID(const std::vector<uint8_t>& id) = 0;


	virtual Tox_Err_Friend_Custom_Packet toxFriendSendLossyPacket(uint32_t friend_number, const std::vector<uint8_t>& data) = 0;
	virtual Tox_Err_Friend_Custom_Packet toxFriendSendLosslessPacket(uint32_t friend_number, const std::vector<uint8_t>& data) = 0;

	// dht and ports
	virtual std::vector<uint8_t> toxSelfGetDHTID(void) = 0;
	virtual std::tuple<std::optional<uint16_t>, Tox_Err_Get_Port> toxSelfGetUDPPort(void) = 0;
	virtual std::tuple<std::optional<uint16_t>, Tox_Err_Get_Port> toxSelfGetTCPPort(void) = 0;

	// group

	virtual uint32_t toxGroupMaxTopicLength(void) = 0;
	virtual uint32_t toxGroupMaxPartLength(void) = 0;
	virtual uint32_t toxGroupMaxMessageLength(void) = 0;
	virtual uint32_t toxGroupMaxCustomLossyPacketLength(void) = 0;
	virtual uint32_t toxGroupMaxCustomLosslessPacketLength(void) = 0;
	virtual uint32_t toxGroupMaxGroupNameLength(void) = 0;
	virtual uint32_t toxGroupMaxPasswordSize(void) = 0;
	virtual uint32_t toxGroupChatIdSize(void) = 0;
	virtual uint32_t toxGroupPeerPublicKeySize(void) = 0;

	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_New> toxGroupNew(Tox_Group_Privacy_State privacy_state, std::string_view group_name, std::string_view name) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_Join> toxGroupJoin(const std::vector<uint8_t>& chat_id, std::string_view name, std::string_view password) = 0;
	virtual std::optional<bool> toxGroupIsConnected(uint32_t group_number) = 0; // only 1 error type, skip
	virtual Tox_Err_Group_Disconnect toxGroupDisconnect(uint32_t group_number) = 0;
	virtual Tox_Err_Group_Reconnect toxGroupReconnect(uint32_t group_number) = 0;
	virtual Tox_Err_Group_Leave toxGroupLeave(uint32_t group_number, std::string_view part_message) = 0;

	virtual Tox_Err_Group_Self_Name_Set toxGroupSelfSetName(uint32_t group_number, std::string_view name) = 0;
	virtual std::optional<std::string> toxGroupSelfGetName(uint32_t group_number) = 0; // only 1 error type, skip
	virtual Tox_Err_Group_Self_Status_Set toxGroupSelfSetStatus(uint32_t group_number, Tox_User_Status status) = 0;
	virtual std::optional<Tox_User_Status> toxGroupSelfGetStatus(uint32_t group_number) = 0;
	virtual std::optional<Tox_Group_Role> toxGroupSelfGetRole(uint32_t group_number) = 0;
	virtual std::optional<uint32_t> toxGroupSelfGetPeerId(uint32_t group_number) = 0;
	virtual std::optional<std::vector<uint8_t>> toxGroupSelfGetPublicKey(uint32_t group_number) = 0;

	virtual std::tuple<std::optional<std::string>, Tox_Err_Group_Peer_Query> toxGroupPeerGetName(uint32_t group_number, uint32_t peer_id) = 0;
	virtual std::tuple<std::optional<Tox_User_Status>, Tox_Err_Group_Peer_Query> toxGroupPeerGetStatus(uint32_t group_number, uint32_t peer_id) = 0;
	virtual std::tuple<std::optional<Tox_Group_Role>, Tox_Err_Group_Peer_Query> toxGroupPeerGetRole(uint32_t group_number, uint32_t peer_id) = 0;
	virtual std::tuple<std::optional<Tox_Connection>, Tox_Err_Group_Peer_Query> toxGroupPeerGetConnectionStatus(uint32_t group_number, uint32_t peer_id) = 0;
	virtual std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Group_Peer_Query> toxGroupPeerGetPublicKey(uint32_t group_number, uint32_t peer_id) = 0;

	virtual Tox_Err_Group_Topic_Set toxGroupSetTopic(uint32_t group_number, std::string_view topic) = 0;
	virtual std::optional<std::string> toxGroupGetTopic(uint32_t group_number) = 0; // only 1 error type, skip

	virtual std::optional<std::string> toxGroupGetName(uint32_t group_number) = 0; // only 1 error type, skip
	virtual std::optional<std::vector<uint8_t>> toxGroupGetChatId(uint32_t group_number) = 0; // only 1 error type, skip
	// TODO: str

	//virtual uint32_t toxGroupGetNumberGroups(void) = 0;
	virtual size_t toxGroupGetNumberGroups(void) = 0;
	virtual std::vector<uint32_t> toxGroupGetList(void) = 0;

	//virtual Tox_Group_Privacy_State toxGroupGetPrivacyState(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual Tox_Group_Voice_State toxGroupGetVoiceState(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual Tox_Group_Topic_Lock toxGroupGetTopicLock(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual uint16_t toxGroupGetPeerLimit(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual std::string toxGroupGetPassword(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;

	// returns message_id
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> toxGroupSendMessage(uint32_t group_number, Tox_Message_Type type, std::string_view message) = 0;
	virtual std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Private_Message> toxGroupSendPrivateMessage(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, std::string_view message) = 0;

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
	static constexpr const char* version {ToxI_raw::version};

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

	std::tuple<std::optional<uint32_t>, Tox_Err_File_Send> toxFileSend_str(uint32_t friend_number, uint32_t kind, uint64_t file_size, const std::vector<uint8_t>& file_id, const std::string& filename) {
		return toxFileSend(friend_number, kind, file_size, file_id, filename);
	}

	Tox_Err_Conference_Send_Message toxConferenceSendMessage_str(uint32_t conference_number, Tox_Message_Type type, const std::string& message) {
		return toxConferenceSendMessage(conference_number, type, message);
	}

	Tox_Err_Conference_Title toxConferenceSetTitle_str(uint32_t conference_number, const std::string& title) {
		return toxConferenceSetTitle(conference_number, title);
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

	Tox_Err_Group_Self_Name_Set toxGroupSelfSetName_str(uint32_t group_number, const std::string& name) {
		return toxGroupSelfSetName(group_number, name);
	}

	Tox_Err_Group_Topic_Set toxGroupSetTopic_str(uint32_t group_number, const std::string& topic) {
		return toxGroupSetTopic(group_number, topic);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> toxGroupSendMessage_str(uint32_t group_number, Tox_Message_Type type, const std::string& message) {
		return toxGroupSendMessage(group_number, type, message);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Private_Message> toxGroupSendPrivateMessage_str(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, const std::string& message) {
		return toxGroupSendPrivateMessage(group_number, peer_id, type, message);
	}

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Invite_Accept> toxGroupInviteAccept_str(uint32_t friend_number, const std::vector<uint8_t>& invite_data, const std::string& name, const std::string& password) {
		return toxGroupInviteAccept(friend_number, invite_data, name, password);
	}
};

