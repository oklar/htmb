// Builds a small settings page with HTMB on an ESP-12E and prints it over serial.
#include <Arduino.h>
#include "htmb.h"

void setup()
{
    Serial.begin(115200);

    // anything you didn't write yourself, such as a saved form value, goes through htmb_escape()
    const char *saved_name = "<b>My network</b>";

    char *page =
      Body(
        Header(
          H1("Wi-Fi settings"),
          PAttr(("class=current"), "Connected to ", htmb_escape(saved_name))
        ),
        Main(
          Form(
            LabelAttr(("for=ssid"), "Network name:"),
            InputAttr(("type=text", "id=ssid", "name=ssid", "required")),
            Br(),
            InputAttr(("type=submit", "value=Save"))
          ),
          DivAttr(("id=status"))
        )
      );

    Serial.println(page ? page : "HTMB arena too small");
    Serial.printf("arena used: %u of %u bytes\n", (unsigned)htmb_used(), (unsigned)HTMB_ARENA_SIZE);
    htmb_reset();
}

void loop()
{
}
