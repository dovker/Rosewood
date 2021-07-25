#pragma once

#include "rwpch.h"
#include "Rosewood/Core/Types.h"
#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    template<typename T> 
    struct MessageHeader
    {
        T Id {};
        uint32_t Size = 0;
    }

    template<typename T> 
    struct Message
    {
        MessageHeader<T> Header {};
        std::vector<Byte> Data;

        uint32_t GetSize() { return sizeof(MessageHeader<T>) + Data.size(); }

        friend std::ostream& operator << (std::ostream& os, const Message<T>& msg)
        {
            os << "ID:" << int(msg.Header.Id) << " Size:" << msg.Header.Size;
            return os;
        }

        template<typename DataType>
        friend Message<T>& operator << (Message<T>& msg, const DataType& data)
        {
            RW_CORE_ASSERT(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");
            //TODO: DON'T USE MEMCPY, INSTEAD UTILIZE BIT SHIFTING, FOR ENDIANESS
            size_t i = msg.Data.size();

            msg.Data.resize(msg.Data.size() + sizeof(DataType));

            std::memcpy(msg.Data.data() + i, &data, sizeof(DataType));

            msg.Header.size = msg.size();

            return msg;
        }

        template<typename DataType>
        friend Message<T>& operator >> (Message<T>& msg, DataType& data)
        {
            RW_CORE_ASSERT(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

            size_t i = msg.Data.size() - sizeof(DataType);

            std::memcpy(&data, msg.Data.data() + i, sizeof(DataType));

            msg.Data.resize(i);

            msg.Header.size = msg.size();

            return msg;
        }		        
    }

    template <typename T>
    class Connection;

    template <typename T>
    struct OwnedMessage
    {
        Ref<Connection<T>> Remote = nullptr;
        Message<T> Msg;

        // Again, a friendly string maker
        friend std::ostream& operator<<(std::ostream& os, const OwnedMessage<T>& msg)
        {
            os << msg.Msg;
            return os;
        }
    };	
}