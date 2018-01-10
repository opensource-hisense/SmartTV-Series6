#ifndef __TEEIMPL_INTERNAL_INCLUDE_H__
#define __TEEIMPL_INTERNAL_INCLUDE_H__

#include <stdio.h>
#include <time.h>

#include <teecommon.h>
#include <drmblackboxtypes.h>

#define UNINIT_TYPE_ID (-1)

// Secure Stop Data
typedef struct {
    int version;
    DRM_BYTE session_id[TEE_SESSION_ID_LEN]; // nonce in license challenge becomes session id
    DRM_BYTE kid[TEE_KEY_ID_LEN]; // content key id
    long start_time; // license arrival time - set once
    long update_time; // last playback-in-progress time - updated miltiple times
    long auth_time; // secure stop authentication (signing) time - set once
    int stopped; // 1 if was normally stopped, 0 - if abnormally shut down
} SECURE_STOP;

typedef struct {
    int id; // sequential session id, for internal reference
    OEM_HAL_KEY_REGISTER_INDEX key_id; // id of the corresponding content decryption key
    SECURE_STOP ss;
    int first_update;
} TEE_SESSION;

// error codes - to be expanded
#define TEE_SUCCESS 0
#define TEE_ERR_FAIL 1
#define TEE_ERR_BUFFERTOOSMALL 2

/*
 * helpers
 */
void * _tee_malloc(size_t size);
void   _tee_free(void * ptr);
void * _tee_memcpy (void * destination, const void * source, size_t num );
void * _tee_memset ( void * ptr, int value, size_t num );
void   _tee_lock();
void   _tee_unlock();

int _print_hex_func(const char * const func, const char * const header, const DRM_BYTE inbuf[], const int inlen);
int _print_bin_func(const char * const func, const char * const header, const DRM_BYTE * const inbuf, const int inlen);
int _print_txt_func(const char * const func, const char * const header, const DRM_BYTE * const inbuf, const int inlen);

time_t _get_drm_time();

int             _der_get_field_enc_len(int const inlen);
int             _der_get_int_field_enc_len(long const value);
DRM_BYTE * _der_write_octets(DRM_BYTE * p, unsigned char * inbuf, int inlen);
DRM_BYTE * _der_write_int(DRM_BYTE * p, long val);

/*
 * tee crypto-objects lifecycle
 */
int    _tee_init(const DRM_BYTE * const inbuf, DRM_DWORD const inlen);
int    _tee_destroy();

/*
 * session lifecycle
 */
int _tee_add_session(const DRM_BYTE * const session_id);
int _tee_cancel_session(const DRM_BYTE * const session_id);
int _tee_bind_license(const DRM_BYTE * const session_id, const DRM_BYTE * const kid);
int _tee_bind_session(const OEM_HAL_KEY_REGISTER_INDEX secKey, const DRM_BYTE * const kid);
int _tee_remove_session(const OEM_HAL_KEY_REGISTER_INDEX key_id);
int _tee_reset_sessions();

/*
 * secure stop lifecycle
 */
int _tee_init_secure_stops(const DRM_BYTE * const inbuf, DRM_DWORD const inlen);
int _tee_get_secure_stops(DRM_BYTE * const outbuf, DRM_DWORD * const outlen);
int _tee_get_secure_stop_ids(DRM_BYTE session_id[][TEE_SESSION_ID_LEN], DRM_DWORD * const outnum);
int _tee_get_secure_stop(const DRM_BYTE * const session_id, DRM_BYTE * const outbuf, DRM_DWORD * const outlen);
int _tee_update_secure_stop(const int key_id, DRM_BOOL * const updated);
int _tee_commit_secure_stop(const DRM_BYTE * const session_id);
int _tee_reset_secure_stops(DRM_DWORD * const outNumRemoved);

/*
 * Secure Store Version Management
 */
int _teeInitStateVersion(); // init state version from persisted value
int _teeGetStateVersion(); // get current version value
int _teeAdvanceStateVersion(); // advance version by 1 and persist it

#ifndef __func__
#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#else
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#endif
#endif

#ifdef TEE_DEBUG
#define _print_bin(x, y, z) _print_bin_func(__func__, x, y, z)
#define _print_hex(x, y, z) _print_hex_func(__func__, x, y, z)
#define _print_txt(x, y, z) _print_txt_func(__func__, x, y, z)
#define _error(fmt, ...) printf("****** (ERR) %s: " fmt, __func__, ##__VA_ARGS__)
#define _info(fmt, ...)  printf("****** (INF) %s: " fmt, __func__, ##__VA_ARGS__)
#define _dbg(fmt, ...)   printf("****** (DBG) %s: " fmt, __func__, ##__VA_ARGS__)
#define _print(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define _print_bin(fmt, args...) ((void)0)
#define _print_hex(fmt, args...) ((void)0)
#define _print_txt(fmt, args...) ((void)0)
#define _error(fmt, args...)     ((void)0)
#define _info(fmt, args...)      ((void)0)
#define _dbg(fmt, args...)       ((void)0)
#define _print(fmt, args...)     ((void)0)
#endif

int _get_hex(const DRM_BYTE inbuf[], const int inlen, char outbuf[]);

#define CHECK(X) if ((status = (X)) != TEE_SUCCESS) { RETURN(status); }


#ifdef TEE_DEBUG
#define RETURN(X) { status = X; _dbg("TEE Failure %d\n", X); goto Exit; }
#else
#define RETURN(X) { status = X; goto Exit; }
#endif

#define FREE(X) if ((X) != NULL) { _tee_free(X); (X) = NULL; }
#define FREE_ON_ERROR(X) if ( (status != TEE_SUCCESS) && ((X) != NULL)) { _tee_free(X); (X) = NULL; }

#define CHECK_NULL(P) if (P == NULL) { _dbg("NULL %s passed\n", #P); RETURN(TEE_ERR_FAIL); }
#define DBG_ENTER _dbg("Enter\n");
#define DBG_EXIT _dbg("Exit %d\n", status);

#define SECURE_STOP_UPDATE_TIME_SEC 600

#if TARGET_LITTLE_ENDIAN
#define INT32(X) ((((X)>>24)&0x000000ff)|(((X)<<8)&0x00ff0000)|(((X)>>8)&0x0000ff00)|(((X)<<24)&0xff000000))
#else
#define INT32(X) (X)
#endif

#endif /* __TEEIMPL_INTERNAL_INCLUDE_H__ */
