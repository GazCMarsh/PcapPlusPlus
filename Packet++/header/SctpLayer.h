#ifndef PACKETPP_SCTP_LAYER
#define PACKETPP_SCTP_LAYER

#include "Layer.h"

/// @file

/**
 * \namespace pcpp
 * \brief The main namespace for the PcapPlusPlus lib
 */
namespace pcpp
{
    /**
     * @struct sctphdr
     * Represents a common SCTP protocol header
     */
#pragma pack(push,1)
    struct sctphdr
    {
        uint16_t portSrc;
        uint16_t portDst;
        uint32_t verificationTag;
        uint32_t checksum;
    };
#pragma pack(pop)

    /**
     * @class SctpLayer
     * Represents a SCTP (Stream Control Transmission Protocol) protocol layer
     */
    class SctpLayer : public Layer
    {
    public:
        /**
         * A constructor that creates the layer from an existing packet's raw data
         * @param[in] data A pointer to the raw data (will be cast to @ref sctphdr)
         * @param[in] dataLen Size of the data in bytes
         * @param[in] prevLayer A pointer to the previous layer
         * @param[in] packet A pointer to the Packet instance where layer will be stored
         */
        SctpLayer(uint8_t* data, size_t dataLen, Layer* prevLayer, Packet* packet);

        /**
         * A constructor that allocates a new SCTP header
         */
        SctpLayer();

        ~SctpLayer() {}

        /**
         * Get a pointer to the SCTP header.  Note that this points directly
         * to the data, so every change will change the actual packet data.
         * @return A pointer to the @ref sctphdr
         */
        sctphdr* getSctpHeader() const { return (sctphdr*)m_Data; }

        /**
         * @return SCTP source port
         */
        uint16_t getSrcPort() const;

        /**
         * @return SCTP destination port
         */
        uint16_t getDstPort() const;

        /**
         * @return SCTP verification tag
         */
        uint32_t getVerificationTag() const;

        /**
         * @return SCTP checksum
         */
        uint32_t getChecksum() const;

        /**
         * Static method to validate input data
         * @param[in] data Pointer to the beginning of a byte stream
         * @param[in] dataLen The length of the byte stream
         * @return True if the data is valid and can represent an SCTP packet
         */
        static inline bool isDataValid(const uint8_t* data, size_t dataLen);

        // abstract method overrides

        /**
         * Currently a no-op
         */
        void parseNextLayer();

        /**
         * @return size of @ref sctphdr
         */
        size_t getHeaderLen() const { return 12; }

        /**
         * Calculate @ref checksum field
         */
        void computeCalculateFields();

        std::string toString() const;

        OsiModelLayer getOsiModelLayer() const { return OsiModelTransportLayer; }
    };

    // implementation of inline methods

    bool SctpLayer::isDataValid(const uint8_t* data, size_t dataLen)
    {
        return dataLen >= 12;
    }
} // namespace pcpp

#endif /* PACKETPP_SCTP_LAYER */
