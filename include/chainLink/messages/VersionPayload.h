// Copyright (c) 2019 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CHAIN_GRABBER_VERSIONPAYLOAD_H
#define CHAIN_GRABBER_VERSIONPAYLOAD_H

#include <ostream>
#include "chainLink/messages/Payload.h"
#include "chainLink/Address.h"
namespace chain_link::messages {
    class Version : public Payload {
    public:
    private:


    public:
        std::vector<unsigned char> Serialize() override;
        int32_t version;
        uint64_t services;
        int64_t timestamp;
        Address addr_to;
        Address addr_from;
        uint64_t nonce;
        std::string user_agent;
        int32_t start_height;
        bool relay;


        static Version Deserialize(std::vector<unsigned char>::iterator& data);

        friend std::ostream &operator<<(std::ostream &os, const Version &version);

        bool operator==(const Version &rhs) const;

        bool operator!=(const Version &rhs) const;

        Version *Clone() override;
    };
}
#endif //CHAIN_GRABBER_VERSIONPAYLOAD_H
