#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
	bool:PlayerTogHUD[MAX_PLAYERS][E_TOGGLE_HUD:E_TOG_SIZE];

YCMD:togglehud(playerid, params[], help)
{
	ShowControlHUDDialog(playerid);
	return 1;
}

ShowControlHUDDialog(playerid)
{
	inline const Response(response, listitem, string:inputtext[]) 
	{
		#pragma unused response, inputtext, listitem

		if (response)
		{
			CustomRPC_ToggleHud(playerid, listitem, PlayerTogHUD[playerid][E_TOGGLE_HUD:listitem]); // เดิมตัวเกมเป็น 1 ดังนั้นส่ง 0 ไปเพื่อปิดในครั้งแรก (สลับเปิด/ปิด)
			PlayerTogHUD[playerid][E_TOGGLE_HUD:listitem] = !PlayerTogHUD[playerid][E_TOGGLE_HUD:listitem];

			@return ShowControlHUDDialog(playerid);
		}
	}

	new szDialogMsg[80 + 22 * _:E_TOG_SIZE + 1];
	format(szDialogMsg, sizeof(szDialogMsg), 
		"แชท\t[%s]\nเรดาร์\t[%s]\nป้ายชื่อ\t[%s]\nวิดเจ็ต\t[%s]\nHUD\t[%s]\nรายชื่อ (Speaker SAMPVoice)\t[%s]\nข้อความ 3DText\t[%s]",
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_CHAT] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_RADAR] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_TAG] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_WIDGET] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_HUD] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_SPEAKER] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_3DTEXT] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE"")
	
		);

	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST, "การควบคุม HUD (สำหรับเวอร์ชั่นโค้ด 134)", szDialogMsg, "เลือก", "ปิดหน้าต่าง");
}

stock CustomRPC_ToggleHud(playerid, hud_id, bool:toggled)
{
	new BitStream:bsn = BS_New();
	BS_WriteUint8(bsn, CUSTOM_SYNC);
	BS_WriteInt32(bsn, 1);

	BS_WriteInt32(bsn, hud_id);
	BS_WriteInt32(bsn, toggled);

	PR_SendPacket(bsn, playerid);
}