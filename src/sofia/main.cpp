import <print>;
import <vector>;

import sofia.all;

using namespace std;
using namespace sofia;

int main() {
    const auto source = "Hello, dear World!";
    string_pool string_pool;
    vector<source_message> messages;
    tokenizer tokenizer(source, &string_pool, &messages);
    const auto tokens = tokenizer.read_all(true);

    println("Tokens:");

    for (const auto &token : tokens) {
        println(" - {}", token);
    }
}