#include "Crypt.h"


int InitCrypt(){
    AutoSeededRandomPool rng;

    RSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, 2048);
    RSA::PublicKey publicKey(privateKey);

    SaveHexPrivateKey(ServerPriKey, privateKey);
	SaveHexPublicKey(ServerPubKey, publicKey);
    //cout<<"Public key: "<<ServerPubKey<<endl;	
    return 0;
}

int PrepareString(string &str, string Pub_key)
{
    if(str == "exit"){
        return 0;
    }
    //cout<<ServerPubKey<<endl;
    CryptString(str, Pub_key);
    str += "#" + ServerPubKey;
    return 0;
}

int ExtractKey(string &str, string &Pub_key)
{
    //cout<<"Extracting key..."<<endl;
    for(int i=0; i<str.size(); i++){
        if(str[i] == '#'){
            Pub_key = str.substr(i+1);
            str = str.substr(0, i);
            //cout<<"Data: "<<str<<endl;
            //cout<<"Key: "<<Pub_key<<endl;
        }
    }  
    return 0; 
}


int CryptString(string &str, string Pub_key){
    string cipher, encoded;
    AutoSeededRandomPool rng;

    RSA::PublicKey publicKey;
    LoadPublicKey(Pub_key, publicKey);

    RSAES_OAEP_SHA_Encryptor e( publicKey );

    StringSource( str, true,
        new PK_EncryptorFilter( rng, e,
            new StringSink( cipher )
        ) // PK_EncryptorFilter
    ); // StringSource

    encoded.clear();
    StringSource(cipher, true,
        new HexEncoder(
            new StringSink(encoded)
        ) // HexEncoder
    ); // StringSource
    
    str = encoded;
    return 0;
}

int DecryptString(string &str, string Priv_key){
    AutoSeededRandomPool rng;
    string cipher, recovered;

    RSA::PrivateKey PR_K;
    LoadPrivateKey(Priv_key, PR_K);
   
    StringSource ss(str, true,
        new HexDecoder(
            new StringSink(cipher)
        ) // HexDecoder
    ); // StringSource
    
    RSAES_OAEP_SHA_Decryptor d( PR_K );

    StringSource( cipher, true,
        new PK_DecryptorFilter( rng, d,
            new StringSink( recovered )
        ) // PK_EncryptorFilter
    ); // StringSource

    str = recovered;
    return 0;
}

void LoadPublicKey(string& str, PublicKey& key)
{
	ByteQueue queue;

	Load(str, queue);
	key.Load(queue);	
}

void LoadPrivateKey(string& str, PrivateKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;

	Load(str, queue);
	key.Load(queue);
}

void Load(string& str, BufferedTransformation& bt)
{
	StringSource ss(str, true /*pumpAll*/);

    HexDecoder decoder;
	ss.CopyTo(decoder);
    decoder.MessageEnd();

    decoder.CopyTo(bt);
	bt.MessageEnd();

}

void SaveHex(string& str, const BufferedTransformation& bt)
{
    HexEncoder encoder;
    bt.CopyTo(encoder);
    encoder.MessageEnd();

    word64 size = encoder.MaxRetrievable();
    if(size)
    {
        //cout<<"Size setted"<<endl;
        str.resize(size);		
        encoder.Get((byte*)&str[0], str.size());
    }

    //cout<<"Key: "<<str<<endl;
}

void SaveHexPrivateKey(string& str, const PrivateKey& key)
{
    ByteQueue queue;
    key.Save(queue);

    SaveHex(str, queue);
}

void SaveHexPublicKey(string& str, const PublicKey& key)
{
    ByteQueue queue;
    key.Save(queue);

    SaveHex(str, queue);
}
