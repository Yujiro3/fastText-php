#include <fasttext.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_fasttext.h"

/* If you declare any globals in php_fasttext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(fasttext)
*/

/* True global resources - no need for thread safety here */
static int le_fasttext;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("fasttext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_fasttext_globals, fasttext_globals)
    STD_PHP_INI_ENTRY("fasttext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_fasttext_globals, fasttext_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_fasttext_predict, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_INFO(1, modelpath)
	ZEND_ARG_INFO(1, word)
	ZEND_ARG_INFO(0, k)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fasttext_vectors, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_INFO(1, modelpath)
	ZEND_ARG_INFO(1, word)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fasttext_test, 0, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_INFO(1, modelpath)
	ZEND_ARG_INFO(1, word)
	ZEND_ARG_INFO(0, k)
ZEND_END_ARG_INFO()
/* }}} */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_fasttext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_fasttext_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "fasttext", arg);

	RETURN_STR(strg);
}
/* }}} */

/* {{{ proto string fasttext_predict(string modelpath, string word, int k)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(fasttext_predict)
{
	char *modelpath = NULL, *word = NULL;
	size_t modelpath_len, word_len;
	zend_long k = 1;
	char result[1024];

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss|l", &modelpath, &modelpath_len, &word, &word_len, &k) == FAILURE) {
		return;
	}

	if (!FastTextPredict(modelpath, word, (int32_t)k, result)) {
		RETURN_FALSE;
	}

	RETURN_STRING(result);
}
/* }}} */

/* {{{ proto string fasttext_predictProb(string modelpath, string word, int k)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(fasttext_predictprob)
{
	char *modelpath = NULL, *word = NULL;
	size_t modelpath_len, word_len;
	zend_long k = 1;
	char result[1024];

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss|l", &modelpath, &modelpath_len, &word, &word_len, &k) == FAILURE) {
		return;
	}

	if (!FastTextPredictProb(modelpath, word, (int32_t)k, result)) {
		RETURN_FALSE;
	}

	RETURN_STRING(result);
}
/* }}} */


/* {{{ proto string fasttext_word_vectors(string modelpath, string word)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(fasttext_word_vectors)
{
	char *modelpath = NULL, *word = NULL;
	size_t modelpath_len, word_len;
	char result[1024];

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &modelpath, &modelpath_len, &word, &word_len) == FAILURE) {
		return;
	}

	if (!FastTextPrintWordVectors(modelpath, word, result)) {
		RETURN_FALSE;
	}

	RETURN_STRING(result);
}
/* }}} */


/* {{{ proto string fasttext_sentence_vectors(string modelpath, string word)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(fasttext_sentence_vectors)
{
	char *modelpath = NULL, *word = NULL;
	size_t modelpath_len, word_len;
	char result[1024];

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &modelpath, &modelpath_len, &word, &word_len) == FAILURE) {
		return;
	}

	if (!FastTextPrintSentenceVectors(modelpath, word, result)) {
		RETURN_FALSE;
	}

	RETURN_STRING(result);
}
/* }}} */


/* {{{ proto string fasttext_test(string modelpath, string word, int k)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(fasttext_test)
{
	char *modelpath = NULL, *word = NULL;
	size_t modelpath_len, word_len;
	zend_long k = 1;
	char result[1024];

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss|l", &modelpath, &modelpath_len, &word, &word_len, &k) == FAILURE) {
		return;
	}

	if (!FastTextTest(modelpath, word, (int32_t)k, result)) {
		RETURN_FALSE;
	}

	RETURN_STRING(result);
}
/* }}} */


/* {{{ php_fasttext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_fasttext_init_globals(zend_fasttext_globals *fasttext_globals)
{
	fasttext_globals->global_value = 0;
	fasttext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(fasttext)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(fasttext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(fasttext)
{
#if defined(COMPILE_DL_FASTTEXT) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(fasttext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(fasttext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "fasttext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ fasttext_functions[]
 *
 * Every user visible function must have an entry in fasttext_functions[].
 */
const zend_function_entry fasttext_functions[] = {
	PHP_FE(confirm_fasttext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(fasttext_predict, arginfo_fasttext_predict)
	PHP_FE(fasttext_predictprob, arginfo_fasttext_predict)
	PHP_FE(fasttext_word_vectors, arginfo_fasttext_vectors)
	PHP_FE(fasttext_sentence_vectors, arginfo_fasttext_vectors)
	PHP_FE(fasttext_test, arginfo_fasttext_test)

	PHP_FE_END	/* Must be the last line in fasttext_functions[] */
};
/* }}} */

/* {{{ fasttext_module_entry
 */
zend_module_entry fasttext_module_entry = {
	STANDARD_MODULE_HEADER,
	"fasttext",
	fasttext_functions,
	PHP_MINIT(fasttext),
	PHP_MSHUTDOWN(fasttext),
	PHP_RINIT(fasttext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(fasttext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(fasttext),
	PHP_FASTTEXT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FASTTEXT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(fasttext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
