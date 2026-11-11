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

static       int topbar    = 0;
static       int centered  = 1;
static const int min_width = 700;

static const float menu_height_ratio = 2.0f;

static const char *prompt = NULL;

static const char worddelimiters[] = " ";

static const char *fonts[] =
{
    "CaskaydiaCoveNerdFont:size=20",
    "JetBrainsMonoNerdFont:size=20",
	"monospace:size=20",
};

static const char *colors[SchemeLast][2] =
{
	/*                fg         bg       */
	[SchemeNorm] = { "#bbbbbb", "#222222" },
	[SchemeSel]  = { "#eeeeee", "#005577" },
	[SchemeOut]  = { "#000000", "#00ffff" },
};

static const unsigned int alphas[SchemeLast][2] =
{
	[SchemeNorm] = { OPAQUE, alpha  },
	[SchemeSel]  = { OPAQUE, OPAQUE },
	[SchemeOut]  = { OPAQUE, OPAQUE },
};
