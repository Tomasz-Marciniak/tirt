//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


//
// Represents a packet in the network.
//
packet Packet
{
    int srcAddr;
    int dstAddr;
    int sessionId;
    int packetId = -1;
    int priority = 0;
    int clazz;
    int payload;
}

