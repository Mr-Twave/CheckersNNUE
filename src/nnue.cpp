#include <Eigen/Dense>

class SimpleNNUE {
public:
    Eigen::MatrixXf weights1; // Input to hidden layer weights
    Eigen::VectorXf biases1;  // Hidden layer biases
    Eigen::MatrixXf weights2; // Hidden to output layer weights
    Eigen::VectorXf biases2;  // Output layer biases

    SimpleNNUE(int inputSize, int hiddenSize) {
        weights1 = Eigen::MatrixXf::Random(hiddenSize, inputSize);
        biases1 = Eigen::VectorXf::Random(hiddenSize);
        weights2 = Eigen::MatrixXf::Random(1, hiddenSize);
        biases2 = Eigen::VectorXf::Random(1);
    }

    float evaluate(const std::vector<float>& features) {
        Eigen::VectorXf input = Eigen::Map<const Eigen::VectorXf>(features.data(), features.size());

        // Feedforward to hidden layer
        Eigen::VectorXf hidden = (weights1 * input + biases1).array().max(0); // ReLU activation
        // Feedforward to output layer
        float output = (weights2.transpose() * hidden + biases2)(0,0);

        return output;
    }
};

#include <Eigen/Dense>
#include <vector>
#include <cmath> // For std::exp in softmax

class TrainableNNUE {
public:
    Eigen::MatrixXf weights1, weights2;
    Eigen::VectorXf biases1, biases2;

    TrainableNNUE(int inputSize, int hiddenSize)
        : weights1(Eigen::MatrixXf::Random(hiddenSize, inputSize)),
          biases1(Eigen::VectorXf::Zero(hiddenSize)),
          weights2(Eigen::MatrixXf::Random(1, hiddenSize)),
          biases2(Eigen::VectorXf::Zero(1)) {}

    // Forward pass, returning hidden layer activations and output
    std::tuple<Eigen::VectorXf, float> forward(const Eigen::VectorXf& input) {
        Eigen::VectorXf hidden = (weights1 * input + biases1).unaryExpr([](float x) { return std::max(0.0f, x); }); // ReLU
        float output = (weights2.transpose() * hidden + biases2)(0, 0);
        return {hidden, output};
    }

    // Backpropagation and weight update
    void updateWeights(const Eigen::VectorXf& input, const Eigen::VectorXf& hidden, float output, float target, float learningRate) {
        float error = output - target;

        // Output to hidden layer gradients
        Eigen::VectorXf dOutput = Eigen::VectorXf::Constant(1, error);
        Eigen::VectorXf gradients2 = dOutput * hidden.transpose();
        Eigen::VectorXf biasGradients2 = dOutput;

        // Backpropagate error to hidden layer
        Eigen::VectorXf dHidden = weights2.transpose() * dOutput;
        dHidden = dHidden.array() * (hidden.array() > 0).cast<float>(); // Derivative of ReLU

        // Hidden to input layer gradients
        Eigen::MatrixXf gradients1 = dHidden * input.transpose();
        Eigen::VectorXf biasGradients1 = dHidden;

        // Update weights and biases
        weights1 -= learningRate * gradients1;
        biases1 -= learningRate * biasGradients1;
        weights2 -= learningRate * gradients2.transpose();
        biases2 -= learningRate * biasGradients2;
    }
};

struct TrainingSample {
    std::vector<float> features; // Input features extracted from the game state
    float evaluation; // Target evaluation (e.g., from -1.0 to 1.0)
};

std::vector<TrainingSample> loadTrainingData() {
    std::vector<TrainingSample> dataset;
    // Load your dataset here
    return dataset;
}
