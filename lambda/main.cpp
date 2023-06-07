#include <iostream>
#include <memory>


class SummatorFactory {
public:

    explicit SummatorFactory(int addition) : addition_(addition) {
    }

    auto Generate() {
        std::cout << "Generating summator with addition: " << addition_ << std::endl;
        return [=](int value) {
            return value + addition_;
        };
    }

    static auto GetSummator(int addition) {
        auto factory = std::make_unique<SummatorFactory>(addition);
        return factory->Generate();
    }

private:
    int addition_;
};


int main() {

    auto summator = SummatorFactory::GetSummator(42);
    int result = summator(1);
    std::cout << result << std::endl;

    return EXIT_SUCCESS;
}
