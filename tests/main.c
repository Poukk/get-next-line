#include "munit.h"
#include "../get_next_line.h"  // Assume get_line is declared here
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* ================== New Tests for get_line ================== */

static MunitResult test_get_line_empty(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *result = get_line("");
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_single_line(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *buffer = "Hello, World!";
    char *result = get_line(buffer);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "Hello, World!");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_single_newline(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *result = get_line("\n");
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_multiple_lines(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *buffer = "First line\nSecond line\n";
    char *result = get_line(buffer);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "First line");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_trailing_newline(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *buffer = "Line with trailing newline\n";
    char *result = get_line(buffer);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "Line with trailing newline");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_no_newline(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *buffer = "No newline here";
    char *result = get_line(buffer);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "No newline here");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_mixed_endings(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *buffer = "Mixed line endings\r\nNext line\r\n";
    char *result = get_line(buffer);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "Mixed line endings");
    free(result);
    return MUNIT_OK;
}

static MunitResult test_get_line_null_input(const MunitParameter params[], void *data) {
    (void)params; (void)data;
    char *result = get_line(NULL);
    munit_assert_null(result);
    return MUNIT_OK;
}

/* ================== Existing Tests for read_file ================== */

static MunitResult test_read_file_normal(const MunitParameter params[], void *data) {
    (void)params; (void)data;

    char filename[] = "/tmp/test_file_XXXXXX";
    int fd = mkstemp(filename);
    munit_assert_int(fd, >, -1);

    const char *content = "Hello, World!";
    write(fd, content, strlen(content));
    lseek(fd, 0, SEEK_SET);

    char *result = read_file(fd);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, content);

    close(fd);
    unlink(filename);
    free(result);

    return MUNIT_OK;
}

static MunitResult test_read_file_empty(const MunitParameter params[], void *data) {
    (void)params; (void)data;

    char filename[] = "/tmp/test_file_empty_XXXXXX";
    int fd = mkstemp(filename);
    munit_assert_int(fd, >, -1);

    char *result = read_file(fd);
    munit_assert_not_null(result);
    munit_assert_string_equal(result, "");

    close(fd);
    unlink(filename);
    free(result);

    return MUNIT_OK;
}

static MunitResult test_read_file_invalid_fd(const MunitParameter params[], void *data) {
    (void)params; (void)data;

    char *result = read_file(-1);
    munit_assert_null(result);

    return MUNIT_OK;
}

/* ================== Test Suite Setup ================== */

static MunitTest test_suite_tests[] = {
    // Tests for read_file
    { "/test_read_file_normal", test_read_file_normal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_read_file_empty", test_read_file_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_read_file_invalid_fd", test_read_file_invalid_fd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // Tests for get_line
    { "/test_get_line_empty", test_get_line_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_single_line", test_get_line_single_line, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_single_newline", test_get_line_single_newline, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_multiple_lines", test_get_line_multiple_lines, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_trailing_newline", test_get_line_trailing_newline, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_no_newline", test_get_line_no_newline, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_mixed_endings", test_get_line_mixed_endings, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_get_line_null_input", test_get_line_null_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    "/combined_tests", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
