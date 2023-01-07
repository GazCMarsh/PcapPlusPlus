#define LOG_MODULE PacketLogModuleSctpLayer

#include "EndianPortable.h"
#include "SctpLayer.h"

#include <iostream>
#include <iomanip>

namespace pcpp
{

/// ~~~~~~~~~
/// SctpLayer
/// ~~~~~~~~~
SctpLayer::SctpLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet) : Layer(data, dataLen, prevLayer, packet)
{
    m_Protocol = SCTP;
}

SctpLayer::SctpLayer()
{
}

void SctpLayer::parseNextLayer()
{
}

uint16_t SctpLayer::getSrcPort() const
{
    return be16toh(getSctpHeader()->portSrc);
}

uint16_t SctpLayer::getDstPort() const
{
    return be16toh(getSctpHeader()->portDst);
}

uint32_t SctpLayer::getVerificationTag() const
{
    return be32toh(getSctpHeader()->verificationTag);
}

uint32_t SctpLayer::getChecksum() const
{
    return be32toh(getSctpHeader()->checksum);
}

void SctpLayer::computeCalculateFields()
{
}

std::string SctpLayer::toString() const
{
    std::string result = "SCTP Layer, ";
    return result;
}

} // namespace pcpp
