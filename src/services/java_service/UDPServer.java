import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UDPServer{
	
	private DatagramSocket udp;
	private byte[] buffer = new byte[1024];
	private Integer port;
	private String message;
	private String service;	
	
	
	public UDPServer(Integer port, String service, String message) throws IOException {		
		udp = new DatagramSocket(port);
		this.port = port;
		this.service = service;
		this.message = message;
		
		createFile(port, service);
	}
	
	private void createFile(Integer port, String service) throws IOException {
		FileWriter file = new FileWriter("conf/java.conf");
		file.write(this.port + "\t" + this.service);
		file.close();
	}
	
	public void exec() throws IOException {
		while(true) {
			DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
			
			udp.receive(packet);
			
			InetAddress address = packet.getAddress();
			int port = packet.getPort();
            packet = new DatagramPacket(buffer, buffer.length, address, port);
            
			packet.setData(this.message.getBytes(), 0, this.message.length());			
			udp.send(packet);
		}			
	}
	
	public static void main(String[] args) throws IOException {
		Integer port = Integer.parseInt(args[0]);
		String service = args[1];
		String message = args[2];
		
		UDPServer server = new UDPServer(port, service, message);
		server.exec();
	}
}
