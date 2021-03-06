#include "segment.h"

void segment_to_raw(segment seg, char *raw) {
	raw[0] = seg.soh;
	char* x = (char*) &seg.seqNum;
	raw[1] = *x;
	raw[2] = *(x+1);
	raw[3] = *(x+2);
	raw[4] = *(x+3);
	raw[5] = seg.stx;
	raw[6] = seg.data;
	raw[7] = seg.etx;
	raw[8] = seg.checksum;
	// printf("%c\n", raw[6]);
}

void to_segment(segment* seg, char* raw) {
	seg->soh = *raw;
	seg->seqNum = ((int) *(raw+1)) + ((int) *(raw+2)<<8) + ((int) *(raw+3)<<16) + ((int) *(raw+4)<<24);
	seg->stx =  *(raw+5);
	seg->data = *(raw+6);
	seg->etx = *(raw+7);
	seg->checksum = *(raw+8);
}

void ack_to_raw(packet_ack ack_seg, char* raw) {
	raw[0] = ack_seg.ack;
	char* x = (char*) &ack_seg.nextSeqNum;
	raw[1] = *x;
	raw[2] = *(x+1);
	raw[3] = *(x+2);
	raw[4] = *(x+3);
	raw[5] = ack_seg.windowSize;
	raw[6] = ack_seg.checksum;
}

void to_ack(packet_ack* ack_seg, char* raw) {
	ack_seg->ack = *raw;
	ack_seg->nextSeqNum = ((int) *(raw+1)) + ((int) *(raw+2)<<8) + ((int) *(raw+3)<<16) + ((int) *(raw+4)<<24);
	ack_seg->windowSize = *(raw+5);
	ack_seg->checksum = *(raw+6);	
}

char checksum_str(char* x, int length) {
	int n = 0;
	while(length--) {
		n += (char) *(x++); 
	}
	return (char) n;
}

segment create_segment(int n, int c){
	segment seg;
	seg.soh = 0x1;
	seg.seqNum = n;
	seg.stx = 0x2;
	seg.data = (char)c;
	seg.etx = 0x3;
	seg.checksum = 0x0;
	return seg;
}
segment create_sentinel(){
	segment seg;
	seg.soh = 0xFF;
	seg.seqNum = -1;
	seg.stx = 0xFF;
	seg.data = 0;
	seg.etx = 0xFF;
	seg.checksum = 0xFF;
	return seg;
}