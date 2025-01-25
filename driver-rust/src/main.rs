use serialport::SerialPort;
use std::io::{self, Read, Write};
use std::time::Duration;

fn main() {
    let portName = "/dev/ttyUSB0";
    let baudRate = 115200;

    match serialport::new(portName, baudRate)
        .timeout(Duration::from_millis(1000))
        .open()
    {
        Ok(mut port) => {
            println!("Reading from serial port: {}", portName);
            let mut buffer: Vec<u8> = vec![0; 1024];

            loop {
                match port.read(&mut buffer) {
                    Ok(bytes_read) => {
                        let received = String::from_utf8_lossy(&buffer[..bytes_read]);
                        print!("{}", received);
                        io::stdout().flush().unwrap();
                    }
                    Err(ref e) if e.kind() == std::io::ErrorKind::TimedOut => {
                        // Continue reading on timeout (no data available)
                        continue;
                    }
                    Err(e) => {
                        eprintln!("Error reading from serial port: {:?}", e);
                        break;
                    }
                }
            }
        }
        Err(e) => {
            eprintln!("Failed to open serial port: {}", e);
        } 
    }
}
