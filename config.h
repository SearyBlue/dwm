// #include "gaplessgrid.c"

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
// static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = {"Fira Code:size=11:style=bold", "Font Awesome 5 Brands Regular:size=11:style=bold", "Font Awesome 5 Free Solid:size=11:style=bold", "Font Awesome 5 Free Regular:size=11:style=bold"};
static const char dmenufont[]       = "Hack Nerd Font:size=12";
static const char col_gray1[]       = "#0d1011";
static const char col_cyan[]        = "#0055ff";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#000000";
static const char col_gray[]        = "#1d1f21";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray4 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan },
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6"};
static const char *tags[] = { "", "", "", "", "", ""};

static const Rule rules[] = {
	/* class      	instance    title       tags mask    switch to tag   isfloating   monitor */
	{ "firefox", NULL, "Mozilla Firefox",       1<<0,     	1,		  	0,           -1 },
	{ "Waterfox","Navigator",  "Waterfox Current",   1<<0,     	1,		  	0,           -1 },
	{ "Chromium","chromium",  NULL,   1<<0,     			1,		  	0,           -1 },
	{ NULL, NULL, "Preferences", 1<<0,     	1,		  	1,           -1 },
	{ "Waterfox",  "Places",  NULL,   			NULL,     	0,		  	1,           -1 },
	{ NULL,  	   NULL,  "Waterfox Classic",   1<<0,     	1,		  	0,           -1 },
	{ "St",  			"st",    "ranger",		1<<1,     	1,		  	0,           -1 },
	{ "St",  			"st",    "nnn",		1<<1,     	1,		  	0,           -1 },
	{ "St",				"st",     "st",       	1<<2,     	1,		  	0,           -1 },
	{ "Subl3",  		NULL,  "Sublime Text",  1<<3,     	1,		  	0,           -1 },
	{ "Zathura",  		NULL,       NULL,       1<<4,     	1,		  	1,           -1 },
	{"Transmission-gtk",NULL,       NULL,       1<<5,      	1, 			1,           -1 },
	{ "Evince",  		NULL,       NULL,       1<<4,     	1,		  	1,           -1 },
	{ NULL, 			NULL,  "LibreOffice",   1<<5,     	1,		  	1,           -1 },
	{ "float-term",  	NULL,       NULL,       NULL,      	NULL,	 	1,           -1 },
	{NULL,       		NULL,        "mutt",  	NULL,      	NULL,	 	1,           -1 },
	{NULL,       		NULL,        "qalc",  	NULL,      	NULL,	 	1,           -1 },
	{ "Pqiv",			NULL,       NULL,       NULL,      	NULL,	 	1,           -1 },
	{ "Mtpaint",		NULL,       NULL,       NULL,      	NULL,	 	1,           -1 },
	{ "mpv",			NULL,       NULL,       NULL,      	NULL,	 	0,           -1 },
	{"Lxappearance",	NULL,       NULL,       NULL,      	NULL,	 	1,           -1 },
	{NULL,	NULL, "/home/kirito/.cache/manpages/",       1<<2,      	NULL,	 	1,           -1 },
	{"Gnuplot",			NULL,       NULL,       NULL,      	NULL,	 	1,           -1 },
	{"St",				NULL,     "mocp",       NULL,      	NULL,	 	1,           -1 },
	{NULL,		"gpartedbin",       NULL,       NULL,      	NULL,	 	1,           -1 },
	{"Nm-connection-editor", NULL,	NULL,		NULL,      	NULL,	 	1,           -1 },
	{"Matplotlib", NULL,	NULL,		NULL,      	NULL,	 	1,           -1 },
	{NULL,NULL, "Default (Linux).sublime-keymap - Sublime Text (UNREGISTERED)",       NULL,       NULL,      	NULL,	 	1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;   /* number of clients in master area */
static const int resizehints = 0;   /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	// { "",      gaplessgrid },
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,         {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,   {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,          {.ui = 1 << TAG} }, \
    { MODKEY|Mod1Mask, 				KEY,      tag,      	{.ui = 1 << TAG} }, \
    { MODKEY|Mod1Mask, 				KEY,      view,      	{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	// { MODKEY,                       XK_a,	   spawn,          SHCMD("find ${PATH//:/ } -maxdepth 1 -executable -printf '%f\n' | dmenu | xargs bash -c")},
	{ MODKEY,                       XK_a,	   spawn,          SHCMD("dmenu_run")},
	{ MODKEY|ControlMask,			XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,			XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,			XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Down,     setcfact,       {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_Up,   setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_Page_Up,zoom,           {0} },
	{ MODKEY,             			XK_x,      killclient,     {0} },
	{ MODKEY|ControlMask,			XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,			XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,      		XK_m,	   setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)


	{ MODKEY|ShiftMask,				 XK_r,        spawn,    SHCMD("st -c float-term bash -ic \"cd /home/kirito/.config/dwm; make install && killall dwm || read\"") },
	{ MODKEY,                        XK_s,     spawn,       SHCMD("subl3") },
    { MODKEY,                        XK_b,     spawn,       SHCMD("wmctrl -a 'chromium' || chromium") },
    { MODKEY,                        XK_z,     spawn,       SHCMD("wmctrl -x -a Zathura || open-book") },
    { MODKEY,                        XK_l,     spawn,       SHCMD("wmctrl -a 'LibreOffice' || libreoffice6.4 --quickstart --nologo") },
{ MODKEY,                        XK_e,     spawn,       SHCMD("wmctrl -x -a mpv || wmctrl -lp | grep $(pgrep -fx -n 'st ranger') | awk '{print $1}' | xargs wmctrl -ia || st ranger") },
    { MODKEY|ShiftMask,              XK_e,     spawn,       SHCMD("st ranger") },
    { MODKEY,                        XK_t,        spawn,       SHCMD("wmctrl -lp | grep $(pgrep -fx -n 'st') | awk '{print $1}' | xargs wmctrl -ia || st") },
    { MODKEY,                        XK_Return,   spawn,          {.v = termcmd } },



    { MODKEY,                        XK_n,        spawn,       SHCMD("network") },
    { MODKEY|ShiftMask,            	XK_h,        spawn,       SHCMD("mocp --seek -10") },
    { MODKEY|ShiftMask,            	XK_j,        spawn,       SHCMD("mocp --seek +10") },
    { MODKEY|ControlMask,            XK_h,        spawn,       SHCMD("mocp --seek -50") },
    { MODKEY|ControlMask,            XK_j,        spawn,       SHCMD("mocp --seek +50") },
    { MODKEY|ShiftMask,				 XK_n,        spawn,       SHCMD("nmcli radio wifi | grep disable && nmcli radio wifi on || nmcli radio wifi off") },
    { NULL,                          XK_Print,    spawn,       SHCMD("gnome-screenshot -f /storage/pictures/$(date '+%F_%T').png") },
    { MODKEY,                        XK_Print,    spawn,       SHCMD("name=/storage/pictures/$(date '+%F_%T').png; gnome-screenshot -a -f ${name} && pqiv ${name}") },
    { MODKEY,                        XK_i,        spawn,       SHCMD("subl3 -w ~/.config/dwm/config.h") },
    { MODKEY,                        XK_u,        spawn,       SHCMD("unmount") },
    { MODKEY|ShiftMask,				 XK_u,        spawn,       SHCMD("st -c float-term bash -ic \"hkp\"") },
    { MODKEY|ShiftMask,				 XK_k,        spawn,       SHCMD("st -c float-term bash -ic \"builtin cd $HOME/storage/downloads/; xclip -o | xargs youtube-dl --extract-audio -i --audio-format mp3 && notify-send 'Download Complete' || notify-send 'Download Failed'\"") },
    { MODKEY|ControlMask,				 XK_k,        spawn,   SHCMD("st -c float-term bash -ic \"cd $HOME/storage/downloads/; xclip -o | xargs youtube-dl -i && notify-send 'Download Complete' || notify-send 'Download Failed'\"") },
    { MODKEY,                        XK_g,        spawn,       SHCMD("wmctrl -Fa mutt || st -g 100x25+350+200 mutt") },
    { MODKEY,                        XK_m,        spawn,       SHCMD("mount-all") },
    { MODKEY,                        XK_r,        spawn,       SHCMD("subl3 ~/.config/ranger/rc.conf") },
    { MODKEY|ShiftMask,            XK_t,        spawn,       SHCMD("task-manager") },
    { MODKEY|ControlMask,            XK_w,        spawn,       SHCMD("find /storage/walls/* | shuf -n 1 | xargs hsetroot -cover") },
    { MODKEY|Mod1Mask,            	XK_d, 	spawn,       SHCMD("search -d") },
    { MODKEY|Mod1Mask,            	XK_w, 	spawn,       SHCMD("search -w") },
    { MODKEY|Mod1Mask,            	XK_y, 	spawn,       SHCMD("search -y") },
    { MODKEY|Mod1Mask,            	XK_r, 	spawn,       SHCMD("search -r") },
    { MODKEY|Mod1Mask,            	XK_u, 	spawn,       SHCMD("search -u") },
    { MODKEY|Mod1Mask,            	XK_l, 	spawn,       SHCMD("search -l") },
    { MODKEY|Mod1Mask,            	XK_a, 	spawn,       SHCMD("search -a") },
    { MODKEY|Mod1Mask,            	XK_f, 	spawn,       SHCMD("search -f") },
    { MODKEY|Mod1Mask,            	XK_m, 	spawn,       SHCMD("search -m") },

    { MODKEY|ShiftMask,              XK_b,      spawn,       SHCMD("find /storage/docs/ | egrep '*.(pdf|djvu)' | dmenu | xargs -d $'\n' sh -c 'for arg do wmctrl -a \"$arg\" || zathura --fork \"$arg\"; done' _") },
    { MODKEY|ControlMask,              XK_c,    spawn,       SHCMD("find ~/.config/ -maxdepth 2 -type f ! -path */.git/* | dmenu | xargs -r subl3") },
    { MODKEY|ShiftMask,            	XK_comma,  spawn,       SHCMD("light -A 1 && brightness-show") },
    { MODKEY|ShiftMask,            	XK_period,  	spawn,       SHCMD("light -U 1 && brightness-show") },
	{ MODKEY|ControlMask,          	XK_comma,  	spawn,        SHCMD("amixer set Master unmute && amixer set Master 0.75db+ && pkill -SIGRTMIN+12 dwmblocks") },
	{ MODKEY|ControlMask,          	XK_period,  	spawn,        SHCMD("amixer set Master unmute && amixer set Master 0.75db- && pkill -SIGRTMIN+12 dwmblocks") },
    // { MODKEY ,           			 XK_c,   	  spawn,       SHCMD("st qalc") },
    { MODKEY ,  XK_c,  spawn,  SHCMD("while expr=$((echo -e \"\ ${expr}\n\"; cat /home/kirito/.cache/functions) | dmenu); do expr=$(qalc \"${expr}\"); done") },
    { MODKEY|ShiftMask,              XK_Delete,  spawn,       SHCMD("delete-song-wallpaper s") },
    { MODKEY|ControlMask,            XK_Delete,  spawn,       SHCMD("delete-song-wallpaper i") },
    { MODKEY|ControlMask,            XK_x,  spawn,       SHCMD("xrdb -load ~/.Xresources") },
    { MODKEY,                       XK_d,       spawn,     	   SHCMD("song-select") },
    { MODKEY|ShiftMask,				XK_d,       spawn,     	   SHCMD("song-select a") },
    { MODKEY|ShiftMask,				XK_c,       spawn,     	   SHCMD("killall picom; picom --experimental-backends") },
    { MODKEY,						XK_Home,    spawn,     	   SHCMD("st mocp") },
    { MODKEY|ShiftMask,				XK_p,       spawn,     	   SHCMD("st -c float-term gnuplot") },
    { MODKEY,                       XK_f,       spawn,     	   SHCMD("wmctrl -r :ACTIVE: -b toggle,fullscreen") },
    { MODKEY,                       XK_Tab,       spawn,       SHCMD("wmctrl -l | dmenu | cut -d ' ' -f1 | xargs wmctrl -ia")},
    { MODKEY|ControlMask, 			XK_p,       spawn,     	   SHCMD("firefox --preferences") },


    { MODKEY|ShiftMask,             XK_l,       spawn,     	   SHCMD("slock") },
    { MODKEY,                       XK_p,       spawn,     	   SHCMD("uninstall") },
    { MODKEY|ShiftMask,              XK_x,        spawn,       SHCMD("killall xinit") },
    { MODKEY|ShiftMask,             XK_s,       spawn,     	   SHCMD("systemctl suspend -i") },
    { MODKEY|ShiftMask,             XK_y,       spawn,     	   SHCMD("reboot") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         		Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,   MODKEY|ShiftMask,     Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

