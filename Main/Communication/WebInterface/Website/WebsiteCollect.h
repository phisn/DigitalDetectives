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
    <script>
		let cookie = document.cookie.replace(/(?:(?:^|.*;\s*)pid\s*\=\s*([^;]*).*$)|^.*$/, "$1");

		if (parseInt(cookie, 10) == 0 || isNaN(cookie)) {
			alert("Got invalid PlayerID, reconnecting soon");

			setTimeout(function () {
				location.reload();
			}, 300);
		}

		let socket = new WebSocket("ws://" + document.domain + "/ws?pid=" + cookie);
		socket.binaryType = "arraybuffer";

		socket.onopen = function (event) {
		};

		socket.onmessage = function (event) {
			var data = event.data;
			var dataView = new DataView(data);

			var type = dataView.getInt8(0);

			switch (type) {
				case 1: // collect
					var playerCount = dataView.getInt8(1);
					document.getElementById("pcount").innerHTML = playerCount;

					break;
			}
		};

		socket.onclose = function (event) {
			alert("Lost Connection!");
		};
    </script>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <title></title>
  </head>
  <body>
    <p style="text-align: center;">Waiting for other players</p>
    <p style="text-align: center;">Currently <b id="pcount">loading ...</b> Online</p>
  </body>
</html>
)";
	}
}