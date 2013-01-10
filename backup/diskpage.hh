#ifndef __DISKPAGE_H_
#define __DISKPAGE_H_

class diskPage {
	public:
		long fid, offset;
		char chunk[DPSIZE];
		diskPage* next;
		diskPage(const long& f, const long& ofst): fid(f), offset(ofst) {}

		diskPage(const diskPage& that) {
			fid = that.fid;
			offset = that.offset;
			memcpy (chunk, that.chunk, DPSIZE);
		}

		bool operator== (diskPage& that) {
			return fid == that.fid && offset == that.offset ? true: false;
		}
};

#endif
