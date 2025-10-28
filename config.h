/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "alacritty"
#define BROWSER "brave"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "aporeticsansmono:style=bold:size=14:antialias=true:autohint=true:hintstyle=hintfull" };
static const char dmenufont[]       = "aporeticsansmono:style=bold:size=14:antialias=true:autohint=true:hintstyle=hintfull";
static const char col_gray1[]       = "#0d0e1c";
static const char col_gray2[]       = "#222222";
static const char col_gray3[]       = "#aaaaaa";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#4a4f69";
static const char col_border[]      = "#535d6c";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
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
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, focusmon,       {.i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_m,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY,                       XK_w,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = (const char*[]){ TERMINAL, "-e", "nmtui", NULL } } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = (const char*[]){ "passmenu", NULL } } },
	{ MODKEY,                       XK_BackSpace,  spawn,      {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY|ShiftMask,             XK_BackSpace,  spawn,      {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = (const char*[]){ "displayselect", NULL } } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = (const char*[]){ TERMINAL, "-e", "pulsemixer", NULL } } },
	{ MODKEY,                       XK_F10,    spawn,          {.v = (const char*[]){ "mpv", "av://v4l2:/dev/video0", "--profile=low-latency", "--untimed", "--no-osc", NULL } } },
	{ MODKEY,                       XK_period, spawn,          {.v = (const char*[]){ "mpc", "next", NULL } } },
	{ MODKEY,                       XK_comma,  spawn,          {.v = (const char*[]){ "mpc", "prev", NULL } } },
	{ MODKEY,                       XK_p,      spawn,          {.v = (const char*[]){ "mpc", "toggle", NULL } } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = (const char*[]){ "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL } } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL } } },
	{ MODKEY,                       XK_plus,   spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+", NULL } } },
	{ 0, XF86XK_AudioMute,                     spawn,          {.v = (const char*[]){ "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL } } },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL } } },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          {.v = (const char*[]){ "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,               spawn,          {.v = (const char*[]){ "brightnessctl", "set", "+10%", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,             spawn,          {.v = (const char*[]){ "brightnessctl", "set", "10-%", NULL } } },

	/* Conflicting with larbs */
	{ MODKEY|ShiftMask, 		XK_l, 	   spawn, 	   {.v = (const char*[]){ "xlock", NULL } } },

	{ MODKEY,                       XK_a,      spawn,          {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
	{ MODKEY,                       XK_s,      spawn,          {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

