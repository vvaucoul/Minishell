char *tgetstr ();

char *cl_string, *cm_string;
int height;
int width;
int auto_wrap;

char PC;   /* For tputs.  */
char *BC;  /* For tgoto.  */
char *UP;

interrogate_terminal ()
{
#ifdef Unix
  /* Here we assume that an explicit term_buffer
     was provided to tgetent.  */
  char *buffer
    = (char *) malloc (strlen (term_buffer));
#define BUFFADDR &buffer
#else
#define BUFFADDR 0
#endif

  char *temp;

  /* Extract information we will use.  */
  cl_string = tgetstr ("cl", BUFFADDR);
  cm_string = tgetstr ("cm", BUFFADDR);
  auto_wrap = tgetflag ("am");
  height = tgetnum ("li");
  width = tgetnum ("co");

  /* Extract information that termcap functions use.  */
  temp = tgetstr ("pc", BUFFADDR);
  PC = temp ? *temp : 0;
  BC = tgetstr ("le", BUFFADDR);
  UP = tgetstr ("up", BUFFADDR);
}
