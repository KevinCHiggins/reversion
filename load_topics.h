void load_topics(void);

int contains_lang(char *lang);
str_list *get_languages(void);
str_list *get_versions(char *lang);
str_list *get_features(char *lang, char *ver);
size_t count_features_of_lang(char *lang);
size_t *count_features_of_lang_per_version(char *lang);
char *get_nth_feature_of_lang(char *lang, size_t n);
//size_t get_ver_num_containing_nth_of_all_features(char *lang, size_t n);
