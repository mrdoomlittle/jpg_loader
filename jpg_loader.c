# include "jpg_loader.h"
mdl_i8_t load_jpg(char const *__filepth, struct jpg_loader *__jpg_loader) {
	int fd;
	if ((fd = open(__filepth, O_RDONLY)) < 0) {
		fprintf(stderr, "failed to open file at '%s', errno: %d\n", __filepth, errno);
		return -1;
	}

	struct stat finfo;
	if (stat(__filepth, &finfo) < 0) {
		fprintf(stderr, "failed to stat file, errno: %d\n", errno);
		close(fd);
		return -1;
	}

	mdl_uint_t fbuff_size = finfo.st_size;
	mdl_u8_t *fbuff = (mdl_u8_t *)malloc(finfo.st_size * sizeof(mdl_u8_t));

	if (read(fd, fbuff, finfo.st_size * sizeof(mdl_u8_t)) < 0) {
		fprintf(stderr, "failed to read file, errno: %d\n", errno);
		close(fd);
		return -1;
	}

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, fbuff, fbuff_size);
	if (jpeg_read_header(&cinfo, TRUE) != 1) {
		close(fd);
		return -1;
	}

	jpeg_start_decompress(&cinfo);
	__jpg_loader-> width = cinfo.output_width;
	__jpg_loader-> height = cinfo.output_height;
	__jpg_loader-> chn_c = cinfo.output_components;

	__jpg_loader-> buff_size = __jpg_loader-> width * __jpg_loader-> height * __jpg_loader-> chn_c;
	__jpg_loader-> buff = (mdl_u8_t *)malloc(__jpg_loader-> buff_size * sizeof(mdl_u8_t));

	while (cinfo.output_scanline < cinfo.output_height) {
		char unsigned *c[1] = {(char unsigned *)(__jpg_loader-> buff + cinfo.output_scanline * (__jpg_loader-> width * __jpg_loader-> chn_c))};
		jpeg_read_scanlines(&cinfo, c, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	close(fd);
	free((void *)fbuff);
	return 0;
}
