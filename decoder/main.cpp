#include <fstream>
#include <cstdint>
#include <iostream>
#include <ctime>

int main()
{
        std::ifstream inFile(BASE_PATH "/Encoded.nnv", std::ios::binary);
        // File to be decoded has not yet be created, returning EXIT_SUCCESS allows to
        // run this application and Network in the same task without stopping.
        if (!inFile)
                return EXIT_SUCCESS;

        // Data sizes
        uint32_t infos[3] {};
        inFile.read((char *)&infos, 3 * sizeof(uint32_t));

        // Sizes array
        uint32_t *sizes { new uint32_t[infos[0]]() };
        inFile.read((char *)sizes, infos[0] * (std::streamsize)sizeof(uint32_t));

        // Weights array
        float *weights { new float[infos[1]]()};
        inFile.read((char *)weights, infos[1] * (std::streamsize)sizeof(float));

        // Biases array
        float *biases { new float[infos[2]]()};
        inFile.read((char *)biases, infos[2] * (std::streamsize)sizeof(float));

        inFile.close();
        std::ofstream outFile(BASE_PATH "/Values.h");
        if (!outFile)
                return EXIT_FAILURE;

        // File const prefix
        outFile << "#pragma once\n"
                   "\n"
                   "#include <array>\n"
                   "#include <cstdint>\n"
                   "\n"
                   "namespace Values {\n"
                   "\n";

        // Weights array declaration
        outFile << "        constexpr std::array<float, " << infos[1] << "U> weights {\n";

        for (uint32_t i { 0 }; i < infos[1] - 1; i++)
                outFile << "                " << weights[i] << ",\n";

        // Weights array end
        outFile << "                " << weights[infos[1] - 1] << "\n" << "        };\n\n";

        // Biases array declaration
        outFile << "        constexpr std::array<float, " << infos[2] << "U> biases {\n";

        for (uint32_t i { 0 }; i < infos[2] - 1; i++)
                outFile << "                " << biases[i] << ",\n";

        // Weights array end
        outFile << "                " << biases[infos[2] - 1] << "\n" << "        };\n\n";

        // File const suffix;
        outFile << "}";
        outFile.close();

        delete [] sizes;
        delete [] weights;
        delete [] biases;

        char buffer[80]{};
        time_t rawTime{};

        // Get time as formatted string
        time(&rawTime);
        tm tm{};
        localtime_s(&tm, &rawTime);
        std::strftime(buffer, sizeof(buffer), "%X", &tm);

        std::cout << buffer << " Decoded data.\n";
        return EXIT_SUCCESS;
}