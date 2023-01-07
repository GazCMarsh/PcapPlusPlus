#define LOG_MODULE PacketLogModuleSctpLayer

#include "EndianPortable.h"
#include "SctpLayer.h"

#include <string.h>

namespace pcpp
{

/// ~~~~~~~~~
/// SctpLayer
/// ~~~~~~~~~
SctpLayer::SctpLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet) : Layer(data, dataLen, prevLayer, packet)
{
    m_Protocol = SCTP;
}

SctpLayer::SctpLayer(uint16_t portSrc, uint16_t portDst, uint32_t verificationTag)
{
    initLayer();
    getSctpHeader()->portSrc = htobe16(portSrc);
    getSctpHeader()->portDst = htobe16(portDst);
    getSctpHeader()->verificationTag = htobe32(verificationTag);
}

SctpLayer::SctpLayer()
{
    initLayer();
}

SctpLayer::SctpLayer(const SctpLayer& other)
{
    copyLayerData(other);
}

SctpLayer& SctpLayer::operator=(const SctpLayer& other)
{
    Layer::operator=(other);
    copyLayerData(other);
    
    return *this;
}

void SctpLayer::initLayer()
{
    m_DataLen = sizeof(sctphdr);
    m_Data = new uint8_t[m_DataLen];
    memset(m_Data, 0, m_DataLen);
    m_Protocol = SCTP;
}

void SctpLayer::copyLayerData(const SctpLayer& other)
{
    // Placeholder for now - real work currently done by Layer
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
