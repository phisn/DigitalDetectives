#pragma once

#include "../../../Common/Common.h"

namespace Communication
{
	namespace Website
	{
		const char* Collect PROGMEM =
R"(
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <title></title>
  </head>
  <body>
    <p style="text-align: center;">Waiting for other players</p>
    <p style="text-align: center;">Currently <b>loading ...</b> Online</p>
  </body>
</html>
)");
	}
}