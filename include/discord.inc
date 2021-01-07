#if defined _discord_included
	#endinput
#endif
#define _discord_included

#include <smjansson>
#include <discord/stocks>

typedef DiscordGuildsRetrieve = function void (DiscordBot bot, char[] id, char[] name, char[] icon, bool owner, int permissions, any data);

typedef DiscordGuildsRetrievedAll = function void (DiscordBot bot, ArrayList id, ArrayList name, ArrayList icon, ArrayList owner, ArrayList permissions, any data);

//Channel are Handles that are closed immediately after forwards called. To keep, clone. Or store id if thats what you want
typedef DiscordGuildChannelsRetrieve = function void (DiscordBot bot, char[] guild, DiscordChannel Channel, any data);

typedef DiscordGuildChannelsRetrieveAll = function void (DiscordBot bot, char[] guild, ArrayList Channels, any data);

typedef DiscordGuildGetRoles = function void (DiscordBot bot, char[] guild, RoleList Roles, any data);

/** 
 * Called when message is received
 * bot/channel/message are all destroyed after callback is sent.
 * You can clone it if need to keep.
 */
typeset OnChannelMessage { 
	function void(DiscordBot bot, DiscordChannel channel, DiscordMessage message);
};

typedef OnGetReactions = function void (DiscordBot bot, ArrayList Users, char[] channelID, const char[] messageID, const char[] emoji, any data);

typedef OnMessageSent = function void(DiscordBot bot, char[] channel, DiscordMessage message, any data);

typedef OnMessageDeleted = function void(DiscordBot bot, any data);

//hMemberList is JSON array containing guild members
typedef OnGetMembers = function void(DiscordBot bot, char[] guild, Handle hMemberList);

methodmap DiscordRole < Handle {
	public native void GetID(char[] buffer, int maxlength);
	
	public native void GetName(char[] buffer, int maxlength);
	
	public native int GetColor();
	
	public native bool IsHoist();
	
	public native int GetPosition();
	
	public native void GetPermissions(char[] buffer, int maxlength);
	
	public native bool IsManaged();
	
	public native bool IsMentionable();
};

methodmap RoleList < Handle {
	property int Size 
	{
		public get() 
		{
			return json_array_size(this);
		}
	}
	public DiscordRole GetRole(int i) 
	{
		return view_as<DiscordRole>(json_array_get(this, i));
	}
	public DiscordRole Get(int i) 
	{
		return this.GetRole(i);
	}
	
};

/*
{
    "id": "80351110224678912",
    "username": "Nelly",
    "discriminator": "1337",
    "avatar": "8342729096ea3675442027381ff50dfe",
    "verified": true,
    "email": "nelly@discord.com"
}
 */
//It's a JSON Handle with the above info TODO stop using natives!
methodmap DiscordUser < Handle {
	public native void GetID(char[] buffer, int maxlength);
	
	public native void GetUsername(char[] buffer, int maxlength);
	
	public native void GetDiscriminator(char[] buffer, int maxlength);
	public int GetDiscriminatorInt() {
		char buffer[16];
		this.GetDiscriminator(buffer, sizeof(buffer));
		return StringToInt(buffer);
	}
	
	public native void GetAvatar(char[] buffer, int maxlength);
	
	public native bool IsVerified();
	
	public native void GetEmail(char[] buffer, int maxlength);
	
	public native bool IsBot();
};

methodmap DiscordGuildUser < Handle {
	//Returns User Object
	public DiscordUser GetUser() {
		return view_as<DiscordUser>(json_object_get(this, "user"));
	}
	
	//Returns player's nick
	public void GetNickname(char[] buffer, int maxlength) {
		JsonObjectGetString(this, "nick", buffer, maxlength);
	}
	
	//Returns JSON array list of roles. You can manually loop through them for now.
	public RoleList GetRoles() {
		return view_as<RoleList>(json_object_get(this, "roles"));
	}
	
	//Returns the date the user joined the guild in format: "2015-04-26T06:26:56.936000+00:00"
	public void GetJoinedAt(char[] buffer, int maxlength) {
		JsonObjectGetString(this, "joined_at", buffer, maxlength);
	}
	
	public bool IsDeaf() {
		return JsonObjectGetBool(this, "deaf");
	}
	
	public bool IsMute() {
		return JsonObjectGetBool(this, "mute");
	}
};

//It's a JSON Handle with the above info TODO stop using natives!
methodmap DiscordAttachment < Handle {
	public native void GetID(char[] buffer, int maxlength);
	
	public native void GetFilename(char[] buffer, int maxlength);
	
	public native int GetSize();
	
	public native void GetURL(char[] buffer, int maxlength);

	public native void GetProxyURL(char[] buffer, int maxlength);
	
	public native int GetHeight();
	
	public native int GetWidth();
};

methodmap AttachmentList < Handle {
	property int Size 
	{
		public get() 
		{
			return json_array_size(this);
		}
	}
	public DiscordAttachment GetAttachment(int i) 
	{
		return view_as<DiscordAttachment>(json_array_get(this, i));
	}
	public DiscordAttachment Get(int i) 
	{
		return this.GetAttachment(i);
	}
	
};

/*

{"timestamp": "2017-01-15T20:26:35.353000+00:00", "mention_everyone": false, "id": "270287641155469313", "pinned": false, "edited_timestamp": null, "author": {"username": "DK-Bot", "discriminator": "6274", "bot": true, "id": "186256454863290369", "avatar": null}, "mention_roles": [], "content": "ab", "channel_id": "229677130483499008", "mentions": [], "type": 0}
 */
methodmap DiscordMessage < Handle {
	public native void GetID(char[] buffer, int maxlength);
	
	public native bool IsPinned();
	
	public native DiscordUser GetAuthor();
	
	public native void GetContent(char[] buffer, int maxlength);
	
	public native void GetChannelID(char[] buffer, int maxlength);
	
	public native AttachmentList GetAttachments();
};

#include <discord/channel>
#include <discord/message_embed>
#include <discord/webhook>
#include <discord/bot>

public SharedPlugin __pl_discordapi =
{
	name = "discord-api",
	file = "discord-api.smx",
	#if defined REQUIRE_PLUGIN
	required = 1,
	#else
	required = 0,
	#endif
};

#if !defined REQUIRE_PLUGIN
public void __pl_discordapi_SetNTVOptional()
{
	MarkNativeAsOptional("DiscordRole.GetID");
	MarkNativeAsOptional("DiscordRole.GetName");
	MarkNativeAsOptional("DiscordRole.GetColor");
	MarkNativeAsOptional("DiscordRole.IsHoist");
	MarkNativeAsOptional("DiscordRole.GetPositon");
	MarkNativeAsOptional("DiscordRole.GetPermissions");
	MarkNativeAsOptional("DiscordRole.IsManaged");
	MarkNativeAsOptional("DiscordRole.IsMentionable");
	MarkNativeAsOptional("DiscordUser.GetID");
	MarkNativeAsOptional("DiscordUser.GetUsername");
	MarkNativeAsOptional("DiscordUser.GetDiscriminator");
	MarkNativeAsOptional("DiscordUser.GetAvatar");
	MarkNativeAsOptional("DiscordUser.IsVerified");
	MarkNativeAsOptional("DiscordUser.GetEmail");
	MarkNativeAsOptional("DiscordUser.IsBot");
	MarkNativeAsOptional("DiscordMessage.GetID");
	MarkNativeAsOptional("DiscordMessage.IsPinned");
	MarkNativeAsOptional("DiscordMessage.DiscordUser GetAuthor");
	MarkNativeAsOptional("DiscordMessage.GetContent");
	MarkNativeAsOptional("DiscordMessage.GetChannelID");
	MarkNativeAsOptional("DiscordBot.StartTimer");
	MarkNativeAsOptional("DiscordBot.AddReactionID");
	MarkNativeAsOptional("DiscordBot.DeleteReactionID");
	MarkNativeAsOptional("DiscordBot.GetReactionID");
	MarkNativeAsOptional("DiscordBot.GetToken");
	MarkNativeAsOptional("DiscordBot.SendMessage");
	MarkNativeAsOptional("DiscordBot.SendMessageToChannelID");
	MarkNativeAsOptional("DiscordBot.DeleteMessageID");
	MarkNativeAsOptional("DiscordBot.DeleteMessage");
	MarkNativeAsOptional("DiscordBot.GetGuilds");
	MarkNativeAsOptional("DiscordBot.GetGuildChannels");
	MarkNativeAsOptional("DiscordBot.GetGuildMembers");
	MarkNativeAsOptional("DiscordBot.GetGuildMembersAll");
	MarkNativeAsOptional("DiscordBot.GetGuildRoles");
	MarkNativeAsOptional("DiscordChannel.SendMessage");
	MarkNativeAsOptional("DiscordWebHook.Send");
	MarkNativeAsOptional("DiscordAttachment.GetID");
	MarkNativeAsOptional("DiscordAttachment.GetFilename");
	MarkNativeAsOptional("DiscordAttachment.GetSize");
	MarkNativeAsOptional("DiscordAttachment.GetURL");
	MarkNativeAsOptional("DiscordAttachment.GetProxyURL");
	MarkNativeAsOptional("DiscordAttachment.GetHeight");
	MarkNativeAsOptional("DiscordAttachment.GetWidth");
}
#endif