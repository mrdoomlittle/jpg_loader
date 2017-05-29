# ifndef __jpg__loader__h
# define __jpg__loader__h
# include <eint_t.h>
# include <stdio.h>
# include <errno.h>
# include <stddef.h>
# include <jpeglib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>

struct jpg_loader_t {
	mdl_uint_t width, height;
	mdl_u8_t *buff;
	mdl_u8_t chn_c;
	mdl_uint_t buff_size;
};

mdl_i8_t load_jpg(char const*, struct jpg_loader_t*);
# endif /*__freq__jpg__h*/
