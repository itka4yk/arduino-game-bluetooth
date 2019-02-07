const SerialPort = require('serialport')
const port = new SerialPort('/dev/tty.HCrn-DevB')

function send(char) {
  port.write(char, function (err) {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
  })
}

port.on('error', function (err) {
  console.log('Error: ', err.message)
})

var keypress = require('keypress')
  , tty = require('tty');

keypress(process.stdin);

process.stdin.on('keypress', function (ch, key) {
  if (key && key.ctrl && key.name == 'c') {
    process.stdin.pause();
  }
  switch(key.name) {
    case 'down':
      send('0');
      break;
    case 'up':
      send('1');
      break;
  }
});

if (typeof process.stdin.setRawMode == 'function') {
  process.stdin.setRawMode(true);
} else {
  tty.setRawMode(true);
}
process.stdin.resume();