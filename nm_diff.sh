export LC_ALL=C
diff -u <(./ft_nm $@) <(nm $@)  | perl /usr/share/doc/git/contrib/diff-highlight/diff-highlight