/**
  @file |FILE|

  (c) 2009 WSI-RA University of Tuebingen

  @author Karsten Bohlmann
  @email bohlmann@gmail.com

  @date Sun Apr 5 2009
*/
#include <unistd.h>
#include <stdio.h>
#include "ublox.h"
#include "ubloxobservations.h"
#include "ubloxmsg.h"
#include "ecefgk.h"

namespace GPS {

    Ublox::Ublox(const string& serialDevice)
        : SerialGps(serialDevice,UBLOX_BAUDRATE)
    {

    }


    Ublox::~Ublox()
    {
        Disconnect();
    }


    void Ublox::ResetUbx()
    {
        bool status;
        char Ubx_reset[] = "\xB5\x62\x06\x04\x04\x00\xFF\x07\x00\x00\x14\x75"; // UBX forced (watchdog) reset with coldstart (change to hotstart)
        status = write(mSerialFd, &Ubx_reset,12);
    }

    void Ublox::DisableUbxMsgs()
    {
        bool status;
        char Config_usb[] = "\xB5\x62\x06\x00\x14\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00\x00\x00\x00\x00\x23\xAE";  // USB in: UBX+NMEA; USB out: UBX+NMEA
        char Config_posecef[] = "\xB5\x62\x06\x01\x08\x00\x01\x01\x00\x00\x00\x00\x00\x00\x11\xB2"; //NAV-POSECEF disable
        char Config_sol[] = "\xB5\x62\x06\x01\x08\x00\x01\x06\x00\x00\x00\x00\x00\x00\x16\xD5";   // NAV-SOL disable
        char Config_llh[] = "\xB5\x62\x06\x01\x08\x00\x01\x02\x00\x00\x00\x00\x00\x00\x12\xB9";   // NAV-POSLLH disable
        char Config_velned[] = "\xB5\x62\x06\x01\x08\x00\x01\x12\x00\x00\x00\x00\x00\x00\x22\x29";   // NAV-VELNED disable
        char Config_dop[] = "\xB5\x62\x06\x01\x08\x00\x01\x04\x00\x00\x00\x00\x00\x00\x14\xC7";   // NAV-DOP disable
        char Config_status[] = "\xB5\x62\x06\x01\x08\x00\x01\x03\x00\x00\x00\x00\x00\x00\x13\xC0";   // NAV-STATUS disable
        char Config_svinfo[] = "\xB5\x62\x06\x01\x08\x00\x01\x30\x00\x00\x00\x00\x00\x00\x40\xFB";   // NAV-SVINFO disable
        char Config_raw[] = "\xB5\x62\x06\x01\x08\x00\x02\x10\x00\x00\x00\x00\x00\x00\x21\x23";   // RXM-RAW disable
        char Config_sfrb[] = "\xB5\x62\x06\x01\x08\x00\x02\x11\x00\x00\x00\x00\x00\x00\x22\x2A";   // RXM-SFRB disable
        char Config_save[] = "\xB5\x62\x06\x09\x0D\x00\x00\x00\x00\x00\xFF\xFF\x00\x00\x00\x00\x00\x00\x07\x21\xAF";// save Ublox Config
        status = write(mSerialFd, &Config_usb, 28);
        status = write(mSerialFd, &Config_posecef, 16);
        status = write(mSerialFd, &Config_sol, 16);
        status = write(mSerialFd, &Config_llh, 16);
        status = write(mSerialFd, &Config_velned, 16);
        status = write(mSerialFd, &Config_dop, 16);
        status = write(mSerialFd, &Config_status, 16);
        status = write(mSerialFd, &Config_svinfo, 16);
        status = write(mSerialFd, &Config_raw, 16);
        status = write(mSerialFd, &Config_sfrb, 16);
        status = write(mSerialFd, &Config_save, 21);
    }

    bool Ublox::EnableUbxMsgs()
    {
        bool status;
        char Config_usb[] = "\xB5\x62\x06\x00\x14\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x01\x00\x00\x00\x00\x00\x21\xA2";  // USB in: UBX+NMEA; USB out: UBX
        char Config_posecef[] = "\xB5\x62\x06\x01\x08\x00\x01\x01\x01\x01\x01\x01\x01\x00\x16\xC6"; //NAV-POSECEF enable
        char Config_sol[] = "\xB5\x62\x06\x01\x08\x00\x01\x06\x01\x01\x01\x01\x01\x00\x1B\xE9";   // NAV-SOL enable
        char Config_llh[] = "\xB5\x62\x06\x01\x08\x00\x01\x02\x01\x01\x01\x01\x01\x00\x17\xCD";   // NAV-POSLLH enable
        char Config_velned[] = "\xB5\x62\x06\x01\x08\x00\x01\x12\x01\x01\x01\x01\x01\x00\x27\x3D";   // NAV-VELNED enable
        char Config_dop[] = "\xB5\x62\x06\x01\x08\x00\x01\x04\x01\x01\x01\x01\x01\x00\x19\xDB";   // NAV-DOP enable
        char Config_status[] = "\xB5\x62\x06\x01\x08\x00\x01\x03\x01\x01\x01\x01\x01\x00\x18\xD4";   // NAV-STATUS enable
        char Config_svinfo[] = "\xB5\x62\x06\x01\x08\x00\x01\x30\x01\x01\x01\x01\x01\x00\x45\x0F";   // NAV-SVINFO enable
        char Config_raw[] = "\xB5\x62\x06\x01\x08\x00\x02\x10\x01\x01\x01\x01\x01\x00\x26\x37";   // RXM-RAW enable
        char Config_sfrb[] = "\xB5\x62\x06\x01\x08\x00\x02\x11\x01\x01\x01\x01\x01\x00\x27\x3E";   // RXM-SFRB enable
        char Config_save[] = "\xB5\x62\x06\x09\x0D\x00\x00\x00\x00\x00\xFF\xFF\x00\x00\x00\x00\x00\x00\x07\x21\xAF";// save Ublox Config
        status = write(mSerialFd, &Config_usb, 28);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_posecef, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_sol, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_llh, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_velned, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_dop, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_status, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_svinfo, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_raw, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_sfrb, 16);
        if (status<=0) return false;
        status = write(mSerialFd, &Config_save, 21);
        if (status<=0) return false;

        return true;
    }

    bool Ublox::Update()
    {
        bool  status;         // Status of port read.
        char  readChar;         // One byte received from the port.
        bool  start;          // Has the start of an UBX sentence been read?
        unsigned int numBytesRead;       // Number of bytes read from each call to ReadFile().
        unsigned int count;       // Number of bytes read for a sentence.
        // for the UBX Protocol
        unsigned char Binary_Class;   // UBX Message-class
        unsigned char Binary_ID;    // UBX Message-ID

        unsigned char Binary_Lenght[2]; // Length of the message (Bin)
        unsigned int Binary_Lenght_out; // Length of the message

        unsigned char Binary_CKA;   // UBX CKA
        unsigned char Binary_CKB;   // UBX CKA
        unsigned char temp;       // UBX temp

        bool check_ok;          // Checksum

        char  sentence[1024];
        unsigned char sentence2[1024];

        double PosGK[3];

        start = false;
        numBytesRead = read (mSerialFd, &readChar, 1);
        //    cout<<"1 ReadChar: "<<hex<<(int)readChar<<endl;
        if (numBytesRead!=1 ) {
            cout << "timeout UBLOX serial port \n";
            start = false;
        } else {
            if (readChar == '\xB5' && start == false)
            {  // sync char 1
                numBytesRead = read (mSerialFd, &readChar, 1);
                if (readChar == '\x62' && start == false) {   // sync char 2
                    start = true;
                    count = 0;
                }
            }
            else
            {
                cout << "faield to read valid UBX packet"<< endl;
                return false;
            }
            if (start == true) {
                // A sentence is currently being read; add the character read
                // from the com port.
                if (count == 0)
                {
                    numBytesRead = read (mSerialFd, &readChar, 1);
                    Binary_Class = readChar;

                    numBytesRead = read (mSerialFd, &readChar, 1);
                    Binary_ID = readChar;

                    numBytesRead = read (mSerialFd, &readChar, 1);
                    Binary_Lenght[0] = readChar;
                    numBytesRead = read (mSerialFd, &readChar, 1);
                    Binary_Lenght[1] = readChar;

                    Binary_Lenght_out = (unsigned char) Binary_Lenght[0] + (unsigned char) Binary_Lenght[1] *256;

                }

                Binary_CKA = Binary_Class  + Binary_ID + (unsigned char) Binary_Lenght[0] + (unsigned char) Binary_Lenght[1];
                Binary_CKB = 4*Binary_Class  + 3*Binary_ID + 2*(unsigned char) Binary_Lenght[0] + (unsigned char) Binary_Lenght[1];

                if(Binary_Lenght_out>1023)
                {
                    cout<<(this->mSerialDevice)<<": Incredible Binary_Length_out "<<endl;
                    check_ok = false;
                    return false;
                }

                for (count = 0; count < Binary_Lenght_out; count++)
                {
                    numBytesRead = read (mSerialFd, &readChar, 1);
                    sentence[count] = readChar;
                    sentence2[count] = readChar;
                    Binary_CKA = Binary_CKA + (unsigned char) readChar;     // 8-Bit Fletcher Algorithm
                    Binary_CKB = Binary_CKB + Binary_CKA;
                }

                numBytesRead = read (mSerialFd, &readChar, 1);  // read CKA
                temp = (unsigned char) readChar;
                check_ok = false;

                if (Binary_CKA == temp)
                {
                    numBytesRead = read (mSerialFd, &readChar, 1);  // read CKB

                    if (Binary_CKB == (unsigned char) readChar)
                    {
                        check_ok = true;
                    }
                }
                if(!check_ok)
                {
                    cout<<"Fletcher Check failed...."<<endl;
                    return false;
                }
                //          TimeStamp ts;

                if((Binary_Class == '\x01') && (check_ok == true))
                {
                    //           cout<<"msg:"<<(int)Binary_Class<<" "<<(int)Binary_ID<<endl;
                    if (Binary_ID == '\x06')
                    {

                        NAVSOL.read(sentence);
                    }
                }

                if((Binary_Class == '\x01') && (check_ok == true))
                {
                    //           cout<<"msg:"<<(int)Binary_Class<<" "<<(int)Binary_ID<<endl;
                    if (Binary_ID == '\x02')
                    {
                        NAVPOSLLH.read(sentence);
                    }
                }

                if((Binary_Class == '\x01') && (check_ok == true))
                {
                    //           cout<<"msg:"<<(int)Binary_Class<<" "<<(int)Binary_ID<<endl;
                    if (Binary_ID == '\x12')
                    {
                        NAVVELNED.read(sentence);
                    }
                }

                if((Binary_Class == '\x01') && (check_ok == true))
                {
                    //           cout<<"msg:"<<(int)Binary_Class<<" "<<(int)Binary_ID<<endl;
                    if (Binary_ID == '\x04')
                    {
                        NAVDOP.read(sentence);
                    }
                }

                if((Binary_Class == '\x01') && (check_ok == true))
                {
                    //           cout<<"msg:"<<(int)Binary_Class<<" "<<(int)Binary_ID<<endl;
                    if (Binary_ID == '\x03')
                    {
                        NAVSTATUS.read(sentence);
                    }
                }

            }
            start = false;
            sentence[count] = '\0';

        }
        // markStopped();
        // success
        return true;
    }
}
