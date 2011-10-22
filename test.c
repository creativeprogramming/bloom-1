/**
 * file name  : test.c
 * authors    : Dave Pederson
 * created    : Oct 22, 2011
 *
 * modifications:
 * Date:         Name:            Description:
 * ------------  ---------------  ----------------------------------------------
 * Oct 22, 2011  Dave Pederson    Creation
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "bloom.h"

/**
 * Strip '\r' or '\n' chars from a string
 */
static void strip(char *string)
{
    char *c;
    if ((c = strchr(string, '\r'))) {
        *c = 0;
    }
    if ((c = strchr(string, '\n'))) {
        *c = 0;
    }
}

/**
 * Ad-hoc bloom filter test
 */
int main(int argc, char *argv[])
{
    FILE *fp; 
    if (!(fp = fopen("dictionary", "r"))) {
        fprintf(stderr, "E: Couldn't open dictionary file\n");
        fflush (stderr);
        return 1;
    }
    bloom_t *filter = bloom_filter_new(500000);
    assert(filter);
    char *p;
    char line[1024];
    while (fgets(line, 1024, fp)) {
        strip(line);
        assert(bloom_filter_add(filter, line));
    }
    fclose(fp);
    size_t size = bloom_filter_size(filter);
    assert(size);
    size_t count = bloom_filter_count(filter);
    assert(count);
    const char* word = "penguin";
    assert(bloom_filter_contains(filter, word));
    assert(bloom_filter_remove(filter, word));
    assert(!bloom_filter_contains(filter, word));
    assert(bloom_filter_count(filter) == (count-1));
    assert(bloom_filter_free(filter));
    printf("OK\n");
    return 0;
}

