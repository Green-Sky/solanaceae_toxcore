#pragma once

#include "./tox_interface.hpp"

struct ToxDefaultImpl : public ToxI {
	Tox* _tox = nullptr;

	virtual ~ToxDefaultImpl(void) {}

	Tox_Connection toxSelfGetConnectionStatus(void) override;
	uint32_t toxIterationInterval(void) override;

	std::vector<uint8_t> toxSelfGetAddress(void) override;

	void toxSelfSetNospam(uint32_t nospam) override;
	uint32_t toxSelfGetNospam(void) override;

	std::vector<uint8_t> toxSelfGetPublicKey(void) override;
	//virtual void toxSelfGetSecretKey(const Tox *tox, uint8_t *secret_key);

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
	std::tuple<std::optional<uint32_t>, Tox_Err_Conference_Join> toxConferenceJoin(uint32_t friend_number, const std::vector<uint8_t>& cookie) override;
	Tox_Err_Conference_Send_Message toxConferenceSendMessage(uint32_t conference_number, Tox_Message_Type type, std::string_view message) override;

	Tox_Err_Friend_Custom_Packet toxFriendSendLossyPacket(uint32_t friend_number, const std::vector<uint8_t>& data) override;
	Tox_Err_Friend_Custom_Packet toxFriendSendLosslessPacket(uint32_t friend_number, const std::vector<uint8_t>& data) override;

	// dht
	// udp
	// tcp

	// group

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

	//virtual uint32_t toxGroupGetNumberGroups(void) = 0;

	//virtual Tox_Group_Privacy_State toxGroupGetPrivacyState(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual Tox_Group_Voice_State toxGroupGetVoiceState(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual Tox_Group_Topic_Lock toxGroupGetTopicLock(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual uint16_t toxGroupGetPeerLimit(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;
	//virtual std::string toxGroupGetPassword(uint32_t group_number, Tox_Err_Group_State_Queries *error) = 0;

	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Send_Message> toxGroupSendMessage(uint32_t group_number, Tox_Message_Type type, std::string_view message) override;
	Tox_Err_Group_Send_Private_Message toxGroupSendPrivateMessage(uint32_t group_number, uint32_t peer_id, Tox_Message_Type type, std::string_view message) override;

	Tox_Err_Group_Send_Custom_Packet toxGroupSendCustomPacket(uint32_t group_number, bool lossless, const std::vector<uint8_t>& data) override;
	Tox_Err_Group_Send_Custom_Private_Packet toxGroupSendCustomPrivatePacket(uint32_t group_number, uint32_t peer_id, bool lossless, const std::vector<uint8_t>& data) override;

	Tox_Err_Group_Invite_Friend toxGroupInviteFriend(uint32_t group_number, uint32_t friend_number) override;
	std::tuple<std::optional<uint32_t>, Tox_Err_Group_Invite_Accept> toxGroupInviteAccept(uint32_t friend_number, const std::vector<uint8_t>& invite_data, std::string_view name, std::string_view password) override;
	//virtual Tox_Err_Group_Founder_Set_Password toxGroupFounderSetPassword(uint32_t group_number, std::string_view password) = 0;
	//virtual Tox_Err_Group_Founder_Set_Topic_Lock toxGroupFounderSetTopicLock(uint32_t group_number, Tox_Group_Topic_Lock topic_lock) = 0;
	//virtual Tox_Err_Group_Founder_Set_Voice_State toxGroupFounderSetVoiceState(uint32_t group_number, Tox_Group_Voice_State voice_state) = 0;
	//virtual Tox_Err_Group_Founder_Set_Privacy_State toxGroupFounderSetPrivacyState(uint32_t group_number, Tox_Group_Privacy_State privacy_state) = 0;
	//virtual Tox_Err_Group_Founder_Set_Peer_Limit toxGroupFounderSetPeerLimit(uint32_t group_number, uint16_t max_peers) = 0;
	//virtual Tox_Err_Group_Set_Ignore toxGroupSetIgnore(uint32_t group_number, uint32_t peer_id, bool ignore) = 0;
	//virtual Tox_Err_Group_Mod_Set_Role toxGroupModSetRole(uint32_t group_number, uint32_t peer_id, Tox_Group_Role role) = 0;
	//virtual Tox_Err_Group_Mod_Kick_Peer toxGroupModKickPeer(uint32_t group_number, uint32_t peer_id) = 0;

};

