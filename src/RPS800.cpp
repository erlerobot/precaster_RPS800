#include "RPS800.hpp"

RPS800::RPS800(std::string port, unsigned long baud)
 :my_serial(port,
            baud,
            serial::Timeout::simpleTimeout(1000),
            serial::eightbits,
            serial::parity_none,
            serial::stopbits_one)
{
  std::cout << "Is the serial port open?";
  if(my_serial.isOpen())
    std::cout << " Yes." << std::endl;
  else
    std::cout << " No." << std::endl;

  ros::NodeHandle n;
  rangefinder_pub = n.advertise<sensor_msgs::Range>("range", 1);
}

void RPS800::read_message()
{

  std::string result = my_serial.read(1);
	if(result.length()==0)
		return;

	std::vector<uint> bytes(result.begin(), result.end());

  if(bytes[0]==0xFA){

		std::vector<uint> read_bytes;
		read_bytes.resize(4);
		int count_readbytes = 0;
		while(1){
			std::string data = my_serial.read(1);
			if(data.length()==0) continue;
			std::vector<uint> byte(data.begin(), data.end());
			read_bytes[count_readbytes++] = byte[0];
			if(count_readbytes==4){
				break;
			}
		}

		unsigned char value = bytes[0];
		value = value + (unsigned char)read_bytes[0];
    value = value + (unsigned char)read_bytes[1];
    value = value + (unsigned char)read_bytes[2];

    int distance =  (read_bytes[1] << 8) + read_bytes[0];

/* Debug
    printf("%.2X %.2X %.2X %.2X %.2X", bytes[0], read_bytes[0], read_bytes[1], read_bytes[2], read_bytes[3]);
    printf(" (%.2X) D %.2f", value, distance/1000.0);
		if(read_bytes[2]==0x00) printf(" Normal\n");
                else if(read_bytes[2]==0x01) printf(" Out of range\n");
                else if(read_bytes[2]==0x02) printf(" Signal is to weak\n");
                else if(read_bytes[2]==0x06) printf(" Out of working temperature\n");
		else printf("\n");
*/
    sensor_msgs::Range range_msgs;
    range_msgs.radiation_type = 1; //INFRARED
    range_msgs.field_of_view = 0;
    range_msgs.min_range = 0.1;
    range_msgs.max_range = 5.0;
    range_msgs.range = distance/1000.0;

    rangefinder_pub.publish(range_msgs);
	}
  return;
}
