/**********************************************************
 * This file has been automatically created by "typemaker2"
 * from the file "ct_keyinfo.xml".
 * Please do not edit this file, all changes will be lost.
 * Better edit the mentioned source file instead.
 **********************************************************/

#ifndef GWEN_CRYPT_TOKEN_KEYINFO_CT_KEYINFO_H
#define GWEN_CRYPT_TOKEN_KEYINFO_CT_KEYINFO_H


#ifdef __cplusplus
extern "C" {
#endif

/** @page P_GWEN_CRYPT_TOKEN_KEYINFO Structure GWEN_CRYPT_TOKEN_KEYINFO
<p>This page describes the properties of GWEN_CRYPT_TOKEN_KEYINFO.</p>



<h1>GWEN_CRYPT_TOKEN_KEYINFO</h1>



@anchor GWEN_CRYPT_TOKEN_KEYINFO_id
<h2>id</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetId(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetId().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_keyDescr
<h2>keyDescr</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetKeyDescr(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetKeyDescr().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_flags
<h2>flags</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetFlags(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetFlags().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_keySize
<h2>keySize</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetKeySize(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetKeySize().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_cryptAlgoId
<h2>cryptAlgoId</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetCryptAlgoId(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetCryptAlgoId().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_modulus
<h2>modulus</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetModulus(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetModulus().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_exponent
<h2>exponent</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetExponent(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetExponent().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_keyNumber
<h2>keyNumber</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetKeyNumber(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetKeyNumber().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_keyVersion
<h2>keyVersion</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetKeyVersion(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetKeyVersion().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_signCounter
<h2>signCounter</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetSignCounter(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetSignCounter().</p>


@anchor GWEN_CRYPT_TOKEN_KEYINFO_certificate
<h2>certificate</h2>

<p>Set this property with @ref GWEN_Crypt_Token_KeyInfo_SetCertificate(), get it with @ref GWEN_Crypt_Token_KeyInfo_GetCertificate().</p>

*/

/* define GWEN_CRYPT_TOKEN_KEYFLAGS */
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASSTATUS 0x00010000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASMODULUS 0x00020000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASEXPONENT 0x00040000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASACTIONFLAGS 0x00080000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASKEYVERSION 0x00100000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASSIGNCOUNTER 0x00200000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASKEYNUMBER 0x00400000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_HASCERTIFICATE 0x00800000
#define GWEN_CRYPT_TOKEN_KEYFLAGS_ACTIONMASK 0x0000000f
#define GWEN_CRYPT_TOKEN_KEYFLAGS_CANSIGN 0x00000001
#define GWEN_CRYPT_TOKEN_KEYFLAGS_CANVERIFY 0x00000002
#define GWEN_CRYPT_TOKEN_KEYFLAGS_CANENCIPHER 0x00000004
#define GWEN_CRYPT_TOKEN_KEYFLAGS_CANDECIPHER 0x00000008


/* needed system headers */
#include <gwenhywfar/types.h>
#include <gwenhywfar/list1.h>
#include <gwenhywfar/list2.h>
#include <gwenhywfar/inherit.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/xml.h>

/* pre-headers */
#include <gwenhywfar/types.h>
#include <gwenhywfar/buffer.h>
#include <gwenhywfar/text.h>

typedef struct GWEN_CRYPT_TOKEN_KEYINFO GWEN_CRYPT_TOKEN_KEYINFO;
GWEN_LIST_FUNCTION_LIB_DEFS(GWEN_CRYPT_TOKEN_KEYINFO, GWEN_Crypt_Token_KeyInfo, GWENHYWFAR_API)
GWEN_LIST2_FUNCTION_LIB_DEFS(GWEN_CRYPT_TOKEN_KEYINFO, GWEN_Crypt_Token_KeyInfo, GWENHYWFAR_API)
GWEN_INHERIT_FUNCTION_LIB_DEFS(GWEN_CRYPT_TOKEN_KEYINFO, GWENHYWFAR_API)



typedef enum {
  GWEN_Crypt_Token_KeyStatusUnknown = -1,
  GWEN_Crypt_Token_KeyStatusFree,
  GWEN_Crypt_Token_KeyStatusNew,
  GWEN_Crypt_Token_KeyStatusActive
} GWEN_CRYPT_TOKEN_KEYSTATUS;


/* post-headers */
#include <gwenhywfar/cryptalgo.h>


GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYSTATUS GWEN_Crypt_Token_KeyStatus_fromString(const char *p_s);

GWENHYWFAR_API const char *GWEN_Crypt_Token_KeyStatus_toString(GWEN_CRYPT_TOKEN_KEYSTATUS p_i);

/** Destructor. */
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_free(GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_Attach(GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_dup(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_copy(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, const GWEN_CRYPT_TOKEN_KEYINFO *p_src);

/** Getter.
 * Use this function to get the member "id" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_id)
*/
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetId(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "keyDescr" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keyDescr)
*/
GWENHYWFAR_API const char *GWEN_Crypt_Token_KeyInfo_GetKeyDescr(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "flags" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_flags)
*/
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetFlags(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "keySize" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keySize)
*/
GWENHYWFAR_API int GWEN_Crypt_Token_KeyInfo_GetKeySize(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "cryptAlgoId" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_cryptAlgoId)
*/
GWENHYWFAR_API int GWEN_Crypt_Token_KeyInfo_GetCryptAlgoId(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "keyNumber" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keyNumber)
*/
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetKeyNumber(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "keyVersion" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keyVersion)
*/
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetKeyVersion(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Getter.
 * Use this function to get the member "signCounter" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_signCounter)
*/
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetSignCounter(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct);

/** Setter.
 * Use this function to set the member "id" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_id)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetId(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/** Setter.
 * Use this function to set the member "keyDescr" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keyDescr)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetKeyDescr(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, const char *p_src);

/** Setter.
 * Use this function to set the member "flags" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_flags)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetFlags(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/** Add flags.
 * Use this function to add flags to the member "flags"
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_AddFlags(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/** Sub flags.
 * Use this function to sub flags from the member "flags"
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SubFlags(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/** Setter.
 * Use this function to set the member "keySize" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keySize)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetKeySize(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, int p_src);

/** Setter.
 * Use this function to set the member "cryptAlgoId" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_cryptAlgoId)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetCryptAlgoId(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, int p_src);

/** Setter.
 * Use this function to set the member "keyNumber" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keyNumber)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetKeyNumber(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/** Setter.
 * Use this function to set the member "keyVersion" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_keyVersion)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetKeyVersion(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/** Setter.
 * Use this function to set the member "signCounter" (see @ref GWEN_CRYPT_TOKEN_KEYINFO_signCounter)
*/
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetSignCounter(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, uint32_t p_src);

/* list1 functions */
GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO_LIST *GWEN_Crypt_Token_KeyInfo_List_dup(const GWEN_CRYPT_TOKEN_KEYINFO_LIST *p_src);

GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_ReadDb(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_DB_NODE *p_db);

GWENHYWFAR_API int GWEN_Crypt_Token_KeyInfo_WriteDb(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_DB_NODE *p_db);

GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_fromDb(GWEN_DB_NODE *p_db);

GWENHYWFAR_API int GWEN_Crypt_Token_KeyInfo_toDb(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_DB_NODE *p_db);

GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_ReadXml(GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_XMLNODE *p_db);

GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_WriteXml(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_XMLNODE *p_db);

GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_toXml(const GWEN_CRYPT_TOKEN_KEYINFO *p_struct, GWEN_XMLNODE *p_db);

GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_fromXml(GWEN_XMLNODE *p_db);

GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_List_GetById(const GWEN_CRYPT_TOKEN_KEYINFO_LIST *p_list, uint32_t p_cmp);

GWENHYWFAR_API GWEN_CRYPT_TOKEN_KEYINFO *GWEN_Crypt_Token_KeyInfo_new(uint32_t kid,
    GWEN_CRYPT_CRYPTALGOID a,
    int keySize);
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetModulus(GWEN_CRYPT_TOKEN_KEYINFO *st, const uint8_t *p, uint32_t len);
GWENHYWFAR_API const uint8_t* GWEN_Crypt_Token_KeyInfo_GetModulusData(const GWEN_CRYPT_TOKEN_KEYINFO *st);
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetModulusLen(const GWEN_CRYPT_TOKEN_KEYINFO *st);
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetExponent(GWEN_CRYPT_TOKEN_KEYINFO *st, const uint8_t *p, uint32_t len);
GWENHYWFAR_API const uint8_t* GWEN_Crypt_Token_KeyInfo_GetExponentData(const GWEN_CRYPT_TOKEN_KEYINFO *st);
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetExponentLen(const GWEN_CRYPT_TOKEN_KEYINFO *st);
GWENHYWFAR_API void GWEN_Crypt_Token_KeyInfo_SetCertificate(GWEN_CRYPT_TOKEN_KEYINFO *st, const uint8_t *p, uint32_t len);
GWENHYWFAR_API const uint8_t* GWEN_Crypt_Token_KeyInfo_GetCertificateData(const GWEN_CRYPT_TOKEN_KEYINFO *st);
GWENHYWFAR_API uint32_t GWEN_Crypt_Token_KeyInfo_GetCertificateLen(const GWEN_CRYPT_TOKEN_KEYINFO *st);
/* end-headers */


#ifdef __cplusplus
}
#endif

#endif

