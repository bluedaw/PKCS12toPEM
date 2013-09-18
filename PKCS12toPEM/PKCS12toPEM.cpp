// PKCS12toPEM.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PKCS12toPEM.h"
#
#define errBufSize 8192


 extern "C"  __declspec(dllexport) int _cdecl PFXtoPEM(char* PFXinfile, char* password, char* PEMoutfile)
{
	FILE *fp;
	EVP_PKEY *pkey;
	X509 *cert;
	STACK_OF(X509) *ca = NULL;
	PKCS12 *p12;
	int i;

	ERR_load_crypto_strings();
	char * errBuf = new char[errBufSize];
	memset(errBuf, '\0', sizeof(char)*errBufSize);
	freopen("NUL","a", stderr);
	setvbuf(stderr, errBuf, _IOFBF, errBufSize);

	OpenSSL_add_all_algorithms();

	if (!(fp = fopen(PFXinfile, "rb"))) {
		MessageBoxA(GetDesktopWindow(), std::string("Error opening file: ").append(PFXinfile).c_str(), "Error converting PFX to PEM", MB_ICONEXCLAMATION);
		return 1;
	}
	p12 = d2i_PKCS12_fp(fp, NULL);
	fclose (fp);
	if (!p12) {
		ERR_print_errors_fp(stderr);
		MessageBoxA(GetDesktopWindow(),std::string("Error reading PKCS#12 file: \n").append(errBuf).c_str(), "Error converting PFX to PEM", MB_ICONEXCLAMATION);
		return 1;
	}
	if (!PKCS12_parse(p12, password, &pkey, &cert, &ca)) {
		ERR_print_errors_fp(stderr);
		MessageBoxA(GetDesktopWindow(),std::string("Error parsing PKCS#12 file, check pfx password: \n").append(errBuf).c_str(), "Error converting PFX to PEM", MB_ICONEXCLAMATION);
		return 1;
	}
	PKCS12_free(p12);
	if (!(fp = fopen(PEMoutfile, "w"))) {
		MessageBoxA(GetDesktopWindow(),std::string("Error opening file: ").append(PEMoutfile).c_str(), "Error converting PFX to PEM", MB_ICONEXCLAMATION);
		return 1;
	}
	if (pkey) {
		fprintf(fp, "***Private Key***\n");
		PEM_write_PrivateKey(fp, pkey, NULL, NULL, 0, NULL, NULL);
	}

	if (cert) {
		fprintf(fp, "***User Certificate***\n");
		fprintf(fp,"subject=");
		fprintf(fp,X509_NAME_oneline(cert->cert_info->subject,0,0));
		fprintf(fp,"\nissuer=");
		fprintf(fp,X509_NAME_oneline(cert->cert_info->issuer,0,0));
		fprintf(fp,"\n");
		PEM_write_X509_AUX(fp, cert);
	}
	if (ca && sk_X509_num(ca)) {
		fprintf(fp, "***Other Certificates***\n");
		for (i = 0; i < sk_X509_num(ca); i++) 
		{
			fprintf(fp,"subject=");
		    fprintf(fp,X509_NAME_oneline(sk_X509_value(ca, i)->cert_info->subject,0,0));
		    fprintf(fp,"\nissuer=");
		    fprintf(fp,X509_NAME_oneline(sk_X509_value(ca, i)->cert_info->issuer,0,0));
		    fprintf(fp,"\n");
			PEM_write_X509_AUX(fp, sk_X509_value(ca, i));
		}
	}
	fclose(fp);

	return 0;
}

