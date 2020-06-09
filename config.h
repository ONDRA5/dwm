/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;	/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;	/* 0 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]  = { "Hack Nerd Font:size=10:antialias=true:autohint=true", "fontawesome:size=10" };
static const char dmenufont[]       = "Hack Nerd Font:size=10";
static const char col_gray1[]       = "#282828";	/* bar background color */
static const char col_gray2[]       = "#444444";	/* unfocused window frame color */
static const char col_gray3[]       = "#ebdbb2"; 	/* bar item color */
static const char col_gray4[]       = "#ebdbb2"; 	/* selected bar item color */
static const char col_cyan[]        = "#98971a";	/* accent color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *
	 * 1 << 8, moves 1 8times left generating number 100000000, so forexample if you want tag 4, do 1 << 3,
	 */
	/* class	instance	title       tags mask     isfloating   isterminal	noswallow	monitor */
	{ "Gimp",     	NULL,     	NULL,       0,            1,           0,		0,		-1 },
	{ "Firefox",  	NULL,     	NULL,       1,		  0,           0,		0,		-1 },
	{ "Galculator", NULL,     	NULL,       0,		  1,	       0,		0,		-1 },
	{ "Brave",     	NULL,	  	NULL,       1,	    	  0,	       0,		0,		-1 },
	{ "st-256color",NULL,	  	NULL,	    0,	  	  0,	       1,		0,		-1 },
	{ NULL,		NULL, "Event Tester", 	    0,	    	  0,	       0,		1,		-1 },
	{ "firefox", 	NULL, "Picture-in-Picture", 0,      	  1,	       0,		0,		-1 },
	{ "qutebrowser",NULL,	  	NULL,	    1,		  0,	       0,	        0,		-1 },
	{ "TelegramDesktop", "telegram-desktop", "Telegram", 1 << 3, 0,        0,		0,		-1 },
	{ "Pcmanfm",	"pcmanfm",	NULL,	    1 << 1,	  0,	       1,		0,		-1 },
	{ NULL,		NULL,		"ranger",   1 << 1,	  0,	       0,		0,		-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
	{ "[]=",      tile },
	{ "\\",	      dwindle },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *scrot[] = { "scrot", NULL };
static const char *dmenuexit[] = { "/home/ondra/.local/bin/dmenuexit.sh", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
//static const char *volup[] = { "amixer", "set", "Master", "10%+", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,		        XK_Return, spawn,          {.v = termcmd } },
	{ 0,				XK_Print,  spawn,	   {.v = scrot } },
	{ MODKEY,			XK_o,	   spawn,	   SHCMD("dmenu_websearch") },
	{ MODKEY|ShiftMask,		XK_n,	   spawn,	   SHCMD("st -e newsboat") },
	{ MODKEY|ShiftMask,		XK_w,	   spawn,	   SHCMD("st -e weather") },
	{ MODKEY,			XK_c,	   spawn,	   SHCMD("st -e calcurse") },
	{ MODKEY,			XK_semicolon,   spawn,	   SHCMD("dswitcher") },
	{ MODKEY,			XK_BackSpace, spawn,	   SHCMD("dmenufm") },
	{ MODKEY,			XK_t,	   spawn,	   SHCMD("telegram-desktop") },
	{ MODKEY,			XK_w,	   spawn,	   SHCMD("qutebrowser") }, 
	{ MODKEY,			XK_e,	   spawn,	   SHCMD("emoji") },
	{ MODKEY|ShiftMask,		XK_m,      spawn,	   SHCMD("dmenumount") },
	{ MODKEY|ShiftMask,		XK_u,	   spawn,	   SHCMD("dmenuumount") },
	{ MODKEY,			XK_m,	   spawn,	   SHCMD("st -e neomutt") },
	{ MODKEY|ShiftMask,		XK_r,	   spawn,	   SHCMD("st -e ranger") },
	{ MODKEY,			XK_r,	   rotatestack,	   {0} },
	{ MODKEY,			XK_s,	   togglesticky,   {0} },
	{ MODKEY|ShiftMask,		XK_Return, togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
//	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,	                XK_space,  togglefloating, {0} },
	{ MODKEY,			XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_plus,                      0)
	TAGKEYS(                        XK_ecaron,                      1)
	TAGKEYS(                        XK_scaron,                      2)
	TAGKEYS(                        XK_ccaron,                      3)
	TAGKEYS(                        XK_rcaron,                      4)
	TAGKEYS(                        XK_zcaron,                      5)
	TAGKEYS(                        XK_yacute,                      6)
	TAGKEYS(                        XK_aacute,                      7)
	TAGKEYS(                        XK_iacute,                      8)
//numpad
	TAGKEYS(			XK_KP_End,			0)
	TAGKEYS(			XK_KP_Down,			1)
	TAGKEYS(			XK_KP_Next,			2)
	TAGKEYS(			XK_KP_Left,			3)
	TAGKEYS(			XK_KP_Begin,			4)
	TAGKEYS(			XK_KP_Right,			5)
	TAGKEYS(			XK_KP_Home,			6)
	TAGKEYS(			XK_KP_Up,			7)
	TAGKEYS(			XK_KP_Prior,			8)
//	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ShiftMask,		XK_e,	   spawn,	   {.v = dmenuexit } },
	
	{ 0, XF86XK_AudioRaiseVolume,	spawn,			    SHCMD("amixer -q -D pulse sset Master 5%+ && pkill -RTMIN+13 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,			    SHCMD("amixer -q -D pulse sset Master 5%- && pkill -RTMIN+13 dwmblocks") },
	{ 0, XF86XK_AudioMute,		spawn,			    SHCMD("amixer -q -D pulse sset Master toggle") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,			    SHCMD("xbacklight -dec 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,			    SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_TouchpadToggle,	spawn,			    SHCMD("(synclient | grep 'Touchpad0ff.*1' && synclient Touchpad0ff=0) || synclient Touchpad0ff=1") },	
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

