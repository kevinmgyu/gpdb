//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CDXLRelStats.h
//
//	@doc:
//		Class representing relation stats
//---------------------------------------------------------------------------



#ifndef GPMD_CDXLRelStats_H
#define GPMD_CDXLRelStats_H

#include "gpos/base.h"
#include "gpos/common/CDouble.h"

#include "gpos/string/CWStringDynamic.h"

#include "naucrates/md/IMDRelStats.h"
#include "naucrates/md/CMDIdRelStats.h"

namespace gpdxl
{
class CXMLSerializer;
}

namespace gpmd
{
using namespace gpos;
using namespace gpdxl;

//---------------------------------------------------------------------------
//	@class:
//		CDXLRelStats
//
//	@doc:
//		Class representing relation stats
//
//---------------------------------------------------------------------------
class CDXLRelStats : public IMDRelStats
{
private:
	// memory pool
	CMemoryPool *m_mp;

	// metadata id of the object
	CMDIdRelStats *m_rel_stats_mdid;

	// table name
	CMDName *m_mdname;

	// number of rows
	CDouble m_rows;

	// flag to indicate if input relation is empty
	BOOL m_empty;

	// DXL string for object
	CWStringDynamic *m_dxl_str;

public:
	CDXLRelStats(const CDXLRelStats &) = delete;

	CDXLRelStats(CMemoryPool *mp, CMDIdRelStats *rel_stats_mdid,
				 CMDName *mdname, CDouble rows, BOOL is_empty);

	~CDXLRelStats() override;

	// the metadata id
	IMDId *MDId() const override;

	// relation name
	CMDName Mdname() const override;

	// DXL string representation of cache object
	const CWStringDynamic *GetStrRepr() const override;

	// number of rows
	CDouble Rows() const override;

	// is statistics on an empty input
	BOOL
	IsEmpty() const override
	{
		return m_empty;
	}

	// serialize relation stats in DXL format given a serializer object
	void Serialize(gpdxl::CXMLSerializer *) const override;

#ifdef GPOS_DEBUG
	// debug print of the metadata relation
	void DebugPrint(IOstream &os) const override;
#endif

	// dummy relstats
	static CDXLRelStats *CreateDXLDummyRelStats(CMemoryPool *mp, IMDId *mdid);
};

}  // namespace gpmd



#endif	// !GPMD_CDXLRelStats_H

// EOF
