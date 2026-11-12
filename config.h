/*          __                          
 *     ____/ /___ ___  ___  ____  __  __
 *    / __  / __ `__ \/ _ \/ __ \/ / / /
 *   / /_/ / / / / / /  __/ / / / /_/ / 
 *   \__,_/_/ /_/ /_/\___/_/ /_/\__,_/  
 */

static const unsigned int alpha        = 0x77;
static       unsigned int lines        = 10;
static       unsigned int columns      = 3;
static       unsigned int border_width = 5;
static       unsigned int vi_mode      = 1;
static const unsigned int start_mode   = 0;

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

#ifndef DMENU_THEME
#  define DMENU_THEME catppuccin
#endif

#if DMENU_THEME == catppuccin
#  define COL_INACTIVE_FG      "#74c7ec"
#  define COL_INACTIVE_BG      "#1e1e2e"
#  define COL_INACTIVE_ALPHA     alpha
#  define COL_ACTIVE_FG        "#8839ef"
#  define COL_ACTIVE_BG        "#1e1e2e"
#  define COL_ACTIVE_ALPHA       alpha
#  define COL_MULTISEL_FG      "#0000ff"
#  define COL_MULTISEL_BG      "#1e1e2e"
#  define COL_MULTISEL_ALPHA     alpha
#  define COL_VIM_CURSOR_BLOCK "#cdd6f4"
#  define COL_VIM_CURSOR_TEXT  "#74c7ec"
#  define COL_CURSOR           "#cdd6f4"
#  define COL_BORDER           "#1e1e2e"
#else
#  error "bad theme"
#endif

#define COL_NIL "#000000"

static const char *colors[SchemeLast][2] =
{
    /*                  fg         bg       */
    [SchemeNorm  ] = { COL_INACTIVE_FG
                     , COL_INACTIVE_BG
                     },
    [SchemeSel   ] = { COL_ACTIVE_FG
                     , COL_ACTIVE_BG
                     },
    [SchemeOut   ] = { COL_MULTISEL_FG
                     , COL_MULTISEL_BG
                     },
	[SchemeBorder] = { COL_NIL
                     , COL_BORDER
                     },
    [SchemeCursor] = { COL_VIM_CURSOR_TEXT
                     , COL_VIM_CURSOR_BLOCK
                     },
    [SchemeCaret ] = { COL_CURSOR
                     , COL_NIL
                     },
};

static const unsigned int alphas[SchemeLast][2] =
{
    [SchemeNorm  ] = { OPAQUE, COL_INACTIVE_ALPHA  },
    [SchemeSel   ] = { OPAQUE, COL_ACTIVE_ALPHA    },
    [SchemeOut   ] = { OPAQUE, COL_MULTISEL_ALPHA  },
    [SchemeBorder] = { OPAQUE, OPAQUE              },
    [SchemeCursor] = { OPAQUE, OPAQUE              },
    [SchemeCaret ] = { OPAQUE, OPAQUE              },
};

