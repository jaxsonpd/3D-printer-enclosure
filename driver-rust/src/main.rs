use serialport::SerialPort;
use std::io::{self, Read, Write};
use std::time::Duration;
use customCANProtocol::{Packet, PacketByteLocations};


/// Open the serial port
/// 
fn open_serial_port(port_name: &str, baud_rate: u32) -> Result<Box<dyn SerialPort>, Box<dyn std::error::Error>> {
    let port = serialport::new(port_name, baud_rate)
        .timeout(Duration::from_millis(1000))
        .open()
        .map_err(|e| Box::new(e) as Box<dyn std::error::Error>)?;

    Ok(port)
}

/// Read a custom can protocol packet from the serial port
/// 
/// # Parameters
/// - `port` the serial port to read from
/// 
/// # Returns
/// Return the packet as a buffer of u8s
fn read_packet(port: Box<dyn SerialPort>) -> Result<Box<Vec<u8>>, Box<dyn std::error::Error>> {
    let mut buffer = vec![0u8; customCANProtocol::MAX_PACKET_LENGTH];
    let mut idx = 0;

    loop {
        let byte = port.read()?;
        if byte == customCANProtocol::PACKET_START_BYTE {
            buffer[idx] = byte;
            idx += 1;
            break;
        }
    }

    let cmd_byte = port.read();
    buffer[idx] = Ok(cmd_byte);
    idx += 1;

    print!("Got packet: ");
    for x in &buffer {
        print!("{}", x);
    }

    Ok(Box::new(buffer))
}



fn main() {
    let port_name = "/dev/ttyUSB0";
    let baud_rate = 115200;

    let mut port = match open_serial_port(port_name, baud_rate) {
        Ok(port) => port,
        Err(e) => {
            eprintln!("Failed to open serial port: {}", e);
            return;
        }
    };
    

    println!("Reading from serial port: {}", port_name);
    loop {
        read_packet(port);
    }

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
