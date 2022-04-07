#include <X11/XF86keysym.h>
/* TODO: Add new keybindings to this file */

	/* modifier                     key        		function        argument */
	{ MODKEY,                       XK_Farsi_yeh,      	spawn,          { .v = dmenucmd } },
	{ MODKEY,             		XK_Arabic_theh,         spawn,          SHCMD("emacs") },
	{ MODKEY,             		XK_Arabic_qaf,          spawn,          SHCMD(TERMINAL " -e lfub") },
	{ MODKEY, 			XK_Arabic_sad,  	spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask, 		XK_Arabic_peh,          spawn,          SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_Arabic_tcheh,    	spawn,          SHCMD("xbacklight -inc 10") },
	{ MODKEY,			XK_Arabic_jeem,    	spawn,          SHCMD("xbacklight -dec 10") },
	{ MODKEY|ShiftMask,		XK_Arabic_tcheh,    	spawn,          SHCMD("xbacklight -inc 25") },
	{ MODKEY|ShiftMask,		XK_Arabic_jeem,    	spawn,          SHCMD("xbacklight -dec 25") },
	{ MODKEY|ShiftMask,             XK_Arabic_tah,  	spawn,          SHCMD("setbg $HOME/.local/share/wallpapers") },
	{ MODKEY,             		XK_Arabic_ain,  	spawn,          SHCMD("dmenuunicode") },
	{ MODKEY|ShiftMask,             XK_Arabic_dad,      	spawn,          SHCMD("sysact") },
	{ MODKEY|ShiftMask,             XK_Arabic_ra,      	spawn,          SHCMD("vpntoggle") },
	{ MODKEY,             		XK_Arabic_ra,      	spawn,          SHCMD("virtualbox") },
	{ MODKEY,             		XK_Arabic_khah,      	spawn,          SHCMD("obs") },
	{ MODKEY,             		XK_Arabic_lam,      	spawn,          SHCMD("thunar") },
	{ MODKEY|ShiftMask,             XK_Arabic_thal,      	spawn,		SHCMD("blueman-manager") },
	{ MODKEY|ShiftMask, 		XK_Arabic_sad,  	spawn,          SHCMD(TERMINAL " -e nmtui") },
	{ MODKEY,             		0x100200d,  		togglescratch, 	{ .v = scratchpadcmd } },
					/* key code for (`) in hex  */
	{ MODKEY,             		XK_Arabic_seen,  	togglesticky, 	{0} },
	{ MODKEY,                       XK_Arabic_thal,      	togglebar,      {0} },
	{ MODKEY,                       XK_Arabic_teh,      	focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Arabic_noon,      	focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Arabic_ha,      	incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_Arabic_hah,      	incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Arabic_teh,      	setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Arabic_meem,      	setmfact,       {.f = +0.05} },
	{ MODKEY,		        XK_Arabic_zah,      	incrgaps,       {.i = +3 } },
	{ MODKEY,			XK_Arabic_tah,     	incrgaps,       {.i = -3 } },
	{ MODKEY,		        XK_Arabic_sheen,      	togglegaps,     {0} },
	{ MODKEY|ShiftMask,		XK_Arabic_sheen,      	defaultgaps,    {0} },
	{ MODKEY,             		XK_Arabic_dad,      	killclient,     {0} },
	{ MODKEY,                       XK_Arabic_feh,      	setlayout,      { .v = &layouts[0] } },
	{ MODKEY|ShiftMask,             XK_Arabic_beh,      	setlayout,      { .v = &layouts[1] } },
	{ MODKEY,   		        XK_Arabic_beh,      	togglefullscr,  {0} },
	{ MODKEY,                       XK_Arabic_peh,      	setlayout,      { .v = &layouts[2] } },
	{ MODKEY,                       XK_Farsi_0,      	view,           { .ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_Farsi_0,      	tag,            { .ui = ~0 } },
	{ MODKEY,                       XK_Arabic_waw,  	focusmon,       { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_Arabic_waw,  	tagmon,         { .i = -1 } },
	TAGKEYS(                        XK_Farsi_1,             0)
	TAGKEYS(                        XK_Farsi_2,             1)
	TAGKEYS(                        XK_Farsi_3,             2)
	TAGKEYS(                        XK_Farsi_4,             3)
	TAGKEYS(                        XK_Farsi_5,             4)
	TAGKEYS(                        XK_Farsi_6,             5)
	TAGKEYS(                        XK_Farsi_7,             6)
	TAGKEYS(                        XK_Farsi_8,             7)
	TAGKEYS(                        XK_Farsi_9,             8)
