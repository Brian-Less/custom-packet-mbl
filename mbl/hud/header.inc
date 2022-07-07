#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI_Coding\y_inline>
#include <YSI_Visual\y_dialog>
#include <YSI_Players\y_groups>
#include <YSI_Visual\y_commands>

#include <Pawn.RakNet>

new CUSTOM_SYNC = 251;

enum E_TOGGLE_HUD
{
	E_TOG_CHAT = 0,
	E_TOG_RADAR,
	E_TOG_TAG,
	E_TOG_WIDGET,
	E_TOG_HUD,
	E_TOG_SPEAKER,
	E_TOG_3DTEXT,
	E_TOG_SIZE
}