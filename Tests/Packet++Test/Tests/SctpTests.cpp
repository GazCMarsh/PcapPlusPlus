#include "../TestDefinition.h"
#include "../Utils/TestUtils.h"
#include "Packet.h"
#include "SctpLayer.h"

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

    PTF_ASSERT_EQUAL(sctpLayer->getSrcPort(), 2944);
    PTF_ASSERT_EQUAL(sctpLayer->getDstPort(), 16384);
    PTF_ASSERT_EQUAL(sctpLayer->getVerificationTag(), 0x21441523);
    PTF_ASSERT_EQUAL(sctpLayer->getChecksum(), 0x2bf2024e);

} // SctpLayerParsingTest
