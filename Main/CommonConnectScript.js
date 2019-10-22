let cookie = document.cookie.replace(/(?:(?:^|.*;\s*)pid\s*\=\s*([^;]*).*$)|^.*$/, "$1");

if (parseInt(cookie, 10) == 0 || isNaN(cookie)) {
    alert("Got invalid PlayerID, reconnecting soon");

    setTimeout(function () {
        location.reload();
    }, 300);
}

let socket = new WebSocket("ws://" + document.domain + "/ws?pid=" + cookie);

socket.onopen = function (event) {
};

socket.onmessage = function (event) {
    var dataView = new DataView(event.data);

    var type = dataView.getInt8(0);

    switch (type) {
        case 1: // collect
            var playerCount = dataView.getInt8(1);
            document.getElementById("pcount").innerHTML = playerCount;

            break;
    }
};

socket.onclose = function (event) {
    alert("socket onclose");
};