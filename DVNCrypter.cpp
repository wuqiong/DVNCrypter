#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include "DVNCrypto.h"

#define TXT     "\n12345678901234567890\n"


using namespace std;
using namespace Diveinedu;
bool generatekey = false;
bool encode = false;
bool decode = false;

string plaintext;
string ciphertext;
string publickey ;
string privatekey;
string key;

string  key_prefix="test", cipher = "";
void PrintUsage(void);
bool parseParam(int argc , char * argv[]);


int main(int argc, char* argv[])
{
    if(!parseParam(argc,argv))
        return -1;
    DVNCrypto crypter;
    if(generatekey)
    {
        privatekey = key_prefix+"_private.key";
        publickey  = key_prefix+"_public.key";
        plaintext = TXT;
        if(crypter.generate_key(publickey,privatekey, cipher))
        {
            return -1;
        }
#if 0
        string encryptedHex, plain;
#if 1

        std::cerr << "************测  试 开   始*************" << std::endl;
        encryptedHex = crypter.encrypt(plaintext,publickey);
        std::cerr <<std::endl
                  << "用公钥加密前明文：" <<plaintext << std::endl
                  << "用公钥加密后密文：" <<encryptedHex << std::endl;
        plain = crypter.decrypt(encryptedHex, privatekey, cipher);
        std::cerr << "用私钥解密后明文: " <<plain <<std::endl;
        std::cerr <<std::endl
                  << "************测  试 结   束*************" << std::endl;
#else

        std::cerr << "************测  试 开   始*************" << std::endl;
        crypter.setPublicKey(publickey);
        encryptedHex = crypter.encrypt(plaintext);
        std::cerr <<std::endl
                  << "用公钥加密前明文：" <<plaintext << std::endl
                  << "用公钥加密后密文：" <<encryptedHex << std::endl;
        crypter.setPrivateKey(privatekey, cipher);
        size_t hexlen = encryptedHex.length();
        plain = crypter.decrypt(encryptedHex);
        std::cerr << "用私钥解密后明文: " <<plain <<std::endl;
        std::cerr <<std::endl
                  << "************测  试 结   束*************" << std::endl;
#endif
	return 0;
#endif
    }else
    if(encode && !plaintext.empty() && !key.empty())
    {
        std::cerr << "PlainText before encrypt:" << std::endl <<plaintext << std::endl;
        string encryptedHex;
        encryptedHex = crypter.encrypt(plaintext,key);
        std::cerr << "CipherText  after  encrypt:" << std::endl <<encryptedHex <<std::endl;
	return 0;
    }else
    if(decode && !ciphertext.empty() && !key.empty())
    {
        std::cerr << "CipherText before decrypt:" << std::endl << ciphertext << std::endl;
        string plain = crypter.decrypt(ciphertext, key, cipher);
        std::cerr << "PlainText  after  decrypt:" << std::endl << plain <<std::endl;
    	return 0;
	
    }else
    {

        std::cerr << " Invalid arguments!" <<std::endl;
	PrintUsage();
    	return -1;
    }

}



bool parseParam(int argc , char * argv[])
{
    if(argc<=1)
    {
        PrintUsage();
        exit(-1);
    }
    try
    {
        int opt;
        //解析运行参数
        while((opt=getopt(argc,argv,"g:c:e:d:k:h"))!=EOF)
        {
            switch(opt)
            {
            case 'g':
                generatekey = true;
                key_prefix = string(optarg);
                break;
            case 'c':
                cipher = string(optarg);
                break;
            case 'e':
                encode = true;
                plaintext = string(optarg);
                break;
            case 'd':
                decode = true;
                ciphertext = string(optarg);
                break;
            case 'k':
                key = string(optarg);
                break;
            case 'h':
                PrintUsage();
                return false;
            default:
                PrintUsage();
                return false;
                //break;
            }
        }
	
    	return true;
    }
    catch(...)
    {
        cout << "[DVNCrypter]Input Paramters Error!" << endl;
        PrintUsage();
        return false;
    }
}


//打印命令帮助
void PrintUsage(void)
{
#if 0
    static const char * usage =
        " Usage:\n"
        "   DVNCrypter -g [key-prefix]  -c [cipher] \n"
        "       //generate  publickey([key-prefix]_public.key) and privateky([key-prefix]_private.key)) with cipher \n"
        "   DVNCrypter -k [public-key]  -e [plain-text] \n"
        "       //encrypt plaintext with public-key. it must be a publickkey\n"
        "   DVNCrypter -k [private-key] -d [encrypted-text] -c [cipher]\n"
        "       //decrypt encrypted-text with private-key, user cipher to encrypt privatekey.\n"
        "   DVNCrypter -h [Usage help]\n";
#else
    static const char * usage =
        " Usage:\n"
        "   DVNCrypter -g [key-prefix]  \n"
        "       //generate  publickey([key-prefix]_public.key) and privateky([key-prefix]_private.key)) \n"
        "   DVNCrypter -k [public-key]  -e [plain-text] \n"
        "       //encrypt plaintext with public-key. It must be a publickkey\n"
        "   DVNCrypter -k [private-key] -d [encrypted-text] \n"
        "       //decrypt encrypted-text with private-key.\n"
        "   DVNCrypter -h [Usage help]\n";
#endif
    cout << usage << endl;
}
