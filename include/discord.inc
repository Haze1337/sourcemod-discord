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
typedef OnGetMembers = function void(DiscordBot bot, char[] guild, GuildMemberList Members);

enum MessageTypes
{
	DEFAULT = 0,
	RECIPIENT_ADD = 1,
	RECIPIENT_REMOVE=  2,
	CALL = 3,
	CHANNEL_NAME_CHANGE = 4,
	CHANNEL_ICON_CHANGE = 5,
	CHANNEL_PINNED_MESSAGE = 6,
	GUILD_MEMBER_JOIN= 7,
	USER_PREMIUM_GUILD_SUBSCRIPTION = 8,
	USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
	USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
	USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
	CHANNEL_FOLLOW_ADD = 12,
	GUILD_DISCOVERY_DISQUALIFIED = 14,
	GUILD_DISCOVERY_REQUALIFIED = 15,
	REPLY = 19,
	APPLICATION_COMMAND = 20,
}

methodmap DiscordRole < Handle 
{
	public void GetID(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "id", buffer, maxlength);
	}
	
	public void GetName(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "name", buffer, maxlength);
	}
	
	public int GetColor()
	{
		return JsonObjectGetInt(this, "color");
	}
	
	public bool IsHoist()
	{
		return JsonObjectGetBool(this, "hoist");
	}

	public int GetPosition()
	{
		return JsonObjectGetInt(this, "position");
	}
	
	public void GetPermissions(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "permissions", buffer, maxlength);
	}
	
	public bool IsManaged()
	{
		return JsonObjectGetBool(this, "managed");
	}
	
	public bool IsMentionable()
	{
		return JsonObjectGetBool(this, "mentionable");
	}
};

methodmap RoleList < Handle 
{
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

methodmap RoleIDs < Handle 
{
	property int Size 
	{
		public get() 
		{
			return json_array_size(this);
		}
	}
	
	public void GetID(int i, char[] sID, int maxlength) 
	{
		json_array_get_string(this, i, sID, maxlength);
		
	}
	
	public void Get(int i, char[] sID, int maxlength) 
	{
		this.GetID(i, sID, maxlength);
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

methodmap DiscordUser < Handle 
{
	public void GetID(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "id", buffer, maxlength);
	}
	
	public void GetUsername(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "username", buffer, maxlength);
	}
	
	public void GetDiscriminator(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "discriminator", buffer, maxlength);
	}
	
	public int GetDiscriminatorInt() {
		char buffer[16];
		this.GetDiscriminator(buffer, sizeof(buffer));
		return StringToInt(buffer);
	}
	
	public void GetAvatar(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "avatar", buffer, maxlength);
	}
	
	public bool IsVerified()
	{
		return JsonObjectGetBool(this, "verified");
	}
	
	public void GetEmail(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "email", buffer, maxlength);
	}
	
	public bool IsBot()
	{
		return JsonObjectGetBool(this, "bot");
	}
};

methodmap DiscordGuildMember < Handle 
{
	//Returns User Object
	public DiscordUser GetUser() 
	{
		return view_as<DiscordUser>(json_object_get(this, "user"));
	}
	
	//Returns player's nick
	public void GetNickname(char[] buffer, int maxlength) 
	{
		JsonObjectGetString(this, "nick", buffer, maxlength);
	}
	
	//Returns JSON array of role object ids. You can manually loop through them for now.
	public RoleIDs GetRoleIDs() 
	{
		return view_as<RoleIDs>(json_object_get(this, "roles"));
		
	}
	
	//Returns the date the user joined the guild in format: "2015-04-26T06:26:56.936000+00:00"
	public void GetJoinedAt(char[] buffer, int maxlength) 
	{
		JsonObjectGetString(this, "joined_at", buffer, maxlength);
	}
	
	public bool IsDeaf() 
	{
		return JsonObjectGetBool(this, "deaf");
	}
	
	public bool IsMute() 
	{
		return JsonObjectGetBool(this, "mute");
	}
};

methodmap GuildMemberList < Handle {
	property int Size 
	{
		public get() 
		{
			return json_array_size(this);
		}
	}
	public DiscordGuildMember GetMember(int i) 
	{
		return view_as<DiscordGuildMember>(json_array_get(this, i));
	}
	public DiscordGuildMember Get(int i) 
	{
		return this.GetMember(i);
	}
	
};

methodmap DiscordAttachment < Handle 
{
	public void GetID(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "id", buffer, maxlength);
	}
	
	public void GetFilename(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "filename", buffer, maxlength);
	}
	
	public int GetSize()
	{
		return JsonObjectGetInt(this, "size");
	}
	
	public void GetURL(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "url", buffer, maxlength);
	}

	public void GetProxyURL(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "proxy_url", buffer, maxlength);
	}
	
	public int GetHeight()
	{
		return JsonObjectGetInt(this, "height");
	}
	
	public int GetWidth()
	{
		return JsonObjectGetInt(this, "width");
	}
};

methodmap AttachmentList < Handle 
{
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

methodmap EmbedAuthor < Handle 
{
	public void GetName(char[] buffer, int maxlength) 
	{
		JsonObjectGetString(this, "name", buffer, maxlength);
	}
	
	public void GetUrl(char[] buffer, int maxlength) 
	{
		JsonObjectGetString(this, "url", buffer, maxlength);
	}
	
	public void GetIconUrl(char[] buffer, int maxlength) 
	{
		JsonObjectGetString(this, "icon_url", buffer, maxlength);
	}
	
	public void GetProxyIconUrl(char[] buffer, int maxlength) 
	{
		JsonObjectGetString(this, "proxy_icon_url", buffer, maxlength);
	}
};


methodmap MessageEmbed < Handle 
{
	public MessageEmbed() 
	{
		Handle hObj = json_object();
		return view_as<MessageEmbed>(hObj);
	}

	public bool GetColor(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "color", buffer, maxlength);
	}

	public void SetColor(const char[] color) 
	{
		json_object_set_new(this, "color", json_string(color));
	}

	public bool GetTitle(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "title", buffer, maxlength);
	}

	public void SetTitle(const char[] title) 
	{
		json_object_set_new(this, "title", json_string(title));
	}

	public bool GetTitleLink(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "title_link", buffer, maxlength);
	}

	public void SetTitleLink(const char[] title_link) 
	{
		json_object_set_new(this, "title_link", json_string(title_link));
	}

	public bool GetImage(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "image_url", buffer, maxlength);
	}

	public void SetImage(const char[] image_url) 
	{
		json_object_set_new(this, "image_url", json_string(image_url));
	}
	
	public EmbedAuthor GetAuthor()
	{
		return view_as<EmbedAuthor>(json_object_get(this, "author"));
	}

	public void SetAuthor(const char[] author_name) 
	{
		json_object_set_new(this, "author_name", json_string(author_name));
	}

	public bool GetAuthorLink(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "author_link", buffer, maxlength);
	}

	public void SetAuthorLink(const char[] author_link) 
	{
		json_object_set_new(this, "author_link", json_string(author_link));
	}

	public bool GetAuthorIcon(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "author_icon", buffer, maxlength);
	}

	public void SetAuthorIcon(const char[] author_icon) 
	{
		json_object_set_new(this, "author_icon", json_string(author_icon));
	}

	public bool GetThumb(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "thumb_url", buffer, maxlength);
	}

	public void SetThumb(const char[] thumb_url) 
	{
		json_object_set_new(this, "thumb_url", json_string(thumb_url));
	}

	public bool GetFooter(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "footer", buffer, maxlength);
	}

	public void SetFooter(const char[] footer) 
	{
		json_object_set_new(this, "footer", json_string(footer));
	}

	public bool GetFooterIcon(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "footer_icon", buffer, maxlength);
	}

	public void SetFooterIcon(const char[] footer_icon) 
	{
		json_object_set_new(this, "footer_icon", json_string(footer_icon));
	}
	/**
	 * Note: Setting Fields will delete the handle!
	 */
	property Handle Fields
	{
		public get() 
		{
			return json_object_get(this, "fields");
		}

		public set(Handle value) 
		{
			json_object_set_new(this, "fields", value);
		}
	}

	public void AddField(const char[] name, const char[] value, bool inline) 
	{
		Handle hObj = json_object();
		json_object_set_new(hObj, "name", json_string(name));
		json_object_set_new(hObj, "value", json_string(value));
		json_object_set_new(hObj, "inline", json_boolean(inline));
		Handle hArray = this.Fields;
		if(this.Fields == null) 
		{
			hArray = json_array();
		}
		json_array_append_new(hArray, hObj);
		this.Fields = hArray;
	}

	//Below don't support Slack Mode
	public bool GetDescription(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "description", buffer, maxlength);
	}

	public void SetDescription(const char[] description) 
	{
		json_object_set_new(this, "description", json_string(description));
	}

	public bool GetURL(char[] buffer, int maxlength) 
	{
		return JsonObjectGetString(this, "url", buffer, maxlength);
	}

	public void SetURL(const char[] url) 
	{
		json_object_set_new(this, "url", json_string(url));
	}
};

methodmap EmbedList < Handle 
{
	property int Size 
	{
		public get() 
		{
			return json_array_size(this);
		}
	}
	public MessageEmbed GetEmbed(int i) 
	{
		return view_as<MessageEmbed>(json_array_get(this, i));
	}
	public MessageEmbed Get(int i) 
	{
		return this.GetEmbed(i);
	}
};

/*

{"timestamp": "2017-01-15T20:26:35.353000+00:00", "mention_everyone": false, "id": "270287641155469313", "pinned": false, "edited_timestamp": null, "author": {"username": "DK-Bot", "discriminator": "6274", "bot": true, "id": "186256454863290369", "avatar": null}, "mention_roles": [], "content": "ab", "channel_id": "229677130483499008", "mentions": [], "type": 0}
 */
methodmap DiscordMessage < Handle 
{
	public void GetID(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "id", buffer, maxlength);
	}
	
	public void GetTimestamp(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "id", buffer, maxlength);
	}
	
	public bool IsPinned()
	{
		return JsonObjectGetBool(this, "pinned");
	}
	
	public DiscordUser GetAuthor()
	{
		return view_as<DiscordUser>(json_object_get(this, "author"));
	}
	
	public void GetContent(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "content", buffer, maxlength);
	}
	
	public void GetChannelID(char[] buffer, int maxlength)
	{
		JsonObjectGetString(this, "channel_id", buffer, maxlength);
	}
	
	public AttachmentList GetAttachments()
	{
		return view_as<AttachmentList>(json_object_get(this, "attachments"));
	}
	
	public MessageTypes GetType()
	{
		return view_as<MessageTypes>(JsonObjectGetInt(this, "type"));
	}
	
	public DiscordMessage ReferencedMessage()
	{
		return view_as<DiscordMessage>(json_object_get(this, "referenced_message"));
	}
	public EmbedList GetEmbeds()
	{
		return view_as<EmbedList>(json_object_get(this, "embeds"));
	}
};

#include <discord/channel>
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
}
#endif