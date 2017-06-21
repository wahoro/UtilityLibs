const char *memstr(const char *src, int len, const char *dst) {
  if (src == NULL || len <= 0 || dst == NULL) {
    return NULL;
  }

  if (*dst == '\0') {
    return NULL;
  }

  const char *cur = src;
  int dst_len = strlen(dst);
  int last = len - dst_len + 1;
  for (int i = 0; i < last; i++) {
    if (*cur == *dst) {
      if (memcmp(cur, dst, dst_len) == 0) {
        return cur;
      }
    }
    cur++;
  }

  return NULL;
}
