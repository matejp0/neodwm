#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const char *fonts[]          = { "JetBrainsMono NF:size=12" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282c34";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#abb2bf";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray3  },
};

/* tagging */
// static const char *tags[] = { "\uebb5", "\uebb5", "\uebb5", "\uebb5", "\uebb5", "\uebb5", "\uebb5", "\uebb5", "\uebb5" };
static const char *tags[] = { "\uf10c", "\uf10c", "\uf10c", "\uf10c","\uf10c", "\uf10c","\uf10c", "\uf10c","\uf10c"};
//static const char tagsSel[] = "\uebb4";
static const char tag_decorated[] = "\uf111";

static const char *tagsel[][2] = {
	{ "#e06c75", col_gray1 },
	{ "#be5046", col_gray1 },
	{ "#98c379", col_gray1 },
	{ "#e5c07b", col_gray1 },
	{ "#d19a66", col_gray1 },
	{ "#61afef", col_gray1 },
	{ "#c678dd", col_gray1 },
	{ "#56b6c2", col_gray1 },
	{ "#5c6370", col_gray1 },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
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
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALTKEY,             		KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "librewolf", NULL };
static const char *filescmd[]  = { "Thunar", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             					XK_e, 	   spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,         		XK_e, 	   spawn,          SHCMD("pkill librewolf && librewolf") },
	{ MODKEY,             					XK_z, 	   spawn,          {.v = filescmd } },

	{ 0,														XF86XK_AudioLowerVolume,	 spawn,		SHCMD("/usr/bin/wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%- && pkill -RTMIN+6 dwmblocks") },
	{ 0,														XF86XK_AudioRaiseVolume,	 spawn,		SHCMD("/usr/bin/wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+ && pkill -RTMIN+6 dwmblocks") },
	{ 0,														XF86XK_AudioMute,					 spawn,		SHCMD("/usr/bin/wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle && pkill -RTMIN+6 dwmblocks") },
	{ 0,														XF86XK_MonBrightnessDown,	 spawn,		SHCMD("/usr/bin/xbacklight -dec 5 && pkill -RTMIN+7 dwmblocks") },
	{ 0,														XF86XK_MonBrightnessUp,		 spawn,		SHCMD("/usr/bin/xbacklight -inc 5 && pkill -RTMIN+7 dwmblocks") },

	{ ALTKEY|ShiftMask,							XK_Return, spawn,					 SHCMD("setxkbmap -query | grep -q 'us' && setxkbmap -layout cz -variant qwerty || setxkbmap us; pkill -RTMIN+11 dwmblocks ") },
	{ 0,														XK_Print,	 spawn,					 SHCMD("xfce4-screenshooter") },
	{ MODKEY,												XK_a,			 spawn,					 SHCMD("/usr/bin/autorandr --change && dunstify -r 15 'autorandr' 'reload'") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
//	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             					XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
// 	{ MODKEY,                       XK_space,  setlayout,      {} },
	{ MODKEY|ShiftMask,             XK_f,  		 togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_m,  		 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,  		 tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,   	 quit,           {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_plus,                   0)
	TAGKEYS(                        XK_ecaron,                 1)
	TAGKEYS(                        XK_scaron,                 2)
	TAGKEYS(                        XK_ccaron,                 3)
	TAGKEYS(                        XK_rcaron,                 4)
	TAGKEYS(                        XK_zcaron,                 5)
	TAGKEYS(                        XK_yacute,                 6)
	TAGKEYS(                        XK_aacute,                 7)
	TAGKEYS(                        XK_iacute,                 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

