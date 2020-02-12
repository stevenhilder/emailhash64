#include <stdint.h>

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include "php.h"
#include "ext/standard/md5.h"
#include "php_emailhash64.h"

PHP_FUNCTION(emailhash64) {
	char* email_address;
	int email_address_length;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &email_address, &email_address_length) == SUCCESS) {
		PHP_MD5_CTX context;
		union {
			uint8_t bytes[16];
			int64_t qword;
		} hash;
		PHP_MD5Init(&context);
		PHP_MD5Update(&context, email_address, email_address_length);
		PHP_MD5Final(hash.bytes, &context);
		RETURN_LONG(
			(((hash.qword & 0xFF00000000000000ULL) >> 56)
			| ((hash.qword & 0x00FF000000000000ULL) >> 40)
			| ((hash.qword & 0x0000FF0000000000ULL) >> 24)
			| ((hash.qword & 0x000000FF00000000ULL) >> 8)
			| ((hash.qword & 0x00000000FF000000ULL) << 8)
			| ((hash.qword & 0x0000000000FF0000ULL) << 24)
			| ((hash.qword & 0x000000000000FF00ULL) << 40)
			| ((hash.qword & 0x00000000000000FFULL) << 56))
			^ 0x8000000000000000ULL
		);
	}
}

ZEND_BEGIN_ARG_INFO(emailhash64_arg_info, UNUSED)
	ZEND_ARG_INFO(0, email_address)
ZEND_END_ARG_INFO()

static const zend_function_entry emailhash64_functions[] = {
	PHP_FE(emailhash64, emailhash64_arg_info)
	PHP_FE_END
};

zend_module_entry emailhash64_module_entry = {
	STANDARD_MODULE_HEADER,
	"emailhash64",
	emailhash64_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"5.0.0",
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_EMAILHASH64
	ZEND_GET_MODULE(emailhash64)
#endif
