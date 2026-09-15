
#include "common.h"

#include <fcntl.h>
#include <glob.h>
#include <linux/limits.h>
#include <sys/stat.h>

#define DEF_EXT ".txt"

// file_t* file_stack = NULL;
static string_list_t* common_env = NULL;
static char buffer[PATH_MAX]; // returning a pointer to this

/**
 * @brief Handle errors around realpath().
 *
 * @param str
 * @return const char*
 */
static inline const char* get_path(const char* str) {

    if(NULL == realpath(str, buffer))
        FATAL("cannot resolve path: \"%s\": %s", str, strerror(errno));

    return buffer;
}

/**
 * @brief Add a path defined in the environment to the internal finder path.
 *
 * @param str
 */
static void add_env(const char* str) {

    if(str != NULL) {
        char* tmp = getenv(str);
        if(tmp != NULL) {
            tmp = _COPY_STRING(tmp);
            // printf("%s = %s\n", str, tmp);
            if(tmp != NULL) {
                char* s;
                // char* save;
                char* f = ":";
                s = strtok(tmp, f);
                while(s != NULL) {
                    append_string_list(common_env, create_string(s));
                    s = strtok(NULL, f);
                }

                _FREE(tmp);
            }
        }
    }
}

/**
 * @brief Add a directory and all sub directories to the internal finder path.
 *
 * @param dname
 */
static void add_dirs(const char* dname) {

    // ENTER;
    char* tmp = NULL;
    struct stat s;

    tmp = (char*)get_path(dname);
    strcat(tmp, "/*");
    glob_t gstruct;
    glob(tmp, GLOB_NOSORT | GLOB_NOESCAPE, NULL, &gstruct);

    // TRACE("adding path: %s", tmp);
    // TRACE("paths: %lu", gstruct.gl_pathc);
    for(size_t i = 0; i < gstruct.gl_pathc; i++) {
        stat(gstruct.gl_pathv[i], &s);
        if(S_ISDIR(s.st_mode)) {
            // TRACE("%lu. %s", i+1, gstruct.gl_pathv[i]);
            append_string_list(common_env, create_string(gstruct.gl_pathv[i]));
            // recursively add subdirectories
            add_dirs(gstruct.gl_pathv[i]);
        }
    }
    // RETURN();
}

/**
 * @brief See if the file exists.
 *
 * @param fname
 * @return true
 * @return false
 */
static bool file_exists(const char* fname) {

    struct stat sb;
    return ((stat(fname, &sb) == 0));
}

/**
 * @brief Create the internal finder path environment.
 *
 */
void setup_env(void) {

    if(common_env == NULL)
        common_env = create_string_list();

    add_env("INCLUDE_PATH");
    add_env("IMPORT_PATH");
    // add_dirs("..");
    add_env("PATH");
}

/**
 * @brief Find a file. Returns the full path given just the name.
 *
 * @param fname
 * @return string_t*
 */
string_t* find_file(string_t* fname) {

    ENTER;

    char* found = NULL;
    /*
        // add the ".toy" on the end if it was not specified
        char* tmp_name = strrchr(fname, '.');
        if(NULL == tmp_name || strcmp(tmp_name, DEF_EXT)) {
            tmp_name = _ALLOC(PATH_MAX);
            strcpy(tmp_name, fname);
            strcat(tmp_name, DEF_EXT);
        }
        else
    */
    char* tmp_name = _COPY_STRING(raw_string(fname));

    TRACE("searching for \"%s\"", tmp_name);

    if(common_env == NULL)
        setup_env();

    int mark = 0;
    string_t* s;

    while(NULL != (s = iterate_string_list(common_env, &mark))) {
        strncpy(buffer, raw_string(s), PATH_MAX);
        strcat(buffer, "/");
        strcat(buffer, tmp_name);

        TRACE("try: %s", buffer);
        if(file_exists(buffer)) {
            TRACE("found: %s", buffer);
            found = _COPY_STRING((buffer));
            break;
        }
    }

    _FREE(tmp_name);

    if(found == NULL)
        RETURN(fname);
    else
        RETURN(create_string(found));
}

/**
 * Add a directory to the search path.
 */
void add_dir_to_search(string_t* str) {
    //ENTER;
    if(common_env == NULL)
        common_env = create_string_list();
    add_dirs(str->buffer);
    //RETURN();
}
