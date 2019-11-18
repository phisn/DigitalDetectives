#pragma once

#include "../../Communication/InterfaceManager.h"

#include "../../Communication/WebInterface/WebServerManager.h"
#include "../../Communication/WebInterface/WebInterface.h"

#include "../../Game/GameController.h"

namespace
{
	using namespace Communication;
}

namespace Communication
{
	namespace Website
	{
		const char* Running PROGMEM =
			R"(
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="content-type" content="text/html; charset=UTF-8">
  <title></title>
 </head>
<body>
  <div id="playerdata"></div>
  <h3>Move:</h3>
  <p><b id="taxititle"></b></p>
  <form class="taxi" id="taxi" action="" method="post">
  </form>
 <p><b id="bustitle"></b></p>
  <form class="bus" id="bus" action="" method="post">
  </form>
 <p><b id="undergroundtitle"></b></p>
  <form class="underground" id="underground" action="" method="post">
 </form>
</body>
<script language="javascript">
  let cookie = document.cookie.replace(/(?:(?:^|.*;\s*)pid\s*\=\s*([^;]*).*$)|^.*$/, "$1");

	if (parseInt(cookie, 10) == 0 || isNaN(cookie)) {
		alert("Got invalid PlayerID, reconnecting soon");

		setTimeout(function () {
			location.reload();
		}, 300);
	}

	let socket = new WebSocket("ws://" + document.domain + "/ws?pid=" + cookie);
	socket.binaryType = "arraybuffer";
		
	socket.onmessage = function (event) {
		var d = new DataView(event.data);

		var html = '';
		html += '<p><b>Tickets: </b>' + d.getUint8(4) + ' Taxi, ' + d.getUint8(5) + ' Bus, ' + d.getUint8(6) + ' Underground</p>';
		html += '\n';
		html += '<p><i><b>Tickets of Mr. X: </b> ' + d.getUint8(12) + ' Black, ' + d.getUint8(13) + ' Double, ' + d.getUint8(11) + ' Underground, ' + d.getUint8(10) + ' Bus, ' + d.getUint8(9) + ' Taxi</i></p>';
		html += '\n';
		html += '<p>Position of Mr. X revealed in <b>' + d.getUint8(7) + '</b> moves</p>';
		document.getElementById('playerdata').innerHTML = html;
		var turnYellowCount = d.getUint8(27);
		var turnGreenCount = d.getUint8(28);
		var turnRedCount = d.getUint8(29);
 
		if(d.getUint8(4) > 0){
			document.getElementById('taxititle').innerHTML = 'Taxi';
			var tHtml = '';
			for(i = 0; i < turnYellowCount; i++){
				var station = d.getUint8(30 + i);
				tHtml += '<button value=\"' + station + '\" type=\"submit\" name=\"y\" formmethod="post">' + station + '</button>';
			}
			document.getElementById('taxi').innerHTML = tHtml;
		}
		if(d.getUint8(5) > 0){
			document.getElementById('bustitle').innerHTML = 'Bus';
			var bHtml = '';
			for(i = 0; i < turnGreenCount; i++){
			var station = d.getUint8(36 + i);
			bHtml += '<button value=\"' + station + '\" type=\"submit\" name=\"g\" formmethod="post">' + station + '</button>';
		}
		document.getElementById('bus').innerHTML = bHtml;
		}
		if(d.getUint8(6) > 0){
			document.getElementById('undergroundtitle').innerHTML = 'Underground';
			var uHtml = '';
			for(i = 0; i < turnRedCount; i++){
				var station = d.getUint8(41 + i);
				uHtml += '<button value=\"' + station + '\" type=\"submit\" name=\"r\" formmethod="post">' + station + '</button>';
			}

			document.getElementById('underground').innerHTML = uHtml;
		}
	}
</script>
</html>
)";
	}

	namespace WebHandler
	{
		void HandleRunningRequest(AsyncWebServerRequest* const request)
		{
			if (Game::Controller::GetState() != Game::GameState::Running)
			{
				request->redirect(WEB_DIR_COMMON);
				return;
			}

			const Game::PlayerId playerId = WebServerManager::EnforcePlayerId(request);

			if (playerId == 0)
			{
				return;
			}

			request->send_P(
				200,
				WEB_RESPONSE_TYPE,
				Website::Running);
		}
	}
}
