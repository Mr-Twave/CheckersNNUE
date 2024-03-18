void trainNetwork(TrainableNNUE& nnue, std::vector<TrainingSample>& dataset, int epochs, float learningRate) {
    for(int epoch = 0; epoch < epochs; ++epoch) {
        float totalLoss = 0.0;
        for(const auto& sample : dataset) {
            Eigen::VectorXf input = Eigen::Map<const Eigen::VectorXf>(sample.features.data(), sample.features.size());
            auto [hidden, output] = nnue.forward(input);

            totalLoss += std::pow(output - sample.evaluation, 2);
            nnue.updateWeights(input, hidden, output, sample.evaluation, learningRate);
        }
        std::cout << "Epoch " << epoch + 1 << ", Loss: " << totalLoss / dataset.size() << std::endl;
    }
}
