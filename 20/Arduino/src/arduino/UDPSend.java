package arduino;

import java.io.*;
import java.net.*;
import java.util.Random;

public class UDPSend {

    public static void main(String args[]) {
        try {
            String host = "192.168.1.2";
            int port = 1111;

            //int random = ;
            
            byte[] message = new byte[2];
            int randomVal;
            Random random =  new Random();
            
            
            while(true) {
                
                
                randomVal = random.nextInt(127);
                
                //randomVal = 127;
                
                System.out.println(randomVal);
                
                message[1] = (byte) (randomVal & 255);
                message[0] = 0;
//                message[0] = (byte) ((randomVal >>> 8) & 255);
                
                //System.out.println(a(message));
                
                // Get the internet address of the specified host
                InetAddress address = InetAddress.getByName(host);

                // Initialize a datagram packet with data and address
                DatagramPacket packet = new DatagramPacket(message, message.length, address, port);

                // Create a datagram socket, send the packet through it, close it.
                DatagramSocket dsocket = new DatagramSocket();
                dsocket.send(packet);
                
                Thread.sleep(10 + random.nextInt(500));
                dsocket.close();
            }
        } catch (Exception e) {
            System.err.println(e);
        }
    }
    
    public static long a (byte[] bytes) 
    {
        long a = 0;
        a = (long) bytes[1];
        a = a << 8;
        a = a | bytes[0];
        
        return a;
    }
}