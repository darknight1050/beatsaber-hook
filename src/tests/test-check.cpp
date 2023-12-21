#ifdef NO_TEST
#if defined(TEST_CALLBACKS) || defined(TEST_SAFEPTR) || defined(TEST_BYREF) || defined(TEST_ARRAY) || defined(TEST_LIST) || defined(TEST_STRING) || defined(TEST_HOOK) || defined(TEST_THREAD)
#error "tests are being built into the release for bs hook!"
#endif
#endif
