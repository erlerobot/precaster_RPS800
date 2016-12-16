#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>     /* atoi */

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial/serial.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
      Sleep(milliseconds); // 100 ms
#else
      usleep(milliseconds*1000); // 100 ms
#endif
}

void enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

		printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
     device.hardware_id.c_str() );
	}
}

void print_usage()
{
	cerr << "Usage: test_serial {-e|<serial port address>} ";
    cerr << "<baudrate> [test string]" << endl;
}

int run(int argc, char **argv)
{
enumerate_ports();
  if(argc < 2) {
	  print_usage();
    return 0;
  }

  // Argument 1 is the serial port or enumerate flag
  string port(argv[1]);

  if( port == "-e" ) {
	  enumerate_ports();
	  return 0;
  }
  else if( argc < 3 ) {
	  print_usage();
	  return 1;
  }

  // Argument 2 is the baudrate
  unsigned long baud = 0;
#if defined(WIN32) && !defined(__MINGW32__)
  sscanf_s(argv[2], "%lu", &baud);
#else
  sscanf(argv[2], "%lu", &baud);
#endif

  // port, baudrate, timeout in milliseconds
  serial::Serial my_serial(port,
			   baud,
                           serial::Timeout::simpleTimeout(250),
			   serial::eightbits,
                           serial::parity_none,
                           serial::stopbits_one);

  cout << "Is the serial port open?";
  if(my_serial.isOpen())
    cout << " Yes." << endl;
  else
    cout << " No." << endl;

  while (1) {

	string result = my_serial.read(1);
	if(result.length()==0)
		continue;
	std::vector<uint> bytes(result.begin(), result.end());
	if(bytes[0]==0xFA){

		std::vector<uint> read_bytes;
		read_bytes.resize(4);
		int count_readbytes = 0;
		while(1){
			string data = my_serial.read(1);
			if(data.length()==0) continue;
			std::vector<uint> byte(data.begin(), data.end());
			read_bytes[count_readbytes++] = byte[0];
			if(count_readbytes==4){
				break;
			}
		}

		printf("%.2X %.2X %.2X %.2X %.2X", bytes[0], read_bytes[0], read_bytes[1], read_bytes[2], read_bytes[3]);
		unsigned char value = bytes[0];
		value = value + (unsigned char)read_bytes[0];
                value = value + (unsigned char)read_bytes[1];
                value = value + (unsigned char)read_bytes[2];

                int distance =  (read_bytes[1] << 8) + read_bytes[0];

		printf(" (%.2X) D %.2f", value, distance/1000.0);
		if(read_bytes[2]==0x00) printf(" Normal\n");
                else if(read_bytes[2]==0x01) printf(" Out of range\n");
                else if(read_bytes[2]==0x02) printf(" Signal is to weak\n");
                else if(read_bytes[2]==0x06) printf(" Out of working temperature\n");
		else printf("\n");
	}
  }
  return 0;
}

int main(int argc, char **argv) {
  try {
    return run(argc, argv);
  } catch (exception &e) {
    cerr << "Unhandled Exception: " << e.what() << endl;
  }
}
