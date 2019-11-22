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
  <title>Digital Detectives</title>
 </head>
<body>
<div class="jumbotron">
  <div id="playerdata"></div>
  <p><b id="taxititle"></b></p>
  <form class="taxi" id="taxi" action="" method="post">
  </form>
 <p><b id="bustitle"></b></p>
  <form class="bus" id="bus" action="" method="post">
  </form>
 <p><b id="undergroundtitle"></b></p>
  <form class="underground" id="underground" action="" method="post">
 </form>
 </div>
</body>
<style>
 p {
  text-align: center;
}

div, h3 {
  text-align: center;
}

button {
	margin-right: 3px;
}

.black{
  background-color: black;
  padding: 20px;
  margin-bottom:10px;
}

.taxi {
  background-color: yellow;
  padding: 20px;
  margin-bottom:10px;
}

.bus {
  background-color: green;
  padding: 20px;
  margin-bottom:10px;
}

.underground {
  background-color: red;
  padding: 20px;
  margin-bottom:10px;
}

.ferry {
  background-color: blue;
  padding: 20px;
  margin-bottom:10px;
}
</style>
<script language="javascript">
    let cookie = document.cookie.replace(/(?:(?:^|.*;\s*)pid\s*\=\s*([^;]*).*$)|^.*$/, "$1");
	var pid = parseInt(cookie, 10);
	if (pid == 0 || isNaN(cookie)) {
		alert("Got invalid PlayerID, reconnecting soon");

		setTimeout(function () {
			location.reload();
		}, 300);
	}

	let socket = new WebSocket("ws://" + document.domain + "/ws?pid=" + cookie);
	socket.binaryType = "arraybuffer";
		
	socket.onmessage = function (event) {
		var d = new DataView(event.data);
    
		var type					= d.getUint8(0), 
			playerID				= d.getUint8(2), 
			playerType				= d.getUint8(3), 
			playerCount				= d.getUint8(1), 
			position				= d.getUint8(4), 			
			yellowTicketCount		= d.getUint8(5), 
			greenTicketCount		= d.getUint8(6), 
			redTicketCount			= d.getUint8(7), 
			positionVillianReveal	= d.getUint8(8), 
			positionVillian			= d.getUint8(9), 
			villianYellowTicketCount = d.getUint8(10), 
			villianGreenTicketCount	= d.getUint8(11),
			villianRedTicketCount	= d.getUint8(12), 
			villianBlackTicketCount = d.getUint8(13), 
			villianDoubleTicketCount = d.getUint8(14), 
			color					= d.getUint8(15),
			turnYellowCount			= d.getUint8(29), 
			turnGreenCount			= d.getUint8(30), 
			turnRedCount 			= d.getUint8(31);
		var turnYellowOffset = 32,
			turnGreenOffset = 38,
			turnRedOffset = 43;
		
		if(type != 3){
		  location.reload(true);
		}

		var html = '';
		var colorStr = '';
		switch(color){
		  case 0:
		   colorStr = "Black";
		   break;
		   case 1:
		   colorStr = "Red"
		   break;
		   case 2:
		   colorStr = "Green";
		   break;
		   case 3:
		   colorStr = "Blue";
		   break;
		   case 4:
		   colorStr = "Purple";
		   break;
		   case 5:
		   colorStr = "Yellow";
		   break;
		}
		html += '<h3>Color: ' + colorStr + '</h3>';
		html += '<p><b>Tickets: </b>' + yellowTicketCount + ' Taxi, ' + greenTicketCount + ' Bus, ' + redTicketCount + ' Underground</p>';
		html += '\n';
		html += '<p><i><b>Tickets of Mr. X: </b> ' + villianBlackTicketCount + ' Black, ' + villianDoubleTicketCount + ' Double, ' + villianRedTicketCount + ' Underground, ' + villianGreenTicketCount + ' Bus, ' + villianYellowTicketCount + ' Taxi</i></p>';
		html += '\n';
		html += '<p>Position of Mr. X revealed in <b>' + positionVillianReveal + '</b> moves</p>';
		document.getElementById('playerdata').innerHTML = html;
 
		if(pid === playerID){
			if(turnYellowCount > 0 && yellowTicketCount > 0){
				document.getElementById('taxititle').innerHTML = 'Taxi';
				var tHtml = '';
				for(i = 0; i < turnYellowCount; i++){
					var station = d.getUint8(turnYellowOffset + i);
					tHtml += '<button value=\"' + station + '\" type=\"submit\" name=\"y\" formmethod="post">' + station + '</button>';
				}
				document.getElementById('taxi').innerHTML = tHtml;
			}
			if(turnGreenCount > 0 && greenTicketCount > 0){
				document.getElementById('bustitle').innerHTML = 'Bus';
				var bHtml = '';
				for(i = 0; i < turnGreenCount; i++){
				var station = d.getUint8(turnGreenOffset + i);
				bHtml += '<button value=\"' + station + '\" type=\"submit\" name=\"g\" formmethod="post">' + station + '</button>';
			}
			document.getElementById('bus').innerHTML = bHtml;
			}
			if(turnRedCount > 0 && redTicketCount > 0){
				document.getElementById('undergroundtitle').innerHTML = 'Underground';
				var uHtml = '';
				for(i = 0; i < turnRedCount; i++){
					var station = d.getUint8(turnRedOffset + i);
					uHtml += '<button value=\"' + station + '\" type=\"submit\" name=\"r\" formmethod="post">' + station + '</button>';
				}

				document.getElementById('underground').innerHTML = uHtml;
			}
		}
	}
</script>
</html>
)";	
	}
	
	namespace
	{
		Game::Ticket CharacterToTicket(const char character)
		{
			switch (character)
			{
			case 'y': return Game::Ticket::Yellow;
			case 'g': return Game::Ticket::Green;
			case 'r': return Game::Ticket::Red;
			case 'b': return Game::Ticket::Black;
			case 'd': return Game::Ticket::Double;
			}

		}

		FlashString fault_invalid_turn = DEVICE_FAULT_MESSAGE("Got invalid turn on POST         ");
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

		void HandleRunningPost(AsyncWebServerRequest* const request)
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

			AsyncWebParameter* const parameter = request->getParam(0);

			Game::Turn turn;

			turn.doubleTicket = false;
			turn.position = 0;
			turn.ticket = CharacterToTicket(parameter->name().charAt(0));

			for (int i = 0; i < parameter->value().length(); ++i)
			{
				turn.position *= 10;
				turn.position += parameter->value()[i] - '0';
			}

			DEBUG_MESSAGE("MAKE TURN");
			const Game::GameManager::TurnResult result = Game::GameManager::MakeTurn(playerId, turn);

			if (result != Game::GameManager::TurnResult::Success)
			{
				DEBUG_MESSAGE("FAIl");

				Device::FaultHandler::Handle(
					{
						Device::FaultModule::WebInterface,
						2,
						fault_invalid_turn
					},
					false);

				request->send(400);
			}
			else
			{
				DEBUG_MESSAGE("SUCCESS");

				request->send(200);
			}

			/*
				Serial.println("Args:");

				for (int i = 0; i < request->args(); ++i)
				{
					Serial.print(request->arg(i));
					Serial.print("=");
					Serial.println(request->argName(i));
				}

				Serial.println("Params:");
				for (int i = 0; i < request->args(); ++i)
				{
					AsyncWebParameter* const parameter = request->getParam(i);

					Serial.print(parameter->isFile());
					Serial.print(" ");
					Serial.print(parameter->isPost());
					Serial.print(" ");
					Serial.print(parameter->size());
					Serial.print(" ");
					Serial.print(parameter->name());
					Serial.print("=");
					Serial.println(parameter->value());
				}
			*/
		}
	}
}
