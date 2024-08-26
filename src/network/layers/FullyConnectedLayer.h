#pragma once

#include <mutex>
#include <fstream>

#include "../ILayer.h"

class FullyConnectedLayer final : public ILayer {
public:
        FullyConnectedLayer(
                        uint32_t previousLayerSize,
                        uint32_t layerSize,
                        FunctionType functionType
                );

        FullyConnectedLayer(
                uint32_t previousLayerSize,
                uint32_t layerSize,
                FunctionType functionType,
                std::ifstream &encodedData
        );

        [[nodiscard]] Vector forward(
                const Vector &input
        ) const override;

        [[nodiscard]] Vector backward(
                // This layer cost
                const Vector &cost,
                // This layer input, also the previous layer
                // activation values
                const Vector &input
        ) override;

        void encode(
                std::ofstream &out
        ) const override;

        [[nodiscard]] inline uint32_t size() const override
        {
                return m_b.size();
        }

private:
        Matrix m_w;
        Vector m_b;
        const FunctionType m_functionType;
        std::mutex m_mutex;

}; // class Layer