public int Native_DiscordAttachment_GetID(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[64];
	JsonObjectGetString(hJson, "id", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordAttachment_GetFilename(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[256];
	JsonObjectGetString(hJson, "filename", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordAttachment_GetSize(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetInt(hJson, "size");
}

public int Native_DiscordAttachment_GetURL(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[1024];
	JsonObjectGetString(hJson, "url", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordAttachment_GetProxyURL(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	char buffer[1024];
	JsonObjectGetString(hJson, "proxy_url", buffer, sizeof(buffer));
	SetNativeString(2, buffer, GetNativeCell(3));
}

public int Native_DiscordAttachment_GetHeight(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetInt(hJson, "height");
}

public int Native_DiscordAttachment_GetWidth(Handle plugin, int numParams) {
	Handle hJson = GetNativeCell(1);
	return JsonObjectGetInt(hJson, "width");
}