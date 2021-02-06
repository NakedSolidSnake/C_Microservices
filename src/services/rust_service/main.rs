use std::env;
use std::fs::File;
use std::io::Write;
use std::net::UdpSocket;

fn main() -> std::io::Result<()>{
    let args: Vec<String> = env::args().collect();
    let port = &args[1];
    let service = &args[2];
    let message = &args[3];

    let _config = format!("{}{}{}", port.to_string(), '\t', service);
    
    let mut file = File::create("conf/rust.conf").unwrap();

    file.write(&_config.as_bytes())?;

    let server_conf = format!("127.0.0.1:{}", port.to_string());

    let socket = UdpSocket::bind(server_conf)?;

    loop{
        let mut buf = [0; 1024];
        let (amt, src) = socket.recv_from(&mut buf)?;
        let buf = &mut buf[..amt];
        buf.reverse();
        socket.send_to(message.as_bytes(), &src)?;
    }    
}
