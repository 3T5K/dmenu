/*          __                          
 *     ____/ /___ ___  ___  ____  __  __
 *    / __  / __ `__ \/ _ \/ __ \/ / / /
 *   / /_/ / / / / / /  __/ / / / /_/ / 
 *   \__,_/_/ /_/ /_/\___/_/ /_/\__,_/  
 */

static const unsigned int alpha        = 0x33;
static       unsigned int lines        = 10;
static       unsigned int columns      = 3;
static       unsigned int border_width = 5;
static       unsigned int vi_mode      = 1;
static const unsigned int start_mode   = 0; /* 0 -> insert, 1 -> normal */

static       int topbar    = 0;
static       int centered  = 1;
static const int min_width = 700;

static const char passwd_sym = '*';

static const float menu_height_ratio = 2.0f;

static const char *prompt = NULL;

static const char worddelimiters[] = " ";

static const char *fonts[] =
{
    "CaskaydiaCoveNerdFont:size=20",
    "JetBrainsMonoNerdFont:size=20",
    "monospace:size=20",
};

static Key global_esc = { XK_Escape, 0 };

static const Key quit_keys[] =
{
    /* keysym   modifier  */
    {  XK_q,    0         },
};

static const char *colors[SchemeLast][2] =
{
    /*                  fg         bg       */
    [SchemeNorm  ] = { "#bbbbbb", "#222222" },
    [SchemeSel   ] = { "#eeeeee", "#005577" },
    [SchemeOut   ] = { "#000000", "#00ffff" },
    [SchemeCursor] = { "#222222", "#bbbbbb" },
};

static const unsigned int alphas[SchemeLast][2] =
{
    [SchemeNorm  ] = { OPAQUE, alpha  },
    [SchemeSel   ] = { OPAQUE, OPAQUE },
    [SchemeOut   ] = { OPAQUE, OPAQUE },
    [SchemeCursor] = { OPAQUE, OPAQUE },
};
