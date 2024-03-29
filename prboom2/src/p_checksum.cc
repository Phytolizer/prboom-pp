#include <cerrno>
#include <cstdio>
#include <cstdlib> /* exit(), atexit() */
#include <cstring>

#include "doomstat.hh" /* players{,ingame} */
#include "lprintf.hh"
#include "md5.hh"
#include "p_checksum.hh"

/* forward decls */
static void p_checksum_cleanup();
void checksum_gamestate(int tic);

/* vars */
static void p_checksum_nop(int /* tic */)
{
} /* do nothing */
void (*P_Checksum)(int) = p_checksum_nop;

/*
 * P_RecordChecksum
 * sets up the file and function pointers to write out checksum data
 */
static FILE *outfile = nullptr;
static struct MD5Context md5global;

void P_RecordChecksum(const char *file)
{
    size_t fnsize;

    fnsize = strlen(file);

    /* special case: write to stdout */
    if (0 == strncmp("-", file, MIN(1, fnsize)))
    {
        outfile = stdout;
    }
    else
    {
        outfile = fopen(file, "wb");
        if (nullptr == outfile)
        {
            I_Error(
                "cannot open %s for writing checksum:\n%s\n", file,
                strerror(errno)
            );
        }
        atexit(p_checksum_cleanup);
    }

    MD5Init(&md5global);

    P_Checksum = checksum_gamestate;
}

void P_ChecksumFinal()
{
    int i;
    unsigned char digest[16];

    if (!outfile)
    {
        return;
    }

    MD5Final(digest, &md5global);
    fprintf(outfile, "final: ");
    for (i = 0; i < 16; i++)
    {
        fprintf(outfile, "%x", digest[i]);
    }
    fprintf(outfile, "\n");
    MD5Init(&md5global);
}

static void p_checksum_cleanup()
{
    if (outfile && (outfile != stdout))
    {
        fclose(outfile);
    }
}

/*
 * runs on each tic when recording checksums
 */
void checksum_gamestate(int tic)
{
    int i;
    struct MD5Context md5ctx;
    unsigned char digest[16];
    char buffer[2048];

    fprintf(outfile, "%6d, ", tic);

    /* based on "ArchivePlayers" */
    MD5Init(&md5ctx);
    for (i = 0; i < MAXPLAYERS; i++)
    {
        if (!playeringame[i])
        {
            continue;
        }

        doom_snprintf(buffer, sizeof(buffer), "%d", players[i].health);
        buffer[sizeof(buffer) - 1] = 0;

        MD5Update(&md5ctx, (md5byte const *)&buffer, strlen(buffer));
    }
    MD5Final(digest, &md5ctx);
    for (i = 0; i < 16; i++)
    {
        MD5Update(&md5global, (md5byte const *)&digest[i], sizeof(digest[i]));
        fprintf(outfile, "%x", digest[i]);
    }

    fprintf(outfile, "\n");
}
