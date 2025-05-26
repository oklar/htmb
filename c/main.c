#include "htmb.h"


int main(void)
{
    char *emptyDiv = Div("");
    char *emptyDiv2 = DivAttr((""), "");
    char *emptyDiv3 = DivAttr((""));


    char *test = 
    Body(
      Header(
        H1("Welcome to my page"),
        P("This is a simple demo using standard and void HTML tags."),
        Hr()
      ),
      Main(
        Section(
          H2("Form Elements"),
          Form(
            LabelAttr(("form=name"), "Name:"),
            InputAttr(("type=text", "id=name", "name=name")),
            Br(),
            Br(),

            LabelAttr(("form=email"), "Email:"),
            InputAttr(("type=email", "id=email", "name=email")),
            Br(), 
            Br(),

            InputAttr(("type=submit", "value=Submit"))
          )
        )
      )
    );
    

    puts(test); free(test);
    puts(emptyDiv); free(emptyDiv);
    puts(emptyDiv2); free(emptyDiv2);
    puts(emptyDiv3); free(emptyDiv3);
    return 0;
}
