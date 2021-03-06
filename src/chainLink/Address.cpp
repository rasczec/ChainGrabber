// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <tuple>
#include "chainLink/Address.h"
#include "chainLink/Utils.h"
namespace chain_link {

    Address Address::DeSerialize(std::vector<unsigned char>::iterator& data,bool initial) {
        Address addr(initial);
        bitsToInt<uint64_t>(addr.services,std::vector<unsigned char>(data,data+8));
        data+=8;
        if(!initial) {
            bitsToInt<int64_t>(addr.timestamp,std::vector<unsigned char>(data,data+8));
            data+=8;
        }
        for(unsigned char & i : addr.ip) {
            i = *data++;
        }
        bitsToInt<uint16_t>(addr.port,std::vector<unsigned char>(data,data+2),false);
        data+=2;
        return addr;
    }

    std::vector<unsigned char> Address::Serialize() {
        std::vector<unsigned char > result;
        std::vector<unsigned char> val;
        val=intToBits<uint64_t>(services);
        result.insert(result.end(),val.begin(),val.end());
        if(!initial_)
        {
            val=intToBits<int16_t>(timestamp);
            result.insert(result.end(),val.begin(),val.end());
        }
        for(unsigned char i : ip){
            result.push_back(i);
        }
        val=intToBits<uint16_t> (port,false);
        result.insert(result.end(),val.begin(),val.end());
        return result;
    }

    Address::Address(bool initial) {
        this->initial_=initial;
        this->port=0;
        this->services=0;
        this->timestamp=0;
    }

    std::ostream &operator<<(std::ostream &os, const Address &address) {
        char ipstr[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6,address.ip,ipstr,sizeof(ipstr));
        os << "services: " << address.services << " timestamp: " << address.timestamp << " ip: " << ipstr
           << " port: " << address.port << " initial_: " << address.initial_;
        return os;
    }

    bool Address::operator==(const Address &rhs) const {

        bool most= std::tie(services, timestamp,  port, initial_) ==
               std::tie(rhs.services, rhs.timestamp, rhs.port, rhs.initial_) ;

        return most && compareArray<const unsigned char>(ip,16,rhs.ip,16);
    }

    bool Address::operator!=(const Address &rhs) const {
        return !(rhs == *this);
    }


    Address::Address() {
        this->initial_=true;
        this->port=0;
        this->services=0;
        this->timestamp=0;
    }

    Address Address::Copy(const Address& addr) {
        this->initial_=addr.initial_;
        this->port=addr.port;
        this->services=addr.services;
        for(int i=0;i<16;i++) {
            this->ip[i]=addr.ip[i];
        }

    }

    void Address::setIP(int a, int b, int c, int d) {
        ip[0]=ip[1]=ip[2]=ip[3]=ip[4]=ip[5]=ip[6]=ip[7]=ip[8]=ip[9]=0x00;
        ip[10] = 0xff;
        ip[11] = 0xff;
        ip[12]=a;
        ip[13]=b;
        ip[14]=c;
        ip[15]=d;

    }
}
