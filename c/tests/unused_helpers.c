/* Builds with -Werror only if htmb.h doesn't warn about the helpers a file leaves unused:
   as is it uses no tags, and with -DNORMAL_TAGS it uses normal tags but no void tag. */
#include "htmb.h"

int main(void)
{
#ifdef NORMAL_TAGS
    return Div(P("hi")) == NULL;
#else
    return 0;
#endif
}
