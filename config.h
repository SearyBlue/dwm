const unsigned int borderpx  = 2;
static const unsigned int gappx     = 5;
static const unsigned int snap      = 32;       
static const unsigned int systraypinning = 0;   
static const unsigned int systrayspacing = 5;   
static const int systraypinningfailfirst = 1;   
static const int showsystray        = 1;     
static const int showbar            = 1;        
static const int topbar             = 0;        

static const char *fonts[]          = {"Fira Code:size=12:style=semibold","Iosevka Nerd Font:size=13"};
static const char col_gray1[]       = "#1a1a1a";
static const char col_cyan[]        = "#3377aa";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#000000";
static const char col_gray[]        = "#1d1f21";

static const char *colors[][3]      = 
{
	[SchemeNorm] = { col_gray3, col_gray1, col_gray4 },
	[SchemeSel]  = { col_gray4, col_cyan, col_cyan },
};

static const char *tags[] = { "web", "file", "term", "edit",  "docs", "loff", "misc"};

static const Rule rules[] = {
	// class     instance   title                  tag              swtch   cent   float    mon
        { "firefox", "Navigator", "Mozilla Firefox",       	1<<0,           1,      1,      0,      -1 },
        { "Firefox", "Navigator", "Mozilla Firefox",       	1<<0,           1,      1,      0,      -1 },
	{ "Waterfox","Navigator",  "Waterfox Current",  1<<0,           1,      1,      0,      -1 },
	{ "st-256color",	"st",    "ranger",	1<<1,           1,      1,      0,      -1 },
	{ "st-256color","st",     "st",                 1<<2,           1,      1,      0,      -1 },
	{ "st-256color",  "VIM SERVER",  NULL,  	1<<3,           1,      1,      0,      -1 },
	{ "tabbed", "zathura",       NULL,       	        1<<4,           1,      1,      0,      -1 },
	{ "Transmission-gtk",NULL,       NULL,       	1<<5,           1,      1,      1,      -1 },
	{ NULL, 	NULL,  "LibreOffice",   	1<<5,           1,      1,	0,      -1 },
	{ "float-term",  	NULL,       NULL,       0,              0,      1,	1,      -1 },
	{ "st-256color",		NULL,        "mutt",    0,              0,      1,	1,      -1 },
	{ NULL,     NULL,        "qalc",                 0,              0,      1,      1,      -1 },
	{ "feh",	NULL,       NULL,        	0,              0,      1,	1,      -1 },
	{ "Mtpaint",		NULL,       NULL,       0,              0,      1,	1,      -1 },
	{ "mpv",		NULL,       NULL,       0,              0,      1,	0,      -1 },
	{ "Lxappearance",	NULL,       NULL,       0,              0,      1,	1,      -1 },
	{ "Gnuplot",		"gnuplot",       NULL,  0,              1,      1,	1,      -1 },
	{ "St",			NULL,     "mocp",       0,              0,      1,	1,      -1 },
	{ NULL,		"gpartedbin",       NULL,       0,              0,      1,	1,      -1 },
	{ "Nm-connection-editor", NULL,	NULL, 		0,              0,      1,	1,      -1 },
	{ "Matplotlib", NULL,	NULL,                   0,              0,      1,	1,      -1 },
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
	{ MODKEY,                       KEY,      view,         {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,   {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,          {.ui = 1 << TAG} }, \
    { MODKEY|Mod1Mask, 				KEY,      tag,      	{.ui = 1 << TAG} }, \
    { MODKEY|Mod1Mask, 				KEY,      view,      	{.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
static const char drun[] = {"dmenu_run"};
static const char rel[] = {"st -c float-term bash -c \"sudo make -C ~/.config/dwm install && pkill dwm\""};
static const char edit[] = {"vimmer"};
static const char surf[] = {"wmctrl -a 'Mozilla Firefox' || firefox"};
static const char office[] = {"wmctrl -a 'LibreOffice' || libreoffice6.4 --quickstart --nologo"};
static const char file[] = {"wmctrl -x -a mpv || wmctrl -lp | grep $(pgrep -fx -n 'st ranger') | awk '{print $1}' | xargs wmctrl -ia || st ranger"};
static const char forcefile[] = {"st ranger"};
static const char term[] = {"wmctrl -lp | grep $(pgrep -fx -n 'st') | awk '{print $1}' | xargs wmctrl -ia || st"};
static const char forceterm[] = {"st"};
static const char net[] = {"(echo \"nmcli radio wifi on\"; echo \"nmcli radio wifi off\"; nmcli -t connection show | cut -d ':' -f1) | dmenu | head -n 1 | xargs -r network"};
static const char seekb[] = {"mocp --seek -10"};
static const char seekf[] = {"mocp --seek +10"};
static const char seekbb[] = {"mocp --seek -50"};
static const char seekfb[] = {"mocp --seek +50"};
static const char nettogg[] = {"nmcli radio wifi | grep disable && nmcli radio wifi on || nmcli radio wifi off"};
static const char sshot[] = {"scrot -zf -e '/usr/bin/feh  --scale-down $f; mv $f /home/kirito/storage/pictures'"};
static const char sshoti[] = {"sleep 0.1; scrot -s zf -e '/usr/bin/feh  --scale-down $f; mv $f /home/kirito/storage/pictures'"};
static const char dwmconf[] = {"vimmer ~/.config/dwm/config.h"};
static const char unm[] = {"unmount"};
static const char hkp[] = {"st -c 'float-term' -g 130x30 bash -ic \"hkp\""};
static const char mdown[] = {"st -c 'float-term' -g 130x30 bash -ic \"builtin cd $HOME/storage/downloads/; xclip -o | xargs youtube-dl --extract-audio -i -audio-format mp3 && notify-send 'Download Complete' || notify-send 'Download Failed'\""};
static const char down[] = {"st -c 'float-term' -g 130x30 bash -ic \"cd $HOME/storage/downloads/; xclip -o | xargs youtube-dl -i && notify-send 'Download omplete' || notify-send 'Download Failed'\""};
static const char mutt[] = {"wmctrl -Fa mutt || st -g 100x25+350+200 mutt"};
static const char mnt[] = {"mount-all"};
static const char rangconf[] = {"vimmer ~/.config/ranger/rc.conf"};
static const char taskm[] ={"ps h -e -o comm,%cpu,%mem --sort -%mem | dmenu -l 20 | cut -d ' ' -f1 | xargs -r -n1 -d '\n' pkill"};
static const char wall[] = {"/usr/bin/feh --bg-fill --randomize ~/storage/walls"};
static const char searchd[] = {"search -d"};
static const char searchw[] = {"search -w"};
static const char searchy[] = {"search -y"};
static const char searchr[] = {"search -r"};
static const char searchu[] = {"search -u"};
static const char searchl[] = {"search -l"};
static const char searcha[] = {"search -a"};
static const char searchf[] = {"search -f"};
static const char searchm[] = {"search -m"};
static const char book[] = {"find ~/storage -type f -iname \"*.pdf\" -o -iname \"*.djvu\" 2>/dev/null | dmenu -l 30 | xargs -r -d '\n' zathura_tabbed"}; 
static const char conf[] = {"finder ~/.config/ -maxdepth 2 | dmenu -l 30 | xargs -r vimmer"};
static const char bryti[] = {"light -A 1 && brightness-show"};
static const char brytd[] = {"light -U 1 && brightness-show"};
static const char voli[] = {"amixer set Master unmute && amixer set Master 0.75db+ && volume-show"};
static const char vold[] = {"amixer set Master unmute && amixer set Master 0.75db- && volume-show"};
static const char calc[] = {"st -c 'float-term' -g 130x30 qalc"};
static const char delwall[] = {"cat $HOME/.cache/wallpaper | xargs rm && (find /storage/walls/* | shuf -n 1 | xargs -d $'\n' sh -c 'for arg do hsetroot cover $arg; echo $arg > $HOME/.cache/wallpaper; done' _) || notify-send 'Failed to delete wallpaper'"};
static const char song[] = {"song-select"};
static const char comp[] = {"pkill picom; picom --experimental-backends"};
static const char mocp[] = {"st mocp"};
static const char plot[] = {"st -c 'float-term' -g 130x30 gnuplot"};
static const char fulls[] = {"wmctrl -r :ACTIVE: -b toggle,fullscreen"};
static const char change[] = {"wmctrl -l | dmenu -l 10 | cut -d ' ' -f1 | xargs -r wmctrl -ia"};
static const char firepref[] = {"firefox --preferences"};
static const char lock[] = {"slock"};
static const char unin[] = {"st -c 'float-term' -g 50x30 bash -c \"yay -Qttq | fzf | xargs -r yay -Rns -\""};
static const char zzz[] = {"loginctl suspend || systemctl suspend -i"};
static const char reb[] = {"loginctl reboot || systemctl reboot"};
static const char vimrc[] = {"vimmer ~/.vim/vimrc"};
static const char killwin[] = {"killwin"};
static const char killx[] = {"pkill xinit"};

static Key keys[] = {
	{ MODKEY|ControlMask,			XK_b,      			togglebar,      	{0} },
	{ MODKEY,                       	XK_Right,  			focusstack,     	{.i = +1 } },
	{ MODKEY,                       	XK_Left,   			focusstack,     	{.i = -1 } },
	{ MODKEY|ShiftMask,             	XK_Left,   			incnmaster,     	{.i = +1 } },
	{ MODKEY|ShiftMask,             	XK_Right,  			incnmaster,     	{.i = -1 } },
	{ MODKEY|ControlMask,		        XK_Left,   			setmfact,       	{.f = -0.05} },
	{ MODKEY|ControlMask,		        XK_Right,  			setmfact,       	{.f = +0.05} },
	{ MODKEY|ControlMask,           	XK_Down,     		setcfact,       	{.f = +0.25} },
	{ MODKEY|ControlMask,           	XK_Up,   			setcfact,       	{.f = -0.25} },
	{ MODKEY,                       	XK_Page_Up,			zoom,           	{0} },
	{ MODKEY|ControlMask,			XK_t,      			setlayout,      	{.v = &layouts[0]} },
	{ MODKEY|ControlMask,			XK_f,      			setlayout,      	{.v = &layouts[1]} },
	{ MODKEY|ControlMask,      		XK_m,	   			setlayout,      	{.v = &layouts[2]} },
	{ MODKEY,                       	XK_space,  			setlayout,      	{0} },
	{ MODKEY|ShiftMask,             	XK_space,  			togglefloating, 	{0} },
	{ MODKEY,                       	XK_0,      			view,           	{.ui = ~0 } },
	{ MODKEY|ShiftMask,             	XK_0,      			tag,            	{.ui = ~0 } },
	TAGKEYS(                        	XK_1,                      				0)
	TAGKEYS(                        	XK_2,                      				1)
	TAGKEYS(                        	XK_3,                      				2)
	TAGKEYS(                        	XK_4,                      				3)
	TAGKEYS(                        	XK_5,                      				4)
	TAGKEYS(                        	XK_6,                      				5)
	TAGKEYS(                        	XK_7,                      				6)
	{ MODKEY,				XK_a,	  			spawn,          	SHCMD(drun)},
	{ MODKEY|ShiftMask,			XK_r,        		spawn,    			SHCMD(rel) },
	{ MODKEY,                        	XK_s,     			spawn,       		SHCMD(edit) },
        { MODKEY,                        	XK_b,     			spawn,       		SHCMD(surf) },
        { MODKEY,                        	XK_l,     			spawn,       		SHCMD(office) },
	{ MODKEY,                        	XK_e,     			spawn,       		SHCMD(file) },
        { MODKEY|ShiftMask,              	XK_e,     			spawn,       		SHCMD(forcefile) },
        { MODKEY,                        	XK_t,        		spawn,       		SHCMD(term) },
        { MODKEY,                        	XK_Return,      	spawn,       		SHCMD(forceterm)},
        { MODKEY,                        	XK_n,        		spawn,       		SHCMD(net) },
        { MODKEY|ShiftMask,            	 	XK_h,        		spawn,       		SHCMD(seekb) },
        { MODKEY|ShiftMask,            	 	XK_j,        		spawn,       		SHCMD(seekf) },
        { MODKEY|ControlMask,            	XK_h,        		spawn,       		SHCMD(seekbb) },
        { MODKEY|ControlMask,            	XK_j,        		spawn,       		SHCMD(seekfb) },
        { MODKEY|ShiftMask,			XK_n,        		spawn,       		SHCMD(nettogg) },
        { 0,                             	XK_Print,    		spawn,       		SHCMD(sshot) },
        { MODKEY,                        	XK_Print,    		spawn,       		SHCMD(sshoti) },
        { MODKEY,                        	XK_i,        		spawn,       		SHCMD(dwmconf) },
        { MODKEY,                        	XK_u,        		spawn,       		SHCMD(unm) },
        { MODKEY|ShiftMask,			XK_u,        		spawn,       		SHCMD(hkp) },
        { MODKEY|ShiftMask,			XK_k,        		spawn,       		SHCMD(mdown) },
        { MODKEY|ControlMask,			XK_k,        		spawn,   			SHCMD(down) },
        { MODKEY,                        	XK_g,        		spawn,       		SHCMD(mutt) },
        { MODKEY,                        	XK_m,        		spawn,       		SHCMD(mnt) },
        { MODKEY,                        	XK_r,        		spawn,       		SHCMD(rangconf) },
        { MODKEY|ShiftMask,              	XK_t,        		spawn,       		SHCMD(taskm) },
        { MODKEY|ControlMask,            	XK_w,        		spawn,       		SHCMD(wall) },
        { MODKEY|Mod1Mask,            	 	XK_d, 				spawn,       		SHCMD(searchd) },
        { MODKEY|Mod1Mask,            	 	XK_w, 				spawn,       		SHCMD(searchw) },
        { MODKEY|Mod1Mask,            	 	XK_y, 				spawn,       		SHCMD(searchy) },
        { MODKEY|Mod1Mask,            	 	XK_r, 				spawn,       		SHCMD(searchr) },
        { MODKEY|Mod1Mask,            	 	XK_u, 				spawn,       		SHCMD(searchu) },
        { MODKEY|Mod1Mask,            	 	XK_l, 				spawn,       		SHCMD(searchl) },
        { MODKEY|Mod1Mask,            		XK_a, 				spawn,       		SHCMD(searcha) },
        { MODKEY|Mod1Mask,            		XK_f, 				spawn,       		SHCMD(searchf) },
        { MODKEY|Mod1Mask,            		XK_m, 				spawn,       		SHCMD(searchm) },
        { MODKEY|ShiftMask,              	XK_b,      			spawn,       		SHCMD(book) },
        { MODKEY|ControlMask,              	XK_c,    			spawn,       		SHCMD(conf) },
        { MODKEY|ShiftMask,            		XK_comma,  			spawn,       		SHCMD(bryti) },
        { MODKEY|ShiftMask,            		XK_period,  		spawn,       		SHCMD(brytd) },
	{ MODKEY|ControlMask,          		XK_comma,  			spawn,        		SHCMD(voli) },
	{ MODKEY|ControlMask,          		XK_period,  		spawn,        		SHCMD(vold) },
        { MODKEY ,  				XK_c,  				spawn,  			SHCMD(calc) },
        { MODKEY|ShiftMask,              	XK_Delete,  		spawn,       		SHCMD(delwall) },
        { MODKEY,                       	XK_d,       		spawn,     	   		SHCMD(song) },
        { MODKEY|ShiftMask,			XK_c,       		spawn,     	   		SHCMD(comp) },
        { MODKEY,				XK_Home,    		spawn,     	   		SHCMD(mocp) },
        { MODKEY|ShiftMask,			XK_p,       		spawn,     	   		SHCMD(plot) },
        { MODKEY,                       	XK_f,       		spawn,     	   		SHCMD(fulls) },
        { MODKEY,                       	XK_Tab,       		spawn,       		SHCMD(change)},
        { MODKEY|ControlMask, 			XK_p,       		spawn,     	   		SHCMD(firepref) },
        { MODKEY, 				XK_v,       		spawn,     	   		SHCMD(vimrc) },
        { MODKEY|ShiftMask,             	XK_l,       		spawn,     	   		SHCMD(lock) },
        { MODKEY,                       	XK_p,       		spawn,     	   		SHCMD(unin) },
        { MODKEY|ShiftMask,              	XK_x,        		spawn,       		        SHCMD(killx) },
        { MODKEY|ShiftMask,             	XK_s,       		spawn,     	   		SHCMD(zzz) },
        { MODKEY|ShiftMask,             	XK_y,       		spawn,     	   		SHCMD(reb) },
	{ MODKEY,             				XK_x,      			killclient,     	{0} },
};

static Button buttons[] = {
	{ ClkLtSymbol,          0,              		Button1,        	setlayout,      		{0} },
	{ ClkLtSymbol,          0,              		Button3,        	setlayout,      		{.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         		Button1,        	movemouse,      		{0} },
	{ ClkClientWin,         MODKEY,         		Button2,        	togglefloating, 		{0} },
	{ ClkClientWin,   		MODKEY|ShiftMask,     	Button1,        	resizemouse,    		{0} },
	{ ClkTagBar,            0,              		Button1,        	view,           		{0} },
	{ ClkTagBar,            0,              		Button3,        	toggleview,     		{0} },
	{ ClkTagBar,            MODKEY,         		Button1,        	tag,            		{0} },
	{ ClkTagBar,            MODKEY,         		Button3,        	toggletag,      		{0} },
};

