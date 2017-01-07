public int Native_DiscordBot_GetGuildChannels(Handle plugin, int numParams) {
	DiscordBot bot = GetNativeCell(1);
	
	char guild[32];
	GetNativeString(2, guild, sizeof(guild));
	
	Function fCallback = GetNativeCell(3);
	Function fCallbackAll = GetNativeCell(4);
	any data = GetNativeCell(5);
	
	char url[64];
	FormatEx(url, sizeof(url), "guilds/%s/channels", guild);
	
	Handle request = PrepareRequest(bot, url, k_EHTTPMethodGET, null, GetGuildChannelsData);
	
	DataPack dp = CreateDataPack();
	WritePackCell(dp, bot);
	WritePackString(dp, guild);
	WritePackCell(dp, plugin);
	WritePackFunction(dp, fCallback);
	WritePackFunction(dp, fCallbackAll);
	WritePackCell(dp, data);
	
	SteamWorks_SetHTTPRequestContextValue(request, dp, UrlToDP(url));
	
	DiscordSendRequest(request, url);
}

public int GetGuildChannelsData(Handle request, bool failure, int offset, int statuscode, any dp) {
	if(failure || statuscode != 200) {
		LogError("[DISCORD] Couldn't Retrieve Guilds - Fail %i %i", failure, statuscode);
		delete request;
		delete view_as<Handle>(dp);
		return;
	}
	SteamWorks_GetHTTPResponseBodyCallback(request, GetGuildChannelsData_Data, dp);
	delete request;
}

public int GetGuildChannelsData_Data(const char[] data, any datapack) {
	Handle hJson = json_load(data);
	
	//Read from datapack to get info
	Handle dp = view_as<Handle>(datapack);
	ResetPack(dp);
	int bot = ReadPackCell(dp);
	
	char guild[32];
	ReadPackString(dp, guild, sizeof(guild));
	
	Handle plugin = view_as<Handle>(ReadPackCell(dp));
	Function func = ReadPackFunction(dp);
	Function funcAll = ReadPackFunction(dp);
	any pluginData = ReadPackCell(dp);
	delete dp;
	
	//Create forwards
	Handle fForward = INVALID_HANDLE;
	Handle fForwardAll = INVALID_HANDLE;
	if(func != INVALID_FUNCTION) {
		fForward = CreateForward(ET_Ignore, Param_Cell, Param_String, Param_Cell, Param_Cell);
		AddToForward(fForward, plugin, func);
	}
	
	if(funcAll != INVALID_FUNCTION) {
		fForwardAll = CreateForward(ET_Ignore, Param_Cell, Param_String, Param_Cell, Param_Cell);
		AddToForward(fForwardAll, plugin, funcAll);
	}
	
	ArrayList alChannels = null;
	
	if(funcAll != INVALID_FUNCTION) {
		alChannels = CreateArray();
	}
	
	//Loop through json
	for(int i = 0; i < json_array_size(hJson); i++) {
		Handle hObject = json_array_get(hJson, i);
		
		DiscordChannel Channel = CreateChannelFromJson(hObject);
		
		if(fForward != INVALID_HANDLE) {
			Call_StartForward(fForward);
			Call_PushCell(bot);
			Call_PushString(guild);
			Call_PushCell(Channel);
			Call_PushCell(pluginData);
			Call_Finish();
		}
		
		if(fForwardAll != INVALID_HANDLE) {
			alChannels.Push(Channel);
		}else {
			delete Channel;
		}
		
		delete hObject;
	}
	
	if(fForwardAll != INVALID_HANDLE) {
		Call_StartForward(fForwardAll);
		Call_PushCell(bot);
		Call_PushString(guild);
		Call_PushCell(alChannels);
		Call_PushCell(pluginData);
		Call_Finish();
		
		for(int i = 0; i < alChannels.Length; i++) {
			Handle hChannel = view_as<Handle>(alChannels.Get(i));
			delete hChannel;
		}
		
		delete alChannels;
	}
	
	delete hJson;
}