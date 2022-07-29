/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 32;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Fira Code:size=10", "joypixels:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282c34";
static const char col_gray2[]       = "#1a1a1a";
static const char col_gray3[]       = "#f8f8f2";
static const char col_gray4[]       = "#282c34";
static const char col_cyan[]        = "#bf93f9";
static const char *colors[][3]      = {
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
	/* class             instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Galculator",      NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "TelegramDesktop", NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Qalculate-gtk",   NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Pavucontrol",     NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Blueman-manager", NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Lxpolkit",        NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Alacritty",       NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "st",              NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,              NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define XK_NO_MOD 0
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ XK_NO_MOD, XK_NO_MOD,     ACTION##stack, {.i = 0 } }, \
	{ XK_NO_MOD, XK_NO_MOD,     ACTION##stack, {.i = 1 } }, \
	{ XK_NO_MOD, XK_NO_MOD,     ACTION##stack, {.i = 2 } }, \
	{ XK_NO_MOD, XK_NO_MOD,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key                   function        argument */
    { MODKEY,                       XK_d,                 spawn,          { .v = dmenucmd }  },
	{ MODKEY,             		    XK_Return,            spawn,          SHCMD("$TERMINAL") },
	{ MODKEY,             		    XK_e,                 spawn,          SHCMD("emacs") },
	{ MODKEY,             		    XK_r,                 spawn,          SHCMD("$TERMINAL -e lfub") },
	{ MODKEY,             		    XK_w,                 spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_equal,             spawn,          SHCMD("pamixer --allow-boost -i  5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,             XK_equal,             spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_minus,             spawn,          SHCMD("pamixer --allow-boost -d  5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,             XK_minus,             spawn,          SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,             XK_m,                 spawn,          SHCMD("pamixer               -t   ; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_bracketright,      spawn,          SHCMD("xbacklight -inc 10") },
	{ MODKEY|ShiftMask,             XK_bracketright,      spawn,          SHCMD("xbacklight -inc 25") },
	{ MODKEY,                       XK_bracketleft,       spawn,          SHCMD("xbacklight -dec 10") },
	{ MODKEY|ShiftMask,             XK_bracketleft,       spawn,          SHCMD("xbacklight -dec 25") },
	{ XK_NO_MOD,                    XK_Print,             spawn,          SHCMD("scrot    ~/pix/$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,                    XK_Print,             spawn,          SHCMD("scrot -s ~/pix/$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,                       XK_n,                 spawn,          SHCMD("find  ~/.local/share/wallpapers | shuf | sxiv -bit") },
	{ MODKEY|ShiftMask,             XK_n,                 spawn,          SHCMD("setbg ~/.local/share/wallpapers") },
	{ MODKEY|ShiftMask,             XK_slash,             spawn,          SHCMD("switchxkbmap; kill -49 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_u,                 spawn,          SHCMD("dmenuunicode") },
	{ MODKEY,                       XK_backslash,         spawn,          SHCMD("dmenuman")     },
	{ MODKEY|AltMask,               XK_i,                 spawn,          SHCMD("dmenumount")   },
	{ MODKEY|AltMask,               XK_o,                 spawn,          SHCMD("dmenuumount")  },
	{ MODKEY,                       XK_slash,             spawn,          SHCMD("dwmmenu")  },
	{ MODKEY,                       XK_BackSpace,         spawn,          SHCMD("sysact")  },
	{ MODKEY|ShiftMask,             XK_q,                 spawn,          SHCMD("sysact")  },
	{ MODKEY|ShiftMask,             XK_h,                 spawn,          SHCMD("$TERMINAL -e htop")  },
	{ MODKEY|ShiftMask,             XK_r,                 spawn,          SHCMD("terminator -e newsboat")  },
	{ MODKEY|ShiftMask,             XK_v,                 spawn,          SHCMD("vpntoggle")  },
	{ MODKEY|ShiftMask,             XK_t,                 spawn,          SHCMD("telegram-desktop")  },
	{ MODKEY,                       XK_v,                 spawn,          SHCMD("virt-manager")  },
	{ MODKEY,                       XK_v,                 spawn,          SHCMD("virt-manager")  },
	{ MODKEY,                       XK_o,                 spawn,          SHCMD("obs")  },
	{ MODKEY,                       XK_g,                 spawn,          SHCMD("thunar")  },
	{ MODKEY|ShiftMask,             XK_b,                 spawn,          SHCMD("blueman-manager")  },
	{ MODKEY|ShiftMask,             XK_w,                 spawn,          SHCMD("$TERMINAL -e nmtui")  },

	{ MODKEY,                       XK_b,      togglebar,      {0} },

	STACKKEYS(MODKEY, focus)
	STACKKEYS(MODKEY|ShiftMask, push)

	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },

	{ MODKEY,              XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_z,      incrgaps,       {.i = -1 } },
	{ MODKEY,              XK_x,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_x,      incrigaps,      {.i = -1 } },
	{ MODKEY,              XK_c,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_c,      incrogaps,      {.i = -1 } },
	/* { MODKEY,              XK_6,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY,              XK_7,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY,              XK_8,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY,              XK_9,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } }, */
	{ MODKEY,              XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,    XK_a,      defaultgaps,    {0} },

	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,		                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_apostrophe,   setborderpx,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon,    setborderpx,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_f, 	         setborderpx,    {.i = 0 } },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	/* function keys */
	{ XK_NO_MOD, XF86XK_AudioMute,         spawn, SHCMD("pamixer               -t  ; kill -44 $(pidof dwmblocks)")},
	{ XK_NO_MOD, XF86XK_AudioLowerVolume,  spawn, SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)")},
	{ XK_NO_MOD, XF86XK_AudioRaiseVolume,  spawn, SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)")},
	{ XK_NO_MOD, XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 10")},
	{ XK_NO_MOD, XF86XK_MonBrightnessUp,   spawn, SHCMD("xbacklight -inc 10")},
	{ XK_NO_MOD, XK_F6,                    spawn, SHCMD("(synclient | grep 'Touchpad.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1")},
	{ XK_NO_MOD, XF86XK_Calculator,        spawn, SHCMD("qalculate-gtk")},
	{ XK_NO_MOD, XF86XK_HomePage,          spawn, SHCMD("thunar")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkRootWin,           XK_NO_MOD,      /*Button*/8,    viewprev,       {0} },
	{ ClkRootWin,           XK_NO_MOD,      /*Button*/9,    viewnext,       {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          XK_NO_MOD,      Button2,        zoom,           {0} },
	{ ClkStatusText,        XK_NO_MOD,      Button1,        sigdwmblocks,   {.i = 1 } },
	{ ClkStatusText,        XK_NO_MOD,      Button2,        sigdwmblocks,   {.i = 2 } },
	{ ClkStatusText,        XK_NO_MOD,      Button3,        sigdwmblocks,   {.i = 3 } },
	{ ClkStatusText,        XK_NO_MOD,      Button4,        sigdwmblocks,   {.i = 4 } },
	{ ClkStatusText,        XK_NO_MOD,      Button5,        sigdwmblocks,   {.i = 5 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            XK_NO_MOD,      Button1,        view,           {0} },
	{ ClkTagBar,            XK_NO_MOD,      Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

