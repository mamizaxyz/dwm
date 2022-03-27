/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  		= 1;        /* border pixel of windows */
static const unsigned int snap      		= 32;       /* snap pixel */
static const unsigned int swallowfloating 	= 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    		= 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    		= 10;       /* vert inner gap between windows */
static const unsigned int gappoh    		= 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    		= 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          		= 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            		= 1;        /* 0 means no bar */
static const unsigned int systraypinning	= 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft		= 0;   	    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing	= 2;        /* systray spacing */
static const int systraypinningfailfirst	= 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray			= 1;	    /* 0 means no systray */
static const int topbar            		= 1;        /* 0 means bottom bar */
static const char *fonts[]          		= { "Mononoki:size=10", "Vazirmatn:size=10", "JoyPixels:pixelsize=14:antialias=true:autohint=true" };
static const char col_gray1[]       		= "#282c34";
static const char col_gray2[]       		= "#1a1a1a";
static const char col_gray3[]       		= "#f8f8f2";
static const char col_gray4[]       		= "#282c34";
static const char col_cyan[]        		= "#bf93f9";
static const char *colors[][3]      		= {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       	tags mask     isfloating  isterminal  noswallow  monitor */
	{ "Galculator", 	NULL,       NULL,       	0,            1,	  0,	      0,         -1 },
	{ "TelegramDesktop", 	NULL,       NULL,       	0,            1,	  0,	      0,         -1 },
	{ "Pavucontrol", 	NULL,       NULL,       	0,            1,	  0,	      0,         -1 },
	{ "Blueman-manager", 	NULL,       NULL,       	0,            1,	  0,	      0,         -1 },
	{ "Lxpolkit",		NULL,       NULL,       	0,            1,	  0,	      0,         -1 },
	{ TERMCLASS,		NULL,       NULL,     		0,            0,	  1,	      0,         -1 },
	{ "st", 	        NULL,       NULL,       	0,            0,	  1,	      0,         -1 },
	{ NULL, 		NULL,       "Event Tester",     0,            0,	  0,	      1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define XK_NO_MOD 0
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { TERMINAL, "-t", scratchpadname, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY,                       XK_d,      		spawn,          { .v = dmenucmd } },
	{ MODKEY,             		XK_Return, 		spawn,          { .v = termcmd } },
	{ MODKEY,             		XK_e, 		        spawn,          SHCMD("emacs") },
	{ MODKEY,             		XK_r, 		        spawn,          SHCMD(TERMINAL " -e lfub") },
	{ MODKEY, 			XK_w,  			spawn,          SHCMD("$BROWSER") },
	{ MODKEY, 			XK_equal,   		spawn,          SHCMD("pamixer --allow-boost -i 5;  kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask, 		XK_equal,   		spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY, 			XK_minus,   		spawn,          SHCMD("pamixer --allow-boost -d 5;  kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask, 		XK_minus,   		spawn,          SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask, 		XK_m,   		spawn,          SHCMD("pamixer -t;                  kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_bracketright,    	spawn,          SHCMD("xbacklight -inc 10") },
	{ MODKEY,			XK_bracketleft,    	spawn,          SHCMD("xbacklight -dec 10") },
	{ MODKEY|ShiftMask,		XK_bracketright,    	spawn,          SHCMD("xbacklight -inc 25") },
	{ MODKEY|ShiftMask,		XK_bracketleft,    	spawn,          SHCMD("xbacklight -dec 25") },
	{ XK_NO_MOD, 			XK_Print,  		spawn,          SHCMD("scrot    $HOME/pix/$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask, 			XK_Print,  		spawn,          SHCMD("scrot -s $HOME/pix/$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY|ShiftMask,             XK_x,  			spawn,          SHCMD("setbg    $HOME/.local/share/wallpapers") },
	{ MODKEY|ShiftMask,             XK_slash, 		spawn,       	SHCMD("switchxkbmap; kill -49 $(pidof dwmblocks)") },
	{ MODKEY,             		XK_u,  			spawn,          SHCMD("dmenuunicode") },
	{ MODKEY,             		XK_backslash,  		spawn,          SHCMD("dmenuman") },
	{ MODKEY,             		XK_BackSpace,  		spawn,          SHCMD("sysact") },
	{ MODKEY|ShiftMask, 		XK_BackSpace,  		spawn,          SHCMD("sysact") },
	{ MODKEY|ShiftMask,             XK_q,      		spawn,          SHCMD("sysact") },
	{ MODKEY|ShiftMask,             XK_v,      		spawn,          SHCMD("vpntoggle") },
	{ MODKEY,             		XK_v,      		spawn,          SHCMD("virtualbox") },
	{ MODKEY,             		XK_o,      		spawn,          SHCMD("obs") },
	{ MODKEY,             		XK_g,      		spawn,          SHCMD("thunar") },
	{ MODKEY|ShiftMask,		XK_b,      		spawn,          SHCMD("blueman-manager") },
	{ MODKEY|ShiftMask, 		XK_w,  			spawn,          SHCMD(TERMINAL " -e nmtui") },
	{ MODKEY,             		XK_grave,  		togglescratch, 	{ .v = scratchpadcmd } },
	{ MODKEY,             		XK_s,  			togglesticky, 	{0} },
	{ MODKEY,                       XK_b,      		togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_Return, 		zoom,           {0} },
	{ MODKEY,                       XK_j,      		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,      		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Up,      		focusstack,     {.i = -1 } },
	{ Mod1Mask,                     XK_Tab,      		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      		incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Left,      		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Right,      		setmfact,       {.f = +0.05} },
	{ MODKEY,		        XK_z,      		incrgaps,       {.i = +3 } },
	{ MODKEY,              		XK_x,     		incrgaps,       {.i = -3 } },
	{ MODKEY,		        XK_a,      		togglegaps,     {0} },
	{ MODKEY|ShiftMask,		XK_a,      		defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    		view,           {0} },
	{ MODKEY,             		XK_q,      		killclient,     {0} },
	{ MODKEY,                       XK_t,      		setlayout,      { .v = &layouts[0] } },
	{ MODKEY|ShiftMask,             XK_f,      		setlayout,      { .v = &layouts[1] } },
	{ MODKEY,   		        XK_f,      		togglefullscr,  {0} },
	{ MODKEY,                       XK_m,      		setlayout,      { .v = &layouts[2] } },
	{ MODKEY,                       XK_space,  		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,                       XK_0,      		view,           { .ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		tag,            { .ui = ~0 } },
	{ MODKEY,                       XK_comma,  		focusmon,       { .i = -1 } },
	{ MODKEY,                       XK_period, 		focusmon,       { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		tagmon,         { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		tagmon,         { .i = +1 } },
	{ MODKEY,			XK_slash, 		spawn,          SHCMD("dwmmenu") },
	TAGKEYS(                        XK_1,                      		0)
	TAGKEYS(                        XK_2,                      		1)
	TAGKEYS(                        XK_3,                      		2)
	TAGKEYS(                        XK_4,                      		3)
	TAGKEYS(                        XK_5,                      		4)
	TAGKEYS(                        XK_6,                      		5)
	TAGKEYS(                        XK_7,                      		6)
	TAGKEYS(                        XK_8,                      		7)
	TAGKEYS(                        XK_9,                      		8)
	{ XK_NO_MOD, XF86XK_AudioMute,      	spawn,          	SHCMD("pamixer -t;                 kill -44 $(pidof dwmblocks)") },
	{ XK_NO_MOD, XF86XK_AudioRaiseVolume,   spawn,          	SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ XK_NO_MOD, XF86XK_AudioLowerVolume,   spawn,          	SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ XK_NO_MOD, XF86XK_MonBrightnessUp,    spawn,          	SHCMD("xbacklight -inc 10") },
	{ XK_NO_MOD, XF86XK_MonBrightnessDown,  spawn,          	SHCMD("xbacklight -dec 10") },
	{ XK_NO_MOD, XF86XK_TouchpadToggle,  	spawn,          	SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ XK_NO_MOD, XF86XK_Calculator,  	spawn,          	SHCMD("galculator") },
	{ XK_NO_MOD, XF86XK_HomePage,  		spawn,          	SHCMD("thunar") },
	#include "farsikeys.h"

	/*
	 * these keys are up for grabs
	 * keep in mind that
	 * you would also have to add the
	 * equivalent in farsikeys.h
	 *
	 * Super + R
	 * Super + y|Y
	 * Super + ;|:
	 * Super + '|"
	 * Super + c|C
	 * Super + n|N
	 */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,		XK_NO_MOD,	Button2,	zoom,		{0} },
	{ ClkStatusText,	XK_NO_MOD,	Button1,	sigdwmblocks,	{.i = 1} },
	{ ClkStatusText,	XK_NO_MOD,	Button2,	sigdwmblocks,	{.i = 2} },
	{ ClkStatusText,	XK_NO_MOD,	Button3,	sigdwmblocks,	{.i = 3} },
	{ ClkStatusText,	XK_NO_MOD,	Button4,	sigdwmblocks,	{.i = 4} },
	{ ClkStatusText,	XK_NO_MOD,	Button5,	sigdwmblocks,	{.i = 5} },
	{ ClkStatusText,	ShiftMask,	Button1,	sigdwmblocks,	{.i = 6} },
#endif
	{ ClkStatusText,	ShiftMask,	Button3,	spawn,		SHCMD("emacs ~/.local/src/dwmblocks/config.h ") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        incrgaps,	{.i = +1} },
	{ ClkClientWin,         MODKEY,         Button5,        incrgaps,	{.i = -1} },
	{ ClkTagBar,            XK_NO_MOD,      Button1,        view,           {0} },
	{ ClkTagBar,            XK_NO_MOD,      Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	/*{ ClkTagBar,            XK_NO_MOD,              Button4,        shiftview,      {.i = -1} },
	{ ClkTagBar,            XK_NO_MOD,              Button5,        shiftview,      {.i = 1} },*/
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkRootWin,           XK_NO_MOD,      Button2,        togglebar,      {0} },
	{ ClkRootWin,           XK_NO_MOD,      Button3,        spawn,		SHCMD("dwmmenu")},
};
