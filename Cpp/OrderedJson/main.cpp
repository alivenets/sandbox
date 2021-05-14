#include <iostream>

#include <nlohmann/json.hpp>

#include <openssl/sha.h>

static constexpr const char *const JSON_STRING = R"JSON({"foo":1,"bar":{"c":"d"},"zorro":"yes","baz":["1",2,3]})JSON";

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

void calc_sha256_string(const std::string &s, char outputBuffer[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, s.c_str(), s.length());
    SHA256_Final(hash, &sha256);

    for(size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[64] = 0;
}

int main(void)
{
    std::string s;
    char sha256_buf[65];

    // Use standard json. The field order in the JSON dump is not guaranteed
    json j = json::parse(JSON_STRING);
    s = j.dump();
    calc_sha256_string(s, sha256_buf);
    std::cout << "SHA256: " << sha256_buf << std::endl;
    std::cout << "Strings are " << (s == JSON_STRING ? "equal" : "NOT equal") << std::endl;

    ordered_json oj= ordered_json::parse(JSON_STRING);
    s = oj.dump();
    calc_sha256_string(s, sha256_buf);
    std::cout << "SHA256: " << sha256_buf << std::endl;
    std::cout << "Strings are " << (s == JSON_STRING ? "equal" : "NOT equal") << std::endl;
}