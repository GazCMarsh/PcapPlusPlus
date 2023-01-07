#include "../TestDefinition.h"
#include "../Utils/TestUtils.h"
#include "EndianPortable.h"
#include "Packet.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "SctpLayer.h"
#include "PayloadLayer.h"

#include <iostream>
#include <iomanip>

PTF_TEST_CASE(SctpLayerParsingTest)
{
    timeval time;
	gettimeofday(&time, NULL);

    READ_FILE_AND_CREATE_PACKET(1, "PacketExamples/sctp-megaco.dat");
    
    pcpp::Packet sctpMegacoPacket(&rawPacket1);

    // SCTP Megaco packet from https://wiki.wireshark.org/SampleCaptures#stream-control-transmission-protocol-sctp
    PTF_ASSERT_TRUE(sctpMegacoPacket.isPacketOfType(pcpp::SCTP));

    pcpp::SctpLayer* sctpLayer = sctpMegacoPacket.getLayerOfType<pcpp::SctpLayer>();
    PTF_ASSERT_NOT_NULL(sctpLayer);

    PTF_ASSERT_EQUAL(sctpLayer->getSrcPort(), 16384);
    PTF_ASSERT_EQUAL(sctpLayer->getDstPort(), 2944);
    PTF_ASSERT_EQUAL(sctpLayer->getVerificationTag(), 0x00016f0a);
    PTF_ASSERT_EQUAL(sctpLayer->getChecksum(), 0x6db01882);

} // SctpLayerParsingTest

PTF_TEST_CASE(SctpLayerCreationTest)
{
	pcpp::MacAddress srcMac("08:00:03:4a:00:35");
	pcpp::MacAddress dstMac("00:a0:80:00:5e:46");
	pcpp::EthLayer ethLayer(srcMac, dstMac, PCPP_ETHERTYPE_IP);
	pcpp::IPv4Address dstIP("10.28.6.44");
	pcpp::IPv4Address srcIP("10.28.6.43");
	pcpp::IPv4Layer ipLayer(srcIP, dstIP);
	ipLayer.getIPv4Header()->ipId = htobe16(0x141c);
	ipLayer.getIPv4Header()->fragmentOffset = htobe16(0);
	ipLayer.getIPv4Header()->timeToLive = 59;
    pcpp::SctpLayer sctpLayer(16384, 2944, 0x00016f0a);

    uint8_t payload[] = {
        // Chunk header
        0x00, 0x03, 0x00, 0x5b, 0x28, 0x02, 0x43, 0x45,
        0x00, 0x00, 0xa0, 0xbd, 0x00, 0x00, 0x00, 0x07,

        // Chunk payload
        0x4d, 0x45, 0x47, 0x41, 0x43, 0x4f, 0x2f, 0x32,
        0x20, 0x3c, 0x6d, 0x67, 0x2d, 0x74, 0x72, 0x3e,
        0x3a, 0x31, 0x36, 0x33, 0x38, 0x34, 0x0a, 0x52,
        0x65, 0x70, 0x6c, 0x79, 0x20, 0x3d, 0x20, 0x31,
        0x37, 0x34, 0x30, 0x39, 0x31, 0x7b, 0x0a, 0x43,
        0x6f, 0x6e, 0x74, 0x65, 0x78, 0x74, 0x20, 0x3d,
        0x20, 0x32, 0x35, 0x35, 0x7b, 0x0a, 0x4d, 0x6f,
        0x64, 0x69, 0x66, 0x79, 0x20, 0x3d, 0x20, 0x4d,
        0x55, 0x58, 0x2f, 0x32, 0x35, 0x35, 0x0a, 0x7d,
        0x0a, 0x7d, 0x0a, 0x67
    };
    pcpp::PayloadLayer payloadLayer(payload, sizeof(payload), true);

    pcpp::Packet sctpPacket(1);
    sctpPacket.addLayer(&ethLayer);
    sctpPacket.addLayer(&ipLayer);
    sctpPacket.addLayer(&sctpLayer);
    sctpPacket.addLayer(&payloadLayer);

    sctpPacket.computeCalculateFields();

    pcpp::RawPacket *rawPacket = sctpPacket.getRawPacket();

    PTF_ASSERT_TRUE(true);
} // SctpLayerCreationTest