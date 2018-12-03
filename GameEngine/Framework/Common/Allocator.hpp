#include <cstddef>
#include <cstdint>


/*
 基于块链（block chain）的内存管理方法
 提高程序在CPU端的执行效率的一个重要手段，就是要减少系统调用。在程序初始化阶段就一次申领所需的资源，然后自己内部进行分配管理
*/



namespace My {

    struct BlockHeader {
        // union-ed with data
        BlockHeader* pNext;
    };

    struct PageHeader {
        PageHeader* pNext;
        BlockHeader* Blocks() {
                return reinterpret_cast<BlockHeader*>(this + 1);
        }
    };

    class Allocator {
        public:
                // debug patterns
                static const uint8_t PATTERN_ALIGN = 0xFC;
                static const uint8_t PATTERN_ALLOC = 0xFD;
                static const uint8_t PATTERN_FREE  = 0xFE;

                Allocator(size_t data_size, size_t page_size, size_t alignment);
                ~Allocator();

                // resets the allocator to a new configuration
                void Reset(size_t data_size, size_t page_size, size_t alignment);

                // alloc and free blocks
                void* Allocate();
                void  Free(void* p);
                void  FreeAll();
        private:
#if defined(_DEBUG)
                // fill a free page with debug patterns
                void FillFreePage(PageHeader* pPage);

                // fill a block with debug patterns
                void FillFreeBlock(BlockHeader* pBlock);

                // fill an allocated block with debug patterns
                void FillAllocatedBlock(BlockHeader* pBlock);
#endif

                // gets the next block
                BlockHeader* NextBlock(BlockHeader* pBlock);

                // the page list
                PageHeader* m_pPageList;

                // the free block list
                BlockHeader* m_pFreeList;

                size_t      m_szDataSize;
                size_t      m_szPageSize;
                size_t      m_szAlignmentSize;
                size_t      m_szBlockSize;
                uint32_t    m_nBlocksPerPage;

                // statistics
                uint32_t    m_nPages;
                uint32_t    m_nBlocks;
                uint32_t    m_nFreeBlocks;

                // disable copy & assignment
                Allocator(const Allocator& clone);
                Allocator &operator=(const Allocator &rhs);
    };
}