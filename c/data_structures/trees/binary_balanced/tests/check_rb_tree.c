#include <check.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../src/rb_tree.h"

START_TEST(check_rb_tree_create)
{
  rb_tree *tree = rb_tree_create();
  ck_assert(tree);
  ck_assert(!tree->root_);
}
END_TEST

START_TEST(check_rb_tree_destroy)
{
  rb_tree *tree = rb_tree_create();
}
END_TEST

Suite *binary_balanced_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Image Processing");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, check_rb_tree_create);
  tcase_add_test(tc_core, check_rb_tree_destroy);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = binary_balanced_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
