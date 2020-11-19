#include "ts/ink_assert.h"
#include "ts/ink_defs.h"
#include "ts/Regex.h"

typedef struct {
    char subject[100];
    bool match;
} subject_match_t;

typedef struct {
    char regex[100];
    subject_match_t tests[4];
} test_t;

static const test_t test_data[] = {
        {"^foo", {{"foo", true}, {"bar", false}, {"foobar", true}, {"foobarbaz", true}}},
        {"foo$", {{"foo", true}, {"bar", false}, {"foobar", false}, {"foobarbaz", false}}},
};

static void
test_basic()
{
    for (unsigned int i = 0; i < countof(test_data); i++) {
        Regex r;

        printf("Regex: %s\n", test_data[i].regex);
        r.compile(test_data[i].regex);
        for (unsigned int j = 0; j < countof(test_data[i].tests); j++) {
            printf("Subject: %s Result: %s\n", test_data[i].tests[j].subject, test_data[i].tests[j].match ? "true" : "false");
            ink_assert(r.exec(test_data[i].tests[j].subject) == test_data[i].tests[j].match);
        }
    }
}

int
main(int /* argc ATS_UNUSED */, char ** /* argv ATS_UNUSED */)
{
    test_basic();
    printf("test_Regex PASSED\n");
}
