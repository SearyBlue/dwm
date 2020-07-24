static const unsigned int borderpx  = 3;
static const unsigned int gappx     = 0;
static const unsigned int snap      = 32;       
static const unsigned int systraypinning = 0;   
static const unsigned int systrayspacing = 5;   
static const int systraypinningfailfirst = 1;   
static const int showsystray        = 1;     
static const int showbar            = 1;        
static const int topbar             = 1;        

static const char *fonts[]          = {"Fira Code:size=12:style=semibold", "JoyPixels:pixelsize=17:antialias=true:autohint=true","Iosevka Nerd Font:size=13"};
static const char col_gray1[]       = "#333333";
static const char col_cyan[]        = "#3377aa";
static const char col_gray3[]       = "#fff";
static const char col_gray4[]       = "#000000";
static const char col_gray[]        = "#1d1f21";

static const char *colors[][3]      = 
{
	[SchemeNorm] = { col_gray3, col_gray1, col_gray4 },
	[SchemeSel]  = { col_gray3, col_gray1,  col_cyan  },
};

static const char *tags[] = { "🌎", "💼", "🛡", "📝",  "📙", "📉", "🗑 "};

static const Rule rules[] = {
	// class        instance         title          tag            swtch   cent     float    mon
	{ NULL, "google-chrome-beta", 	NULL,		1<<0,		1,      1,      0,      -1 },
	{ NULL, "fileman",   		NULL,		1<<1,           1,      1,      0,      -1 },
	{ NULL, "terminal",   		NULL,		1<<2,           1,      1,      0,      -1 },
	{ NULL, "editor",		NULL,		1<<3,           1,      1,      0,      -1 },
	{ NULL, "zathura",       	NULL,		1<<4,           1,      0,      0,      -1 },
	{ NULL, "evince",       	NULL,		1<<4,           1,      0,      0,      -1 },
	{ NULL, "libreoffice",  	NULL,		1<<5,           1,      1,	0,      -1 },
	{ NULL, "transmission-gtk",     NULL,		1<<5,           1,      1,      1,      -1 },
	{ NULL, "floatterm", 		NULL,		0,              0,      1,	1,      -1 },
	{ NULL,	"feh",       		NULL,		0,              0,      1,	1,      -1 },
	{ NULL, "lxappearance",		NULL,		0,              0,      1,	1,      -1 },
	{ NULL, "nm-connection-editor", NULL,		0,              0,      1,	1,      -1 },
	{ NULL, "matplotlib", 		NULL,		0,              0,      1,	1,      -1 },
};

static const float mfact     = 0.5;
static const int nmaster     = 1;  
static const int resizehints = 0;  
static const Layout layouts[] = 
{
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                   KEY,      view,         {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,       KEY,      toggleview,   {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,         KEY,      tag,          {.ui = 1 << TAG} }, \
    { MODKEY|Mod1Mask, 	   	KEY,      tag,      	{.ui = 1 << TAG} }, \
    { MODKEY|Mod1Mask, 		KEY,      view,      	{.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char drun[] 	= {"dmenu_run"};
static const char rel[] 	= {"dwm_reload"};
static const char killdunst[] 	= {"killall dunst"};
static const char edit[] 	= {"vimmer"};
static const char record[] 	= {"rec_screen"};
static const char surf[] 	= {"wmctrl -xa 'Google-chrome' || google-chrome-beta"};
static const char office[] 	= {"wmctrl -a 'LibreOffice' || ~/storage/LibreOffice-still --quickstart --nologo"};
static const char file[] 	= {"wmctrl -x -a mpv || wmctrl -Fa 'fileman' || wmctrl -a 'VIM_ALONE' || st -n 'fileman' -t 'fileman' lf"};
static const char forcefile[] 	= {"st -n 'fileman' -t 'fileman' lf"};
static const char term[] 	= {"wmctrl -Fa terminal || st -n terminal -t terminal"};
static const char forceterm[] 	= {"st -n terminal -t terminal"};
static const char net[] 	= {"(echo \"nmcli radio wifi on\"; echo \"nmcli radio wifi off\";\
				   nmcli -t connection show | cut -d ':' -f1) | dmenu | head -n 1 | xargs -r network"};
static const char musicstart[] 	= {"musicstart && pkill -SIGRTMIN+11 dwmblocks"};
static const char seekb[] 	= {"mocp --seek -10"};
static const char seekf[] 	= {"mocp --seek +10"};
static const char seekbb[] 	= {"mocp --seek -50"};
static const char seekfb[] 	= {"mocp --seek +50"};
static const char nettogg[] 	= {"nmcli radio wifi | grep disable && nmcli radio wifi on || nmcli radio wifi off"};
static const char sshot[] 	= {"scrot -zf -e '/usr/bin/feh  --scale-down $f; mv $f /home/kirito/storage/pictures'"};
static const char sshoti[] 	= {"sleep 0.5; scrot -s -z -f -e '/usr/bin/feh  --scale-down $f; notify-send $f;\
				   mv $f /home/kirito/storage/pictures'"};
static const char dwmconf[] 	= {"vimmer ~/.config/dwm/config.h"};
static const char unm[] 	= {"unmount"};
static const char mutt[] 	= {"wmctrl -Fa mutt || st -n floatterm -g 100x25+350+200 mutt"};
static const char mnt[] 	= {"mount-all"};
static const char rangconf[] 	= {"vimmer ~/.config/lf/lfrc"};
static const char taskm[] 	= {"ps h -e -o comm,%cpu,%mem --sort -%mem | dmenu -l 20 | cut -d ' ' -f1 | xargs -r -n1 -d '\n' pkill"};
static const char wall[] 	= {"/usr/bin/feh --bg-fill --randomize ~/storage/walls"};
static const char book[] 	= {"open_book"}; 
static const char conf[] 	= {"finder ~/.config/ -maxdepth 2 | dmenu -l 30 | xargs -r vimmer"};
static const char bryti[] 	= {"light -A 1 && brightness-show"};
static const char brytd[] 	= {"light -U 1 && brightness-show"};
static const char voli[] 	= {"volume -i 0.75 "};
static const char vold[] 	= {"volume -d 0.75"};
static const char volil[] 	= {"volume -i 10 "};
static const char voldl[] 	= {"volume -d 10"};
static const char calc[] 	= {"st -n 'floatterm' -g 100x25+350+200 qalc"};
static const char song[] 	= {"song-select"};
static const char comp[] 	= {"pgrep picom && pkill picom || picom --experimental-backends -b"};
static const char mocp[] 	= {"st -n floatterm -g 100x25+350+200 mocp"};
static const char fulls[] 	= {"wmctrl -r :ACTIVE: -b toggle,fullscreen"};
static const char change[] 	= {"wmctrl -l | dmenu -l 10 | cut -d ' ' -f1 | xargs -r wmctrl -ia"};
static const char firepref[] 	= {"firefox --preferences"};
static const char lock[] 	= {"slock"};
static const char unin[] 	= {"st -n 'floatterm' bash -c 'yay -Qttq | fzf | xargs -r yay -Rns -'"};
static const char zzz[] 	= {"loginctl suspend || systemctl suspend -i"};
static const char reb[] 	= {"loginctl reboot || systemctl reboot"};
static const char vimrc[] 	= {"vimmer ~/.vim/vimrc"};
static const char killx[] 	= {"pkill xinit"};
static const char note[] 	= {"sort ~/.cache/note | dmenu -l 30 >> ~/.cache/note"};

static Key keys[] = {
	{ MODKEY|ControlMask,			XK_b,      		togglebar,      	{0} },
	{ MODKEY,                       	XK_Right,  		focusstack,     	{.i = +1 } },
	{ MODKEY,                       	XK_Left,   		focusstack,     	{.i = -1 } },
	{ MODKEY|ShiftMask,             	XK_Left,   		incnmaster,     	{.i = +1 } },
	{ MODKEY|ShiftMask,             	XK_Right,  		incnmaster,     	{.i = -1 } },
	{ MODKEY|ControlMask,		        XK_Left,   		setmfact,       	{.f = -0.05} },
	{ MODKEY|ControlMask,		        XK_Right,  		setmfact,       	{.f = +0.05} },
	{ MODKEY|ControlMask,           	XK_Down,     		setcfact,       	{.f = +0.25} },
	{ MODKEY|ControlMask,           	XK_Up,   		setcfact,       	{.f = -0.25} },
	{ MODKEY,                       	XK_Page_Up,		zoom,           	{0} },
	{ MODKEY|ControlMask,			XK_t,      		setlayout,      	{.v = &layouts[0]} },
	{ MODKEY|ControlMask,			XK_f,      		setlayout,      	{.v = &layouts[1]} },
	{ MODKEY|ControlMask,      		XK_m,	   		setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,                       	XK_space,  		setlayout,      	{0} },
	{ MODKEY|ShiftMask,             	XK_space,  		togglefloating, 	{0} },
	{ MODKEY,                       	XK_0,      		view,           	{.ui = ~0 } },
	{ MODKEY|ShiftMask,             	XK_0,      		tag,            	{.ui = ~0 } },
	TAGKEYS(                        	XK_1,                   			0)
	TAGKEYS(                        	XK_2,                   			1)
	TAGKEYS(                        	XK_3,                   			2)
	TAGKEYS(                        	XK_4,                   			3)
	TAGKEYS(                        	XK_5,                   			4)
	TAGKEYS(                        	XK_6,                   			5)
	TAGKEYS(                        	XK_7,                   			6)
	{ MODKEY,				XK_a,	  		spawn,          	SHCMD(drun)},
	{ MODKEY|ShiftMask,			XK_r,        		spawn,    		SHCMD(rel) },
	{ MODKEY,                        	XK_s,     		spawn,       		SHCMD(edit) },
        { MODKEY,                        	XK_b,     		spawn,       		SHCMD(surf) },
        { MODKEY,                        	XK_o,     		spawn,       		SHCMD(office) },
	{ MODKEY,                        	XK_e,     		spawn,       		SHCMD(file) },
        { MODKEY|ShiftMask,              	XK_e,     		spawn,       		SHCMD(forcefile) },
        { MODKEY,                        	XK_t,        		spawn,       		SHCMD(term) },
        { MODKEY,                        	XK_Return,      	spawn,       		SHCMD(forceterm)},
        { MODKEY,                        	XK_n,        		spawn,       		SHCMD(net) },
        { MODKEY|ShiftMask,            	 	XK_h,        		spawn,       		SHCMD(seekb) },
        { MODKEY|ShiftMask,            	 	XK_l,        		spawn,       		SHCMD(seekf) },
        { MODKEY|ControlMask,            	XK_h,        		spawn,       		SHCMD(seekbb) },
        { MODKEY|ControlMask,            	XK_l,        		spawn,       		SHCMD(seekfb) },
        { MODKEY|ShiftMask,			XK_n,        		spawn,       		SHCMD(nettogg) },
        { 0,                             	XK_Print,    		spawn,       		SHCMD(sshot) },
        { MODKEY,                        	XK_Print,    		spawn,       		SHCMD(sshoti) },
        { MODKEY,                        	XK_i,        		spawn,       		SHCMD(dwmconf) },
        { MODKEY,                        	XK_u,        		spawn,       		SHCMD(unm) },
        { MODKEY,                        	XK_g,        		spawn,       		SHCMD(mutt) },
        { MODKEY,                        	XK_m,        		spawn,       		SHCMD(mnt) },
        { MODKEY,                        	XK_r,        		spawn,       		SHCMD(rangconf) },
        { MODKEY|ShiftMask,              	XK_t,        		spawn,       		SHCMD(taskm) },
        { MODKEY|ControlMask,            	XK_w,        		spawn,       		SHCMD(wall) },
        { MODKEY|ShiftMask,              	XK_b,      		spawn,       		SHCMD(book) },
        { MODKEY|ControlMask,              	XK_c,    		spawn,       		SHCMD(conf) },
        { MODKEY|ShiftMask,            		XK_comma,  		spawn,       		SHCMD(bryti) },
        { MODKEY|ShiftMask,            		XK_period,  		spawn,       		SHCMD(brytd) },
	{ MODKEY|ControlMask,          		XK_comma,  		spawn,        		SHCMD(voli) },
	{ MODKEY|ControlMask,          		XK_period,  		spawn,        		SHCMD(vold) },
	{ MODKEY|Mod1Mask,          		XK_comma,  		spawn,        		SHCMD(volil) },
	{ MODKEY|Mod1Mask,          		XK_period,  		spawn,        		SHCMD(voldl) },
        { MODKEY ,  				XK_c,  			spawn,  		SHCMD(calc) },
        { MODKEY,                       	XK_d,       		spawn,     	   	SHCMD(song) },
        { MODKEY|ShiftMask,			XK_c,       		spawn,     	   	SHCMD(comp) },
        { MODKEY,				XK_Home,    		spawn,     	   	SHCMD(mocp) },
        { MODKEY,				XK_period,    		spawn,     	   	SHCMD("mocp --next") },
        { MODKEY,				XK_comma,    		spawn,     	   	SHCMD("mocp --prev") },
        { MODKEY,                       	XK_f,       		spawn,     	   	SHCMD(fulls) },
        { MODKEY,                       	XK_Insert,     		spawn,     	   	SHCMD("mail-show && notify-send 'Checked Mail'") },
        { MODKEY,                       	XK_Tab,       		spawn,       	   	SHCMD(change)},
        { MODKEY, 				XK_v,       		spawn,     	   	SHCMD(vimrc) },
        { MODKEY,		             	XK_l,       		spawn,     	   	SHCMD(lock) },
        { MODKEY|ShiftMask,                     XK_p,       		spawn,     	   	SHCMD(unin) },
        { MODKEY|ShiftMask,              	XK_x,        		spawn,       	   	SHCMD(killx) },
        { MODKEY|ShiftMask,             	XK_s,       		spawn,     	   	SHCMD(zzz) },
        { MODKEY|ShiftMask,             	XK_y,       		spawn,     	   	SHCMD(reb) },
	{ MODKEY,             			XK_x,      		killclient,     		{0} },
	{ MODKEY|ControlMask,  			XK_n,      		spawn,     		SHCMD(note) },
	{ MODKEY|ControlMask,  			XK_r,      		spawn,     		SHCMD(record) },
	{ MODKEY,  				XK_BackSpace,     	spawn,     		SHCMD(killdunst) },
	{ MODKEY,				XK_p,     		spawn,     		SHCMD(musicstart) },
};

static Button buttons[] = {
	{ ClkLtSymbol,          0,              		Button1,        	setlayout,      	{0} },
	{ ClkLtSymbol,          0,              		Button3,        	setlayout,      	{.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         		Button1,        	movemouse,      	{0} },
	{ ClkClientWin,         MODKEY,         		Button2,        	togglefloating, 	{0} },
	{ ClkClientWin,   	MODKEY|ShiftMask,     		Button1,        	resizemouse,    	{0} },
	{ ClkTagBar,            0,              		Button1,        	view,           	{0} },
	{ ClkTagBar,            0,              		Button3,        	toggleview,     	{0} },
	{ ClkTagBar,            MODKEY,         		Button1,        	tag,            	{0} },
	{ ClkTagBar,            MODKEY,         		Button3,        	toggletag,      	{0} },
};

