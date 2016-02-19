#ifndef _LINUX_SEFT_H
#define _LINUX_SEFT_H

#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/pgtable.h>

ssize_t seft_do_io(struct kiocb *iocb, struct inode *inode,
                   struct iov_iter *iter, loff_t pos, get_block_t get_block,
                   dio_iodone_t end_io, int flags);
int seft_clear_blocks(struct inode *, sector_t block, long size);
int seft_fault(struct vm_area_struct *vma, struct vm_fault *vmf,
               get_block_t get_block, dax_iodone_t complete_unwritten);
int __seft_fault(struct vm_area_struct *vma, struct vm_fault *vmf,
                 get_block_t get_block, dax_iodone_t complete_unwritten);

#define seft_mkwrite(vma, vmf, gb, iod)		seft_fault(vma, vmf, gb, iod)
#define __seft_mkwrite(vma, vmf, gb, iod)	__seft_fault(vma, vmf, gb, iod)

int seft_zero_page_range(struct inode *, loff_t from, unsigned len, get_block_t);
int seft_truncate_page(struct inode *, loff_t from, get_block_t);

//#ifdef CONFIG_TRANSPARENT_HUGEPAGE
//int dax_pmd_fault(struct vm_area_struct *, unsigned long addr, pmd_t *,
//				unsigned int flags, get_block_t, dax_iodone_t);
//int __dax_pmd_fault(struct vm_area_struct *, unsigned long addr, pmd_t *,
//				unsigned int flags, get_block_t, dax_iodone_t);
//#else
//static inline int dax_pmd_fault(struct vm_area_struct *vma, unsigned long addr,
//				pmd_t *pmd, unsigned int flags, get_block_t gb,
//				dax_iodone_t di)
//{
//	return VM_FAULT_FALLBACK;
//}
//#define __dax_pmd_fault dax_pmd_fault
//#endif

//int dax_pfn_mkwrite(struct vm_area_struct *, struct vm_fault *);

static inline bool vma_is_seft(struct vm_area_struct *vma)
{
        printk(KERN_NOTICE "SEFT: vma_is_seft: entering");
	return vma->vm_file && IS_SEFT(vma->vm_file->f_mapping->host);
}

#endif
