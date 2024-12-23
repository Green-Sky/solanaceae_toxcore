#pragma once

#include <tox/tox.h>
#include "./tox_interface.hpp"

struct ToxDefaultImpl : public ToxI {
	Tox* _tox = nullptr;

	virtual ~ToxDefaultImpl(void) {}

	Tox_Err_Bootstrap toxBootstrap(const std::string& host, uint16_t port, const std::vector<uint8_t>& public_key) override;
	Tox_Err_Bootstrap toxAddTcpRelay(const std::string& host, uint16_t port, const std::vector<uint8_t>& public_key) override;

	Tox_Connection toxSelfGetConnectionStatus(void) override;
	uint32_t toxIterationInterval(void) override;

	std::vector<uint8_t> toxSelfGetAddress(void) override;

	void toxSelfSetNospam(uint32_t nospam) override;
	uint32_t toxSelfGetNospam(void) override;

	std::vector<uint8_t> toxSelfGetPublicKey(void) override;
	std::vector<uint8_t> toxSelfGetSecretKey(void) override;

	Tox_Err_Set_Info toxSelfSetName(std::string_view name) override;
	std::string toxSelfGetName(void) override;

	Tox_Err_Set_Info toxSelfSetStatusMessage(std::string_view status_message) override;
	std::string toxSelfGetStatusMessage(void) override;

	void toxSelfSetStatus(Tox_User_Status status) override;
	Tox_User_Status toxSelfGetStatus(void) override;

	std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> toxFriendAdd(const std::vector<uint8_t>& address, std::string_view message) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Add> toxFriendAddNorequest(const std::vector<uint8_t>& public_key) override;
	Tox_Err_Friend_Delete toxFriendDelete(uint32_t friend_number) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Friend_By_Public_Key> toxFriendByPublicKey(const std::vector<uint8_t>& public_key) override;
	bool toxFriendExists(uint32_t friend_number) override;
	size_t toxSelfGetFriendListSize(void) override;
	std::vector<uint32_t> toxSelfGetFriendList(void) override;
	std::optional<std::vector<uint8_t>> toxFriendGetPublicKey(uint32_t friend_number) override;
	std::optional<uint64_t> toxFriendGetLastOnline(uint32_t friend_number) override;
	std::optional<std::string> toxFriendGetName(uint32_t friend_number) override;
	std::optional<std::string> toxFriendGetStatusMessage(uint32_t friend_number) override;
	std::optional<Tox_User_Status> toxFriendGetStatus(uint32_t friend_number) override;
	std::optional<Tox_Connection> toxFriendGetConnectionStatus(uint32_t friend_number) override;
	std::optional<bool> toxFriendGetTyping(uint32_t friend_number) override;
	Tox_Err_Set_Typing toxSelfSetTyping(uint32_t friend_number, bool typing) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Friend_Send_Message> toxFriendSendMessage(uint32_t friend_number, Tox_Message_Type type, std::string_view message) override;

	// files
	Tox_Err_File_Control toxFileControl(uint32_t friend_number, uint32_t file_number, Tox_File_Control control) override;
	Tox_Err_File_Seek toxFileSeek(uint32_t friend_number, uint32_t file_number, uint64_t position) override;
	std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_File_Get> toxFileGetFileID(uint32_t friend_number, uint32_t file_number) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_File_Send> toxFileSend(uint32_t friend_number, uint32_t kind, uint64_t file_size, const std::vector<uint8_t>& file_id, std::string_view filename) override;
	Tox_Err_File_Send_Chunk toxFileSendChunk(uint32_t friend_number, uint32_t file_number, uint64_t position, const std::vector<uint8_t>& data) override;

	// conferece
	Tox_Err_Conference_Delete toxConferenceDelete(uint32_t conference_number) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Peer_Query> toxConferencePeerCount(uint32_t conference_number) override;
	std::tuple<std::optional<std::string>, Tox_Err_Conference_Peer_Query>  toxConferencePeerGetName(uint32_t conference_number, uint32_t peer_number) override;
	std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Conference_Peer_Query> toxConferencePeerGetPublicKey(uint32_t conference_number, uint32_t peer_number) override;
	std::tuple<std::optional<bool>, Tox_Err_Conference_Peer_Query> toxConferencePeerNumberIsOurs(uint32_t conference_number, uint32_t peer_number) override;
	Tox_Err_Conference_Set_Max_Offline toxConferenceSetMaxOffline(uint32_t conference_number, uint32_t max_offline_peers) override;
	Tox_Err_Conference_Invite toxConferenceInvite(uint32_t friend_number, uint32_t conference_number) override;

	std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Join> toxConferenceJoin(uint32_t friend_number, const std::vector<uint8_t>& cookie) override;
	Tox_Err_Conference_Send_Message toxConferenceSendMessage(uint32_t conference_number, Tox_Message_Type type, std::string_view message) override;

	std::tuple<std::optional<std::string>, Tox_Err_Conference_Title>  toxConferenceGetTitle(uint32_t conference_number) override;
	Tox_Err_Conference_Title toxConferenceSetTitle(uint32_t conference_number, std::string_view title) override;
	std::vector<uint32_t> toxConferenceGetChatlist(void) override;
	std::tuple<std::optional<Tox_Conference_Type>, Tox_Err_Conference_Get_Type> toxConferenceGetType(uint32_t conference_number) override;
	std::optional<std::vector<uint8_t>> toxConferenceGetID(uint32_t conference_number) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Conference_By_Id> toxConferenceByID(const std::vector<uint8_t>& id) override;

	Tox_Err_Friend_Custom_Packet toxFriendSendLossyPacket(uint32_t friend_number, const std::vector<uint8_t>& data) override;
	Tox_Err_Friend_Custom_Packet toxFriendSendLosslessPacket(uint32_t friend_number, const std::vector<uint8_t>& data) override;

	// dht and ports
	std::vector<uint8_t> toxSelfGetDHTID(void) override;
	std::tuple<std::optional<uint16_t>, Tox_Err_Get_Port> toxSelfGetUDPPort(void) override;
	std::tuple<std::optional<uint16_t>, Tox_Err_Get_Port> toxSelfGetTCPPort(void) override;

	// group

	uint32_t toxGroupMaxTopicLength(void) override;
	uint32_t toxGroupMaxPartLength(void) override;
	uint32_t toxGroupMaxMessageLength(void) override;
	uint32_t toxGroupMaxCustomLossyPacketLength(void) override;
	uint32_t toxGroupMaxCustomLosslessPacketLength(void) override;
	uint32_t toxGroupMaxGroupNameLength(void) override;
	uint32_t toxGroupMaxPasswordSize(void) override;
	uint32_t toxGroupChatIdSize(void) override;
	uint32_t toxGroupPeerPublicKeySize(void) override;

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_New> toxGroupNew(Tox_Group_Privacy_State privacy_state, std::string_view group_name, std::string_view name) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Join> toxGroupJoin(const std::vector<uint8_t>& chat_id, std::string_view name, std::string_view password) override;
	std::optional<bool> toxGroupIsConnected(uint32_t group_number) override;
	Tox_Err_Group_Disconnect toxGroupDisconnect(uint32_t group_number) override;
	Tox_Err_Group_Reconnect toxGroupReconnect(uint32_t group_number) override;
	Tox_Err_Group_Leave toxGroupLeave(uint32_t group_number, std::string_view part_message) override;

	Tox_Err_Group_Self_Name_Set toxGroupSelfSetName(uint32_t group_number, std::string_view name) override;
	std::optional<std::string> toxGroupSelfGetName(uint32_t group_number) override;
	Tox_Err_Group_Self_Status_Set toxGroupSelfSetStatus(uint32_t group_number, Tox_User_Status status) override;
	std::optional<Tox_User_Status> toxGroupSelfGetStatus(uint32_t group_number) override;
	std::optional<Tox_Group_Role> toxGroupSelfGetRole(uint32_t group_number) override;
	std::optional<uint32_t> toxGroupSelfGetPeerId(uint32_t group_number) override;
	std::optional<std::vector<uint8_t>> toxGroupSelfGetPublicKey(uint32_t group_number) override;

	std::tuple<std::optional<std::string>, Tox_Err_Group_Peer_Query> toxGroupPeerGetName(uint32_t group_number, uint32_t peer_id) override;
	std::tuple<std::optional<Tox_User_Status>, Tox_Err_Group_Peer_Query> toxGroupPeerGetStatus(uint32_t group_number, uint32_t peer_id) override;
	std::tuple<std::optional<Tox_Group_Role>, Tox_Err_Group_Peer_Query> toxGroupPeerGetRole(uint32_t group_number, uint32_t peer_id) override;
	std::tuple<std::optional<Tox_Connection>, Tox_Err_Group_Peer_Query> toxGroupPeerGetConnectionStatus(uint32_t group_number, uint32_t peer_id) override;
	std::tuple<std::optional<std::vector<uint8_t>>, Tox_Err_Group_Peer_Query> toxGroupPeerGetPublicKey(uint32_t group_number, uint32_t peer_id) override;

	Tox_Err_Group_Topic_Set toxGroupSetTopic(uint32_t group_number, std::string_view topic) override;
	std::optional<std::string> toxGroupGetTopic(uint32_t group_number) override;

	std::optional<std::string> toxGroupGetName(uint32_t group_number) override;
	std::optional<std::vector<uint8_t>> toxGroupGetChatId(uint32_t group_number) override;
	// TODO: str

	size_t toxGroupGetNumberGroups(void) override;
	std::vector<uint32_t> toxGroupGetList(void) override;

	std::optional<Tox_Group_Privacy_State> toxGroupGetPrivacyState(uint32_t group_number) override;
	std::optional<Tox_Group_Voice_State> toxGroupGetVoiceState(uint32_t group_number) override;
	std::optional<bool> toxGroupGetTopicLock(uint32_t group_number) override;
	std::optional<uint16_t> toxGroupGetPeerLimit(uint32_t group_number) override;
	std::optional<std::string> toxGroupGetPassword(uint32_t group_number) override;

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> toxGroupSendMessage(uint32_t group_number, Tox_Message_Type type, std::string_view message) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Private_Message> toxGroupSendPrivateMessage(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, std::string_view message) override;

	Tox_Err_Group_Send_Custom_Packet toxGroupSendCustomPacket(uint32_t group_number, bool lossless, const std::vector<uint8_t>& data) override;
	Tox_Err_Group_Send_Custom_Private_Packet toxGroupSendCustomPrivatePacket(uint32_t group_number, uint32_t peer_id, bool lossless, const std::vector<uint8_t>& data) override;

	Tox_Err_Group_Invite_Friend toxGroupInviteFriend(uint32_t group_number, uint32_t friend_number) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Invite_Accept> toxGroupInviteAccept(uint32_t friend_number, const std::vector<uint8_t>& invite_data, std::string_view name, std::string_view password) override;

	Tox_Err_Group_Set_Password toxGroupSetPassword(uint32_t group_number, std::string_view password) override;
	Tox_Err_Group_Set_Topic_Lock toxGroupSetTopicLock(uint32_t group_number, bool topic_lock) override;
	Tox_Err_Group_Set_Voice_State toxGroupSetVoiceState(uint32_t group_number, Tox_Group_Voice_State voice_state) override;
	Tox_Err_Group_Set_Privacy_State toxGroupSetPrivacyState(uint32_t group_number, Tox_Group_Privacy_State privacy_state) override;
	Tox_Err_Group_Set_Peer_Limit toxGroupSetPeerLimit(uint32_t group_number, uint16_t max_peers) override;
	Tox_Err_Group_Set_Ignore toxGroupSetIgnore(uint32_t group_number, uint32_t peer_id, bool ignore) override;
	Tox_Err_Group_Set_Role toxGroupSetRole(uint32_t group_number, uint32_t peer_id, Tox_Group_Role role) override;
	Tox_Err_Group_Kick_Peer toxGroupKickPeer(uint32_t group_number, uint32_t peer_id) override;
};

