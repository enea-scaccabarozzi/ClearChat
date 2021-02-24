#ifndef CRYPT_CLI_FLAG
#define CRYPT_CLI_FLAG

#include <cryptopp/rsa.h>
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;

#include <cryptopp/sha.h>
using CryptoPP::SHA1;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::PK_DecryptorFilter;

#include <cryptopp/osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include <cryptopp/queue.h>
using CryptoPP::ByteQueue;

#include <string>
using std::string;

#include <exception>
using std::exception;

#include <cryptopp/cryptlib.h>
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;
using CryptoPP::BufferedTransformation;
using CryptoPP::word64;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::fstream;
using std::ios;

extern string ClientPubKey;
extern string ClientPriKey;

int InitCrypt();

void SaveHex(string& str, const BufferedTransformation& bt);
void SaveHexPrivateKey(string& str, const PrivateKey& key);
void SaveHexPublicKey(string& str, const PublicKey& key);

void LoadPublicKey(string& str, PublicKey& key);
void LoadPrivateKey(string& str, PrivateKey& key);
void Load(string& str, BufferedTransformation& bt);

int PrepareString(string &str, string Pub_key);
int ExtractKey(string &str, string &Pub_key);

int CryptString(string &str, string Pub_key);
int DecryptString(string &str, string Priv_key);




#endif