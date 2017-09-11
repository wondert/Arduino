// define UUIDs for Bluetooth service
var SERVICE_UUID = 'D270';
var UNLOCK_UUID = 'D271';
var MESSAGE_UUID = 'D272';

// helper function to convert strings sent from app (lock/unlock password) into ArrayBuffers of bytes for Bluetooth API
function stringToArrayBuffer(str) {
    // assuming 8 bit bytes
    var ret = new Uint8Array(str.length);
    for (var i = 0; i < str.length; i++) {
        ret[i] = str.charCodeAt(i);
        console.log(ret[i]);
    }
    return ret.buffer;
}

// helper function to convert status messages sent from Bluetooth device as ArrayBuffer of bytes into String for app to display status messages
function bytesToString(buffer) {
    return String.fromCharCode.apply(null, new Uint8Array(buffer));
}

// application logic contained in app variable (looks like a class to me...)
var app = {
    // initialize calls bindEvents and hides the div pages of the app. starts up the app.
    initialize: function() {
        this.bindEvents();
        deviceListScreen.hidden = true;
        unlockScreen.hidden = true;
    },
    // connects HTML DOM (actual pages) to applications javascript code. only called once.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
        refreshButton.ontouchstart = this.scan;
        deviceList.ontouchstart = this.connect;
        document.forms[0].addEventListener('submit', this.unlock, false);
        disconnectButton.onclick = this.disconnect;
    },
    // when called, will scan for peripheral bluetooth devices
    onDeviceReady: function() {
        app.scan();
    },
    // clears all previous devices, runs the scrim div page, and scans/connects to select bluetooth services
    scan: function(e) {
        // clear device list
        deviceList.innerHTML = "";
        app.showProgressIndicator("Scanning for Bluetooth Devices...");

        // scans for peripheral bluetooth devices, but discovery is limited to devices advertising the SERVICE_UUID
        // if successful runs onDeviceDiscovered, else runs inline function
        ble.startScan([SERVICE_UUID],
            app.onDeviceDiscovered,
            function() { alert("Listing Bluetooth Devices Failed"); }
        );

        // stop scan after 5 seconds, calls onScanComplete if ble.stopScan runs successfully 
        setTimeout(ble.stopScan, 5000, app.onScanComplete);

    },
    // recieves JSON object representing peripheral object, makes deviceListPage visible, builds + adds new elements to device list 
    onDeviceDiscovered: function(device) {
        var listItem, rssi;

        app.showDeviceListScreen();

        console.log(JSON.stringify(device));
        listItem = document.createElement('li');
        listItem.dataset.deviceId = device.id;
        if (device.rssi) {
            rssi = "RSSI: " + device.rssi + "<br />";
        } else {
            rssi = "";
        }
        listItem.innerHTML = device.name + "<br />" + rssi + device.id;
        deviceList.appendChild(listItem);

        var deviceListLength = deviceList.getElementsByTag('li').length;
        app.setStatus("Found " + deviceListLength + " device" + (deviceListLength === 1 ? "." : "s."));
    },
    // shows peripheral devices connected after app.scan completes successfully. notify users if no peripherals found. 
    onScanComplete: function() {
        var deviceListLength = deviceList.getElementsByTag('li').length;
        if (deviceListLength === 0) {
            app.showDeviceListScreen();
            app.setStatus("No Bluetooth Peripherals Discovered.");
        }
    },
    // called when user taps a device on the device list screen. gets the device id and then connects with bluetooth device.
    connect: function(e) {
        var device = e.target.dataset.deviceId;
        app.showProgressIndicator("Requesting connection to " + device);
        ble.connect(device, app.onConnect, app.onDisconnect);
    },
    // called on successful connection, and when message characteristic changes. creates peripheral device object so program can access it
    onConnect: function(peripheral) {
        app.connectedPeripheral = peripheral;
        app.showUnlockScreen();
        app.setStatus("Connected");
        ble.startNotification(peripheral.id, SERVICE_UUID, MESSAGE_UUID, app.onData);
    },
    // called if ble.connect fails, usually when the application unexpectedly disconnects. 
    onDisconnect: function(reason) {
        if (!reason) {
            reason = "Connection Lost";
        }
        app.hideProgressIndicator();
        app.showDeviceListScreen();
        app.setStatus(reason);
    },
    // called when user requests disconnect. handles the disconnect button event
    // disconnects from peripheral, then updates status message and calls app.scan to find other peripheral devices
    disconnect: function(e) {
        if (e) {
            e.preventDefault();
        }

        app.setStatus("Disconnecting...");
        ble.disconnect(app.connectedPeripheral.id, function() {
            app.setStatus("Disconnected");
            setTimeout(app.scan, 800);
        });
    },
    // updates status on application whenever status message characteristic changes
    onData: function(buffer) {
        var message = bytesToString(buffer);
        app.setStatus(message);
        app.hideProgressIndicator();
    },
    // called whenever user submits the form with a valid unlock code.
    unlock: function(e) {
        // capture submitted code. check if empty submission.
        var code = e.target.code.value;
        e.preventDefault();

        if (code === "") { return;}
        app.showProgressIndicator();

        // if ble.write succeeds, clear input from application/html form. else 
        function success() {
            e.target.code.value = "";
        }

        function failure(reason) {
            alert("Error sending code" + reason);
            app.hideProgressIndicator();
        }

        // send unlock code to periperhal device. writes unlock code to unlock characteristic
        ble.write(
            app.connectedPeripheral.id,
            SERVICE_UUID,
            UNLOCK_UUID,
            stringToArrayBuffer(code),
            success, failure
        );
    },
    // UI: takes optional message and overlays the progress scrim on top of the user interface 
    showProgressIndicator: function(message) {
        if (!message) { message = "Processing"; }
        scrim.firstElementChild.innerHTML = message;
        scrim.hidden = false;
        statusDiv.innerHTML = "";
    },
    // UI: hides scrim div. can be called safely at any time
    hideProgressIndicator: function() {
        scrim.hidden = true;
    },
    // UI: ensures device list screen visible and hides unlock screen
    showDeviceListScreen: function() {
        unlockScreen.hidden = true;
        deviceListScreen.hidden = false;
        app.hideProgressIndicator();
        statusDiv.innerHTML = "";
    },
    // UI: ensures unlock screen visible and hides device list screen
    showUnlockScreen: function() {
        unlockScreen.hidden = false;
        deviceListScreen.hidden = true;
        app.hideProgressIndicator();
        statusDiv.innerHTML = "";
    },
    // UI: logs status message to JavaScript console and display message to user
    setStatus: function(message) {
        console.log(message);
        statusDiv.innerHTML = message;
    }
};

app.initialize();