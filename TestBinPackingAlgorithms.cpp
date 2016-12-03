#include <iostream>
#include <vector>
#include <ctime>
#include <ios>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<double> bin;
const double total_amount_of_space = 1.0;
/*
*	Algorithm for Next Fit Bin Packing.
*	@param &random_numbers is a vector containing random variables.
* @return the number of bins needed.
*/
int NextFitBinPacking(const bin &random_numbers){
	bin next_fit(1, 0.0);
	int bins = 0;
	for(size_t i = 0; i < random_numbers.size(); i++){
		double sum = random_numbers[i] + next_fit[bins];
		if(sum <= total_amount_of_space){
			next_fit[bins] = sum;
		}
		else{ //create a new bin if the sum is larger than 1.0
			next_fit.push_back(random_numbers[i]);
			bins++;
		}	
	}
	return next_fit.size(); 
}

/*
*	Algorithm for First Fit Bin Packing.
*	@param &random_numbers is a vector containing random variables.
* @return the number of bins needed.
*/
int FirstFitBinPacking(const bin &random_numbers){
	priority_queue<double> first_fit;
	vector<double> store_elements;
	for(size_t i = 0; i < random_numbers.size(); i++){
		while(!first_fit.empty()){
			double sum = random_numbers[i] + first_fit.top();
			if(sum <= total_amount_of_space){
				first_fit.pop();
				first_fit.push(sum);
				i++;
				for(size_t j = 0; j < store_elements.size(); j++){
					first_fit.push(store_elements[j]);
					store_elements.erase(store_elements.begin() + j);
				}
			}
			else{ //traverse first_fit till random_number[i] is placed
				store_elements.push_back(first_fit.top());
				first_fit.pop();
			}
		}
		//if first_fit is empty, add new bin
		first_fit.push(random_numbers[i]);
		i++;
		for(size_t j = 0; j < store_elements.size(); j++){
			first_fit.push(store_elements[j]);
			store_elements.erase(store_elements.begin() + j);
		}
	}
	return first_fit.size();
	/*
	//naive approach
	vector<double> first_fit;
	first_fit.clear();
	for(size_t i = 0; i < random_numbers.size(); i++){
		for(size_t j = 0; j < first_fit.size(); j++){
			double sum = random_numbers[i] + first_fit[j];
			if(sum <= total_amount_of_space){
				first_fit[j] = sum;
				i++;
			}
			else{ //traverse first_fit till random_number[i] is placed
				j++;
			}
		}
		//if end of first_fit is reached, add new bin
		first_fit.push_back(random_numbers[i]);
		i++;
	}
	return first_fit.size();
	*/
}

int main(int argc, char **argv) {
  if(argc != 2){
    cout << "Usage: " << argv[0] << " <Number of items>" << endl;
    return 0;
  }
  const size_t number_of_items = atoi(argv[1]);
  cout << "Input number of items is " << number_of_items << endl;

  if(number_of_items == 50 || number_of_items == 100 || number_of_items == 500){
  	bin random_numbers;
		srand(time(0)); //use current time as seed for random generator
		for(size_t i = 0; i < number_of_items; i++) {
			const double random_variable = (double)rand()/(double)RAND_MAX;
			cout.setf(ios_base::fixed, ios_base::floatfield);
			cout.precision(1); //set to one decimal place
			// Push it into the vector of random numbers.
			random_numbers.push_back(random_variable);
		}

		const int number_of_bins_next_fit = NextFitBinPacking(random_numbers);
		const int number_of_bins_first_fit = FirstFitBinPacking(random_numbers);
		//Sort the random_numbers from largest to smallest
		std::sort(random_numbers.begin(), random_numbers.end(), std::greater<double>());
		const int number_of_bins_first_fit_decreasing = FirstFitBinPacking(random_numbers);
		
		cout << "Number of bins:" << endl;
		cout << "Next Fit: " << number_of_bins_next_fit << endl;
		cout << "First Fit: " << number_of_bins_first_fit << endl;
		cout << "First Fit Decreasing: " << number_of_bins_first_fit_decreasing << endl;
  }
  else{
    cout << "Unknown number of items (User should input 50, 100 or 500)" << endl;
  }
  return 0;
}
