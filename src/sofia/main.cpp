import <locale>;
import <print>;
import <vector>;

import sofia.all;

using namespace std;
using namespace sofia;

int main() {
    locale::global(locale("en_US.UTF-8"));

    const auto source = "Hello, dear World!";
    string_pool string_pool;
    vector<source_message> messages;
    tokenizer tokenizer(source, &string_pool, &messages);
    const auto tokens = tokenizer.read_all(true);

    if (tokens.empty())
        println("No tokens");
    else {
        println("Tokens:");

        for (const auto &token : tokens)
            println(" - {}", token);
    }

    println("");

    if (messages.empty())
        println("No messages");
    else {
        println("Messages:");

        for (const auto &message : messages)
            println(" - {}", message);
    }

    println("");

    if (string_pool.empty())
        println("No strings");
    else {
        println("Strings:");

        for (const auto &string : string_pool)
            println(" - {}", string);
    }
}