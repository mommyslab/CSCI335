// Include your name here.
// Place comments describing the class Chain (two lines).

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <sstream>
#include <cstddef>

namespace teaching_project {
	// Place comments that provide a brief explanation of the class,
	// and its sample usage.
	template<typename Object>
	class Chain {
	public:
		// Default "big five" -- you have to alter them for your assignment.
		// That means that you will remove the "= default" statement.
		//  and you will provide an implementation.

		// Zero-parameter constructor.
		//Chain() = default;
		Chain() {
			size_ = 0;
			array_ = nullptr;
		};

		// Copy-constructor.
		//Chain(const Chain &rhs) = default;
		Chain(const Chain &rhs)
		{
			//  array_=new object *{rhs.array_};
			this->size_=rhs.size_;
			this->array_= new Object[size_];
			for(size_t i = 0; i < size_; i++)
			{
				array_[i] = rhs.array_[i];
			}
		}



		// Copy-assignment. If you have already written
		// the copy-constructor and the move-constructor
		// you can just use:
		// {
		// Chain copy = rhs; 
		// std::swap(*this, copy);
		// return *this;
		// }
		//Chain& operator=(const Chain &rhs) = default;
		Chain& operator=(const Chain &rhs){
			/*if(this!=&rhs)
				this->array_=rhs.array_;
			this->size_=rhs.size_;*/
			Chain copy = rhs; 
			std::swap(*this, copy);
			return *this;
		}

		// Move-constructor. 
		//Chain(Chain &&rhs) = default;
		Chain(Chain &&rhs)
		{
			this->size_ = rhs.size_;
			rhs.size_ = 0;
			this->array_ = rhs.array_;
			rhs.array_ = nullptr;
		}

		// Move-assignment.
		// Just use std::swap() for all variables.
		// Chain& operator=(Chain &&rhs) = default;
		Chain& operator=(Chain &&rhs)
		{
			// Swap implementation actually swaps left and right sides instead of moving
			// right into left and leaving right empty. Since output example have priority 
			// in determining correct implementation, commentary about swap is ignored
			//std::swap(this->size_,rhs.size_);
			//std::swap(this->array_,rhs.array_);
			this->size_ = rhs.size_;
			rhs.size_ = 0;
			this->array_ = rhs.array_;
			rhs.array_ = nullptr;
			return *this;
		}

		~Chain() {
			delete[] array_;
		}

		// End of big-five.

		// One parameter constructor.
		Chain(const Object& item) {
			array_ = new Object[1];
			array_[0] = item;
			size_ = 1;
		}

		// Read a chain from standard input.
		void ReadChain() {
			std::string str;
			std::getline(std::cin, str); // read entire string
			std::string prefix = str.substr(0,1); // get first symbol
			std::string postfix = str.substr(str.length() - 1,1); // get last symbol
			size_t size_token_end = str.find(':', 0); // find ':' delimiter position
			std::string size_token = str.substr(1,size_token_end - 1); // get substring from second symbol until delimiter
			std::string body = str.substr(size_token_end + 1, str.length() - size_token_end - 2); // get substring after delimeter and until last symbol
			std::stringstream body_stream(body); // wrap it in stream
			if (prefix != "[" || postfix != "]") // verify first and last symbol
				abort(); // we use abort as exception handler according to comment for [] operator		
			size_t temp_size = std::stoi(size_token); // convert size to integer			
			if (temp_size < 0) // check for it to be positive
				abort();
			if (temp_size == 0  && body.length() > 0) // check for case of zero size and non-zero number of objects in input
				abort();
			if (temp_size == 0) // if size is zero
			{
				// make chain empty
				delete[] this->array_;
				this->array_ = nullptr;
				this->size_ = 0;
				return;
			}
			// Prepare array. We would read into temporary array to avoid corrupting chain in case of invalid input
			Object* temp_array = new Object[temp_size]; 
			size_t i = 0;
			Object insert;
			while(body_stream >> insert) // read object from string stream
			{
				temp_array[i]=insert; // put it into array
				i++; // increment object counter
				if (i > temp_size) { // if there are more objects in input than declared in size
					delete[] temp_array;
					abort(); // abort
				}
			}
			if (i < temp_size) { // if there were less objects in input than declared in size
				delete[] temp_array;
				abort(); // abort
			}
			// Put temporary values into actual chain
			delete[] this->array_;
			this->array_ = temp_array;
			this->size_ = temp_size;
		}

		size_t size() const { // Write something
			return size_;
		}

		// @location: an index to a location in the chain.
		// @returns the Object at @location.
		// const version.
		// abort() if out-of-range.
		const Object& operator[](size_t location) const { 
			if (location >= this->size_)
				abort();
			return  array_[location];
		}

		// @location: an index to a location in the range.
		// @returns the Object at @location.
		// non-const version.
		// abort() if out-of-range.
		Object& operator[](size_t location) { 
			if (location >= this->size_)
				abort();
			return array_[location];
			// Write something (will be the same as above)
		}

		//  @c1: A chain.
		//  @c2: A second chain.
		//  @return the concatenation of the two chains.
		friend Chain operator+(const Chain &c1, const Chain &c2) {//learn why there is no return tpe for friend function
			Chain res;
			res.size_ = c1.size_ + c2.size_;
			res.array_ = new Object[res.size_]; 
			for (size_t i=0; i<c1.size();i++)
				res.array_ [i] = c1[i];
			for (size_t i=0; i<c2.size();i++)
				res.array_ [c1.size() + i] = c2[i];
			return res;

		}

		// Overloading the << operator.
		friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain) {
			// Print the chain.
			out << "[";
			for (size_t i = 0; i < a_chain.size(); i++)
			{        
				out << a_chain[i];
				if (i < a_chain.size() - 1)
					out <<" ";
			}
			out << "]";
			out << std::endl;			
			return out;
		}

	private:
		size_t size_;
		Object *array_;
	};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
