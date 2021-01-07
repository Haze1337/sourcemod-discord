public int Native_DiscordRole_GetID(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[64];
	JsonObjectGetString(hJson, "id", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordRole_GetName(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[64];
	JsonObjectGetString(hJson, "name", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordRole_GetColor(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetInt(hJson, "color");
}

public int Native_DiscordRole_IsHoist(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetBool(hJson, "hoist");
}

public int Native_DiscordRole_GetPosition(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetInt(hJson, "position");
}

public int Native_DiscordRole_GetPermissions(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[64];
	JsonObjectGetString(hJson, "permissions", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordRole_IsManaged(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetBool(hJson, "managed");
}

public int Native_DiscordRole_IsMentionable(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetBool(hJson, "mentionable");
}