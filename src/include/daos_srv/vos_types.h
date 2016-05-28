/**
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * GOVERNMENT LICENSE RIGHTS-OPEN SOURCE SOFTWARE
 * The Government's rights to use, modify, reproduce, release, perform, display,
 * or disclose this software are subject to the terms of the LGPL License as
 * provided in Contract No. B609815.
 * Any reproduction of computer software, computer software documentation, or
 * portions thereof marked with this legend must also reproduce the markings.
 *
 * (C) Copyright 2015, 2016 Intel Corporation.
 */

#ifndef __VOS_TYPES_H__
#define __VOS_TYPES_H__

#include <daos_types.h>

/**
 * pool attributes returned to query
 */
typedef struct {
	/** # of containers in this pool */
	unsigned int		pif_ncos;
	/** # of objects in this pool */
	unsigned int		pif_nobjs;
	/** Total space available */
	daos_size_t		pif_size;
	/** Current vailable space */
	daos_size_t		pif_avail;
	/** TODO */
} vos_pool_info_t;

/**
 * container attributes returned to query
 */
typedef struct {
	/** number of objects */
	unsigned int		pci_nobjs;
	/** used space */
	daos_size_t		pci_used;
	/** TODO */
} vos_co_info_t;

/**
 * object shard metadata stored in VOS
 */
typedef struct {
	/* TODO: metadata for rebuild */
	char			omd_data[64];
} vos_obj_md_t;

/**
 * VOS iterator types
 */
typedef enum {
	VOS_ITER_NONE,
	/** iterate container UUIDs in a pool */
	VOS_ITER_COUUID,
	/** iterate objects within a container */
	VOS_ITER_OBJ,
	/** iterate all d-keys */
	VOS_ITER_DKEY,
	/** iterate all a-keys */
	VOS_ITER_AKEY,
	/** iterate record extents and epoch validities of these extents */
	VOS_ITER_RECX,
} vos_iter_type_t;

/**
 * Parameters for initialising VOS iterator
 */
typedef struct {
	/** pool connection handle or container open handle */
	daos_handle_t		ip_hdl;
	/** Optional, object ID for VOS_ITER_DKEY */
	daos_unit_oid_t		ip_oid;
	/** distribution key for VOS_ITER_AKEY */
	daos_dkey_t		ip_dkey;
	/** attribute key for VOS_ITER_RECX */
	daos_akey_t		ip_akey;
	/** epoch validity range for the iterator */
	daos_epoch_range_t	ip_epr;
} vos_iter_param_t;

/**
 * Returned entry of a VOS iterator
 */
typedef struct {
	/**
	 * Returned epoch range. It is ignored for container iteration for the
	 * time being.
	 */
	daos_epoch_range_t	ie_epr;
	union {
		/** Returned entry for container UUID iterator */
		uuid_t				ie_couuid;
		daos_dkey_t			ie_dkey;
		/** unused for now */
		daos_akey_t			ie_akey;
		struct {
			daos_recx_t		ie_recx;
			/** iovec to return data or ZC address */
			daos_iov_t		ie_iov;
		};
	};
} vos_iter_entry_t;

#endif /* __VOS_TYPES_H__ */
