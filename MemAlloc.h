#ifndef MEMALLOC_H
#define MEMALLOC_H

#define mem_free(a) free(a)
#define mem_alloc(a) malloc(a)

#if defined(_WINDOWS)
#	include <new.h>
#else
#	include <new>
#endif

#if defined(_WINDOWS)
#	pragma warning(disable:4018)
#endif

#if defined(_LINUX) || defined(_MAC)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wsign-compare"
#endif

template <typename T, int SizeBlock = 256>
class MemAlloc
{
	struct MemCell
	{
		MemCell():IsFree(true)
		{
		}
		bool IsFree;
		T data;
	};
	struct MemBlock
	{
		MemCell * mem;
		unsigned int size;
		unsigned int pos;
	};
	MemBlock * memblocks;
	int NumCurBlock;
	int NumCurBlockCount;
public:
	MemAlloc():memblocks(NULL), NumCurBlock(0), NumCurBlockCount(0)
	{
		//printf("MemAlloc()\n");
		AllocBlock(sizeof(MemCell) * 256);
	}

	MemAlloc(const MemAlloc & al)
	{
		//printf("MemAlloc()\n");
		this->NumCurBlock = al.NumCurBlock;
		this->NumCurBlockCount = al.NumCurBlockCount;
		this->memblocks = new MemBlock[this->NumCurBlockCount];
		//SX_DBG_NEW(this->NumCurBlockCount * sizeof(MemBlock), this->memblocks);
			for(int i = 0; i < this->NumCurBlockCount; i++)
			{
				this->memblocks[i].size = al.memblocks[i].size;
				this->memblocks[i].pos = al.memblocks[i].pos;
				this->memblocks[i].mem = (MemCell*)malloc(al.memblocks[i].size);
				//SX_DBG_NEW(al.memblocks[i].size, this->memblocks[i].mem);
					for(int j = 0; j < al.memblocks[i].size / sizeof(MemCell); j++)
					{
						this->memblocks[i].mem[j].IsFree = al.memblocks[i].mem[j].IsFree;
						this->memblocks[i].mem[j].data = al.memblocks[i].mem[j].data;
					}
				//SX_SAFE_DELETE_A(memblocks[i].mem);
			}
	}

	MemAlloc & operator=(const MemAlloc & al)
	{//clear mem
			for(int i = 0; i < this->NumCurBlockCount; i++)
			{
				if(this->memblocks[i].mem)
				{
					for(int j = 0; j < this->memblocks[i].size / sizeof(MemCell); j++)
					{
						if(!this->memblocks[i].mem[j].IsFree)
						{
							this->memblocks[i].mem[j].data.~T();
						}

					}
					mem_free(this->memblocks[i].mem);
				}
				//SX_SAFE_DELETE_A(this->memblocks[i].mem);
			}
		mem_delete_a(this->memblocks);

		this->NumCurBlock = al.NumCurBlock;
		this->NumCurBlockCount = al.NumCurBlockCount;
		this->memblocks = new MemBlock[this->NumCurBlockCount];
		//SX_DBG_NEW(this->NumCurBlockCount * sizeof(MemBlock), this->memblocks);
			for(int i = 0; i < this->NumCurBlockCount; i++)
			{
				this->memblocks[i].size = al.memblocks[i].size;
				this->memblocks[i].pos = al.memblocks[i].pos;
				
					if(!this->memblocks[i].size)
					{
						this->memblocks[i].mem = NULL;
					}
					else
					{
						this->memblocks[i].mem = new MemCell[al.memblocks[i].size / sizeof(MemCell)];
						//SX_DBG_NEW(al.memblocks[i].size, this->memblocks[i].mem);
						for(int j = 0; (unsigned int)j < al.memblocks[i].size / sizeof(MemCell); j++)
							{
								this->memblocks[i].mem[j].IsFree = al.memblocks[i].mem[j].IsFree;
								if(!al.memblocks[i].mem[j].IsFree)
								{
									this->memblocks[i].mem[j].data = al.memblocks[i].mem[j].data;
								}
							}
					}
				//SX_SAFE_DELETE_A(memblocks[i].mem);
			}
		return(*this);
	}

	~MemAlloc()
	{
		//printf("~MemAlloc()\n");
			for(int i = 0; i < this->NumCurBlockCount; i++)
			{
					if(this->memblocks[i].mem)
					{
							for(int j = 0; j < this->memblocks[i].size / sizeof(MemCell); j++)
							{
									if(!this->memblocks[i].mem[j].IsFree)
									{
										this->memblocks[i].mem[j].data.~T();
									}

							}
						mem_free(this->memblocks[i].mem);
					}
				//SX_SAFE_DELETE_A(this->memblocks[i].mem);
			}
		mem_delete_a(this->memblocks);
		this->NumCurBlockCount = 0;
		this->NumCurBlock = 0;
	}

	void clear()
	{
			for(int i = 0; i < this->NumCurBlockCount; i++)
			{
					if(this->memblocks[i].mem)
					{
							for(int j = 0; j < this->memblocks[i].size / sizeof(MemCell); j++)
							{
									if(!this->memblocks[i].mem[j].IsFree)
									{
										(&(this->memblocks[i].mem[j].data))->~T();
									}
							}
						mem_free(this->memblocks[i].mem);
					}
				//SX_SAFE_DELETE_A(this->memblocks[i].mem);
			}
		mem_delete_a(this->memblocks);
		this->NumCurBlockCount = 0;
		this->NumCurBlock = 0;
		AllocBlock(sizeof(MemCell) * 256);
	}

	void AllocBlock(int size)
	{
		MemBlock * tmpMB = this->memblocks;

		NumCurBlockCount += 256;

		this->memblocks = new MemBlock[NumCurBlockCount];
		//SX_DBG_NEW(this->NumCurBlockCount * sizeof(MemBlock), this->memblocks);
			if(tmpMB)
			{
				memcpy(this->memblocks, tmpMB, (NumCurBlockCount - 256) * sizeof(MemBlock));
			}
		memset(this->memblocks + (NumCurBlockCount - 256), 0, 256 * sizeof(MemBlock));
		mem_delete_a(tmpMB);

			if(!this->memblocks[NumCurBlock].mem)
			{
				this->memblocks[NumCurBlock].mem = (MemCell*)mem_alloc(size);
				//SX_DBG_NEW(size * sizeof(MemCell), this->memblocks[NumCurBlock].mem);
					for(int i = 0; i < size / sizeof(MemCell); i++)
					{
						this->memblocks[NumCurBlock].mem[i].IsFree = true;
					}
				this->memblocks[NumCurBlock].size = size;
			}
	}

	T * Alloc()
	{
		T * tmpNewNode = NULL;
			if(!NumCurBlockCount)
			{
				AllocBlock(SizeBlock);
			}
			if(this->memblocks[NumCurBlock].pos + sizeof(MemCell) < this->memblocks[NumCurBlock].size)
			{
					if(((MemCell*)((uintptr_t)this->memblocks[NumCurBlock].mem + this->memblocks[NumCurBlock].pos))->IsFree)
					{
						((MemCell*)((uintptr_t)this->memblocks[NumCurBlock].mem + this->memblocks[NumCurBlock].pos))->IsFree = false;
						tmpNewNode = &(((MemCell*)((uintptr_t)this->memblocks[NumCurBlock].mem + this->memblocks[NumCurBlock].pos))->data);
						this->memblocks[NumCurBlock].pos += sizeof(MemCell);
					}
					else // find next free cell
					{
							while(true)
							{
								this->memblocks[NumCurBlock].pos += sizeof(MemCell);
									if(this->memblocks[NumCurBlock].pos + sizeof(MemCell) < this->memblocks[NumCurBlock].size)
									{
											if(((MemCell*)((uintptr_t)this->memblocks[NumCurBlock].mem + this->memblocks[NumCurBlock].pos))->IsFree)
											{
												tmpNewNode = &(((MemCell*)((uintptr_t)this->memblocks[NumCurBlock].mem + this->memblocks[NumCurBlock].pos))->data);
												this->memblocks[NumCurBlock].pos += sizeof(MemCell);
												break;
											}
									}
									else
									{
										//next block
										NumCurBlock++;
											if(NumCurBlock < NumCurBlockCount)
											{
													if(!this->memblocks[NumCurBlock].mem)
													{
														this->memblocks[NumCurBlock].mem = (MemCell*)mem_alloc(sizeof(MemCell)* SizeBlock);
															for(int i = 0; i < SizeBlock; i++)
															{
																this->memblocks[NumCurBlock].mem[i].IsFree = true;
															}
														//SX_DBG_NEW(SizeBlock * sizeof(MemCell), this->memblocks[NumCurBlock].mem);
														this->memblocks[NumCurBlock].size = sizeof(MemCell) * SizeBlock;
														tmpNewNode = Alloc();
													}
											}
											else
											{
												AllocBlock(SizeBlock);
												tmpNewNode = Alloc();
												break;
											}
									}
							}
					}
			}
			else
			{
				NumCurBlock++;
					if(NumCurBlock < NumCurBlockCount)
					{
							if(!this->memblocks[NumCurBlock].mem)
							{
								//this->memblocks[NumCurBlock].mem = new MemCell[SizeBlock];
								this->memblocks[NumCurBlock].mem = (MemCell*)mem_alloc(sizeof(MemCell)* SizeBlock);
								//SX_DBG_NEW(SizeBlock * sizeof(MemCell), this->memblocks[NumCurBlock].mem);
									for(int i = 0; i < SizeBlock; i++)
									{
										this->memblocks[NumCurBlock].mem[i].IsFree = true;
									}
								this->memblocks[NumCurBlock].size = sizeof(MemCell) * SizeBlock;
							}
						tmpNewNode = Alloc();
					}
					else
					{
						AllocBlock(SizeBlock);
						tmpNewNode = Alloc();
					}
			}
		tmpNewNode = new (tmpNewNode) T;
		return(tmpNewNode);
	}

	void Delete(T * pointer)
	{
		//find cell
		//mark cell as free
		
			for(int i = 0; i < NumCurBlockCount; i++)
			{
					if((int)pointer >= (int)memblocks[i].mem && (int)pointer < (int)memblocks[i].mem + (int)memblocks[i].pos)
					{
							for(int j = 0; j < (int)memblocks[i].size / sizeof(MemCell); j++)
							{
									if(pointer == &(memblocks[i].mem[j].data))
									{
										//founded
										//_asm{int 3};
										pointer->~T();
										memblocks[i].mem[j].IsFree = true;
										memblocks[i].pos = min((unsigned int)j * sizeof(MemCell), memblocks[i].pos);
										NumCurBlock = NumCurBlock > i ? NumCurBlock : i;
									}
							}
					}
			}
	}
};

#if defined(_WINDOWS)
#	pragma warning(default:4018)
#endif
#if defined(_LINUX) || defined(_MAC)
#	pragma GCC diagnostic pop
#endif

#endif