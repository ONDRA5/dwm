/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;	/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282A36";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#FF5555";
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
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "\\",	      dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *scrot[] = { "i3-scrot", NULL };
static const char *dmenuexit[] = { "/home/ondra/.local/bin/dmenuexit.sh", NULL };
//static const char *volup[] = { "amixer", "set", "Master", "10%+", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,		        XK_Return, spawn,          {.v = termcmd } },
	{ 0,				XK_Print,  spawn,	   {.v = scrot } },
	{ MODKEY,			XK_b,	   spawn,	   SHCMD("tabbed -r 2 surf -pe x 'https://www.duckduckgo.com'") }, { MODKEY,			XK_eacute, spawn,	   SHCMD("i3exit lock") },
	{ MODKEY,			XK_r,	   rotatestack,	   {0} },
	{ MODKEY,			XK_s,	   togglesticky,   {0} },
//	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
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
	
	{ 0, XF86XK_AudioRaiseVolume,	spawn,			    SHCMD("amixer -q sset Master 2%+") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,			    SHCMD("amixer -q sset Master 2%-") },
	{ 0, XF86XK_AudioMute,		spawn,			    SHCMD("amixer -q sset Master toggle") },
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
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

