#pragma once

namespace Communciation
{
	namespace Website
	{
		const char* NeutralRequestPid = PROGMEM
			R"(
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <title>Request PID</title>
  </head>
  <body>
    <p style="text-align: center;">Waiting for other players</p>
	<div class="requestpid" action="" method="post">
        <input type="text" class="input-field"/>
        <button value="set" type="submit" formmethod="post">Ok</button>
    </div>
  </body>
</html>
)";
	}
}