/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 5;        /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Latin Modern Roman:size=11", "Symbols Nerd Font:size=11", "Noto Serif CJK KR:size=11", "Noto Color Emoji:size=11" };
static const char col_black[]       = "#2e3440";
static const char col_gray[]        = "#4c566a";
static const char col_gray2[]       = "#3b4252";
static const char col_white[]       = "#d8dee9";
static const char *colors[][3]      = {
        /*                     fg           bg           border   */
        [SchemeNorm]       = { col_white,   col_black,   col_gray2 },
        [SchemeSel]        = { col_white,   col_gray,    col_gray  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "kitty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[0]",      monocle },
	{ "[-]",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define ALTKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for 	spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>

/* commands */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *ymenucmd[] = { "ytfzf", "-D", NULL };
static const char *ymenu2cmd[] = { "alacritty", "-e", "ytfzf", "-t", NULL };
static const char *ytmkvcmd[] = { "ymenu", NULL };
static const char *ytflaccmd[] = { "ymenu2", NULL };
static const char *termcmd[] = { "alacritty", NULL };
static const char *term2cmd[] = { "terminal2", NULL };
static const char *term3cmd[] = { "kitty", NULL };
static const char *webcmd[] = { "librewolf-bin", NULL };
static const char *web2cmd[] = { "librewolf-bin", "--private-window", NULL };
static const char *web3cmd[] = { "firefox-bin", NULL };
static const char *web4cmd[] = { "firefox-bin", "--private-window", NULL };
static const char *powercmd[] = { "dlogin", NULL };
static const char *screenshotcmd1[] = { "magickshot", "--selection", NULL };
static const char *screenshotcmd2[] = { "magickshot", "--window", NULL };
static const char *screenshotcmd3[] = { "magickshot", "--monitor", NULL };
static const char *screenshotcmd4[] = { "magickshot", "--display", NULL };
static const char *colorpickercmd[] = { "gcolor2", NULL };
static const char *upvol1[] = { "pavol", "-v", "+1", NULL };
static const char *upvol10[] = { "pavol", "-v", "+10", NULL };
static const char *upvol50[] = { "pavol", "-v", "+50", NULL };
static const char *downvol1[] = { "pavol", "-v", "-1", NULL };
static const char *downvol10[] = { "pavol", "-v", "-10", NULL };
static const char *downvol50[] = { "pavol", "-v", "-50", NULL };
static const char *vol0[] = { "pavol", "-v", "0", NULL };
static const char *volmax[] = { "pavol", "-v", "100", NULL };
static const char *mute[] = { "pavol", "--toggle", NULL };
static const char *micupvol1[] = { "pavol", "-i", "-v", "+1", NULL };
static const char *micupvol10[] = { "pavol", "-i", "-v", "+10", NULL };
static const char *micupvol50[] = { "pavol", "-i", "-v", "+50", NULL };
static const char *micdownvol1[] = { "pavol", "-i", "-v", "-1", NULL };
static const char *micdownvol10[] = { "pavol", "-i", "-v", "-10", NULL };
static const char *micdownvol50[] = { "pavol", "-i", "-v", "-50", NULL };
static const char *micvol0[] = { "pavol", "-i", "-v", "0", NULL };
static const char *micvolmax[] = { "pavol", "-i", "-v", "100", NULL };
static const char *micmute[] = { "pavol", "-i", "--toggle", NULL };
static const char *touchpadtogglecmd[] = { "touchtog", NULL };
static const char *dmojicmd[] = { "dmoji", NULL };
static const char *dmoji2cmd[] = { "dmoji", "--number", NULL };
static const char *cpucmd[] = { "dcpu", NULL };
static const char *killcmd[] = { "xdotool", "getwindowfocus", "windowkill", NULL };
static const char *ytcpcmd[] = { "ytcp", NULL };
static const char *dreccmd[] = { "ffrec", "--dmenu", NULL };
static const char *togglepausecmd[] = { "ffrec", "--pause", NULL };
static const char *endrecordcmd[] = { "ffrec", "--end", NULL };
static const char *clipmenucmd[] = { "clipmenu", NULL };
static const char *dfmcmd[] = { "dfm", NULL };
static const char *dfm2cmd[] = { "dfm", "-c", "clipboard", NULL };
static const char *dfm3cmd[] = { "dfm", "--cat", "-c", "clipboard", NULL };
static const char *webcamcmd[] = { "mpvcam", NULL };
static const char *webcam2cmd[] = { "mpvcam", "-t", NULL };
static const char *cmenucmd[] = { "cmenu", NULL };
static const char *cmenucpcmd[] = { "cmenu", "-c", "clipboard", NULL };
static const char *cmenu3cmd[] = { "cmenu", "--no-copy", NULL };
static const char *statuscmd[] = { "status", NULL };
static const char *togmoncmd[] = { "togmon", NULL };
static const char *keymap[] = { "keymap", NULL };
static const char *playerctl[] = { "playerctl", "play-pause", NULL };
static const char *playerctl_plus_1[] = { "playerctl", "position", "1+", NULL };
static const char *playerctl_minus_1[] = { "playerctl", "position", "1-", NULL };
static const char *playerctl_plus_5[] = { "playerctl", "position", "5+", NULL };
static const char *playerctl_minus_5[] = { "playerctl", "position", "5-", NULL };
static const char *playerctl_plus_10[] = { "playerctl", "position", "10+", NULL };
static const char *playerctl_minus_10[] = { "playerctl", "position", "10-", NULL };
static const char *playerctl_plus_60[] = { "playerctl", "position", "60+", NULL };
static const char *playerctl_minus_60[] = { "playerctl", "position", "60-", NULL };
static const char *playerctl_next[] = { "playerctl", "next", NULL };
static const char *playerctl_previous[] = { "playerctl", "previous", NULL };
static const char *lockcmd[] = { "slock", NULL };
static const char *mancmd[] = { "dman", NULL };

static Key keys[] = {
	/* modifier			key				function			argument */
	{ MODKEY,             		XK_Left,      			spawn,          		{.v = playerctl_minus_10} },
	{ MODKEY,             		XK_Right,      			spawn,          		{.v = playerctl_plus_10} },
	{ MODKEY|ShiftMask,             XK_Left,      			spawn,          		{.v = playerctl_minus_1} },
	{ MODKEY|ShiftMask,             XK_Right,      			spawn,          		{.v = playerctl_plus_1} },
	{ MODKEY,                       XK_Left,      			spawn,          		{.v = playerctl_minus_60} },
	{ MODKEY,                       XK_Right,      			spawn,          		{.v = playerctl_plus_60} },
	{ MODKEY|ShiftMask,             XK_Left,      			spawn,          		{.v = playerctl_minus_5} },
	{ MODKEY|ShiftMask,             XK_Right,      			spawn,          		{.v = playerctl_plus_5} },
	{ MODKEY|ShiftMask,             XK_comma,      			spawn,          		{.v = playerctl_previous} },
	{ MODKEY|ShiftMask,             XK_period,      		spawn,          		{.v = playerctl_next} },
	{ MODKEY,             		XK_f,      			fullscreen,			{0} },
	{ MODKEY,             		XK_Return,      		reorganizetags,     		{0} },
	{ MODKEY,                       XK_b,				togglebar,			{0} },
	{ MODKEY|ShiftMask,             XK_e,      			pushdown,       		{0} },
	{ MODKEY|ShiftMask,             XK_n,				pushup,				{0} },
	{ MODKEY,             		XK_m,      			zoom,           		{0} },
	{ MODKEY,                       XK_Tab,    			view,           		{0} },
	{ MODKEY,                       XK_c,      			killclient,     		{0} },
	{ MODKEY,                       XK_n,				focusstack,			{.i = -1 } },
	{ MODKEY,                       XK_e,      			focusstack,			{.i = +1 } },
	{ MODKEY,                       XK_h,				incnmaster,     		{.i = +1 } },
	{ MODKEY,                       XK_k,    			incnmaster,			{.i = -1 } },
	{ MODKEY,                       XK_i,  				focusmon,       		{.i = -1 } },
	{ MODKEY,                       XK_o, 				focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,  				tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_o, 				tagmon,         		{.i = +1 } },
	{ MODKEY,                       XK_comma,      			setmfact,       		{.f = -0.05} },
	{ MODKEY,                       XK_period,			setmfact,       		{.f = +0.05} },
	{ MODKEY,                       XK_q,      			setlayout,      		{.v = &layouts[0]} },
	{ MODKEY,                       XK_p,      			setlayout,      		{.v = &layouts[1]} },
	{ MODKEY,                       XK_w,      			setlayout,      		{.v = &layouts[2]} },
	{ MODKEY,                       XK_0,      			view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      			tag,            		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_m,      			spawn,          		{.v = statuscmd } },
	{ ALTKEY,             		XK_m,      			spawn,          		{.v = togmoncmd } },
	{ MODKEY,             		XK_l,      			spawn,          		{.v = keymap } },
	{ MODKEY,                       XK_v,      			spawn,          		{.v = cmenucmd } },
	{ MODKEY,                       XK_space,      			spawn,          		{.v = playerctl } },
	{ MODKEY|ShiftMask,             XK_v,      			spawn,          		{.v = cmenucpcmd } },
	{ MODKEY|ControlMask|ShiftMask,             XK_v,      			spawn,          		{.v = cmenu3cmd } },
	{ MODKEY|ShiftMask,             XK_c,      			spawn,          		{.v = killcmd } },
	{ MODKEY,			XK_u,				spawn,				{.v = dfmcmd } },
	{ ALTKEY,			XK_u,				spawn,				{.v = dfm2cmd } },
	{ ALTKEY|ShiftMask,		XK_u,				spawn,				{.v = dfm3cmd } },
	{ MODKEY,               	XK_s,      			spawn,          		{.v = dmenucmd } },
	{ MODKEY,           		XK_z,      			spawn,          		{.v = clipmenucmd } },
	{ ALTKEY,               	XK_o,      			spawn,          		{.v = ytmkvcmd } },
	{ ALTKEY|ShiftMask,		XK_o,      			spawn,          		{.v = ytflaccmd } },
	{ MODKEY|ControlMask,           XK_o,      			spawn,          		{.v = ymenucmd } },
	{ ALTKEY|ControlMask,           XK_o,      			spawn,          		{.v = ymenu2cmd } },
	{ ALTKEY,			XK_i,      			spawn,          		{.v = cpucmd } },
	{ MODKEY,                       XK_t,      			spawn,          		{.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_t,      			spawn,          		{.v = term2cmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_t,      			spawn,          		{.v = term3cmd } },
	{ MODKEY,                       XK_a,      			spawn,          		{.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_a,				spawn,          		{.v = web2cmd } },
	{ MODKEY|ControlMask,           XK_a,				spawn,          		{.v = web3cmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_a,				spawn,          		{.v = web4cmd } },
	{ ALTKEY,                       XK_a,      			spawn,         			{.v = dmojicmd } },
	{ ALTKEY|ShiftMask,             XK_a,      			spawn,          		{.v = dmoji2cmd } },
	{ ALTKEY,              		XK_n,				spawn,				{.v = dreccmd } },
	{ ALTKEY|ShiftMask,             XK_n,				spawn,				{.v = togglepausecmd } },
	{ ALTKEY|ControlMask,           XK_n,				spawn,				{.v = endrecordcmd } },
	{ 0,                       	XF86XK_Battery,			spawn,				{.v = cpucmd } },
	{ ALTKEY,                       XK_e,				spawn,				{.v = webcam2cmd } },
	{ ALTKEY|ShiftMask,             XK_e,				spawn,				{.v = webcamcmd } },
        { MODKEY,                       XK_r,      			spawn,          		{.v = screenshotcmd1 } },
        { MODKEY|ShiftMask,             XK_r,      			spawn,          		{.v = screenshotcmd2 } },
        { ALTKEY,                       XK_r,      			spawn,          		{.v = screenshotcmd3 } },
        { ALTKEY|ShiftMask,             XK_r,      			spawn,          		{.v = screenshotcmd4 } },
        { ALTKEY,                       XK_c,      			spawn,          		{.v = colorpickercmd } },
        { MODKEY|ShiftMask,             XK_equal,  			spawn,          		{.v = upvol1 } },
	{ MODKEY,             		XK_equal,  			spawn,          		{.v = upvol10 } },
	{ MODKEY|ControlMask,           XK_equal,  			spawn,          		{.v = upvol50 } },
	{ MODKEY|ShiftMask,             XK_minus,			spawn,				{.v = downvol1 } },
	{ MODKEY,			XK_minus,			spawn,          		{.v = downvol10 } },
	{ MODKEY|ControlMask,           XK_minus,  			spawn,          		{.v = downvol50 } },
	{ MODKEY,                       XK_BackSpace, 			spawn,       			{.v = mute } },
        { MODKEY|ShiftMask,             XK_BackSpace, 			spawn,       			{.v = vol0 } },
        { MODKEY|ControlMask,           XK_BackSpace, 			spawn,       			{.v = volmax } },
        { MODKEY|ControlMask,           XK_backslash, 			spawn,       			{.v = micvolmax } },
        { MODKEY|ShiftMask,             XK_bracketright,  		spawn,          		{.v = micupvol1 } },
        { MODKEY,             		XK_bracketright,  		spawn,          		{.v = micupvol10 } },
        { MODKEY|ControlMask,           XK_bracketright,  		spawn,          		{.v = micupvol50 } },
        { MODKEY|ShiftMask,             XK_bracketleft,			spawn,          		{.v = micdownvol1 } },
        { MODKEY,             		XK_bracketleft,			spawn,				{.v = micdownvol10 } },
        { MODKEY|ControlMask,           XK_bracketleft,  		spawn,          		{.v = micdownvol50 } },
        { MODKEY,                       XK_backslash, 			spawn,       			{.v = micmute } },
        { MODKEY|ShiftMask,             XK_backslash, 			spawn,       			{.v = micvol0 } },
	{ ShiftMask,              	XF86XK_AudioRaiseVolume,	spawn,          		{.v = upvol1 } },
        { ShiftMask,             	XF86XK_AudioLowerVolume, 	spawn,          		{.v = downvol1 } },
	{ ControlMask,            	XF86XK_AudioRaiseVolume, 	spawn,          		{.v = upvol50 } },
	{ 0,              		XF86XK_AudioRaiseVolume, 	spawn,		          	{.v = upvol10 } },
        { 0,              		XF86XK_AudioLowerVolume, 	spawn,          		{.v = downvol10 } },
        { ControlMask,              	XF86XK_AudioLowerVolume, 	spawn,          		{.v = downvol50 } },
        { 0,              		XF86XK_AudioMute,        	spawn,          		{.v = mute } },
        { 0,              		XF86XK_AudioMicMute,        	spawn,          		{.v = micmute } },
        { ShiftMask,              	XF86XK_AudioMute,        	spawn,          		{.v = vol0 } },
	{ ShiftMask,              	XF86XK_AudioMicMute,        	spawn,          		{.v = micvol0 } },
        { 0,              		XF86XK_TouchpadToggle,        	spawn,          		{.v = touchpadtogglecmd } },
        { MODKEY,                	XK_d,        			spawn,          		{.v = powercmd } },
        { MODKEY|ShiftMask,             XK_d,        			spawn,          		{.v = lockcmd } },
        { MODKEY,             		XK_slash,        		spawn,          		{.v = mancmd } },
        { MODKEY|ControlMask,           XK_d,        			quit,          		        {0} },
        { MODKEY,                	XK_x,        			spawn,          		{.v = touchpadtogglecmd } },
	TAGKEYS(                        XK_1,                   	0)
	TAGKEYS(                        XK_2,                   	1)
	TAGKEYS(                        XK_3,                   	2)
	TAGKEYS(                        XK_4,                   	3)
	TAGKEYS(                        XK_5,                   	4)
	TAGKEYS(                        XK_6,                   	5)
	TAGKEYS(                        XK_7,                   	6)
	TAGKEYS(                        XK_8,                   	7)
	TAGKEYS(                        XK_9,                   	8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
