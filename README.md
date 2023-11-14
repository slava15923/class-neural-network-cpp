This is just a template for creating a layered neural network
usage:
w - weights
ra - you can put a number there. usage example: l1.ra = 1;
l1.corW(1,l1.ra);
l1.ra++;
NumNeiron - number of neurons
NumNextLayerNeiron - number of neurons in the next layer
learning_rate - learning rate
input - the input data MUST BE AN ARRAY, the get() and get1layer() FUNCTIONS also return arrays in response
getfirstweight() - create random weights
get() - calculation of neurons if there are 2 or more of them per input
get1layer() - calculation of neurons if there are 1 of them
corW(1, 0) - adjustment of weights 1 argument is responsible for increasing and decreasing 1 = decrease the weight of the neuron, -1 = increase the weight of the neuron. 2nd argument is the number of the neuron that is being corrected
PrintW() - output to the console of weights
by slava15923
